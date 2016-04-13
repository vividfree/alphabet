// Author: vividfree (vividfree@qq.com)
//  Date : 2015-12-30

#include "base/cpp/thirdparty/gtest-1.6.0/include/gtest/gtest.h"

#include "base/cpp/thirdparty/boost_1.52.0/include/boost/algorithm/string.hpp"
#include "base/cpp/thirdparty/boost_1.52.0/include/boost/lexical_cast.hpp"
#include "base/cpp/thirdparty/gflags-2.0/include/gflags/gflags.h"
#include "base/cpp/thirdparty/glog-0.3.3/include/glog/logging.h"

#include "machine_learning/src/data_dict/array_param_value_dict.h"

using namespace std;
using namespace machine_learning::data_dict;

class ArrayParamValueDictTest: public testing::Test {
 protected:
  virtual void SetUp() {
    dict_ = new ArrayParamValueDict(
                "test_data/data/test_array_param_value_dict");
    CHECK(dict_) << "new dict_ error";
    bool b_success = dict_->Init();
    CHECK(b_success) << "dict_->Init() error";
  }

  virtual void TearDown() {
    if (dict_) {
      dict_->Destroy();
      delete dict_;
      dict_ = NULL;
    }
  }

  ArrayParamValueDict* dict_;
};

TEST_F(ArrayParamValueDictTest, GetValueForSingleParamTest) {
  cerr << "\nIn ArrayParamValueDictTest::GetValueForSingleParamTest()\n\n";

  bool b_success = false;
  int index = -2;
  float value = 0;

  b_success = dict_->GetValueForSingleParam(index, &value);
  EXPECT_FALSE(b_success);

  index = -1;
  b_success = dict_->GetValueForSingleParam(index, &value);
  EXPECT_FALSE(b_success);

  index = 0;
  b_success = dict_->GetValueForSingleParam(index, &value);
  EXPECT_TRUE(b_success);
  EXPECT_FLOAT_EQ(0.1, value);

  index = 1;
  b_success = dict_->GetValueForSingleParam(index, &value);
  EXPECT_TRUE(b_success);
  EXPECT_FLOAT_EQ(0.3, value);

  index = 2;
  b_success = dict_->GetValueForSingleParam(index, &value);
  EXPECT_TRUE(b_success);
  EXPECT_FLOAT_EQ(0.5, value);

  index = 3;
  b_success = dict_->GetValueForSingleParam(index, &value);
  EXPECT_TRUE(b_success);
  EXPECT_FLOAT_EQ(0.4, value);

  index = 4;
  b_success = dict_->GetValueForSingleParam(index, &value);
  EXPECT_TRUE(b_success);
  EXPECT_FLOAT_EQ(0.2, value);

  index = 5;
  b_success = dict_->GetValueForSingleParam(index, &value);
  EXPECT_FALSE(b_success);

  index = 6;
  b_success = dict_->GetValueForSingleParam(index, &value);
  EXPECT_FALSE(b_success);
}

TEST_F(ArrayParamValueDictTest, SetValueForSingleParamTest) {
  cerr << "\nIn ArrayParamValueDictTest::SetValueForSingleParamTest()\n\n";

  bool b_success = false;
  int index = -2;
  float value = 1.2;
  float tmp_value;

  b_success = dict_->SetValueForSingleParam(index, value);
  EXPECT_FALSE(b_success);

  index = -1;
  b_success = dict_->SetValueForSingleParam(index, value);
  EXPECT_FALSE(b_success);

  index = 0;
  b_success = dict_->SetValueForSingleParam(index, value);
  EXPECT_TRUE(b_success);
  b_success = dict_->GetValueForSingleParam(index, &tmp_value);
  EXPECT_TRUE(b_success);
  EXPECT_FLOAT_EQ(1.2, tmp_value);

  index = 2;
  value = 2.1;
  b_success = dict_->SetValueForSingleParam(index, value);
  EXPECT_TRUE(b_success);
  b_success = dict_->GetValueForSingleParam(index, &tmp_value);
  EXPECT_TRUE(b_success);
  EXPECT_FLOAT_EQ(2.1, tmp_value);

  index = 4;
  value = 31;
  b_success = dict_->SetValueForSingleParam(index, value);
  EXPECT_TRUE(b_success);
  b_success = dict_->GetValueForSingleParam(index, &tmp_value);
  EXPECT_TRUE(b_success);
  EXPECT_FLOAT_EQ(31, tmp_value);

  index = 5;
  b_success = dict_->SetValueForSingleParam(index, value);
  EXPECT_FALSE(b_success);

  index = 6;
  b_success = dict_->SetValueForSingleParam(index, value);
  EXPECT_FALSE(b_success);
}

TEST_F(ArrayParamValueDictTest, AddValueForSingleParamTest) {
  cerr << "\nIn ArrayParamValueDictTest::AddValueForSingleParamTest()\n\n";

  bool b_success = false;
  int index = -2;
  float value = 1.2;
  float tmp_value;

  b_success = dict_->AddValueForSingleParam(index, value);
  EXPECT_FALSE(b_success);

  index = -1;
  b_success = dict_->AddValueForSingleParam(index, value);
  EXPECT_FALSE(b_success);

  index = 0;
  b_success = dict_->AddValueForSingleParam(index, value);
  EXPECT_TRUE(b_success);
  b_success = dict_->GetValueForSingleParam(index, &tmp_value);
  EXPECT_TRUE(b_success);
  EXPECT_FLOAT_EQ(1.3, tmp_value);

  index = 2;
  value = -2;
  b_success = dict_->AddValueForSingleParam(index, value);
  EXPECT_TRUE(b_success);
  b_success = dict_->GetValueForSingleParam(index, &tmp_value);
  EXPECT_TRUE(b_success);
  EXPECT_FLOAT_EQ(-1.5, tmp_value);

  index = 4;
  value = 31;
  b_success = dict_->AddValueForSingleParam(index, value);
  EXPECT_TRUE(b_success);
  b_success = dict_->GetValueForSingleParam(index, &tmp_value);
  EXPECT_TRUE(b_success);
  EXPECT_FLOAT_EQ(31.2, tmp_value);

  index = 5;
  b_success = dict_->AddValueForSingleParam(index, value);
  EXPECT_FALSE(b_success);

  index = 6;
  b_success = dict_->AddValueForSingleParam(index, value);
  EXPECT_FALSE(b_success);
}

TEST_F(ArrayParamValueDictTest, GetParamArraySizeTest) {
  cerr << "\nIn ArrayParamValueDictTest::GetParamArraySizeTest()\n\n";

  int array_size = 0;
  bool b_success = dict_->GetParamArraySize(&array_size);
  EXPECT_TRUE(b_success);
  EXPECT_EQ(5, array_size);

  dict_->Destroy();
  b_success = dict_->GetParamArraySize(&array_size);
  EXPECT_FALSE(b_success);

  dict_->Init();
  b_success = dict_->GetParamArraySize(&array_size);
  EXPECT_TRUE(b_success);
  EXPECT_EQ(5, array_size);
}

TEST_F(ArrayParamValueDictTest, DumpModelTest) {
  cerr << "\nIn ArrayParamValueDictTest::DumpModelTest()\n\n";

  dict_->Destroy();

  string output_model_filename = "";
  bool b_success = dict_->DumpModel(output_model_filename);
  EXPECT_FALSE(b_success);

  dict_->Init();
  b_success = dict_->DumpModel(output_model_filename);
  EXPECT_FALSE(b_success);

  output_model_filename = "test_data/data/test_output_model_file";
  b_success = dict_->DumpModel(output_model_filename);
  EXPECT_TRUE(b_success);
}


int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  google::InitGoogleLogging(argv[0]);
  FLAGS_stderrthreshold = 0;
  FLAGS_logtostderr = true;

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
