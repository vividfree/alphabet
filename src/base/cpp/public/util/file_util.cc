// Author: vividfree (vividfree@qq.com)
//  Date : 2015-12-30

#include "base/cpp/public/util/file_util.h"

#include <fstream>
#include "base/cpp/thirdparty/boost_1.52.0/include/boost/algorithm/string.hpp"
#include "base/cpp/thirdparty/glog-0.3.3/include/glog/logging.h"

using namespace std;

namespace base {
namespace util {

bool FileUtil::ReadFile(const string& file_name,
                        vector<string>* lines) {
  lines->clear();
  ifstream fin(file_name.c_str());
  if (!fin) {
    LOG(ERROR) << "Failed to read file:" << file_name;
    return false;
  }

  string line;
  while (getline(fin, line)) {
    if (line.empty()) continue;
    boost::algorithm::trim(line);
    lines->push_back(line);
  }

  fin.close();
  return true;
}

}  // namespace util
}  // namespace base
