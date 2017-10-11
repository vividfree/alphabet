// Author: vividfree (vividfree@qq.com)
//  Date : 2017-10-11

#include <cstdlib>
#include <iostream>
#include <string>

#include <glog/logging.h>

#include "fcgio.h"

#include "cgi_demo/cplusplus/engine/suggestion_engine.h"

using namespace std;
using namespace cgi_demo;

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);

  if (2 != argc) {
    cerr << "Usage: cgi_demo conf_file" << endl;
    exit(9);
  }

  engine::SuggestionEngine suggestion_engine(argv[1]);
  suggestion_engine.Init();

  // Backup the stdio streambufs
  streambuf * cin_streambuf  = cin.rdbuf();
  streambuf * cout_streambuf = cout.rdbuf();
  streambuf * cerr_streambuf = cerr.rdbuf();

  FCGX_Request request;

  FCGX_Init();
  FCGX_InitRequest(&request, 0, 0);

  while (FCGX_Accept_r(&request) == 0) {
    fcgi_streambuf cin_fcgi_streambuf(request.in);
    fcgi_streambuf cout_fcgi_streambuf(request.out);
    fcgi_streambuf cerr_fcgi_streambuf(request.err);

    cin.rdbuf(&cin_fcgi_streambuf);
    cout.rdbuf(&cout_fcgi_streambuf);
    cerr.rdbuf(&cerr_fcgi_streambuf);

    string response_str;
    suggestion_engine.Apply(request, &response_str);

    // Output response_str to cout to finish current request
    // Content-type: text/plain is also OK for output response_str
    cout << "Content-type: application/json\n\n"
         << response_str << endl;

    // Note: the fcgi_streambuf destructor will auto flush
  }

  // restore stdio streambufs
  cin.rdbuf(cin_streambuf);
  cout.rdbuf(cout_streambuf);
  cerr.rdbuf(cerr_streambuf);

  return 0;
}
