// Author: vividfree (vividfree@qq.com)
//  Date : 2015-12-30

#include "base/cpp/thirdparty/gtest-1.6.0/include/gtest/gtest.h"

#include "base/cpp/thirdparty/boost_1.52.0/include/boost/lexical_cast.hpp"
#include "base/cpp/thirdparty/gflags-2.0/include/gflags/gflags.h"
#include "base/cpp/thirdparty/glog-0.3.3/include/glog/logging.h"

#include "base/cpp/public/util/vector_struct_util.h"

using namespace std;
using namespace base::util;

TEST(VectorStructUtilTest, SplitVec2VVecTest) {
  cerr << "In VectorStructUtilTest::SplitVec2VVecTest\n";

  bool b_success = false;
  vector<string> vec_data;
  vector<vector<string> > vvec_data;

  // case 0
  b_success = VectorStructUtil::SplitVec2VVec(&vec_data, 3, &vvec_data);
  EXPECT_FALSE(b_success);

  // case 1
  for (int i = 0; i < 2; ++i) {
    string tmp_str = boost::lexical_cast<string>(i + 1);
    vec_data.push_back(tmp_str);
  }

  b_success = VectorStructUtil::SplitVec2VVec(&vec_data, 3, &vvec_data);
  EXPECT_TRUE(b_success);
  EXPECT_EQ(0, static_cast<int>(vec_data.size()));
  EXPECT_EQ(1, static_cast<int>(vvec_data.size()));
  EXPECT_EQ(2, static_cast<int>(vvec_data.at(0).size()));
  EXPECT_EQ("1", vvec_data.at(0).at(0));
  EXPECT_EQ("2", vvec_data.at(0).at(1));

  // case 2
  for (int i = 0; i < 3; ++i) {
    string tmp_str = boost::lexical_cast<string>(i + 1);
    vec_data.push_back(tmp_str);
  }

  b_success = VectorStructUtil::SplitVec2VVec(&vec_data, 3, &vvec_data);
  EXPECT_TRUE(b_success);
  EXPECT_EQ(0, static_cast<int>(vec_data.size()));
  EXPECT_EQ(1, static_cast<int>(vvec_data.size()));
  EXPECT_EQ(3, static_cast<int>(vvec_data.at(0).size()));
  EXPECT_EQ("1", vvec_data.at(0).at(0));
  EXPECT_EQ("3", vvec_data.at(0).at(2));

  // case 3
  for (int i = 0; i < 23; ++i) {
    string tmp_str = boost::lexical_cast<string>(i + 1);
    vec_data.push_back(tmp_str);
  }

  b_success = VectorStructUtil::SplitVec2VVec(&vec_data, 3, &vvec_data);
  EXPECT_TRUE(b_success);
  EXPECT_EQ(0, static_cast<int>(vec_data.size()));
  EXPECT_EQ(8, static_cast<int>(vvec_data.size()));
  EXPECT_EQ(3, static_cast<int>(vvec_data.at(0).size()));
  EXPECT_EQ(3, static_cast<int>(vvec_data.at(5).size()));
  EXPECT_EQ(2, static_cast<int>(vvec_data.at(7).size()));
  EXPECT_EQ("1", vvec_data.at(0).at(0));
  EXPECT_EQ("3", vvec_data.at(0).at(2));
  EXPECT_EQ("4", vvec_data.at(1).at(0));
  EXPECT_EQ("6", vvec_data.at(1).at(2));
  EXPECT_EQ("16", vvec_data.at(5).at(0));
  EXPECT_EQ("18", vvec_data.at(5).at(2));
  EXPECT_EQ("22", vvec_data.at(7).at(0));
  EXPECT_EQ("23", vvec_data.at(7).at(1));

  // test vector.reserve() and vector.resize()
  vector<string> vec1;
  vec1.reserve(10);
  EXPECT_EQ(0, static_cast<int>(vec1.size()));
  EXPECT_EQ(10, static_cast<int>(vec1.capacity()));

  vector<string> vec2;
  vec2.resize(9);
  EXPECT_EQ(9, static_cast<int>(vec2.size()));
  EXPECT_EQ(9, static_cast<int>(vec2.capacity()));
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
