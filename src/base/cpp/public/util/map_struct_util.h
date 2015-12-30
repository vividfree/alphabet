// Author: vividfree (vividfree@qq.com)
//  Date : 2015-12-30

#ifndef BASE_CPP_PUBLIC_UTIL_MAP_STRUCT_UTIL_H_
#define BASE_CPP_PUBLIC_UTIL_MAP_STRUCT_UTIL_H_

#include <map>
#include <string>
#include <vector>

namespace base {
namespace util {

class MapStructUtil {
 public:
  static bool ReadMapDataFromStr(const std::string& str,
                                 const std::string& level1_delimeter,
                                 const std::string& level2_delimeter,
                                 std::map<std::string, double>* map_data);

  static bool InterpolateTwoMap(const std::map<std::string, double>& map1,
                                double map1_weight,
                                const std::map<std::string, double>& map2,
                                double map2_weight,
                                std::map<std::string, double>* result);

  static bool NormalizeMap(std::map<std::string, double>* map_data);

  static void GetOutputStrForIntMap(
      const std::map<std::string, int>& map_data,
      const std::string& level1_delimeter,
      const std::string& level2_delimeter,
      std::string* output_str);

  static void GetOutputStrForDoubleMap(
      const std::map<std::string, double>& map_data,
      const std::string& level1_delimeter,
      const std::string& level2_delimeter,
      std::string* output_str);
};

}  // namespace util
}  // namespace base

#endif  // BASE_CPP_PUBLIC_UTIL_MAP_STRUCT_UTIL_H_
