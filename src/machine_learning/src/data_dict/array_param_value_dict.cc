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

ArrayParamValueDict::ArrayParamValueDict(const string& model_filename):
    initialized_(false),
    model_filename_(model_filename),
    array_size_(0),
    param_value_array_(NULL) {
}

ArrayParamValueDict::~ArrayParamValueDict() {
}

bool ArrayParamValueDict::Init() {
  if (initialized_) return true;

  bool b_success = LoadData();
  CHECK(b_success) << "ArrayParamValueDict::Init() failed. "
                   << "dict file name [" << model_filename_ << "]";

  initialized_ = true;
  LOG(INFO) << "ArrayParamValueDict::Init() success. "
            << "dict file name [" << model_filename_ << "]";
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
            << "dict file name [" << model_filename_ << "]";
  return true;
}

bool ArrayParamValueDict::GetValueForSingleParam(int index,
                                                 float* value) const {
  *value = 0;
  if (!initialized_) {
    LOG(ERROR) << "ArrayParamValueDict::GetValueForSingleParam() "
               << "use ArrayParamValueDict::Init() first. "
               << "dict file name [" << model_filename_ << "]";
    return false;
  }

  if (index < 0 || index >= array_size_) {
    LOG(ERROR) << "ArrayParamValueDict::GetValueForSingleParam() "
               << "index [" << index << "] not in [0, " << array_size_
               << "). dict file name [" << model_filename_ << "]";
    return false;
  }

  *value = param_value_array_[index];
  return true;
}

bool ArrayParamValueDict::SetValueForSingleParam(int index, float value) {
  if (!initialized_) {
    LOG(ERROR) << "ArrayParamValueDict::SetValueForSingleParam() "
               << "use ArrayParamValueDict::Init() first. "
               << "dict file name [" << model_filename_ << "]";
    return false;
  }

  if (index < 0 || index >= array_size_) {
    LOG(ERROR) << "ArrayParamValueDict::SetValueForSingleParam() "
               << "index [" << index << "] not in [0, " << array_size_
               << "). dict file name [" << model_filename_ << "]";
    return false;
  }

  param_value_array_[index] = value;
  return true;
}

bool ArrayParamValueDict::AddValueForSingleParam(int index, float value) {
  if (!initialized_) {
    LOG(ERROR) << "ArrayParamValueDict::AddValueForSingleParam() "
               << "use ArrayParamValueDict::Init() first. "
               << "dict file name [" << model_filename_ << "]";
    return false;
  }

  if (index < 0 || index >= array_size_) {
    LOG(ERROR) << "ArrayParamValueDict::AddValueForSingleParam() "
               << "index [" << index << "] not in [0, " << array_size_
               << "). dict file name [" << model_filename_ << "]";
    return false;
  }

  param_value_array_[index] += value;
  return true;
}

bool ArrayParamValueDict::LoadData() {
  ifstream fin(model_filename_.c_str());
  if (!fin) {
    CHECK(false) << "Failed to read file:" << model_filename_;
  }

  string line;
  vector<string> items;

  bool b_success = getline(fin, line);
  CHECK(b_success) << "Failed to read the first line in file:"
                   << model_filename_;
  boost::algorithm::trim(line);
  array_size_ = boost::lexical_cast<int>(line);
  CHECK(array_size_ > 0) << "the first line should be the number of parameter,"
                         << " the value [" << line << "] should be larger than"
                         << " 0. dict file name [" << model_filename_ << "]";
  param_value_array_ = new float[array_size_];

  // step 1: 初始化 param_value_array_
  for (int index = 0; index < array_size_; ++index) {
    param_value_array_[index] = 0;
  }  // end for

  // step 2: 读取模型文件给特征赋值
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
                 << "]. dict file name [" << model_filename_ << "]";
      continue;
    }

    int index = boost::lexical_cast<int>(items.at(0));
    if (index < 0 || index >= array_size_) {
      LOG(ERROR) << "ArrayParamValueDict::LoadData() "
                 << "index [" << index << "] not in [0, " << array_size_
                 << "], in line [" << line
                 << "]. dict file name [" << model_filename_ << "]";
      continue;
    } else {
      float value = boost::lexical_cast<float>(items.at(2));
      param_value_array_[index] = value;
    }
  }

  fin.close();
  return true;
}

bool ArrayParamValueDict::GetParamArraySize(int* array_size) const {
  *array_size = 0;
  if (!initialized_) {
    LOG(ERROR) << "ArrayParamValueDict::GetParamArraySize() "
               << "use ArrayParamValueDict::Init() first. "
               << "dict file name [" << model_filename_ << "]";
    return false;
  }

  *array_size = array_size_;
  return true;
}

bool ArrayParamValueDict::DumpModel(const string& output_model_filename) const {
  if (!initialized_) {
    LOG(ERROR) << "ArrayParamValueDict::DumpModel() "
               << "use ArrayParamValueDict::Init() first. "
               << "dict file name [" << model_filename_ << "]";
    return false;
  }

  if (output_model_filename.empty()) {
    LOG(ERROR) << "output_model_filename is empty "
               << "for ArrayParamValueDict::DumpModel()";
    return false;
  }

  ofstream fout(output_model_filename.c_str());
  if (!fout) {
    LOG(ERROR) << "Failed to open file:" << output_model_filename
               << " for ArrayParamValueDict::DumpModel()";
    return false;
  }

  fout << array_size_ << endl;
  for (int index = 0; index < array_size_; ++index) {
    fout << index << "\001\001" << param_value_array_[index] << "\n";
  }  // end for
  fout << endl;

  return true;
}

}  // namespace data_dict
}  // namespace machine_learning
