// Author: vividfree (vividfree@qq.com)
//  Date : 2015-12-30

#ifndef BASE_CPP_PUBLIC_UTIL_NUM_UTIL_H_
#define BASE_CPP_PUBLIC_UTIL_NUM_UTIL_H_

#include <string>

namespace base {
namespace util {

class NumUtil {
 public:
  static bool DoubleToString(double input, std::string* output);

  static bool Sigmoid(float input, float* output);

  static int Sign(float input);
};

}  // namespace util
}  // namespace base

#endif  // BASE_CPP_PUBLIC_UTIL_NUM_UTIL_H_
