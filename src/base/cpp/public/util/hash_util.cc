// Author: vividfree (vividfree@qq.com)
//  Date : 2015-12-30

#include "base/cpp/public/util/hash_util.h"

#include <algorithm>
#include <iostream>
#include "base/cpp/thirdparty/boost_1.52.0/include/boost/algorithm/string.hpp"
#include "base/cpp/thirdparty/boost_1.52.0/include/boost/lexical_cast.hpp"

#include "base/cpp/thirdparty/cityhash/include/city.h"

using namespace std;

namespace base {
namespace util {

bool HashUtil::StrHash(const string& str, string* hash_str) {
  hash_str->clear();

  uint64 uint_val = CityHash64(str.c_str(), str.length());
  char data[17];
  sprintf(data, "%016lx", uint_val);
  *hash_str = string(data);

  return true;
}

}  // namespace util
}  // namespace base
