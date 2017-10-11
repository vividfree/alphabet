// Author: vividfree (vividfree@qq.com)
//  Date : 2017-10-11

#ifndef CGI_DEMO_CPLUSPLUS_ENGINE_SUGGESTION_ENGINE_H_
#define CGI_DEMO_CPLUSPLUS_ENGINE_SUGGESTION_ENGINE_H_

#include <string>

class FCGX_Request;

namespace cgi_demo {

namespace def_struct {
class RequestParameters; 
}

namespace response {
class ResponseGenerator; 
}

namespace util {
class Config;
}

namespace engine {

class SuggestionEngine {
 public:
  SuggestionEngine(const std::string& conf_file);
  ~SuggestionEngine();

  bool Init();

  void Apply(const FCGX_Request& request, std::string* response_str) const;

  bool Destroy();

 private:
  bool InitPathMemberVariable();
  bool InitOtherMemberVariable();

  static const char* kStrReadConfLogPrefix;
  static const char* kStrReadConfLogSuffix;

  bool initialized_;

  std::string conf_file_;
  util::Config* config_;

  std::string project_path_root_;

  response::ResponseGenerator* response_generator_;
};

}  // engine
}  // cgi_demo

#endif  // CGI_DEMO_CPLUSPLUS_ENGINE_SUGGESTION_ENGINE_H_
