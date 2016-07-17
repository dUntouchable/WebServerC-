#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <microhttpd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
//#include <pthread.h>
#include <curl/curl.h>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <map>


#define POSTBUFFERSIZE 512
#define MAXNAMESIZE 512
#define MAXANSWERSIZE 512
#define GET 0
#define POST 1

struct connection_info_struct
{
  int connectiontype;
  char *answerstring;
  MHD_PostProcessor *postprocessor;
};

struct Str_struct{
  std::string token_str;
  std::string full_str;
};

// Server class to start the web-server
class Server{
 public:
 Server(int p):port(p),daemon(nullptr){}
 ~Server(){
   MHD_stop_daemon (daemon);
 }
 void start();

 private:
  MHD_Daemon *daemon;
  int port;
};

// Singleton class to share data during sessions and files
class Singleton{
public:
  void add(const std::string &, const std::string &);
  void update(char *);
  char * getString();
  static Singleton * getInstance();
  std::map<std::string,std::string> & retrieve();
  std::string & getUrl();
  void putUrl(std::string &);
  std::vector<Str_struct> & getText();
  void putText(std::vector<Str_struct> &);
  void clear();
  void getMap();

  ~Singleton();

 private:
   Singleton():answerstring(nullptr){}
   static Singleton *instance;
   std::map<std::string,std::string> mymap;
   char *answerstring;
   std::string url;
   std::vector<Str_struct> text;
};
