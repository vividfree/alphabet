// Author: vividfree (vividfree@qq.com)
//  Date : 2015-12-30

#ifndef MACHINE_LEARNING_SRC_UTIL_STR_HELPER_H_
#define MACHINE_LEARNING_SRC_UTIL_STR_HELPER_H_

#include <string>

namespace machine_learning {
namespace util {

class StrHelper {
 public:
  static bool ReplaceDelimeterChar(const std::string& input,
                                   std::string* output);
};

}  // namespace util
}  // namespace machine_learning

#endif  // MACHINE_LEARNING_SRC_UTIL_STR_HELPER_H_
