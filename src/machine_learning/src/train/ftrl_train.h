// Author: vividfree (vividfree@qq.com)
//  Date : 2015-12-30

#ifndef MACHINE_LEARNING_SRC_TRAIN_FTRL_TRAIN_H_
#define MACHINE_LEARNING_SRC_TRAIN_FTRL_TRAIN_H_

#include <map>

#include "machine_learning/src/train/supervised_train.h"

namespace machine_learning {

namespace data_dict {
class ArrayParamValueDict;
}  // namespace data_dict

namespace train {

class FtrlTrain : public SupervisedTrain {
 public:
  FtrlTrain(const std::string& conf_file,
            const supervised_model::SupervisedModel& model,
            data_dict::ArrayParamValueDict* data_reader);

  virtual ~FtrlTrain();

  bool Init();

  // 一次处理多个样本，来更新模型权重
  // NOTE: 对多线程处理数据有帮助
  bool Apply(const std::vector<SampleWithLabel>& samples);

  bool Destroy();

 private:
  void ReadConfig();

  void PrintMemberVal() const;

  // 计算新的模型参数
  // Note: 如果取z统计量失败 或者 计算学习率失败，则返回false；
  //       否则返回true
  bool UpdateParamWeight(const std::map<int, float>& map_z_statistic_delta,
                         const std::map<int, float>& map_n_statistic_delta);

  // 计算某样本带来的统计量
  bool ComputeStatisticDelta(const SampleWithLabel& sample,
                             std::map<int, float>* map_z_statistic_delta,
                             std::map<int, float>* map_n_statistic_delta);

  // 计算学习率
  // Note: 如果出现除数小于kEpsilon，则返回false；否则返回true
  //       如果 alpha_, beta_, lambda2_这些参数是被Init()接口检测过的，
  //       则除数不会小于kEpsilon，且一定会返回true
  bool ComputeLearningRate(float n_statistic, float* learning_rate) const;

  // 计算 sigma
  bool ComputeSigma(float n_statistic, float gradient, float* sigma) const;

  // 计算全部样本上的损失
  float ComputeOverallLoss(const std::vector<SampleWithLabel>& samples) const;

  bool whether_open_l1_;  // 是否开启L1正则
  bool whether_open_l2_;  // 是否开启L2正则
  int iter_num_;  // 迭代训练停止条件之迭代轮数。需大于0
  int mini_batch_size_;  // mini-batch的size。需要大于0
  float lambda1_;  // L1正则化因子。需不小于0
  float lambda2_;  // L2正则化因子。需不小于0
  float alpha_;  // 与beta_一起用于调整学习率。需大于0
  float beta_;  // 与alpha_一起用于调整学习率。需大于0

  // 迭代训练停止条件之损失函数的减少值的阈值。
  // 当相邻两轮的损失函数值的减少量低于该值时则跳出循环。需大于0
  float loss_delta_threshold_;

  std::string output_model_file_;

  int array_size_;  // z统计量、n统计量 的数组长度

  float* z_statistic_array_;  // z统计量数组的指针
  float* n_statistic_array_;  // n统计量数组的指针

  data_dict::ArrayParamValueDict* data_reader_;
};

}  // namespace train
}  // namespace machine_learning

#endif  // MACHINE_LEARNING_SRC_TRAIN_FTRL_TRAIN_H_
