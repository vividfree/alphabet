// Author: vividfree (vividfree@qq.com)
//  Date : 2015-12-30

#ifndef BASE_CPP_PUBLIC_UTIL_FILE_UTIL_H_
#define BASE_CPP_PUBLIC_UTIL_FILE_UTIL_H_

#include <string>
#include <vector>

namespace base {
namespace util {

class FileUtil {
 public:
  static bool ReadFile(const std::string& file_name,
                       std::vector<std::string>* lines);
};

}  // namespace util
}  // namespace base

#endif  // BASE_CPP_PUBLIC_UTIL_FILE_UTIL_H_
