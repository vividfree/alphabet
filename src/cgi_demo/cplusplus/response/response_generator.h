// Author: vividfree (vividfree@qq.com)
//  Date : 2017-10-11

#ifndef CGI_DEMO_CPLUSPLUS_RESPONSE_RESPONSE_GENERATOR_H_
#define CGI_DEMO_CPLUSPLUS_RESPONSE_RESPONSE_GENERATOR_H_

#include <string>

namespace Json{
class FastWriter;
}

namespace cgi_demo {

namespace def_struct {
class ResponseParameters;
}

namespace response {

// TODO: need to test whether Json::FastWriter is thread-safe.
class ResponseGenerator {
 public:
  ResponseGenerator();
  ~ResponseGenerator();

  bool Init();
  bool Apply(const def_struct::ResponseParameters& response_params,
             std::string* response_str);
  bool Destroy();

 private:
  bool initialized_;

  Json::FastWriter* writer_;
};

}  // response
}  // cgi_demo

#endif  // CGI_DEMO_CPLUSPLUS_RESPONSE_RESPONSE_GENERATOR_H_
