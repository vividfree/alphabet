// Author: vividfree (vividfree@qq.com)
//  Date : 2015-12-30

#ifndef MACHINE_LEARNING_SRC_MODEL_SUPERVISED_MODEL_H_
#define MACHINE_LEARNING_SRC_MODEL_SUPERVISED_MODEL_H_

#include <map>

namespace machine_learning {

namespace data_dict {
class ArrayParamValueDict;
}  // namespace data_dict

namespace util {
struct SampleWithLabel;
}  // namespace util

namespace supervised_model {

class SupervisedModel {
 public:
  explicit SupervisedModel(const data_dict::ArrayParamValueDict& data_reader):
      initialized_(false),
      data_reader_(&data_reader) {}

  virtual ~SupervisedModel() {}

  virtual bool Init() = 0;

  // 计算模型预测的分数
  // NOTE: 不会用到sample.weight_ 和 sample.label_id_
  virtual bool ModelFunction(const util::SampleWithLabel& sample,
                             float* model_score) const = 0;

  // 计算loss
  // NOTE: 会用到sample.weight_ 和 sample.label_id_
  virtual bool LossFunction(const util::SampleWithLabel& sample,
                            float* loss_score) const = 0;

  // 计算gradient
  // NOTE: 会用到sample.weight_ 和 sample.label_id_
  virtual bool GradientFunction(const util::SampleWithLabel& sample,
                                std::map<int, float>* gradient) const = 0;

  // 基于模型预测的分数，给出预测的label_id
  // NOTE: 不会用到sample.weight_ 和 sample.label_id_
  virtual bool Predict(const util::SampleWithLabel& sample,
                       int* max_score_label_id,
                       std::map<int, float>* label_score) const = 0;

  virtual bool Destroy() = 0;

 protected:
  bool initialized_;
  const data_dict::ArrayParamValueDict* data_reader_;
};

}  // namespace supervised_model
}  // namespace machine_learning

#endif  // MACHINE_LEARNING_SRC_MODEL_SUPERVISED_MODEL_H_
