// Author: vividfree (vividfree@qq.com)
//  Date : 2015-12-30

#ifndef MACHINE_LEARNING_SRC_TRAIN_SUPERVISED_TRAIN_H_
#define MACHINE_LEARNING_SRC_TRAIN_SUPERVISED_TRAIN_H_

#include <string>
#include <vector>

namespace machine_learning {

namespace supervised_model {
class SupervisedModel;
}  // namespace supervised_model

namespace train {

class SupervisedTrain {
 public:
  SupervisedTrain(const std::string& conf_file,
                  const supervised_model::SupervisedModel& model):
      initialized_(false),
      conf_file_(conf_file),
      model_(&model) {}

  virtual ~SupervisedTrain() {}

  virtual bool Init() = 0;

  // 一次处理多个样本，来更新模型权重
  // NOTE: 对多线程处理数据有帮助
  virtual bool Apply(const std::vector<SampleWithLabel>& feat_score) = 0;

  virtual bool Destroy() = 0;

 protected:
  bool initialized_;
  std::string conf_file_;
  const supervised_model::SupervisedModel* model_;
};

}  // namespace train
}  // namespace machine_learning

#endif  // MACHINE_LEARNING_SRC_TRAIN_SUPERVISED_TRAIN_H_
