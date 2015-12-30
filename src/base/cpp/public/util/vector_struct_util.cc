// Author: vividfree (vividfree@qq.com)
//  Date : 2015-12-30

#include "base/cpp/public/util/vector_struct_util.h"

#include <iostream>
#include "base/cpp/thirdparty/boost_1.52.0/include/boost/algorithm/string.hpp"
#include "base/cpp/thirdparty/glog-0.3.3/include/glog/logging.h"

using namespace std;

namespace base {
namespace util {

bool VectorStructUtil::SplitVec2VVec(vector<string>* vec_data,
                                     int split_part_size,
                                     vector<vector<string> >* vvec_data) {
  vvec_data->clear();
  if (vec_data->empty()) return false;
  if (split_part_size <= 0) {
    LOG(ERROR) << "split_part_size should > 0, the real val is "
               << split_part_size;
    return false;
  }

  int vec_size = static_cast<int>(vec_data->size());
  int part_num = vec_size / split_part_size;
  if (0 != vec_size % split_part_size) ++part_num;
  vvec_data->resize(part_num);

  // NOTE: from back to front, because use vector.erase()
  for (int index = part_num - 1; index >= 0; --index) {
    int part_beg_index = split_part_size * index;
    int part_end_index = split_part_size * (index + 1);
    if (part_end_index > vec_size) part_end_index = vec_size;

    vector<string>& tmp_vec = vvec_data->at(index);
    tmp_vec.insert(tmp_vec.end(),
                   vec_data->begin() + part_beg_index,
                   vec_data->begin() + part_end_index);

    vec_data->erase(vec_data->begin() + part_beg_index,
                    vec_data->begin() + part_end_index);
  }  // end for

  return true;
}

}  // namespace util
}  // namespace base
