// Author: vividfree (vividfree@qq.com)
//  Date : 2017-10-11

#include <cstdlib>
#include <glog/logging.h>

#include "fcgio.h"

#include "cgi_demo/cplusplus/request/request_checker.h"

using namespace std;

namespace cgi_demo {
namespace request {

const unsigned long RequestChecker::STDIN_MAX = 1000000;

const char* RequestChecker::kRequestMethod = "POST";
const char* RequestChecker::kScriptName = "/cgi_demo";

def_struct::ReturnCodeMsg RequestChecker::GetQueryStringAndContentIfValid(
    const FCGX_Request& request,
    string* request_query_string,
    string* request_content) {
  request_query_string->clear();
  request_content->clear();

  // step 1: check whether request is valid
  const char* request_method = FCGX_GetParam("REQUEST_METHOD", request.envp);
  if (0 != strcmp(request_method, kRequestMethod)) {
    char return_msg[500];
    sprintf(return_msg,
            "request_method should be [ %s ], but its real value is [ %s ]",
            kRequestMethod,
            request_method);
    LOG(ERROR) << return_msg;
    return def_struct::ReturnCodeMsg(def_struct::INVALID_REQUEST, return_msg);
  }

  const char* script_name = FCGX_GetParam("SCRIPT_NAME", request.envp);
  if (0 != strcmp(script_name, kScriptName)) {
    char return_msg[500];
    sprintf(return_msg,
            "script_name should be [ %s ], but its real value is [ %s ]",
            kScriptName,
            script_name);
    LOG(ERROR) << return_msg;
    return def_struct::ReturnCodeMsg(def_struct::INVALID_REQUEST, return_msg);
  }

  // step 2: get query_string
  *request_query_string = string(FCGX_GetParam("QUERY_STRING", request.envp));

  // step 3: get content
  def_struct::ReturnCodeMsg return_code_msg = \
      GetRequestContent(request, request_content);
  return return_code_msg;
}

/**
 * Note this is not thread safe due to the static allocation of the
 * content_buffer.
 */
def_struct::ReturnCodeMsg RequestChecker::GetRequestContent(
    const FCGX_Request& request,
    string* request_content) {
  request_content->clear();
  char* content_length_str = FCGX_GetParam("CONTENT_LENGTH", request.envp);
  unsigned long content_length = STDIN_MAX;

  if (content_length_str) {
    content_length = strtol(content_length_str, &content_length_str, 10);
    if (*content_length_str) {
      char return_msg[500];
      sprintf(return_msg,
              "Can't Parse 'CONTENT_LENGTH='%s'. Consuming stdin up to %ld",
              FCGX_GetParam("CONTENT_LENGTH", request.envp),
              STDIN_MAX);
      LOG(ERROR) << return_msg;
      return def_struct::ReturnCodeMsg(def_struct::INVALID_REQUEST, return_msg);
    }

    if (content_length > STDIN_MAX) {
      content_length = STDIN_MAX;
    }
  } else {
      // Do not read from stdin if CONTENT_LENGTH is missing
    content_length = 0;
  }

  char * content_buffer = new char[content_length];
  cin.read(content_buffer, content_length);
  content_length = cin.gcount();

  // Chew up any remaining stdin - this shouldn't be necessary
  // but is because mod_fastcgi doesn't handle it correctly.
  // ignore() doesn't set the eof bit in some versions of glibc++
  // so use gcount() instead of eof()...
  do cin.ignore(1024); while (cin.gcount() == 1024);

  *request_content = string(content_buffer, content_length);
  delete [] content_buffer;

  if (0 == request_content->length()) {
    char return_msg[500];
    sprintf(return_msg, "request_content is empty, maybe the frame in POST is empty");
    LOG(ERROR) << return_msg;
    return def_struct::ReturnCodeMsg(def_struct::INVALID_REQUEST, return_msg);
  }

  return def_struct::ReturnCodeMsg(def_struct::SUCCESS, "");
}

}  // request
}  // cgi_demo
