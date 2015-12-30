// Author: vividfree (vividfree@qq.com)
//  Date : 2015-12-30

#ifndef BASE_CPP_PUBLIC_UTIL_VECTOR_STRUCT_UTIL_H_
#define BASE_CPP_PUBLIC_UTIL_VECTOR_STRUCT_UTIL_H_

#include <string>
#include <vector>

namespace base {
namespace util {

class VectorStructUtil {
 public:
  // 将一维的vec_data切分为二维的vvec_data，其中二维中每个大小为split_part_size
  // 为了节省空间，会将vec_data清空
  static bool SplitVec2VVec(std::vector<std::string>* vec_data,
                            int split_part_size,
                            std::vector<std::vector<std::string> >* vvec_data);
};

}  // namespace util
}  // namespace base

#endif  // BASE_CPP_PUBLIC_UTIL_VECTOR_STRUCT_UTIL_H_
