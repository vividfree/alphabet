// Author: vividfree (vividfree@qq.com)
//  Date : 2017-10-11

#ifndef CGI_DEMO_CPLUSPLUS_REQUEST_REQUEST_CHECKER_H_
#define CGI_DEMO_CPLUSPLUS_REQUEST_REQUEST_CHECKER_H_

#include <string>

#include "cgi_demo/cplusplus/def_struct/def_struct.h"

class FCGX_Request;

namespace cgi_demo {
namespace request {

class RequestChecker {
 public:
  static const unsigned long STDIN_MAX;
  static const char* kRequestMethod;
  static const char* kScriptName;

  static def_struct::ReturnCodeMsg GetQueryStringAndContentIfValid(
      const FCGX_Request& request,
      std::string* request_query_string,
      std::string* request_content);

 private:
  static def_struct::ReturnCodeMsg GetRequestContent(
      const FCGX_Request& request,
      std::string* request_content);
};

}  // request
}  // cgi_demo

#endif  // CGI_DEMO_CPLUSPLUS_REQUEST_REQUEST_CHECKER_H_
