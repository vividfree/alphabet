// Author: vividfree (vividfree@qq.com)
//  Date : 2017-10-11

#include "cgi_demo/cplusplus/def_struct/def_struct.h"

using namespace std;

namespace cgi_demo {
namespace def_struct {

/* class RequestParameters */
RequestParameters::RequestParameters(bool is_auto_filter,
                                     int suggestion_num,
                                     const string& format,
                                     const string& source,
                                     const string& type,
                                     const vector<string>& queries):
    is_auto_filter_(is_auto_filter),
    suggestion_num_(suggestion_num),
    format_(format),
    source_(source),
    type_(type),
    queries_(queries) {
}

RequestParameters::RequestParameters(const RequestParameters& rhs) {
  *this = rhs;
}

RequestParameters& RequestParameters::operator= (const RequestParameters& rhs) {
  is_auto_filter_ = rhs.is_auto_filter_;
  suggestion_num_ = rhs.suggestion_num_;
  format_ = rhs.format_;
  source_ = rhs.source_;
  type_ = rhs.type_;
  queries_ = rhs.queries_;

  return *this;
}

/* class ReturnCodeMsg */
ReturnCodeMsg::ReturnCodeMsg(ReturnCode return_code, const string& msg):
    return_code_(return_code),
    msg_(msg) {
}

ReturnCodeMsg::ReturnCodeMsg(const ReturnCodeMsg& rhs) {
  *this = rhs;
}

ReturnCodeMsg& ReturnCodeMsg::operator= (const ReturnCodeMsg& rhs) {
  return_code_ = rhs.return_code_;
  msg_ = rhs.msg_;

  return *this;
}

/* class ResponseParameters */
ResponseParameters::ResponseParameters(const ReturnCodeMsg& error_msg):
    return_code_(error_msg.return_code_),
    msg_(error_msg.msg_) {
}

ResponseParameters::ResponseParameters(ReturnCode return_code,
                                       const string& msg):
    return_code_(return_code),
    msg_(msg) {
}

ResponseParameters::ResponseParameters(ReturnCode return_code,
                                       const VecQueryScorePair& data):
    return_code_(return_code),
    data_(data) {
}

ResponseParameters::ResponseParameters(ReturnCode return_code,
                                       const string& msg,
                                       const VecQueryScorePair& data):
    return_code_(return_code),
    msg_(msg),
    data_(data) {
}

ResponseParameters::ResponseParameters(const ResponseParameters& rhs) {
  *this = rhs;
}

ResponseParameters& ResponseParameters::operator= (const ResponseParameters& rhs) {
  return_code_ = rhs.return_code_;
  msg_ = rhs.msg_;
  data_ = rhs.data_;

  return *this;
}

}  // def_struct
}  // cgi_demo
