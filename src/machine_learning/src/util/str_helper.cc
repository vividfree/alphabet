// Author: vividfree (vividfree@qq.com)
//  Date : 2015-12-30

#include "machine_learning/src/util/str_helper.h"

#include <algorithm>
#include <iostream>
#include "base/cpp/thirdparty/boost_1.52.0/include/boost/algorithm/string.hpp"
#include "base/cpp/thirdparty/boost_1.52.0/include/boost/lexical_cast.hpp"

#include "machine_learning/src/util/def_const.h"

using namespace std;

namespace machine_learning {
namespace util {

bool StrHelper::ReplaceDelimeterChar(const string& input, string* output) {
  output->clear();
  const string kNewChar(" ");

  string tmp_str(input);
  boost::algorithm::replace_all(tmp_str, kLevel1Delimeter, kNewChar);
  boost::algorithm::replace_all(tmp_str, kLevel2Delimeter, kNewChar);
  boost::algorithm::replace_all(tmp_str, kLevel3Delimeter, kNewChar);
  boost::algorithm::replace_all(tmp_str, "\t", kNewChar);

  output->swap(tmp_str);
  return true;
}

}  // namespace util
}  // namespace machine_learning
