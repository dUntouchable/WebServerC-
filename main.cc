#include "common.h"
using namespace std;

Singleton * Singleton::instance = 0;

extern void *Start_server(void *);

void Singleton::add(const string &str1, const string &str2){
//   cout<<"Adding to map "<<str1<<":"<<str2<<endl;
   mymap.insert(pair<string,string>(str1,str2));
}

void Singleton::getMap(){
  map<string,string>::iterator it = mymap.begin();
//  cout<<"getMap call ";
//  for(;it!=mymap.end();++it)
//    cout<<it->first<<" "<<it->second<<endl;
}

void Singleton::update(char * ch){
  answerstring = ch;
//  cout<<answerstring<<endl;
}

char * Singleton::getString(){
   return answerstring;
}

Singleton * Singleton::getInstance(){
  if(!instance)
    instance = new Singleton();
  return instance;
}

map<std::string,std::string> & Singleton::retrieve(){
  return mymap;
}

string & Singleton::getUrl(){
  return url;
}

void Singleton::putUrl(string &u){
  url = u;
}

vector<Str_struct> & Singleton::getText(){
   return text;
}

void Singleton::putText(vector<Str_struct> &txt){
   text = txt;
}

void Singleton::clear(){
  mymap.clear();
  delete[] answerstring;
}


Singleton::~Singleton(){
   delete instance;
   instance = nullptr;
   mymap.clear();
   delete[] answerstring;
   answerstring = nullptr;
   url.clear();
}

int main(int argc, char **argv){

  if(argc!=2){
    cerr<<"Format is: <exe> <port>\n";
    return 1;
  }
  
  Start_server((void *)argv[1]);
  return 0;
}
