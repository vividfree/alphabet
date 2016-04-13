// Author: vividfree (vividfree@qq.com)
//  Date : 2016-04-13

#ifndef MACHINE_LEARNING_SRC_UTIL_MAP_HELPER_H_
#define MACHINE_LEARNING_SRC_UTIL_MAP_HELPER_H_

#include <map>

namespace machine_learning {
namespace util {

template <typename K, typename V>
void TwoMapAddition(const std::map<K, V>& to_add_map,
                    std::map<K, V>* tgt_map);

template <typename K, typename V>
void PrintMap(const std::map<K, V>& map_data);

}  // namespace util
}  // namespace machine_learning

#endif  // MACHINE_LEARNING_SRC_UTIL_MAP_HELPER_H_
