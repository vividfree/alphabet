// Author: vividfree (vividfree@qq.com)
//  Date : 2017-10-11

#include "cgi_demo/cplusplus/request/request_parser.h"

#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <glog/logging.h>

using namespace std;

namespace cgi_demo {
namespace request {

def_struct::ReturnCodeMsg RequestParser::Parse(
    const string& query_string,
    const string& content,
    def_struct::RequestParameters* request_params) {
  // step 1 : parse query_string
  map<string, string> param_map;
  def_struct::ReturnCodeMsg return_code_msg = \
      ParseQueryString(query_string, &param_map);
  if (def_struct::SUCCESS != return_code_msg.return_code_) {
    return return_code_msg;
  }

  string key;
  string value;

  vector<string> valid_values;
  bool whether_value_is_valid = false;
  string return_msg;

  {  // "format"
    valid_values.clear();
    whether_value_is_valid = false;
    return_msg.clear();

    key = "format";
    valid_values.push_back("json");
    if (GetValueByKey(param_map, key, &value)) {
      vector<string>::const_iterator iter = valid_values.begin();
      for (; iter != valid_values.end(); ++iter) {
        if (*iter == value) {
          request_params->format_ = value;
          whether_value_is_valid = true;
          break;
        }
      }  // end for
      if (!whether_value_is_valid) {
        return_msg = GenerateMsgForInvalidValue(key, value, valid_values);
        LOG(ERROR) << return_msg;
        return def_struct::ReturnCodeMsg(
            def_struct::INVALID_QUERY_STRING_IN_REQUEST, return_msg);
      }
    } else {
      return_msg = GenerateMsgForMissingKey(key, valid_values);
      LOG(ERROR) << return_msg;
      return def_struct::ReturnCodeMsg(
          def_struct::INVALID_QUERY_STRING_IN_REQUEST, return_msg);
    }
  }

  {  // "is_auto_filter"
    valid_values.clear();
    whether_value_is_valid = false;
    return_msg.clear();

    key = "is_auto_filter";
    valid_values.push_back("0");
    // valid_values.push_back("1");
    if (GetValueByKey(param_map, key, &value)) {
      vector<string>::const_iterator iter = valid_values.begin();
      for (; iter != valid_values.end(); ++iter) {
        if (*iter == value) {
          request_params->is_auto_filter_ = boost::lexical_cast<bool>(value);
          whether_value_is_valid = true;
          break;
        }
      }  // end for
      if (!whether_value_is_valid) {
        return_msg = GenerateMsgForInvalidValue(key, value, valid_values);
        LOG(ERROR) << return_msg;
        return def_struct::ReturnCodeMsg(
            def_struct::INVALID_QUERY_STRING_IN_REQUEST, return_msg);
      }
    } else {
      return_msg = GenerateMsgForMissingKey(key, valid_values);
      LOG(ERROR) << return_msg;
      return def_struct::ReturnCodeMsg(
          def_struct::INVALID_QUERY_STRING_IN_REQUEST, return_msg);
    }
  }

  {  // "source"
    valid_values.clear();
    whether_value_is_valid = false;
    return_msg.clear();

    key = "source";
    valid_values.push_back("test_1");
    valid_values.push_back("test_2");
    if (GetValueByKey(param_map, key, &value)) {
      vector<string>::const_iterator iter = valid_values.begin();
      for (; iter != valid_values.end(); ++iter) {
        if (*iter == value) {
          request_params->source_ = value;
          whether_value_is_valid = true;
          break;
        }
      }  // end for
      if (!whether_value_is_valid) {
        return_msg = GenerateMsgForInvalidValue(key, value, valid_values);
        LOG(ERROR) << return_msg;
        return def_struct::ReturnCodeMsg(
            def_struct::INVALID_QUERY_STRING_IN_REQUEST, return_msg);
      }
    } else {
      return_msg = GenerateMsgForMissingKey(key, valid_values);
      LOG(ERROR) << return_msg;
      return def_struct::ReturnCodeMsg(
          def_struct::INVALID_QUERY_STRING_IN_REQUEST, return_msg);
    }
  }

  {  // "suggestion_num"
    valid_values.clear();
    whether_value_is_valid = false;
    return_msg.clear();

    key = "suggestion_num";
    valid_values.push_back("[1, 20000]");
    if (GetValueByKey(param_map, key, &value)) {
      int tmp_val = boost::lexical_cast<int>(value);
      if (tmp_val >= 0 && tmp_val < 20000) {
        request_params->suggestion_num_ = tmp_val;
      } else {
        return_msg = GenerateMsgForInvalidValue(key, value, valid_values);
        LOG(ERROR) << return_msg;
        return def_struct::ReturnCodeMsg(
            def_struct::INVALID_QUERY_STRING_IN_REQUEST, return_msg);
      }
    } else {
      return_msg = GenerateMsgForMissingKey(key, valid_values);
      LOG(ERROR) << return_msg;
      return def_struct::ReturnCodeMsg(
          def_struct::INVALID_QUERY_STRING_IN_REQUEST, return_msg);
    }
  }

  {  // "type"
    valid_values.clear();
    whether_value_is_valid = false;
    return_msg.clear();

    key = "type";
    valid_values.push_back("type_1");
    if (GetValueByKey(param_map, key, &value)) {
      vector<string>::const_iterator iter = valid_values.begin();
      for (; iter != valid_values.end(); ++iter) {
        if (*iter == value) {
          request_params->type_ = value;
          whether_value_is_valid = true;
          break;
        }
      }  // end for
      if (!whether_value_is_valid) {
        return_msg = GenerateMsgForInvalidValue(key, value, valid_values);
        LOG(ERROR) << return_msg;
        return def_struct::ReturnCodeMsg(
            def_struct::INVALID_QUERY_STRING_IN_REQUEST, return_msg);
      }
    } else {
      return_msg = GenerateMsgForMissingKey(key, valid_values);
      LOG(ERROR) << return_msg;
      return def_struct::ReturnCodeMsg(
          def_struct::INVALID_QUERY_STRING_IN_REQUEST, return_msg);
    }
  }

  // step 2 : parse content for queries
  return ParseContent(content, request_params);
}

def_struct::ReturnCodeMsg RequestParser::ParseQueryString(
    const string& query_string,
    map<string, string>* param_map) {
  param_map->clear();

  vector<string> items;
  boost::algorithm::split(items,
                          query_string,
                          boost::is_any_of("&"));
  vector<string>::const_iterator iter = items.begin();
  for (; iter != items.end(); ++iter) {
    size_t index = iter->find('=');
    if (string::npos == index || 0 == index || (iter->size() - 1) == index) {
      continue;
    }
    string key = iter->substr(0, index);
    string value = iter->substr(index+1);
    (*param_map)[key] = value;
  }  // end for

  if (param_map->empty()) {
    char return_msg[500];
    sprintf(return_msg, "query_string is empty");
    LOG(ERROR) << return_msg;
    return def_struct::ReturnCodeMsg(def_struct::INVALID_REQUEST, return_msg);
  } else {
    return def_struct::ReturnCodeMsg(def_struct::SUCCESS, "");
  }
}

bool RequestParser::GetValueByKey(const map<string, string>& param_map,
                                  const string& key,
                                  std::string* value) {
  value->clear();
  map<string, string>::const_iterator iter = param_map.find(key);
  if (iter == param_map.end()) return false;
  *value = iter->second;
  return true;
}

def_struct::ReturnCodeMsg RequestParser::ParseContent(
    const string& content,
    def_struct::RequestParameters* params) {
  params->queries_.clear();
  vector<string> queries;
  boost::algorithm::split(queries,
                          content,
                          boost::is_any_of("\n"));
  if (queries.empty()) {
    char return_msg[500];
    sprintf(return_msg, "request_content is empty, maybe the frame in POST is empty");
    LOG(ERROR) << return_msg;
    return def_struct::ReturnCodeMsg(def_struct::INVALID_REQUEST, return_msg);
  } else {
    params->queries_ = queries;
    return def_struct::ReturnCodeMsg(def_struct::SUCCESS, "");
  }
}

std::string RequestParser::GenerateMsgForMissingKey(
    const string& key,
    const vector<string>& valid_values) {
  char return_msg[1000];
  string tmp_val = boost::algorithm::join(valid_values, " | ");
  sprintf(return_msg,
          "key [ %s ] does not exist in query_string, valid values are %s",
          key.c_str(),
          tmp_val.c_str());
  return return_msg;
}

std::string RequestParser::GenerateMsgForInvalidValue(
    const string& key,
    const string& real_value,
    const vector<string>& valid_values) {
  char return_msg[1000];
  string tmp_val = boost::algorithm::join(valid_values, " | ");
  sprintf(return_msg,
          "value [ %s ] for key [ %s ] is invalid in query_string, "
          "valid values are %s",
          real_value.c_str(),
          key.c_str(),
          tmp_val.c_str());
  return return_msg;
}

}  // request
}  // cgi_demo
