// Author: vividfree (vividfree@qq.com)
//  Date : 2015-12-30

#include "base/cpp/thirdparty/gtest-1.6.0/include/gtest/gtest.h"

#include "base/cpp/thirdparty/gflags-2.0/include/gflags/gflags.h"
#include "base/cpp/thirdparty/glog-0.3.3/include/glog/logging.h"

#include "base/cpp/public/util/num_util.h"

using namespace std;
using namespace base::util;

TEST(NumUtilTest, DoubleToStringTest) {
  cerr << "In NumUtilTest::DoubleToStringTest\n";

  bool b_success = false;
  double input;
  string output;

  input = 0.2;
  b_success = NumUtil::DoubleToString(input, &output);
  EXPECT_TRUE(b_success);
  EXPECT_EQ("0.20000", output);

  input = 0.2123;
  b_success = NumUtil::DoubleToString(input, &output);
  EXPECT_TRUE(b_success);
  EXPECT_EQ("0.21230", output);

  input = 0.21235;
  b_success = NumUtil::DoubleToString(input, &output);
  EXPECT_TRUE(b_success);
  EXPECT_EQ("0.21235", output);

  input = 0.212351;
  b_success = NumUtil::DoubleToString(input, &output);
  EXPECT_TRUE(b_success);
  EXPECT_EQ("0.21235", output);

  input = 0.212356;
  b_success = NumUtil::DoubleToString(input, &output);
  EXPECT_TRUE(b_success);
  EXPECT_EQ("0.21236", output);

  input = -0.212356;
  b_success = NumUtil::DoubleToString(input, &output);
  EXPECT_TRUE(b_success);
  EXPECT_EQ("-0.21236", output);
}

TEST(NumUtilTest, SigmoidTest) {
  cerr << "In NumUtilTest::SigmoidTest\n";

  bool b_success = false;
  float input;
  float output;

  input = 0;
  b_success = NumUtil::Sigmoid(input, &output);
  EXPECT_TRUE(b_success);
  EXPECT_FLOAT_EQ(0.5, output);

  input = 0.2;
  b_success = NumUtil::Sigmoid(input, &output);
  EXPECT_TRUE(b_success);
  EXPECT_FLOAT_EQ(0.54983395, output);

  input = 2;
  b_success = NumUtil::Sigmoid(input, &output);
  EXPECT_TRUE(b_success);
  EXPECT_FLOAT_EQ(0.880797, output);

  input = -3;
  b_success = NumUtil::Sigmoid(input, &output);
  EXPECT_TRUE(b_success);
  EXPECT_FLOAT_EQ(0.047425874, output);
}

TEST(NumUtilTest, SignTest) {
  cerr << "In NumUtilTest::SignTest\n";

  float input;
  int result = 0;

  input = 0;
  result = NumUtil::Sign(input);
  EXPECT_EQ(0, result);

  input = 1e-5;
  result = NumUtil::Sign(input);
  EXPECT_EQ(1, result);

  input = 1e-7;
  result = NumUtil::Sign(input);
  EXPECT_EQ(0, result);

  input = -1e-7;
  result = NumUtil::Sign(input);
  EXPECT_EQ(0, result);

  input = 0.2;
  result = NumUtil::Sign(input);
  EXPECT_EQ(1, result);

  input = -0.2;
  result = NumUtil::Sign(input);
  EXPECT_EQ(-1, result);
}

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  google::InitGoogleLogging(argv[0]);
  FLAGS_stderrthreshold = 0;
  FLAGS_logtostderr = true;
  FLAGS_v = 0;

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
