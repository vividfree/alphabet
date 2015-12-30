// Author: vividfree (vividfree@qq.com)
//  Date : 2015-12-30

#include "base/cpp/thirdparty/gtest-1.6.0/include/gtest/gtest.h"

#include "base/cpp/thirdparty/gflags-2.0/include/gflags/gflags.h"
#include "base/cpp/thirdparty/glog-0.3.3/include/glog/logging.h"

#include "base/cpp/public/util/map_struct_util.h"

using namespace std;
using namespace base::util;

TEST(MapStructUtilTest, ReadMapDataFromStrTest) {
  cerr << "In MapStructUtilTest::ReadMapDataFromStrTest\n";

  bool b_success = false;
  string str;
  map<string, double> result;

  str = "1000\0021\0012100\0022\0012300\0021\0013200\0023";
  b_success = MapStructUtil::ReadMapDataFromStr(str, "\001", "\002", &result);
  EXPECT_TRUE(b_success);
  EXPECT_EQ(4, static_cast<int>(result.size()));
  EXPECT_FLOAT_EQ(1.0, result["1000"]);
  EXPECT_FLOAT_EQ(2.0, result["2100"]);
  EXPECT_FLOAT_EQ(1.0, result["2300"]);
  EXPECT_FLOAT_EQ(3.0, result["3200"]);

  str = "1000:1,2100:2,2300:11,3200:3.0";
  b_success = MapStructUtil::ReadMapDataFromStr(str, ",", ":", &result);
  EXPECT_TRUE(b_success);
  EXPECT_EQ(4, static_cast<int>(result.size()));
  EXPECT_FLOAT_EQ(1.0, result["1000"]);
  EXPECT_FLOAT_EQ(2.0, result["2100"]);
  EXPECT_FLOAT_EQ(11.0, result["2300"]);
  EXPECT_FLOAT_EQ(3.0, result["3200"]);

  str = " , 2100 : 2,2300 ,3200 : 3.0";
  b_success = MapStructUtil::ReadMapDataFromStr(str, ",", ":", &result);
  EXPECT_TRUE(b_success);
  EXPECT_EQ(2, static_cast<int>(result.size()));
  EXPECT_FLOAT_EQ(2.0, result["2100"]);
  EXPECT_FLOAT_EQ(3.0, result["3200"]);

  str = " , 2100  2,2300 ,3200  3.0";
  b_success = MapStructUtil::ReadMapDataFromStr(str, ",", ":", &result);
  EXPECT_FALSE(b_success);
}

TEST(MapStructUtilTest, InterpolateTwoMapTest) {
  cerr << "In MapStructUtilTest::InterpolateTwoMapTest\n";

  map<string, double> map1;
  map1["1000"] = 2.4;
  map1["2000"] = 2.6;
  map1["1030"] = 2.9;
  double map1_weight = 0.3;

  map<string, double> map2;
  map2["1010"] = 2.4;
  map2["2000"] = 3.6;
  map2["1030"] = 3.9;
  double map2_weight = 0.7;

  bool b_success = false;
  map<string, double> result;
  b_success = MapStructUtil::InterpolateTwoMap(map1,
                                               map1_weight,
                                               map2,
                                               map2_weight,
                                               &result);
  EXPECT_TRUE(b_success);
  EXPECT_EQ(4, static_cast<int>(result.size()));
  EXPECT_FLOAT_EQ(0.72, result["1000"]);
  EXPECT_FLOAT_EQ(1.68, result["1010"]);
  EXPECT_FLOAT_EQ(3.6, result["1030"]);
  EXPECT_FLOAT_EQ(3.3, result["2000"]);
}

TEST(MapStructUtilTest, NormalizeMapTest) {
  cerr << "In MapStructUtilTest::NormalizeMapTest\n";

  map<string, double> map_data;
  map_data["1000"] = 3.0;
  map_data["1030"] = 4.0;

  bool b_success = false;
  b_success = MapStructUtil::NormalizeMap(&map_data);
  EXPECT_TRUE(b_success);
  EXPECT_EQ(2, static_cast<int>(map_data.size()));
  EXPECT_FLOAT_EQ(0.6, map_data["1000"]);
  EXPECT_FLOAT_EQ(0.8, map_data["1030"]);

  map_data.clear();
  map_data["2400"] = 7.9;
  map_data["3400"] = -7.9;
  b_success = MapStructUtil::NormalizeMap(&map_data);
  EXPECT_FALSE(b_success);

  map_data.clear();
  map_data["2400"] = 1.2;
  map_data["3400"] = -2;
  b_success = MapStructUtil::NormalizeMap(&map_data);
  EXPECT_FALSE(b_success);
}

TEST(MapStructUtilTest, GetOutputStrForIntMapTest) {
  cerr << "\nIn MapStructUtilTest::GetOutputStrForIntMapTest()\n\n";

  map<string, int> map_data;
  map_data["1000"] = 1;
  map_data["2100"] = 2;
  map_data["2300"] = 1;
  map_data["3200"] = 3;

  string output_str;
  MapStructUtil::GetOutputStrForIntMap(map_data, "\001", "\002", &output_str);
  EXPECT_EQ(output_str, "1000\0021\0012100\0022\001"
                        "2300\0021\0013200\0023");
}

TEST(MapStructUtilTest, GetOutputStrForDoubleMapTest) {
  cerr << "\nIn MapStructUtilTest::GetOutputStrForDoubleMapTest()\n\n";

  map<string, double> map_data;
  map_data["1000"] = 1.1;
  map_data["2100"] = 2.2;
  map_data["2300"] = 3.3;
  map_data["3200"] = 4.4;

  string output_str;
  MapStructUtil::GetOutputStrForDoubleMap(map_data, "\001", "\002", &output_str);
  EXPECT_EQ("10001.1000021002.2000023003.3000032004.40000", output_str);
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
