// Author: vividfree (vividfree@qq.com)
//  Date : 2015-12-30

#ifndef BASE_CPP_PUBLIC_UTIL_HASH_UTIL_H_
#define BASE_CPP_PUBLIC_UTIL_HASH_UTIL_H_

#include <string>

namespace base {
namespace util {

class HashUtil {
 public:
  static bool StrHash(const std::string& str, std::string* hash_str);
};

}  // namespace util
}  // namespace base

#endif  // BASE_CPP_PUBLIC_UTIL_HASH_UTIL_H_
