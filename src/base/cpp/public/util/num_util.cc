// Author: vividfree (vividfree@qq.com)
//  Date : 2015-12-30

#include "base/cpp/public/util/num_util.h"

#include <cmath>
#include <iostream>

using namespace std;

namespace base {
namespace util {

bool NumUtil::DoubleToString(double input, string* output) {
  output->clear();

  char data[17];
  int ret_val = sprintf(data, "%.5f", input);
  if (ret_val <= 0) return false;

  *output = string(data);
  return true;
}

bool NumUtil::Sigmoid(float input, float* output) {
  float tmp = exp(-input);
  *output = 1 / (1 + tmp);
  return true;
}

int NumUtil::Sign(float input) {
  const float kEpsilon = 1e-6;
  if (fabs(input) < kEpsilon) return 0;
  return (input > 0) ? 1: -1;
}

}  // namespace util
}  // namespace base
