// Author: vividfree (vividfree@qq.com)
//  Date : 2017-10-11

#ifndef CGI_DEMO_CPLUSPLUS_UTIL_CONFIG_H_
#define CGI_DEMO_CPLUSPLUS_UTIL_CONFIG_H_

// #include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "cgi_demo/cplusplus/util/util.h"

namespace cgi_demo {
namespace util {

class Config
{
  private:
    std::map<std::string, std::string>* p_category_;
    std::map<std::string, std::map<std::string, std::string>* >* p_config_;

  public:
    Config()
    {
      p_category_=NULL;
      p_config_=new std::map<std::string, std::map<std::string, std::string>* >;
    }

    ~Config()
    {
       if (p_config_) {
         for (std::map<std::string, std::map<std::string, std::string>* >::iterator iter=p_config_->begin();
              iter!=p_config_->end(); ++iter) {
           if (iter->second) {
             delete iter->second;
             iter->second = NULL;
           }
         }
         delete p_config_;
         p_config_ = NULL;
       }
       p_category_ = NULL;
    }

    bool init(const std::string& conf_file)
    {
      FILE * fp;
      unsigned long file_size;
      char * pbegin;          // 行开始	
      char * pend;            // 行结束
      char * pvalbegin;       // 有效值开始
      char * pvalend;         // 有效值结束
      char * pdelimiter;	    // 配置项分隔符"="
      char * ptmpbegin;
      char * ptmpend;

      char buf[500];
      sprintf(buf, "Config start load [%s] file", conf_file.c_str());
      std::cout << buf << std::endl;

      fp = fopen(conf_file.c_str(),"r");
      if (fp == NULL) {
        sprintf(buf, "Config [%s] file not exist", conf_file.c_str());
        std::cerr << buf << std::endl;
        return false;
      }
      //将文件内容读入内存
      file_size = get_file_size(fp);
      char * conf_buf_ = (char *)malloc(file_size);
      if (conf_buf_ == NULL) {
        sprintf(buf, "Config [%s] file no content", conf_file.c_str());
        std::cerr << buf << std::endl;
        return false;
      }
      fread(conf_buf_,1,file_size,fp);
      fclose(fp);
      std::map<std::string, std::string>* p_group_ = NULL;
      std::string group_name = "";
      for (pbegin = conf_buf_; pbegin - conf_buf_ < (int64_t)file_size; pbegin = pend + 1) {
        pend = strchr(pbegin,'\n');
        if (pend == NULL) {//最后一行
          pend = conf_buf_ + file_size;
        }
        *pend = '\0';
        //找寻group name
        pdelimiter = strchr(pbegin,'[');
        if (pdelimiter) {
          pvalbegin = ltrim(pbegin,pend);//去左边空格
          pvalend = rtrim(pend,pvalbegin);//去右边空格
          *pvalend = '\0';
          if (*pvalbegin == '[') {
            pdelimiter = strchr(pvalbegin, ']');
            if (pdelimiter) {
              pvalbegin++;
              if (pvalbegin >= pdelimiter) {
                continue;
              }
              ptmpbegin = ltrim(pvalbegin,pdelimiter);
              ptmpend = ltrim(pdelimiter,ptmpbegin);
              if (ptmpbegin >= ptmpend) {
                continue;
              }
              *ptmpend = '\0';
              group_name = std::string(ptmpbegin);
              if (group_name != "") {
                p_group_ = new std::map<std::string, std::string>;
                (*p_config_)[group_name] = p_group_;
              }
            }
          }
          continue;
        }
        //找寻group下对应的key-value pair, key不能为空
        if (p_group_) {
          pdelimiter = strchr(pbegin,'=');
          if (pdelimiter == NULL) {
            continue;
          }
          pvalbegin = ltrim(pbegin,pdelimiter);
          pvalend = rtrim(pdelimiter,pvalbegin);
          if (pvalbegin >= pvalend || *pvalbegin == '#') {//空标识或注释
            continue;
          }
          if (*pvalbegin == '"') {
            pvalbegin++;
          }
          if (*(pvalend-1) == '"') {
            pvalend--;
          }
          if (pvalbegin >= pvalend) {//空标识
            continue;
          }
          *pvalend = '\0';
          std::string key = std::string(pvalbegin);
          pvalbegin = ltrim(pdelimiter+1, pend);
          pvalend = rtrim(pend,pvalbegin);
          std::string value = "";
          if (pvalbegin >= pvalend) {//空标识
            (*p_group_)[key]=value;
            continue;
          }
          if (*pvalbegin == '"') {
            pvalbegin++;
          }
          if (*(pvalend-1) == '"') {
            pvalend--;
          }
          if (pvalbegin >= pvalend) {//空标识
            (*p_group_)[key]=value;
            continue;
          }
          *pvalend = '\0';
          value = std::string(pvalbegin);
          (*p_group_)[key]=value;
        }
      }
      free(conf_buf_);
      conf_buf_ = NULL;

      sprintf(buf, "Config load [%s] file success", conf_file.c_str());
      std::cout << buf << std::endl;
      return true;
    }

    bool uninit()
    {
      char buf[500];
      sprintf(buf, "Config uninit success");
      std::cout << buf << std::endl;
      return true;
    }

    //按group划分并获取相应配置
    bool import_group_config(const std::string & group_name)
    {
      if (p_config_ == NULL) {
        char buf[500];
        sprintf(buf, "config not init");
        std::cerr << buf << std::endl;
        return false;
      }
      std::map<std::string, std::map<std::string, std::string>* >::iterator iter = p_config_->find(group_name);
      if (iter == p_config_->end()) {
        char buf[500];
        sprintf(buf, "Config [%s] group not found", group_name.c_str());
        std::cerr << buf << std::endl;
        return false;
      }
      p_category_ = iter->second;

      char buf[500];
      sprintf(buf, "import [%s] group success", group_name.c_str());
      std::cout << buf << std::endl;
      return true;
    }

    bool get_config(const std::string& key, std::string& value)
    {
      if (p_category_ == NULL) {
        char buf[500];
        sprintf(buf, "Config config for category not init");
        std::cerr << buf << std::endl;
        return false;
      }
      std::map<std::string, std::string>::iterator iter = p_category_->find(key);
      if (iter == p_category_->end()) {
        char buf[500];
        sprintf(buf, "Config [key:%s] not found", key.c_str());
        std::cerr << buf << std::endl;
        return false;
      }
      value = iter->second;
      return true;
    }

    template<typename T>
    bool get_config(const std::string& key, T& value)
    {
      if (p_category_ == NULL) {
        char buf[500];
        sprintf(buf, "Config config for category not init");
        std::cerr << buf << std::endl;
        return false;
      }
      std::map<std::string, std::string>::iterator iter = p_category_->find(key);
      if (iter == p_category_->end()) {
        char buf[500];
        sprintf(buf, "Config [key:%s] not found", key.c_str());
        std::cerr << buf << std::endl;
        return false;
      }
      std::string value_str = iter->second;
      try {
        value=boost::lexical_cast<T>(value_str);
      } catch (boost::bad_lexical_cast& e) {
        char buf[500];
        sprintf(buf, "Config [key:%s=value:%s]", key.c_str(),value_str.c_str());
        std::cerr << buf << std::endl;
        return false;
      }
      return true;
    }

    template<typename T>
    bool get_config(const std::string& key, std::vector<T>& value)
    {
      if (p_category_ == NULL) {
        char buf[500];
        sprintf(buf, "Config config for category not init");
        std::cerr << buf << std::endl;
        return false;
      }
      std::map<std::string, std::string>::iterator iter = p_category_->find(key);
      if (iter == p_category_->end()) {
        char buf[500];
        sprintf(buf, "Config [key:%s] not found", key.c_str());
        std::cerr << buf << std::endl;
        return false;
      }
      std::string value_str = iter->second;
      std::vector<std::string> value_vector;
      boost::algorithm::split(value_vector, value_str, boost::is_any_of(","));
      for (size_t i = 0; i < value_vector.size(); ++i) {
        try {
          value.push_back(boost::lexical_cast<T>(value_vector[i]));
        }catch (boost::bad_lexical_cast& e) {
          char buf[500];
          sprintf(buf, "Config [key:%s=value:%s]", key.c_str(),value_str.c_str());
          std::cerr << buf << std::endl;
          return false;
        }
      }
      return true;
    }
};

}  // util
}  // cgi_demo

#endif  // CGI_DEMO_CPLUSPLUS_UTIL_CONFIG_H_
