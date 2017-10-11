// Author: vividfree (vividfree@qq.com)
//  Date : 2017-10-11

#ifndef CGI_DEMO_CPLUSPLUS_UTIL_UTIL_H_
#define CGI_DEMO_CPLUSPLUS_UTIL_UTIL_H_

#include <cstdio>

#ifndef UNUSED
# define UNUSED(x) (void)x
#endif

namespace cgi_demo {
namespace util {

/*
 *    get_file_size 获得文件大小
 *    @param fp [in]    文件句柄，已经打开，函数会将指针移至文件头
 *    @return 文件大小
 */
unsigned long get_file_size(FILE* fp);

/*
 *    ltrim 去除字符串左边的控制字符及空格
 *    @param ptr [in/out]  字符串的开始指针
 *    @param ptr [in]  字符串的结束指针
 *    @return 字符串左边第一个非控制字符及空格指针
 */
char* ltrim(char* ptr, const char* ptr_end);

/*
 *    ltrim 去除字符串右边的控制字符及空格
 *    @param ptr [in/out]  字符串的结束指针
 *    @param ptr [in]  字符串的开始指针
 *    @return 字符串右边第一个非控制字符及空格指针
 */
char* rtrim(char* ptr, const char* ptr_start);

}  // util
}  // cgi_demo

#endif  // CGI_DEMO_CPLUSPLUS_UTIL_UTIL_H_
