// Author: vividfree (vividfree@qq.com)
//  Date : 2015-12-30

#include "machine_learning/src/train/ftrl_train.h"

#include <cfloat>
#include <cmath>
#include <cstring>

#include "base/cpp/thirdparty/boost_1.52.0/include/boost/algorithm/string.hpp"
#include "base/cpp/thirdparty/boost_1.52.0/include/boost/lexical_cast.hpp"
#include "base/cpp/thirdparty/glog-0.3.3/include/glog/logging.h"

#include "base/cpp/public/util/num_util.h"

#include "machine_learning/src/data_dict/array_param_value_dict.h"
#include "machine_learning/src/model/lr_model.h"
#include "machine_learning/src/util/def_const.h"
#include "machine_learning/src/util/map_helper-inl.h"

using namespace std;

namespace machine_learning {
namespace train {

FtrlTrain::FtrlTrain(const string& conf_file,
                     const supervised_model::SupervisedModel& model,
                     data_dict::ArrayParamValueDict* data_reader):
    SupervisedTrain(conf_file, model),
    whether_open_l1_(false),
    whether_open_l2_(false),
    iter_num_(0),
    mini_batch_size_(1),
    lambda1_(0),
    lambda2_(0),
    alpha_(1),
    beta_(1),
    loss_delta_threshold_(1e-5),
    z_statistic_array_(NULL),
    n_statistic_array_(NULL),
    data_reader_(data_reader) {
}

FtrlTrain::~FtrlTrain() {
}

bool FtrlTrain::Init() {
  if (initialized_) return true;

  // step 1: 读取配置文件
  ReadConfig();

  // step 2: 初始化统计量
  array_size_ = data_reader_->GetParamArraySize();
  CHECK(array_size_ > 0) << "data_reader_ array_size_ [" << array_size_
                         << "] should > 0";

  z_statistic_array_ = new float[array_size_];
  CHECK(z_statistic_array_) << "z_statistic_array_ is null";
  for (int index = 0; index < array_size_; ++index) {
    z_statistic_array_[index] = 0;
  }  // end for

  n_statistic_array_ = new float[array_size_];
  CHECK(n_statistic_array_) << "n_statistic_array_ is null";
  for (int index = 0; index < array_size_; ++index) {
    n_statistic_array_[index] = 0;
  }  // end for

  // step 3: 初始化模型参数
  for (int index = 0; index < array_size_; ++index) {
    data_reader_->SetValueForSingleParam(index, 0);
  }  // end for

  initialized_ = true;
  LOG(INFO) << "FtrlTrain::Init() success";

  PrintMemberVal();

  return true;
}

bool FtrlTrain::Destroy() {
  if (!initialized_) return true;

  if (n_statistic_array_) {
    delete[] n_statistic_array_;
    n_statistic_array_ = NULL;
  }

  if (z_statistic_array_) {
    delete[] z_statistic_array_;
    z_statistic_array_ = NULL;
  }

  initialized_ = false;
  LOG(INFO) << "FtrlTrain::Destroy() success";

  return true;
}

bool Apply(const vector<SampleWithLabel>& samples) {
  if (!initialized_) {
    LOG(ERROR) << "FtrlTrain::Apply() use FtrlTrain::Init() first";
    return false;
  }

  map<int, float> map_z_statistic_delta;
  map<int, float> map_n_statistic_delta;
  map<int, float> cur_map_z_statistic_delta;
  map<int, float> cur_map_n_statistic_delta;

  float last_overall_loss = FLT_MAX;

  for (int cur_iter = 0; cur_iter < iter_num_; ++cur_iter) {
    vector<SampleWithLabel>::const_iterator iter_sample = samples.begin();
    for (; iter_sample != samples.end(); ++iter_sample) {
      for (int count = 0;
           count < mini_batch_size_ && iter_sample != samples.end();
           ++count, ++iter_sample) {
        if (!ComputeStatisticDelta(*iter_sample,
                                   &cur_map_z_statistic_delta,
                                   &cur_map_n_statistic_delta)) {
          continue;
        }

        // 合并某样本算出的 z统计量 和 n统计量
        util::TwoMapAddition(cur_map_z_statistic_delta, &map_z_statistic_delta);
        util::TwoMapAddition(cur_map_n_statistic_delta, &map_n_statistic_delta);
      }  // end for

      if (samples.end() == iter_sample) {
        // Note: 为了代码健壮。先--后++，第2层for执行逻辑才正常
        --iter_sample;
      }

      UpdateParamWeight(map_z_statistic_delta, map_n_statistic_delta); 
    }  // end for

    // 判断是否需要提前跳出循环
    float cur_overall_loss = ComputeOverallLoss(samples);
    float loss_delta = last_overall_loss - cur_overall_loss;
    if (loss_delta < loss_delta_threshold_) {
      LOG(INFO) << "Iteration [" << cur_iter
                << "]: cur_overall_loss [" << cur_overall_loss
                << "], last_overall_loss [" << last_overall_loss
                << "], loss_delta [" << loss_delta
                << "] < loss_delta_threshold_" << loss_delta_threshold_ << "]";
      break;
    } else {
      LOG(INFO) << "Iteration [" << cur_iter
                << "]: cur_overall_loss [" << cur_overall_loss
                << "], last_overall_loss [" << last_overall_loss
                << "], loss_delta [" << loss_delta
                << "] >= loss_delta_threshold_" << loss_delta_threshold_ << "]";
    }
  }  // end for

  // Dump模型到输出文件中
  bool b_success = data_reader_->DumpModel(output_model_file_);
  if (!b_success) {
    LOG(ERROR) << "Failed to dump model to file:" << output_model_file_;
    return false;
  }

  return true;
}

void FtrlTrain::ReadConfig() {
  LOG(INFO) << "conf_file:" << conf_file_;

  qihoo::ad::ConfigReader conf_reader;
  bool b_success = conf_reader.init(conf_file_.c_str());
  CHECK(b_success) << "read FtrlTrain conf error, file: " << conf_file_;

  string str_section("ftrl");

  // whether_open_l1
  b_success =
      conf_reader.getParameter(str_section,
                               "whether_open_l1",
                               whether_open_l1_);
  CHECK(b_success) << "FtrlTrain conf error, "
                   << "whether_open_l1 error, "
                   << "file: " << conf_file_;

  // whether_open_l2
  b_success =
      conf_reader.getParameter(str_section,
                               "whether_open_l2",
                               whether_open_l2_);
  CHECK(b_success) << "FtrlTrain conf error, "
                   << "whether_open_l2 error, "
                   << "file: " << conf_file_;

  // iter_num
  b_success =
      conf_reader.getParameter(str_section,
                               "iter_num",
                               iter_num_);
  CHECK(b_success) << "FtrlTrain conf error, "
                   << "iter_num error, "
                   << "file: " << conf_file_;
  CHECK(iter_num_ > 0)
      << "FtrlTrain conf error, "
      << "iter_num [" << iter_num_ << "] should > 0, "
      << "file: " << conf_file_;

  // mini_batch_size
  b_success =
      conf_reader.getParameter(str_section,
                               "mini_batch_size",
                               mini_batch_size_);
  CHECK(b_success) << "FtrlTrain conf error, "
                   << "mini_batch_size error, "
                   << "file: " << conf_file_;
  CHECK(mini_batch_size_ > 0)
      << "FtrlTrain conf error, "
      << "mini_batch_size [" << mini_batch_size_ << "] should > 0, "
      << "file: " << conf_file_;

  // lambda1
  if (whether_open_l1_) {
    b_success =
        conf_reader.getParameter(str_section,
                                 "lambda1",
                                 lambda1_);
    CHECK(b_success) << "FtrlTrain conf error, "
                     << "lambda1 error, "
                     << "file: " << conf_file_;
    CHECK(lambda1_ >= 0)
        << "FtrlTrain conf error, "
        << "lambda1 [" << lambda1_ << "] should >= 0, "
        << "file: " << conf_file_;
  }

  // lambda2
  if (whether_open_l2_) {
    b_success =
        conf_reader.getParameter(str_section,
                                 "lambda2",
                                 lambda2_);
    CHECK(b_success) << "FtrlTrain conf error, "
                     << "lambda2 error, "
                     << "file: " << conf_file_;
    CHECK(lambda2_ >= 0)
        << "FtrlTrain conf error, "
        << "lambda2 [" << lambda2_ << "] should >= 0, "
        << "file: " << conf_file_;
  }

  // alpha
  b_success =
      conf_reader.getParameter(str_section,
                               "alpha",
                               alpha_);
  CHECK(b_success) << "FtrlTrain conf error, "
                   << "alpha error, "
                   << "file: " << conf_file_;
  CHECK(alpha_ > 0)
      << "FtrlTrain conf error, "
      << "alpha [" << alpha_ << "] should > 0, "
      << "file: " << conf_file_;

  // beta
  b_success =
      conf_reader.getParameter(str_section,
                               "beta",
                               beta_);
  CHECK(b_success) << "FtrlTrain conf error, "
                   << "beta error, "
                   << "file: " << conf_file_;
  CHECK(beta_ > 0)
      << "FtrlTrain conf error, "
      << "beta [" << beta_ << "] should > 0, "
      << "file: " << conf_file_;

  // loss_delta_threshold
  b_success =
      conf_reader.getParameter(str_section,
                               "loss_delta_threshold",
                               loss_delta_threshold_);
  CHECK(b_success) << "FtrlTrain conf error, "
                   << "loss_delta_threshold error, "
                   << "file: " << conf_file_;
  CHECK(loss_delta_threshold_ > 0)
      << "FtrlTrain conf error, "
      << "loss_delta_threshold [" << loss_delta_threshold_ << "] should > 0, "
      << "file: " << conf_file_;

  // output_model_file
  b_success =
      conf_reader.getParameter(str_section,
                               "output_model_file",
                               output_model_file_);
  CHECK(b_success) << "FtrlTrain conf error, "
                   << "output_model_file error, "
                   << "file: " << conf_file_;
  CHECK(0 != output_model_file_size())
      << "FtrlTrain conf error, "
      << "output_model_file [" << output_model_file_ << "] should not be empty, "
      << "file: " << conf_file_;
}

void FtrlTrain::PrintMemberVal() const {
  LOG(INFO) << "initialized_ : " << initialized_
            << "\nwhether_open_l1_ : " << whether_open_l1_
            << "\nwhether_open_l2_ : " << whether_open_l2_
            << "\niter_num_ : " << iter_num_
            << "\nmini_batch_size_: " << mini_batch_size_
            << "\nlambda1_ : " << lambda1_
            << "\nlambda2_ : " << lambda2_
            << "\nalpha_ : " << alpha_
            << "\nbeta_ : " << beta_
            << "\nloss_delta_threshold_: " << loss_delta_threshold_
            << "\noutput_model_file_: " << output_model_file_;
}

bool FtrlTrain::UpdateParamWeight(
    const map<int, float>& map_z_statistic_delta,
    const map<int, float>& map_n_statistic_delta) {
  map<int, float>::const_iterator iter_stat = map_z_statistic_delta.begin();
  for (; iter_stat != map_z_statistic_delta.end(); ++iter_stat) {
    int feat_index = iter_stat->first;
    if (map_n_statistic_delta.find(feat_index) == map_n_statistic_delta.end()) {
      LOG(ERROR) << "feat_index [" << feat_index << "] in map_z_statistic_delta, "
                 << "but not in map_n_statistic_delta. Continue";
      continue;
    }
    if (feat_index < 0 || feat_index >= array_size_) {
      LOG(ERROR) << "feat_index [" << feat_index << "] not in [0, "
                 << array_size_ << "). Continue";
      continue;
    }

    float to_add_z_statistic = iter_stat->second;
    float to_add_n_statistic = map_n_statistic_delta[feat_index];

    z_statistic_array_[feat_index] += to_add_z_statistic;
    float z_statistic = z_statistic_array_[feat_index];

    n_statistic_array_[feat_index] += to_add_n_statistic;
    float n_statistic = n_statistic_array_[feat_index];

    if (fabs(z_statistic) <= lambda1_) {
      data_reader_->SetValueForSingleParam(feat_index, 0);
      continue;
    }

    float learning_rate = 0;
    if (!ComputeLearningRate(n_statistic, &learning_rate)) continue;
    float tmp_val = -learning_rate *
                    (z_statistic - (lambda1_ * NumUtil::Sign(z_statistic)));
    data_reader_->SetValueForSingleParam(feat_index, tmp_val);
  }  // end for

  return true;
}

bool FtrlTrain::ComputeStatisticDelta(const SampleWithLabel& sample,
                                      map<int, float>* map_z_statistic_delta,
                                      map<int, float>* map_n_statistic_delta) {
  map_z_statistic_delta->clear();
  map_n_statistic_delta->clear();

  map<int, float> gradient;
  bool b_success = model_->GradientFunction(sample, &gradient);
  if (!b_success) return false;

  map<int, float>::const_iterator iter = gradient.begin();
  for (; iter != gradient.end(); ++iter) {
    int feat_index = iter->first;
    if (feat_index < 0 || feat_index >= array_size_) {
      LOG(ERROR) << "feat_index [" << feat_index << "] not in [0, "
                 << array_size_ << "). Continue";
      continue;
    }

    float gradient_of_this_feat = iter->second;
    float n_statistic = n_statistic_array_[feat_index];
    float sigma = 0.0;
    b_success = ComputeSigma(n_statistic, gradient_of_this_feat, &sigma);
    if (!b_success) continue;

    float weight_of_this_feat = 0.0;
    b_success = data_reader_->GetValueForSingleParam(feat_index,
                                                     &weight_of_this_feat);
    if (!b_success) continue;

    float z_statistic_delta =
      gradient_of_this_feat - sigma * weight_of_this_feat;
    float n_statistic_delta = gradient_of_this_feat * gradient_of_this_feat;

    (*map_z_statistic_delta)[feat_index] = z_statistic_delta;
    (*map_n_statistic_delta)[feat_index] = n_statistic_delta;
  }  // end for

  return true;
}

bool FtrlTrain::ComputeLearningRate(float n_statistic,
                                    float* learning_rate) const {
  *learning_rate = 0;
  if (fabs(alpha_) < kEpsilon) {
    LOG(ERROR) << "alpha_ [" << alpha_ << "] should > [" << kEpsilon << "]";
    return false;
  }

  float tmp = ((sqrt(n_statistic) + beta_) / alpha_) + lambda2_;
  if (fabs(tmp) < kEpsilon) {
    LOG(ERROR) << "tmp value [" << tmp << "] should > [" << kEpsilon << "]";
    return false;
  }

  *learning_rate = 1 / tmp;
  return true;
}

bool FtrlTrain::ComputeSigma(float n_statistic,
                             float gradient,
                             float* sigma) const {
  *sigma = 0.0;
  if (n_statistic < 0) {
    LOG(ERROR) << "n_statistic [" << n_statistic << "] should > 0";
    return false;
  }

  *sigma =
      (sqrt(n_statistic + gradient * gradient) - sqrt(n_statistic)) / alpha_;
  return true;
}

float FtrlTrain::ComputeOverallLoss(
    const std::vector<SampleWithLabel>& samples) const {
  float overall_loss = 0;
  bool b_success = false;
  vector<SampleWithLabel>::const_iterator iter = samples.begin();
  for (; iter != samples.end(); ++iter) {
    float cur_loss = 0;
    b_success = model_->LossFunction(*iter, &cur_loss);
    if (!b_success) continue;
    overall_loss += cur_loss;
  }  // end for

  return true;
}

}  // namespace train
}  // namespace machine_learning
