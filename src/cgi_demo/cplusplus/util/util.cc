// Author: vividfree (vividfree@qq.com)
//  Date : 2017-10-11

#include "cgi_demo/cplusplus/util/util.h"

namespace cgi_demo {
namespace util {

unsigned long get_file_size(FILE* fp) {
  unsigned long file_size;
  fseeko(fp,0,SEEK_END);
  file_size=ftello(fp);
  rewind(fp);
  return file_size;
}

char* ltrim(char* ptr, const char* ptr_end) {
  while ((unsigned char)*ptr <= 32 && ptr < ptr_end) {
    ptr++;
  }
  return ptr;
}

char* rtrim(char* ptr, const char* ptr_start) {
  while ((unsigned char)*(ptr-1) <= 32 && ptr > ptr_start) {
    ptr--;
  }
  return ptr;
}

}  // util
}  // cgi_demo
