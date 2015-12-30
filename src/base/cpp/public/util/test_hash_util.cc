// Author: vividfree (vividfree@qq.com)
//  Date : 2015-12-30

#include "base/cpp/thirdparty/gtest-1.6.0/include/gtest/gtest.h"

#include "base/cpp/thirdparty/gflags-2.0/include/gflags/gflags.h"
#include "base/cpp/thirdparty/glog-0.3.3/include/glog/logging.h"
#include "base/cpp/public/util/hash_util.h"

using namespace std;
using namespace base::util;

TEST(HashUtilTest, StrHashTest) {
  cerr << "In HashUtilTest::StrHashTest\n";

  bool b_success = false;
  string feat;
  string hash_str;

  feat = "文件";
  b_success = HashUtil::StrHash(feat, &hash_str);
  EXPECT_TRUE(b_success);
  EXPECT_EQ("02567220c0468cc3", hash_str);

  feat = "从文本中提取ngram";
  b_success = HashUtil::StrHash(feat, &hash_str);
  EXPECT_TRUE(b_success);
  EXPECT_EQ("6635072501e85f17", hash_str);

  feat = "从文本中提取ngra";
  b_success = HashUtil::StrHash(feat, &hash_str);
  EXPECT_TRUE(b_success);
  EXPECT_EQ("608f8df9b88c9ab0", hash_str);

  feat = "从文本中提取ngr";
  b_success = HashUtil::StrHash(feat, &hash_str);
  EXPECT_TRUE(b_success);
  EXPECT_EQ("bcebdef7520d1593", hash_str);

  feat = "中华人民共和国";
  b_success = HashUtil::StrHash(feat, &hash_str);
  EXPECT_TRUE(b_success);
  EXPECT_EQ("2446b9d0318c3176", hash_str);

  feat = "问下   后    端  服务	    的架构策略， 鍋架國家社會 TaGut";
  b_success = HashUtil::StrHash(feat, &hash_str);
  EXPECT_TRUE(b_success);
  EXPECT_EQ("1d5b02c48ec9b188", hash_str);
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
