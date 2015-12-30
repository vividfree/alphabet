// Author: vividfree (vividfree@qq.com)
//  Date : 2015-12-30

#include "base/cpp/thirdparty/gtest-1.6.0/include/gtest/gtest.h"

#include "base/cpp/thirdparty/gflags-2.0/include/gflags/gflags.h"
#include "base/cpp/thirdparty/glog-0.3.3/include/glog/logging.h"

#include "machine_learning/src/util/str_helper.h"

using namespace std;
using namespace machine_learning::util;

TEST(StrHelperTest, ReplaceDelimeterCharTest) {
  cerr << "In StrHelperTest::ReplaceDelimeterCharTest\n";

  bool b_success = false;
  string input;
  string output;

  input = " abc	足球\001  2 \003 21\002";
  b_success = StrHelper::ReplaceDelimeterChar(input, &output);
  EXPECT_TRUE(b_success);
  EXPECT_EQ(" abc 足球   2   21 ", output);

  input = "从文本中提取ngram";
  b_success = StrHelper::ReplaceDelimeterChar(input, &output);
  EXPECT_TRUE(b_success);
  EXPECT_EQ("从文本中提取ngram", output);
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
