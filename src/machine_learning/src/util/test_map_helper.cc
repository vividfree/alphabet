// Author: vividfree (vividfree@qq.com)
//  Date : 2016-04-13

#include <string>

#include "base/cpp/thirdparty/gtest-1.6.0/include/gtest/gtest.h"
#include "base/cpp/thirdparty/gflags-2.0/include/gflags/gflags.h"

#include "machine_learning/src/util/map_helper-inl.h"

using namespace std;
using namespace machine_learning::util;

TEST(MapHelperTest, TwoMapAdditionTest) {
  cerr << "In MapHelperTest::TwoMapAdditionTest\n";

  map<string, float> data_map1;
  data_map1["b"] = 1.1;
  data_map1["a"] = 2.2;
  data_map1["c"] = 3.3;

  map<string, float> data_map2;
  data_map2["d"] = 1.11;
  data_map2["a"] = 2.22;
  data_map2["e"] = 3.33;

  TwoMapAddition(data_map2, &data_map1);
  EXPECT_EQ(5, static_cast<int>(data_map1.size()));
  EXPECT_EQ(3, static_cast<int>(data_map2.size()));
  EXPECT_FLOAT_EQ(4.42, data_map1["a"]);
  EXPECT_FLOAT_EQ(1.1, data_map1["b"]);
  EXPECT_FLOAT_EQ(3.3, data_map1["c"]);
  EXPECT_FLOAT_EQ(1.11, data_map1["d"]);
  EXPECT_FLOAT_EQ(3.33, data_map1["e"]);

  data_map2["f"] = 5;
  TwoMapAddition(data_map2, &data_map1);
  EXPECT_EQ(6, static_cast<int>(data_map1.size()));
  EXPECT_EQ(4, static_cast<int>(data_map2.size()));
  EXPECT_FLOAT_EQ(6.64, data_map1["a"]);
  EXPECT_FLOAT_EQ(1.1, data_map1["b"]);
  EXPECT_FLOAT_EQ(3.3, data_map1["c"]);
  EXPECT_FLOAT_EQ(2.22, data_map1["d"]);
  EXPECT_FLOAT_EQ(6.66, data_map1["e"]);
  EXPECT_FLOAT_EQ(5.0, data_map1["f"]);

  // PrintMap(data_map1);
}

TEST(MapHelperTest, PrintMapTest) {
  cerr << "In MapHelperTest::PrintMapTest\n";

  map<string, float> map_string_float;
  map_string_float["b"] = 1.1;
  map_string_float["a"] = 2.2;
  map_string_float["c"] = 3.3;
  PrintMap(map_string_float);

  map<int, float> map_int_float;
  map_int_float[2] = 1.11;
  map_int_float[1] = 2.22;
  map_int_float[3] = 3.33;
  PrintMap(map_int_float);
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
