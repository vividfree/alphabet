// Author: vividfree (vividfree@qq.com)
//  Date : 2016-04-13

#include "machine_learning/src/util/map_helper.h"

#include "base/cpp/thirdparty/glog-0.3.3/include/glog/logging.h"

namespace machine_learning {
namespace util {

template <typename K, typename V>
void TwoMapAddition(const std::map<K, V>& to_add_map,
                    std::map<K, V>* tgt_map) {
  typedef typename std::map<K,V>::const_iterator MapIterator;
  for (MapIterator iter = to_add_map.begin();
       iter != to_add_map.end();
       ++iter) {
    (*tgt_map)[iter->first] += iter->second;
  }  // end for
}

template <typename K, typename V>
void PrintMap(const std::map<K, V>& map_data) {
  typedef typename std::map<K,V>::const_iterator MapIterator;
  for (MapIterator iter = map_data.begin(); iter != map_data.end(); ++iter) {
    LOG(INFO) << "Key: " << iter->first << " "
              << "Value: " << iter->second << std::endl;
  }  // end for
}

}  // namespace util
}  // namespace machine_learning
