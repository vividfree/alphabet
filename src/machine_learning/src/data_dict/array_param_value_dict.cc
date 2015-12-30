// Author: vividfree (vividfree@qq.com)
//  Date : 2015-12-30

#include "machine_learning/src/data_dict/array_param_value_dict.h"

#include <fstream>
#include <iostream>
#include <vector>
#include "base/cpp/thirdparty/boost_1.52.0/include/boost/algorithm/string.hpp"
#include "base/cpp/thirdparty/boost_1.52.0/include/boost/lexical_cast.hpp"
#include "base/cpp/thirdparty/glog-0.3.3/include/glog/logging.h"

using namespace std;

namespace machine_learning {
namespace data_dict {

ArrayParamValueDict::ArrayParamValueDict(const string& file_name):
    initialized_(false),
    file_name_(file_name),
    array_size_(0),
    param_value_array_(NULL) {
}

ArrayParamValueDict::~ArrayParamValueDict() {
}

bool ArrayParamValueDict::Init() {
  if (initialized_) return true;

  bool b_success = LoadData();
  CHECK(b_success) << "ArrayParamValueDict::Init() failed. "
                   << "dict file name [" << file_name_ << "]";

  initialized_ = true;
  LOG(INFO) << "ArrayParamValueDict::Init() success. "
            << "dict file name [" << file_name_ << "]";
  return true;
}

bool ArrayParamValueDict::Destroy() {
  if (!initialized_) return true;

  if (param_value_array_) {
    delete[] param_value_array_;
    param_value_array_ = NULL;
  }

  initialized_ = false;
  LOG(INFO) << "ArrayParamValueDict::Destory() success. "
            << "dict file name [" << file_name_ << "]";
  return true;
}

bool ArrayParamValueDict::GetValueForSingleParam(int index,
                                                 float* value) const {
  *value = 0;
  if (!initialized_) {
    LOG(ERROR) << "ArrayParamValueDict::GetValueForSingleParam() "
               << "use ArrayParamValueDict::Init() first. "
               << "dict file name [" << file_name_ << "]";
    return false;
  }

  if (index < 0 || index >= array_size_) {
    LOG(ERROR) << "ArrayParamValueDict::GetValueForSingleParam() "
               << "index [" << index << "] not in [0, " << array_size_
               << "). dict file name [" << file_name_ << "]";
    return false;
  }

  *value = param_value_array_[index];
  return true;
}

bool ArrayParamValueDict::SetValueForSingleParam(int index, float value) {
  if (!initialized_) {
    LOG(ERROR) << "ArrayParamValueDict::SetValueForSingleParam() "
               << "use ArrayParamValueDict::Init() first. "
               << "dict file name [" << file_name_ << "]";
    return false;
  }

  if (index < 0 || index >= array_size_) {
    LOG(ERROR) << "ArrayParamValueDict::SetValueForSingleParam() "
               << "index [" << index << "] not in [0, " << array_size_
               << "). dict file name [" << file_name_ << "]";
    return false;
  }

  param_value_array_[index] = value;
  return true;
}

bool ArrayParamValueDict::AddValueForSingleParam(int index, float value) {
  if (!initialized_) {
    LOG(ERROR) << "ArrayParamValueDict::AddValueForSingleParam() "
               << "use ArrayParamValueDict::Init() first. "
               << "dict file name [" << file_name_ << "]";
    return false;
  }

  if (index < 0 || index >= array_size_) {
    LOG(ERROR) << "ArrayParamValueDict::AddValueForSingleParam() "
               << "index [" << index << "] not in [0, " << array_size_
               << "). dict file name [" << file_name_ << "]";
    return false;
  }

  param_value_array_[index] += value;
  return true;
}

bool ArrayParamValueDict::LoadData() {
  ifstream fin(file_name_.c_str());
  if (!fin) {
    CHECK(false) << "Failed to read file:" << file_name_;
  }

  string line;
  vector<string> items;

  bool b_success = getline(fin, line);
  CHECK(b_success) << "Failed to read the first line in file:" << file_name_;
  boost::algorithm::trim(line);
  array_size_ = boost::lexical_cast<int>(line);
  CHECK(array_size_ > 0) << "the first line should be the number of parameter,"
                         << " the value [" << line << "] should be larger than"
                         << " 0. dict file name [" << file_name_ << "]";
  param_value_array_ = new float[array_size_];

  while (getline(fin, line)) {
    if (line.empty() || '#' == line.at(0)) continue;
    items.clear();
    boost::algorithm::trim(line);
    boost::algorithm::split(items,
                            line,
                            boost::algorithm::is_any_of("\001"));
    if (3 != static_cast<int>(items.size())) {
      LOG(ERROR) << "ArrayParamValueDict::LoadData() "
                 << "item size not 3 in line [" << line
                 << "]. dict file name [" << file_name_ << "]";
      continue;
    }

    int index = boost::lexical_cast<int>(items.at(0));
    if (index < 0 || index >= array_size_) {
      LOG(ERROR) << "ArrayParamValueDict::LoadData() "
                 << "index [" << index << "] not in [0, " << array_size_
                 << "], in line [" << line
                 << "]. dict file name [" << file_name_ << "]";
      continue;
    } else {
      float value = boost::lexical_cast<float>(items.at(2));
      param_value_array_[index] = value;
    }
  }

  fin.close();
  return true;
}

int ArrayParamValueDict::GetParamArraySize() const {
  return array_size_;
}

}  // namespace data_dict
}  // namespace machine_learning
