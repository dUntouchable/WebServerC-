<html><body><h4>Simple Web-server in C++, using library libmicrohttpd and libcurl</h4>
<p><li>Enter a URL, and a text to search in the webpage</li>
<li>The result displays all the lines in containing the searched text</li></p>

<br>Command: <br>e.g. ./server 8080

<p><br>Build Command :<br>
g++ -o server -std=c++11 main.cc algo.cc server.cc -I. -I/home/debasis/lab/libmicrohttpd/libmicrohttpd-0.9.50/src/include -L/home/debasis/lab/test_programs/webserver -lmicrohttpd -lcurl -Wl,-rpath /home/debasis/lab/test_programs/webserver
</p>
</body></html>
