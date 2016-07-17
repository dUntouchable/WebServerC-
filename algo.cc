#include "common.h"

using namespace std;

static size_t data_write(void* buf, size_t size, size_t nmemb, void* userp)
{
        if(userp)
        {
                ostream& os = *static_cast<ostream*>(userp);
                streamsize len = size * nmemb;
                if(os.write(static_cast<char*>(buf), len))
                        return len;
        }

        return 0;
}

CURLcode curl_read(const string& url, ostream& os, long timeout = 30)
{
        CURLcode code(CURLE_FAILED_INIT);
        CURL* curl = curl_easy_init();

        if(curl)
        {
                if(CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &data_write))
                && CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L))
                && CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L))
                && CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_FILE, &os))
                && CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout))
                && CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_URL, url.c_str())))
                {
                        code = curl_easy_perform(curl);
                }
                curl_easy_cleanup(curl);
        }else{
          cout<<"curl_easy_init return NULL\n";
        }
        return code;
}

// Parse the html file and strip the tags to get simple text
// Each line is stored in structure "Str_struct" in two formats, 
//	1) mnemonic (short form, first letter of each word of the line is stored to make the mnemonic
//		a) The KMPSearch performs a match of the pattern to be found, the position of their occurance is stored
//	2) Entire line is stored.
//		a) The stored position is used to go to the start of the pattern text, and then a normal string comparison is done to find a match.

vector<Str_struct> stripTags(string &html){
 int pos=0;
 vector<Str_struct> text;
 Str_struct ss;
 string full_str, token_str, str_tag;

 bool script_check = true;
  while(pos < html.size()){
    //Check for html tags
    if(html[pos] == '<'){                   // Start of tag
      while(pos < html.size()){
        str_tag.push_back(html[pos]);

        if(html[pos] == '>'){               // End of tag
          // Checks for script tag
          if(!str_tag.compare("<script>"))
            script_check = false;
          if(!str_tag.compare("</script>"))
            script_check = true;
          ++pos;
          str_tag.clear();
          break;     // Tag is over
        }
        else
          ++pos;
      }
    }
    else {
      if(html[pos] == '\n'){
        if(!full_str.empty())
           full_str.push_back(html[pos]); // End of parsing of a line
        if(!token_str.empty())
           token_str.push_back(html[pos]);
        ++pos;

        if(!full_str.empty()){
          ss.full_str = full_str;
          ss.token_str = token_str;
          text.push_back(ss);

          ss.full_str.clear();
          ss.token_str.clear();
        }

        full_str.clear();
        token_str.clear();
      } else {
          if(script_check){
             if(html[pos] != '\t')
               full_str.push_back(html[pos]);

             if(full_str.size()==1 ||
                ((full_str.size()-2 >= 0) && (full_str[full_str.size()-2]==' '))){
               token_str.push_back(tolower(full_str.back()));
             }
          }
          ++pos;
      }
    }
  }
  return text;
}

//prepare the mnemonic of the text search string
string tinystr(const char *ch){
   string str;
   int i=1;
   str.push_back(tolower(ch[0]));
   for(;i<strlen(ch);++i){
     if(ch[i-1] == ' ')
        str.push_back(tolower(ch[i]));
   }
   return str;
}

// Using KMP alogrithm to search the mnemonics
// it has time complexity of O(n+m)

void KMPsetArr (const string & pattern, vector<int> &arr){
  int len = 0;
  int i = 1;
  int pat_size = arr.size();

  arr[0] = 0;
  while(i<pat_size){
    if(pattern[i] == pattern[len]){
      ++len;
      arr[i] = len;
      ++i;
    } else {
      if(len != 0){
        len = arr[len-1];
      } else {
        arr[i] = 0;
        ++i;
      }
    }
  }
}

// The main KMPSearch Algorithm
vector<vector<int>> KMPSearch(const string & pattern, vector<Str_struct> & text){

 int i;
 int pat_size = pattern.size();
 vector<int> arr(pat_size);
 KMPsetArr(pattern, arr);
 vector<vector<int>> pat_match_pos(text.size());

 for(i=0;i<text.size();++i){
   int str_size = text[i].token_str.size();
   if(pat_size > str_size)
     continue;

   int j = 0;  // index for token_str
   int k = 0;  // index for pattern

   while(j < str_size){
     if(pattern[k] == text[i].token_str[j]){
        ++j;
        ++k;
     }
     if(k==pat_size){
       pat_match_pos[i].push_back(j-k);
       k = arr[k-1];
     } else if((j < str_size) && (pattern[k] != text[i].token_str[j])){
       if(k!=0)
         k = arr[k-1];
       else
         ++j;
     }
   }
 }
 return pat_match_pos;
}


// The main function to read the data from POST, process it, 
// prepare the search mnemonic, find the full line, and update the output html file to be populated
// to the web-client
void curlMain(){

  curl_global_init(CURL_GLOBAL_ALL);

  ostringstream oss;
  bool curl_check = false;
  bool url_bool = false;

  Singleton *ptr = Singleton::getInstance();
  map<string,string> mymap = ptr->retrieve();
  string str1 = mymap["weburl"];
  string output_html = "<html><body><h3>Result:</h3><p><br>";
  vector<Str_struct> text;
//  cout<<"weburl:"<<str1<<endl;

  if(ptr->getUrl().empty()){
     url_bool = true;
  } 
  else {
    if(!str1.compare(ptr->getUrl())){
       url_bool = false;
    }
    else {
       url_bool = true;
    }
  }

  if(url_bool){
    if(CURLE_OK == curl_read(str1.c_str(), oss)){
       curl_check = true;
       string html = oss.str();
       text = stripTags(html);

       ptr->putUrl(str1);
       ptr->putText(text);
    }
     else
       curl_check = false;
  }
  else {
      curl_check = true;
      text = ptr->getText();
  }

     
  if(curl_check)   //web page url
  {
    int i;
    string pattern_text = mymap["textsearch"];
    string tiny_pattern_str = tinystr(pattern_text.c_str());         //Text to search

    vector<vector<int>> pat_match_pos = KMPSearch(tiny_pattern_str,text);

//  Search the entire file
    for(i=0;i<text.size();++i){
       if(!pat_match_pos[i].empty()){  // probable Line found
         vector<int> vec = pat_match_pos[i];
         int j;

//       Check the matched position - mnemonic
         for(j=0;j<vec.size();++j){
           bool flag = true;     // If true then full pattern text match found
           int k,pos = vec[j];
           int temp=0,found,pos1=0;

           string full_line_text = text[i].full_str;

           if(pos){
//           find the position in the full text line to start simple char comparison
             while(temp < pos){
               found = full_line_text.find(' ',pos1);
               if(found != std::string::npos){
                 ++temp;
                 pos1 = found + 1;
               }else
                break;
             }
           }

//         start char comparison
           int temp_pos = 0;
           for(;temp_pos < pattern_text.size();++temp_pos){
              if(tolower(full_line_text[pos1+temp_pos]) != tolower(pattern_text[temp_pos])){
                 flag = false;
                 break;
              }
           }

           if(flag){
               output_html += text[i].full_str + "<br>";   // Line to be outputted
//               cout<<text[i].full_str;
               break;
           }
         }
       }
    }
    // Construct the output html
    output_html += "</p><button onclick=\"goBack()\">Go Back</button><br>Click Go Back to search more text<br><script>function goBack() {window.history.back();} </script>";
    output_html += "</body></html>";
    char *cptr = new char[output_html.size()+1];
    memmove(cptr, output_html.c_str(), output_html.size()+1);
    ptr->update(cptr);
//    output_html.clear();
  } 
  else {
     cout<<" curl_read returned not CURLE_OK\n";
  }

   curl_global_cleanup();
}
