// Author: vividfree (vividfree@qq.com)
//  Date : 2015-12-30
// 数据格式: 第1行表明有多少特征，从第2行开始的格式如下
//           parameter_id \001 parameter_name \001 value
//           允许以"#"开头注释某行
//           parameter_id的取值需要小于第1行描述的特征数

#ifndef MACHINE_LEARNING_SRC_DATA_DICT_ARRAY_PARAM_VALUE_DICT_H_
#define MACHINE_LEARNING_SRC_DATA_DICT_ARRAY_PARAM_VALUE_DICT_H_

#include <string>

namespace machine_learning {
namespace data_dict {

class ArrayParamValueDict {
 public:
  explicit ArrayParamValueDict(const std::string& model_filename);
  virtual ~ArrayParamValueDict();

  bool Init();

  bool GetValueForSingleParam(int index, float* value) const;
  bool SetValueForSingleParam(int index, float value);
  bool AddValueForSingleParam(int index, float value);

  bool GetParamArraySize(int* array_size) const;

  bool DumpModel(const std::string& output_model_filename) const;

  bool Destroy();

 private:
  bool LoadData();

  bool initialized_;
  std::string model_filename_;
  int array_size_;
  float* param_value_array_;
};

}  // namespace data_dict
}  // namespace machine_learning

#endif  // MACHINE_LEARNING_SRC_DATA_DICT_ARRAY_PARAM_VALUE_DICT_H_
