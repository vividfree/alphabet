// Author: vividfree (vividfree@qq.com)
//  Date : 2015-12-30

#include "base/cpp/thirdparty/gtest-1.6.0/include/gtest/gtest.h"

#include "base/cpp/thirdparty/gflags-2.0/include/gflags/gflags.h"
#include "base/cpp/thirdparty/glog-0.3.3/include/glog/logging.h"

#include "machine_learning/src/data_dict/array_param_value_dict.h"
#include "machine_learning/src/model/lr_model.h"
#include "machine_learning/src/util/def_struct.h"

using namespace std;
using namespace machine_learning::data_dict;
using namespace machine_learning::supervised_model;
using namespace machine_learning::util;

class LRModelTest: public testing::Test {
 protected:
  virtual void SetUp() {
    dict_ = new ArrayParamValueDict(
                "test_data/data/test_array_param_value_dict");
    CHECK(dict_) << "new ArrayParamValueDict error";
    bool b_success = dict_->Init();
    CHECK(b_success) << "dict_->Init() error";

    lr_model_ = new LRModel(*dict_);
    CHECK(lr_model_) << "new LRModel failed";
    b_success = lr_model_->Init();
    CHECK(b_success) << "lr_model_ Init() error";
  }

  virtual void TearDown() {
    if (lr_model_) {
      lr_model_->Destroy();
      delete lr_model_;
      lr_model_ = NULL;
    }

    if (dict_) {
      dict_->Destroy();
      delete dict_;
      dict_ = NULL;
    }
  }

  ArrayParamValueDict* dict_;
  SupervisedModel* lr_model_;
};

TEST_F(LRModelTest, ModelFunctionTest) {
  LOG(INFO)<< "== In LRModelTest::ModelFunctionTest() ==";

  bool b_success = false;
  SampleWithLabel sample;
  map<int, float>& feat_score = sample.feat_score_;
  float model_score = 0;

  b_success = lr_model_->ModelFunction(sample, &model_score);
  EXPECT_FALSE(b_success);

  feat_score.insert(make_pair(0, 1));
  b_success = lr_model_->ModelFunction(sample, &model_score);
  EXPECT_TRUE(b_success);
  EXPECT_FLOAT_EQ(0.524979, model_score);

  feat_score.insert(make_pair(1, 3));
  b_success = lr_model_->ModelFunction(sample, &model_score);
  EXPECT_TRUE(b_success);
  EXPECT_FLOAT_EQ(0.7310586, model_score);

  feat_score.insert(make_pair(4, 4));
  b_success = lr_model_->ModelFunction(sample, &model_score);
  EXPECT_TRUE(b_success);
  EXPECT_FLOAT_EQ(0.8581489, model_score);

  feat_score.insert(make_pair(5, 4));  // bad index
  b_success = lr_model_->ModelFunction(sample, &model_score);
  EXPECT_TRUE(b_success);
  EXPECT_FLOAT_EQ(0.8581489, model_score);

  feat_score.insert(make_pair(-1, 4));  // bad index
  b_success = lr_model_->ModelFunction(sample, &model_score);
  EXPECT_TRUE(b_success);
  EXPECT_FLOAT_EQ(0.8581489, model_score);
}

TEST_F(LRModelTest, LossFunctionTest) {
  LOG(INFO)<< "== In LRModelTest::LossFunctionTest() ==";

  bool b_success = false;
  SampleWithLabel sample;
  sample.label_id_ = 0;
  sample.weight_ = 1;
  map<int, float>& feat_score = sample.feat_score_;
  float loss_score = 0;

  b_success = lr_model_->LossFunction(sample, &loss_score);
  EXPECT_FALSE(b_success);

  feat_score.insert(make_pair(0, 1));
  sample.label_id_ = 2;
  b_success = lr_model_->LossFunction(sample, &loss_score);
  EXPECT_FALSE(b_success);

  sample.label_id_ = 1;
  b_success = lr_model_->LossFunction(sample, &loss_score);
  EXPECT_TRUE(b_success);
  EXPECT_FLOAT_EQ(0.64439666, loss_score);

  feat_score.insert(make_pair(1, 3));
  b_success = lr_model_->LossFunction(sample, &loss_score);
  EXPECT_TRUE(b_success);
  EXPECT_FLOAT_EQ(0.31326166, loss_score);

  feat_score.insert(make_pair(4, 4));
  b_success = lr_model_->LossFunction(sample, &loss_score);
  EXPECT_TRUE(b_success);
  EXPECT_FLOAT_EQ(0.15297769, loss_score);

  feat_score.insert(make_pair(5, 4));  // bad index
  b_success = lr_model_->LossFunction(sample, &loss_score);
  EXPECT_TRUE(b_success);
  EXPECT_FLOAT_EQ(0.15297769, loss_score);

  sample.label_id_ = 0;
  feat_score.insert(make_pair(-1, 4));  // bad index
  b_success = lr_model_->LossFunction(sample, &loss_score);
  EXPECT_TRUE(b_success);
  EXPECT_FLOAT_EQ(1.952977, loss_score);

  sample.weight_ = 0.5;
  b_success = lr_model_->LossFunction(sample, &loss_score);
  EXPECT_TRUE(b_success);
  EXPECT_FLOAT_EQ(0.9764885, loss_score);

  sample.weight_ = 2;
  b_success = lr_model_->LossFunction(sample, &loss_score);
  EXPECT_TRUE(b_success);
  EXPECT_FLOAT_EQ(3.905954, loss_score);
}

TEST_F(LRModelTest, GradientFunctionTest) {
  LOG(INFO)<< "== In LRModelTest::GradientFunctionTest() ==";

  bool b_success = false;
  SampleWithLabel sample;
  sample.label_id_ = 0;
  sample.weight_ = 1;
  map<int, float>& feat_score = sample.feat_score_;
  map<int, float> gradient;

  b_success = lr_model_->GradientFunction(sample, &gradient);
  EXPECT_FALSE(b_success);

  feat_score.insert(make_pair(0, 1));
  sample.label_id_ = 2;
  b_success = lr_model_->GradientFunction(sample, &gradient);
  EXPECT_FALSE(b_success);

  sample.label_id_ = 1;
  b_success = lr_model_->GradientFunction(sample, &gradient);
  EXPECT_TRUE(b_success);
  EXPECT_EQ(1, static_cast<int>(gradient.size()));
  EXPECT_TRUE(gradient.find(0) != gradient.end());
  EXPECT_FLOAT_EQ(-0.47502083, gradient[0]);

  feat_score.insert(make_pair(1, 3));
  b_success = lr_model_->GradientFunction(sample, &gradient);
  EXPECT_TRUE(b_success);
  EXPECT_EQ(2, static_cast<int>(gradient.size()));
  EXPECT_TRUE(gradient.find(0) != gradient.end());
  EXPECT_TRUE(gradient.find(1) != gradient.end());
  EXPECT_FLOAT_EQ(-0.2689414, gradient[0]);
  EXPECT_FLOAT_EQ(-0.8068242, gradient[1]);

  feat_score.insert(make_pair(4, 4));
  b_success = lr_model_->GradientFunction(sample, &gradient);
  EXPECT_TRUE(b_success);
  EXPECT_TRUE(gradient.find(0) != gradient.end());
  EXPECT_TRUE(gradient.find(1) != gradient.end());
  EXPECT_TRUE(gradient.find(4) != gradient.end());
  EXPECT_FALSE(gradient.find(2) != gradient.end());
  EXPECT_FALSE(gradient.find(3) != gradient.end());
  EXPECT_FLOAT_EQ(-0.1418511, gradient[0]);
  EXPECT_FLOAT_EQ(-0.4255533, gradient[1]);
  EXPECT_FLOAT_EQ(-0.5674044, gradient[4]);

  feat_score.insert(make_pair(5, 4));  // bad index
  b_success = lr_model_->GradientFunction(sample, &gradient);
  EXPECT_TRUE(b_success);
  EXPECT_TRUE(gradient.find(0) != gradient.end());
  EXPECT_TRUE(gradient.find(1) != gradient.end());
  EXPECT_TRUE(gradient.find(4) != gradient.end());
  EXPECT_FALSE(gradient.find(2) != gradient.end());
  EXPECT_FALSE(gradient.find(3) != gradient.end());
  EXPECT_FLOAT_EQ(-0.1418511, gradient[0]);
  EXPECT_FLOAT_EQ(-0.4255533, gradient[1]);
  EXPECT_FLOAT_EQ(-0.5674044, gradient[4]);

  sample.label_id_ = 0;
  feat_score.insert(make_pair(-1, 4));  // bad index
  b_success = lr_model_->GradientFunction(sample, &gradient);
  EXPECT_TRUE(b_success);
  EXPECT_TRUE(gradient.find(0) != gradient.end());
  EXPECT_TRUE(gradient.find(1) != gradient.end());
  EXPECT_TRUE(gradient.find(4) != gradient.end());
  EXPECT_FALSE(gradient.find(2) != gradient.end());
  EXPECT_FALSE(gradient.find(3) != gradient.end());
  EXPECT_FLOAT_EQ(0.8581489, gradient[0]);
  EXPECT_FLOAT_EQ(2.5744467, gradient[1]);
  EXPECT_FLOAT_EQ(3.4325956, gradient[4]);

  sample.weight_ = 0.5;
  b_success = lr_model_->GradientFunction(sample, &gradient);
  EXPECT_TRUE(b_success);
  EXPECT_TRUE(gradient.find(0) != gradient.end());
  EXPECT_TRUE(gradient.find(1) != gradient.end());
  EXPECT_TRUE(gradient.find(4) != gradient.end());
  EXPECT_FALSE(gradient.find(2) != gradient.end());
  EXPECT_FALSE(gradient.find(3) != gradient.end());
  EXPECT_FLOAT_EQ(0.42907445, gradient[0]);
  EXPECT_FLOAT_EQ(1.28722335, gradient[1]);
  EXPECT_FLOAT_EQ(1.7162978, gradient[4]);

  sample.label_id_ = 1;
  b_success = lr_model_->GradientFunction(sample, &gradient);
  EXPECT_TRUE(b_success);
  EXPECT_TRUE(gradient.find(0) != gradient.end());
  EXPECT_TRUE(gradient.find(1) != gradient.end());
  EXPECT_TRUE(gradient.find(4) != gradient.end());
  EXPECT_FALSE(gradient.find(2) != gradient.end());
  EXPECT_FALSE(gradient.find(3) != gradient.end());
  EXPECT_FLOAT_EQ(-0.07092555, gradient[0]);
  EXPECT_FLOAT_EQ(-0.21277665, gradient[1]);
  EXPECT_FLOAT_EQ(-0.2837022, gradient[4]);
}

TEST_F(LRModelTest, PredictTest) {
  LOG(INFO)<< "== In LRModelTest::PredictTest() ==";

  bool b_success = false;
  SampleWithLabel sample;
  map<int, float>& feat_score = sample.feat_score_;
  int max_score_label_id = -1;
  map<int, float> label_score;

  b_success = lr_model_->Predict(sample, &max_score_label_id, &label_score);
  EXPECT_FALSE(b_success);

  feat_score.insert(make_pair(0, 1));
  b_success = lr_model_->Predict(sample, &max_score_label_id, &label_score);
  EXPECT_TRUE(b_success);
  EXPECT_EQ(1, max_score_label_id);
  EXPECT_EQ(2, static_cast<int>(label_score.size()));
  EXPECT_FLOAT_EQ(0.524979, label_score[1]);
  EXPECT_FLOAT_EQ(0.47502083, label_score[0]);

  feat_score.insert(make_pair(1, 3));
  b_success = lr_model_->Predict(sample, &max_score_label_id, &label_score);
  EXPECT_TRUE(b_success);
  EXPECT_EQ(1, max_score_label_id);
  EXPECT_EQ(2, static_cast<int>(label_score.size()));
  EXPECT_FLOAT_EQ(0.7310586, label_score[1]);
  EXPECT_FLOAT_EQ(0.2689414, label_score[0]);

  feat_score.insert(make_pair(4, 4));
  b_success = lr_model_->Predict(sample, &max_score_label_id, &label_score);
  EXPECT_TRUE(b_success);
  EXPECT_EQ(1, max_score_label_id);
  EXPECT_EQ(2, static_cast<int>(label_score.size()));
  EXPECT_FLOAT_EQ(0.8581489, label_score[1]);
  EXPECT_FLOAT_EQ(0.1418511, label_score[0]);

  feat_score.insert(make_pair(5, 4));  // bad index
  b_success = lr_model_->Predict(sample, &max_score_label_id, &label_score);
  EXPECT_TRUE(b_success);
  EXPECT_EQ(1, max_score_label_id);
  EXPECT_EQ(2, static_cast<int>(label_score.size()));
  EXPECT_FLOAT_EQ(0.8581489, label_score[1]);
  EXPECT_FLOAT_EQ(0.1418511, label_score[0]);

  feat_score.insert(make_pair(-1, 4));  // bad index
  b_success = lr_model_->Predict(sample, &max_score_label_id, &label_score);
  EXPECT_TRUE(b_success);
  EXPECT_EQ(1, max_score_label_id);
  EXPECT_EQ(2, static_cast<int>(label_score.size()));
  EXPECT_FLOAT_EQ(0.8581489, label_score[1]);
  EXPECT_FLOAT_EQ(0.1418511, label_score[0]);

  feat_score.insert(make_pair(2, -10));
  b_success = lr_model_->Predict(sample, &max_score_label_id, &label_score);
  EXPECT_TRUE(b_success);
  EXPECT_EQ(0, max_score_label_id);
  EXPECT_EQ(2, static_cast<int>(label_score.size()));
  EXPECT_FLOAT_EQ(0.03916572, label_score[1]);
  EXPECT_FLOAT_EQ(0.9608343, label_score[0]);
}

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  google::InitGoogleLogging(argv[0]);
  FLAGS_stderrthreshold = 0;
  FLAGS_logtostderr = true;

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
