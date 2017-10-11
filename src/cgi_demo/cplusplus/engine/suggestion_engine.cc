// Author: vividfree (vividfree@qq.com)
//  Date : 2017-10-11

#include "cgi_demo/cplusplus/engine/suggestion_engine.h"

#include <glog/logging.h>

#include "fcgio.h"

#include "cgi_demo/cplusplus/def_struct/def_struct.h"
#include "cgi_demo/cplusplus/request/request_checker.h"
#include "cgi_demo/cplusplus/request/request_parser.h"
#include "cgi_demo/cplusplus/response/response_generator.h"
#include "cgi_demo/cplusplus/util/config.h"
#include "cgi_demo/cplusplus/util/util.h"

using namespace std;

namespace cgi_demo {
namespace engine {

const char* SuggestionEngine::kStrReadConfLogPrefix
    = "SuggestionEngine::Init() read config [";
const char* SuggestionEngine::kStrReadConfLogSuffix
    = "] fail";

SuggestionEngine::SuggestionEngine(const string& conf_file):
    initialized_(false),
    conf_file_(conf_file),
    config_(NULL) {
}

SuggestionEngine::~SuggestionEngine() {
}

bool SuggestionEngine::Init() {
  if (initialized_) return true;

  // init config
  config_ = new util::Config;
  CHECK(config_) << "SuggestionEngine::Init() config_ is NULL";

  CHECK(config_->init(conf_file_)) << 
      "SuggestionEngine::Init() config_.init() fail";

  // read LOG group
  InitPathMemberVariable();

  // read DATA group
  InitOtherMemberVariable();

  initialized_ = true;
  LOG(INFO) << "SuggestionEngine::Init() success";
  return true;
}

bool SuggestionEngine::Destroy() {
  if (!initialized_) return true;

  if (response_generator_) {
    response_generator_->Destroy();
    delete response_generator_;
    response_generator_ = NULL;
  }

  if (config_) {
    delete config_;
    config_ = NULL;
  }

  initialized_ = false;
  LOG(INFO) << "SuggestionEngine::Destroy() success";
  return true;
}

void SuggestionEngine::Apply(const FCGX_Request& request,
                             std::string* response_str) const {
  CHECK(initialized_) <<
      "SuggestionEngine::Apply() use SuggestionEngine::Init() first";

  response_str->clear();

  // step 1 : detect whether request is valid and deal with request
  string request_query_string;
  string request_content;
  def_struct::ReturnCodeMsg return_code_msg = \
      request::RequestChecker::GetQueryStringAndContentIfValid(
          request, &request_query_string, &request_content); 
  if (def_struct::SUCCESS != return_code_msg.return_code_) {
    def_struct::ResponseParameters response_params(return_code_msg);
    response_generator_->Apply(response_params, response_str);
    return;
  }

  def_struct::RequestParameters request_params;
  return_code_msg = \
      request::RequestParser::Parse(
          request_query_string, request_content, &request_params); 
  if (def_struct::SUCCESS != return_code_msg.return_code_) {
    def_struct::ResponseParameters response_params(return_code_msg);
    response_generator_->Apply(response_params, response_str);
    return;
  }

  // step 2 : transfer request to response
  // TODO

  def_struct::VecQueryScorePair return_queries;
  return_queries.push_back(make_pair("test1", 0.9));
  return_queries.push_back(make_pair("test2", 0.7));
  def_struct::ResponseParameters response_params(def_struct::SUCCESS,
                                               return_queries);
  response_generator_->Apply(response_params, response_str);
}

bool SuggestionEngine::InitPathMemberVariable() {
  if (!config_->import_group_config("path")) {
    char buf[500];
    sprintf(buf, "%s path %s", kStrReadConfLogPrefix, kStrReadConfLogSuffix);
    cerr << buf << endl;
    exit(9);
  }

  if (!config_->get_config("project_path_root", project_path_root_)) {
    char buf[500];
    sprintf(buf,
           "%s project_path_root %s",
           kStrReadConfLogPrefix, kStrReadConfLogSuffix);
    cerr << buf << endl;
    exit(9);
  }

  string log_path;
  if (!config_->get_config("log_path", log_path)) {
    char buf[500];
    sprintf(buf,
           "%s log_path %s",
           kStrReadConfLogPrefix, kStrReadConfLogSuffix);
    cerr << buf << endl;
    exit(9);
  }

  FLAGS_log_dir = project_path_root_ + "/" + log_path;
  FLAGS_logbuflevel = -1;  // do not buffer glog INFO message

  cout << "project_path_root [ " << project_path_root_ << " ]" << endl;
  cout << "FLAGS_log_dir [ " << FLAGS_log_dir << " ]" << endl;

  LOG(INFO) << "project_path_root [ " << project_path_root_ << " ]";
  LOG(INFO) << "FLAGS_log_dir [ " << FLAGS_log_dir << " ]";

  return true;
}

bool SuggestionEngine::InitOtherMemberVariable() {
  response_generator_ = new response::ResponseGenerator;
  CHECK(response_generator_) <<
      "SuggestionEngine::InitOtherMemberVariable() response_generator_ is NULL";
  CHECK(response_generator_->Init()) <<
      "SuggestionEngine::InitOtherMemberVariable() response_generator_->Init() failed";

  return true;
}

}  // engine
}  // cgi_demo
