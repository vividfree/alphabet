// Author: vividfree (vividfree@qq.com)
//  Date : 2015-12-30

#include "machine_learning/src/model/lr_model.h"

#include "base/cpp/thirdparty/boost_1.52.0/include/boost/algorithm/string.hpp"
#include "base/cpp/thirdparty/boost_1.52.0/include/boost/lexical_cast.hpp"
#include "base/cpp/thirdparty/glog-0.3.3/include/glog/logging.h"

#include "base/cpp/public/util/num_util.h"
#include "machine_learning/src/data_dict/array_param_value_dict.h"
#include "machine_learning/src/util/def_struct.h"

using namespace std;

namespace machine_learning {
namespace supervised_model {

const int LRModel::kPositiveLabelID = 1;
const int LRModel::kNegativeLabelID = 0;
const float LRModel::kPositiveThreshold = 0.5;

LRModel::LRModel(const data_dict::ArrayParamValueDict& data_reader):
    SupervisedModel(),
    data_reader_(&data_reader) {
}

LRModel::~LRModel() {
}

bool LRModel::Init() {
  if (initialized_) return true;

  initialized_ = true;
  LOG(INFO) << "LRModel::Init() success";
  return true;
}

bool LRModel::Destroy() {
  if (!initialized_) return true;

  initialized_ = false;
  LOG(INFO) << "LRModel::Destroy() success";

  return true;
}

bool LRModel::ModelFunction(const util::SampleWithLabel& sample,
                            float* model_score) const {
  *model_score = 0;
  if (!initialized_) {
    LOG(ERROR) << "LRModel::ModelFunction() use LRModel::Init() first";
    return false;
  }

  if (sample.feat_score_.empty()) return false;

  bool b_success = false;
  float feat_weight = 0;
  float sum_score = 0;
  map<int, float>::const_iterator iter = sample.feat_score_.begin();
  for (; iter != sample.feat_score_.end(); ++iter) {
    b_success = data_reader_->GetValueForSingleParam(iter->first, &feat_weight);
    if (!b_success) continue;
    sum_score += (iter->second * feat_weight);
  }  // end for

  b_success = base::util::NumUtil::Sigmoid(sum_score, model_score);
  return b_success;
}

bool LRModel::LossFunction(const util::SampleWithLabel& sample,
                           float* loss_score) const {
  *loss_score = 0;
  if (!initialized_) {
    LOG(ERROR) << "LRModel::LossFunction() use LRModel::Init() first";
    return false;
  }

  if (sample.feat_score_.empty()) return false;

  if (kPositiveLabelID != sample.label_id_ &&
      kNegativeLabelID != sample.label_id_) {
    LOG(ERROR) << "LRModel::LossFunction() sample.label_id_ ["
               << sample.label_id_
               << "] not " << kPositiveLabelID
               << " or " << kNegativeLabelID;
    return false;
  }

  bool b_success = false;
  float model_score;
  b_success = ModelFunction(sample, &model_score);
  if (!b_success) return false;
  if (model_score <= 0 || model_score >= 1) {
    LOG(ERROR) << "LRModel::LossFunction() model_score [" << model_score
               << "] should be in (0, 1)";
    return false;
  }

  if (kPositiveLabelID == sample.label_id_) {
    *loss_score = -log(model_score);
  } else {
    *loss_score = -log(1 - model_score);
  }
  *loss_score *= sample.weight_;

  return true;
}

bool LRModel::GradientFunction(const util::SampleWithLabel& sample,
                               std::map<int, float>* gradient) const {
  gradient->clear();
  if (!initialized_) {
    LOG(ERROR) << "LRModel::GradientFunction() use LRModel::Init() first";
    return false;
  }

  if (sample.feat_score_.empty()) return false;

  if (kPositiveLabelID != sample.label_id_ &&
      kNegativeLabelID != sample.label_id_) {
    LOG(ERROR) << "LRModel::GradientFunction() sample.label_id_ ["
               << sample.label_id_
               << "] not " << kPositiveLabelID
               << " or " << kNegativeLabelID;
    return false;
  }

  bool b_success = false;
  float model_score;
  b_success = ModelFunction(sample, &model_score);
  if (!b_success) return false;
  if (model_score <= 0 || model_score >= 1) {
    LOG(ERROR) << "LRModel::GradientFunction() model_score [" << model_score
               << "] should be in (0, 1)";
    return false;
  }

  float delta = model_score - sample.label_id_;
  delta *= sample.weight_;
  map<int, float>::const_iterator iter = sample.feat_score_.begin();
  for (; iter != sample.feat_score_.end(); ++iter) {
    gradient->insert(make_pair(iter->first, delta * iter->second));
  }  // end for

  return true;
}

bool LRModel::Predict(const util::SampleWithLabel& sample,
                      int* max_score_label_id,
                      map<int, float>* label_score) const {
  label_score->clear();
  if (!initialized_) {
    LOG(ERROR) << "LRModel::Predict() use LRModel::Init() first";
    return false;
  }

  if (sample.feat_score_.empty()) return false;

  bool b_success = false;
  float model_score = 0;
  b_success = ModelFunction(sample, &model_score);
  if (!b_success) return false;
  if (model_score <= 0 || model_score >= 1) {
    LOG(ERROR) << "LRModel::Predict() model_score [" << model_score
               << "] should be in (0, 1)";
    return false;
  }

  (*label_score)[1] = model_score;
  (*label_score)[0] = 1 - model_score;
  if (model_score >= kPositiveThreshold) {
    *max_score_label_id = 1;
  } else {
    *max_score_label_id = 0;
  }

  return true;
}

}  // namespace supervised_model
}  // namespace machine_learning
