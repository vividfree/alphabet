// Author: vividfree (vividfree@qq.com)
//  Date : 2015-12-30

#include "base/cpp/public/util/map_struct_util.h"

#include <algorithm>
#include <iostream>
#include "base/cpp/thirdparty/boost_1.52.0/include/boost/algorithm/string.hpp"
#include "base/cpp/thirdparty/boost_1.52.0/include/boost/lexical_cast.hpp"

#include "base/cpp/public/util/num_util.h"

using namespace std;

namespace base {
namespace util {

bool MapStructUtil::ReadMapDataFromStr(const string& str,
                                       const string& level1_delimeter,
                                       const string& level2_delimeter,
                                       map<string, double>* map_data) {
  map_data->clear();
  string tmp_str(str);
  boost::algorithm::trim(tmp_str);
  if (tmp_str.empty()) return false;

  vector<string> items;
  boost::algorithm::split(items,
                          tmp_str,
                          boost::algorithm::is_any_of(level1_delimeter));
  if (items.empty()) return false;

  vector<string>::const_iterator iter_item = items.begin();
  for (; iter_item != items.end(); ++iter_item) {
    string tmp_substr(*iter_item);
    boost::algorithm::trim(tmp_substr);
    if (tmp_substr.empty()) continue;

    vector<string> sub_items;
    boost::algorithm::split(sub_items,
                            tmp_substr,
                            boost::algorithm::is_any_of(level2_delimeter));
    if (2 != static_cast<int>(sub_items.size())) continue;

    string key(sub_items.at(0));
    string val(sub_items.at(1));
    boost::algorithm::trim(key);
    boost::algorithm::trim(val);
    map_data->insert(make_pair(key, boost::lexical_cast<double>(val)));
  }  // end for

  if (map_data->empty()) return false;
  return true;
}

bool MapStructUtil::InterpolateTwoMap(const map<string, double>& map1,
                                      double map1_weight,
                                      const map<string, double>& map2,
                                      double map2_weight,
                                      map<string, double>* result) {
  result->clear();

  map<string, double>::const_iterator iter = map1.begin();
  for (; iter != map1.end(); ++iter) {
    (*result)[iter->first] = iter->second * map1_weight;
  }
  for (iter = map2.begin(); iter != map2.end(); ++iter) {
    (*result)[iter->first] += iter->second * map2_weight;
  }

  if (result->empty()) return false;
  return true;
}

bool MapStructUtil::NormalizeMap(map<string, double>* map_data) {
  double root_square_sum = 0.0;
  map<string, double>::const_iterator iter = map_data->begin();
  for (; iter != map_data->end(); ++iter) {
    double tmp_val = iter->second;
    if (tmp_val < 0) return false;
    root_square_sum += (tmp_val * tmp_val);
  }

  if (root_square_sum > 0 && fabs(root_square_sum) > 1e-5) {
    root_square_sum = sqrt(root_square_sum);
    map<string, double>::iterator iter2 = map_data->begin();
    for (; iter2 != map_data->end(); ++iter2) {
      iter2->second /= root_square_sum;
    }
    return true;
  } else {
    return false;
  }
}

void MapStructUtil::GetOutputStrForIntMap(
    const map<string, int>& map_data,
    const string& level1_delimeter,
    const string& level2_delimeter,
    string* output_str) {
  output_str->clear();
  if (map_data.empty()) return;

  map<string, int>::const_iterator iter_map = map_data.begin();
  for (; iter_map != map_data.end(); ++iter_map) {
    string key = iter_map->first;
    string val = boost::lexical_cast<string>(iter_map->second);
    (*output_str) += (key + level2_delimeter + val + level1_delimeter);
  }

  //erase the last "kItemDelimiter"
  output_str->erase(output_str->size() - 1, 1);
}

void MapStructUtil::GetOutputStrForDoubleMap(
    const map<string, double>& map_data,
    const string& level1_delimeter,
    const string& level2_delimeter,
    string* output_str) {
  output_str->clear();
  if (map_data.empty()) return;

  map<string, double>::const_iterator iter_map = map_data.begin();
  for (; iter_map != map_data.end(); ++iter_map) {
    string key = iter_map->first;
    string val;
    bool b_success = NumUtil::DoubleToString(iter_map->second, &val);
    if (!b_success) continue;

    (*output_str) += (key + level2_delimeter + val + level1_delimeter);
  }

  //erase the last "kItemDelimiter"
  output_str->erase(output_str->size() - 1, 1);
}

}  // namespace util
}  // namespace base
