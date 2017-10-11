// Author: vividfree (vividfree@qq.com)
//  Date : 2017-10-11

#ifndef CGI_DEMO_CPLUSPLUS_REQUEST_REQUEST_PARSER_H_
#define CGI_DEMO_CPLUSPLUS_REQUEST_REQUEST_PARSER_H_

#include <map>
#include <string>
#include <vector>

#include "cgi_demo/cplusplus/def_struct/def_struct.h"

namespace cgi_demo {

namespace def_struct {
class RequestParameters;
}

namespace request {

class RequestParser {
 public:
  static def_struct::ReturnCodeMsg Parse(
      const std::string& query_string,
      const std::string& content,
      def_struct::RequestParameters* request_params);

 private:
  static def_struct::ReturnCodeMsg ParseQueryString(
      const std::string& query_string,
      std::map<std::string, std::string>* param_map);

  static bool GetValueByKey(const std::map<std::string, std::string>& param_map,
                            const std::string& key,
                            std::string* value);

  static std::string GenerateMsgForMissingKey(
      const std::string& key,
      const std::vector<std::string>& valid_values);

  static std::string GenerateMsgForInvalidValue(
      const std::string& key,
      const std::string& real_value,
      const std::vector<std::string>& valid_values);

  static def_struct::ReturnCodeMsg ParseContent(
      const std::string& content,
      def_struct::RequestParameters* params);
};

}  // request
}  // cgi_demo

#endif  // CGI_DEMO_CPLUSPLUS_REQUEST_REQUEST_PARSER_H_
