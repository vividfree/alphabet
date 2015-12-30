// Author: vividfree (vividfree@qq.com)
//  Date : 2015-12-30

#ifndef MACHINE_LEARNING_SRC_UTIL_DEF_STRUCT_H_
#define MACHINE_LEARNING_SRC_UTIL_DEF_STRUCT_H_

#include <map>

namespace machine_learning {
namespace util {

struct SampleWithLabel {
 public:
  int label_id_;  // 样本的label_id
  float weight_;  // 样本的权重
  std::map<int, float> feat_score_;  // 样本的特征向量
};

struct SampleWithoutLabel {
 public:
  float weight_;  // 样本的权重
  std::map<int, float> feat_score_;  // 样本的特征向量
};

}  // namespace util
}  // namespace machine_learning

#endif  // MACHINE_LEARNING_SRC_UTIL_DEF_STRUCT_H_
