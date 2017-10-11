// Author: vividfree (vividfree@qq.com)
//  Date : 2017-10-11

#include <glog/logging.h>
#include <json/json.h>

#include "cgi_demo/cplusplus/def_struct/def_struct.h"
#include "cgi_demo/cplusplus/response/response_generator.h"

using namespace std;

namespace cgi_demo {
namespace response {

ResponseGenerator::ResponseGenerator():
    initialized_(false),
    writer_(NULL) {
}

ResponseGenerator::~ResponseGenerator() {
}

bool ResponseGenerator::Init() {
  if (initialized_) return true;

  writer_ = new Json::FastWriter;
  CHECK(writer_) << "ResponseGenerator::Init() writer_ is NULL";

  initialized_ = true;
  LOG(INFO) << "ResponseGenerator::Init() success";
  return true;
}

bool ResponseGenerator::Destroy() {
  if (!initialized_) return true;

  if (writer_) {
    delete writer_;
    writer_ = NULL;
  }

  initialized_ = false;
  LOG(INFO) << "ResponseGenerator::Destroy() success";
  return true;
}

bool ResponseGenerator::Apply(const def_struct::ResponseParameters& response_params,
                              string* response_str) {
  if (!initialized_) {
    LOG(ERROR) << "ResponseGenerator::Apply() use ResponseGenerator::Init() first";
    return false;
  }

  response_str->clear();

  Json::Value root;
  root["return_code"] = response_params.return_code_;
  root["msg"] = response_params.msg_;

  Json::Value data_detail;
  Json::Value item;
  int count = 0;
  def_struct::VecQueryScorePair::const_iterator iter = response_params.data_.begin();
  for (; iter != response_params.data_.end(); ++iter) {
    item["query"] = iter->first;
    item["score"] = iter->second;
    data_detail.append(item);
    ++count;
  }  // end for
  root["data"]["num"] = count;
  root["data"]["detail"] = data_detail;

  *response_str = writer_->write(root);

  LOG(INFO) << *response_str;

  return true;
}

}  // response
}  // cgi_demo
