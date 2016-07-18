<html><body><h4>Simple Web-server in C++, using library libmicrohttpd and libcurl</h4>
<p>
<li>Enter a URL, and a text to search in the webpage</li>
<li>The result displays all the lines in containing the searched text</li>
<li>libmicrohttpd is a GNU library, and it is used to setup the Web-Server, it handles all the GET/POST from the web-client</li>
<li>And libcurl is a file transfer library, it retrieves the contents of the website to be searched.</li>
<li>HTML Conents are parsed to get simple text lines (lines - that ends with '\n') are stored as string. All the strings, are stored in a vector.</li>
<li>Algorithm: There are two stores for the prased lines. 
<ol><li>In first, first letter of each word is stored, comprising a mnemonic line</li>
<li>In second, the full line is stored.</li>
<li>KMP Search algorithm is used to find the all the matchs through the mnemonics, the matched positions are stored in a vector of int</li>
<li>it is followed with a normal character comparison of the pattern string, starting from the position found in the earlier search</li>
<li>This algorithm has a liner time complexity.</li>
</ol>

</li>
</p>

<br>Command: <br>e.g. ./server 8080

<p><br>Build Command :<br>
g++ -o server -std=c++11 main.cc algo.cc server.cc -I. -I/home/debasis/lab/libmicrohttpd/libmicrohttpd-0.9.50/src/include -L/home/debasis/lab/test_programs/webserver -lmicrohttpd -lcurl -Wl,-rpath /home/debasis/lab/test_programs/webserver
</p>
</body></html>
