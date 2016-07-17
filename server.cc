#include "common.h"
using namespace std;

extern void curlMain();

const char *greetingpage = "<html><body>%s</body></html>";

const char *errorpage = "<html><body>This doesn’t seem to be right.</body></html>";


int send_page (MHD_Connection *connection, const char *page)
{
  int ret;
  MHD_Response *response;
  response = MHD_create_response_from_buffer (strlen (page), (void *) page, MHD_RESPMEM_PERSISTENT);

  if (!response)
    return MHD_NO;

  ret = MHD_queue_response (connection, MHD_HTTP_OK, response);
  MHD_destroy_response (response);
  return ret;
}

int iterate_post (void *coninfo_cls, enum MHD_ValueKind kind, const char *key,
              const char *filename, const char *content_type,
              const char *transfer_encoding, const char *data, uint64_t off,
              size_t size)
{
  connection_info_struct *con_info = (connection_info_struct *) coninfo_cls;

  Singleton *sptr = Singleton::getInstance();

  if(!strcasecmp(key,"weburl"))
    sptr->clear();

  sptr->add(key,data);

//  cout<<"key:"<<key<<endl;

  if(!strcasecmp(key,"textsearch")){
    sptr->getMap();
//    cout<<"Calling curlMain\n";
    curlMain();
  }

  if(!strcasecmp(key,"submit"))
    con_info->answerstring = sptr->getString();

  return MHD_YES;
}

void request_completed (void *cls, MHD_Connection *connection,
                        void **con_cls, enum MHD_RequestTerminationCode toe)
{
  connection_info_struct *con_info = (connection_info_struct *) (*con_cls);
  if (NULL == con_info)
  return;
  if (con_info->connectiontype == POST)
  {
    MHD_destroy_post_processor (con_info->postprocessor);
//    if (con_info->answerstring)
//      delete[] con_info->answerstring;
  }
  delete con_info;
  *con_cls = NULL;
}


int answer_to_connection (void *cls, MHD_Connection *connection,
const char *url, const char *method,
const char *version, const char *upload_data,
size_t *upload_data_size, void **con_cls)
{
  if (NULL == *con_cls)
  {
    connection_info_struct *con_info;
    con_info = new connection_info_struct;
    if (NULL == con_info)
      return MHD_NO;
    con_info->answerstring = NULL;
    if (0 == strcmp (method, "POST"))
    {
//      cout<<"1st POST\n";
      con_info->postprocessor = MHD_create_post_processor (connection, POSTBUFFERSIZE, iterate_post, (void *) con_info);
      if (NULL == con_info->postprocessor)
      {
        delete con_info;
        return MHD_NO;
      }
      con_info->connectiontype = POST;
    }
    else
      con_info->connectiontype = GET;
    *con_cls = (void *) con_info;
    return MHD_YES;
  }
  if (0 == strcmp (method, "GET"))
  {
    ifstream ifile("html1.txt");
    string temp,str;
    while(getline(ifile,temp)){
      str += temp;
      str.push_back('\n');
    }

//    cout<<"Calling send_page from GET\n";
    return send_page (connection, str.c_str());
  }
  if (0 == strcmp (method, "POST"))
  {
//    cout<<"2nd POST\n";
    connection_info_struct *con_info = (connection_info_struct *)(*con_cls);
    if (*upload_data_size != 0)
    {
      MHD_post_process (con_info->postprocessor, upload_data,
                        *upload_data_size);
      *upload_data_size = 0;
      return MHD_YES;
    }
    else if (NULL != con_info->answerstring){
//      cout<<"Calling send_page from 2nd POST\n";
      return send_page (connection, con_info->answerstring);
    }
  }
//  cout<<"Calling send_page from 2nd POST Error Page\n";
  return send_page (connection, errorpage);
}

void Server::start(){

  daemon = MHD_start_daemon (MHD_USE_SELECT_INTERNALLY, port, NULL, NULL,
                            &answer_to_connection, NULL,
                            MHD_OPTION_NOTIFY_COMPLETED, request_completed,
                            NULL, MHD_OPTION_END);
  if (nullptr == daemon)
     cerr<"daemon is null\n";
  cout<<"Web-Server Running!\n";

  while(1){
    sleep(10000);
  }

//  getchar();

}

void *Start_server(void *arg){

 Server server(atoi((char *)arg));
 server.start();

// pthread_exit(NULL);
  
}
/*
int main(int argc, char **argv){
  if(argc!=2){
    cerr<<"Format is : <exe> <port>\n";
    return 1;
  }
  Start_server((void *)argv[1]);
  return 0; 
}
*/
