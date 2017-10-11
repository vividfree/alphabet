// Author: vividfree (vividfree@qq.com)
//  Date : 2017-10-11

#ifndef CGI_DEMO_CPLUSPLUS_DEF_STRUCT_DEF_STRUCT_H_
#define CGI_DEMO_CPLUSPLUS_DEF_STRUCT_DEF_STRUCT_H_

#include <string>
#include <vector>

namespace cgi_demo {
namespace def_struct {

// class RequestParameters
class RequestParameters {
 public:
  RequestParameters() {}
  RequestParameters(bool is_auto_filter,
                    int suggestion_num,
                    const std::string& format,
                    const std::string& source,
                    const std::string& type,
                    const std::vector<std::string>& queries);
  RequestParameters(const RequestParameters& rhs);
  RequestParameters& operator= (const RequestParameters& rhs);
  virtual ~RequestParameters() {};

  bool is_auto_filter_;
  int suggestion_num_;
  std::string format_;
  std::string source_;
  std::string type_;
  std::vector<std::string> queries_;
};

// enum ReturnCode
enum ReturnCode {
  SUCCESS = 0,
  INVALID_REQUEST = 1,
  INVALID_QUERY_STRING_IN_REQUEST = 2,
};

// class ReturnCodeMsg
class ReturnCodeMsg {
 public:
  ReturnCodeMsg() {}

  ReturnCodeMsg(ReturnCode return_code, const std::string& msg);

  ReturnCodeMsg(const ReturnCodeMsg& rhs);

  ReturnCodeMsg& operator= (const ReturnCodeMsg& rhs);

  virtual ~ReturnCodeMsg() {};

  ReturnCode return_code_;
  std::string msg_;
};

// typedef VecQueryScorePair
typedef std::vector<std::pair<std::string, double> > VecQueryScorePair;

// class ResponseParameters
class ResponseParameters {
 public:
  ResponseParameters() {}

  explicit ResponseParameters(const ReturnCodeMsg& error_msg);

  ResponseParameters(ReturnCode return_code,
                     const std::string& msg);

  ResponseParameters(ReturnCode return_code,
                     const VecQueryScorePair& data);

  ResponseParameters(ReturnCode return_code,
                     const std::string& msg,
                     const VecQueryScorePair& data);

  ResponseParameters(const ResponseParameters& rhs);

  ResponseParameters& operator= (const ResponseParameters& rhs);

  virtual ~ResponseParameters() {};

  ReturnCode return_code_;
  std::string msg_;
  VecQueryScorePair data_;
};

}  // def_struct
}  // cgi_demo

#endif  // CGI_DEMO_CPLUSPLUS_DEF_STRUCT_DEF_STRUCT_H_
