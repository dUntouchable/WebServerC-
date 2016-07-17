# WebServerC-

Notes:
Simple Web-server in C++, using library libmicrohttpd and libcurl
1) Enter a URL, and a text to search in the webpage

The result displays all the lines in containing the searched text

Command:
<exe> <port>
e.g.
./server 8080

-------------------------------------------------------------------------
Makefile:
CC=g++
OPT = -O1
CFLAGS = -std=c++11
DEPS = common.h
OBJ = main.o server.o algo.o
LDFLAGS = -L/home/debasis/lab/libmicrohttpd/libmicrohttpd-0.9.50/src/microhttpd/.libs -L/home/debasis/lab/curl-7.49.1/lib/.libs
INCLUDEDIRS = -I. -I/home/debasis/lab/libmicrohttpd/libmicrohttpd-0.9.50/src/include

%.o: %.cc $(DEPS) 
	$(CC) -c -o $@ $< $(OPT) $(CFLAGS) $(INCLUDEDIRS)

server: $(OBJ)
	$(CC) -o $@ $^ $(OPT) $(CFLAGS) $(LDFLAGS) -lmicrohttpd -lcurl

.PHONY: clean
clean: 
	rm server $(OBJ)

-------------------------------------------------------------------------


ldd ./server
	linux-vdso.so.1 =>  (0x00007ffd07782000)
	libmicrohttpd.so.12 => /home/debasis/lab/libmicrohttpd/libmicrohttpd-0.9.50/src/microhttpd/.libs/libmicrohttpd.so.12 (0x00007ff0772bc000)
	libcurl.so.4 => /home/debasis/lab/curl-7.49.1/lib/.libs/libcurl.so.4 (0x00007ff077057000)
	libstdc++.so.6 => /usr/lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007ff076d53000)
	libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007ff076b3d000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007ff076778000)
	libgnutls.so.26 => /usr/lib/x86_64-linux-gnu/libgnutls.so.26 (0x00007ff0764ba000)
	libgcrypt.so.11 => /lib/x86_64-linux-gnu/libgcrypt.so.11 (0x00007ff07623a000)
	libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007ff07601c000)
	libidn.so.11 => /usr/lib/x86_64-linux-gnu/libidn.so.11 (0x00007ff075de9000)
	librtmp.so.0 => /usr/lib/x86_64-linux-gnu/librtmp.so.0 (0x00007ff075bcf000)
	liblber-2.4.so.2 => /usr/lib/x86_64-linux-gnu/liblber-2.4.so.2 (0x00007ff0759c0000)
	libldap_r-2.4.so.2 => /usr/lib/x86_64-linux-gnu/libldap_r-2.4.so.2 (0x00007ff07576f000)
	libz.so.1 => /lib/x86_64-linux-gnu/libz.so.1 (0x00007ff075556000)
	libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007ff075250000)
	/lib64/ld-linux-x86-64.so.2 (0x00007ff0774d5000)
	libtasn1.so.6 => /usr/lib/x86_64-linux-gnu/libtasn1.so.6 (0x00007ff07503c000)
	libp11-kit.so.0 => /usr/lib/x86_64-linux-gnu/libp11-kit.so.0 (0x00007ff074dfa000)
	libgpg-error.so.0 => /lib/x86_64-linux-gnu/libgpg-error.so.0 (0x00007ff074bf5000)
	libresolv.so.2 => /lib/x86_64-linux-gnu/libresolv.so.2 (0x00007ff0749da000)
	libsasl2.so.2 => /usr/lib/x86_64-linux-gnu/libsasl2.so.2 (0x00007ff0747bf000)
	libgssapi.so.3 => /usr/lib/x86_64-linux-gnu/libgssapi.so.3 (0x00007ff074581000)
	libffi.so.6 => /usr/lib/x86_64-linux-gnu/libffi.so.6 (0x00007ff074379000)
	libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007ff074175000)
	libheimntlm.so.0 => /usr/lib/x86_64-linux-gnu/libheimntlm.so.0 (0x00007ff073f6c000)
	libkrb5.so.26 => /usr/lib/x86_64-linux-gnu/libkrb5.so.26 (0x00007ff073ce4000)
	libasn1.so.8 => /usr/lib/x86_64-linux-gnu/libasn1.so.8 (0x00007ff073a43000)
	libcom_err.so.2 => /lib/x86_64-linux-gnu/libcom_err.so.2 (0x00007ff07383f000)
	libhcrypto.so.4 => /usr/lib/x86_64-linux-gnu/libhcrypto.so.4 (0x00007ff07360c000)
	libroken.so.18 => /usr/lib/x86_64-linux-gnu/libroken.so.18 (0x00007ff0733f7000)
	libwind.so.0 => /usr/lib/x86_64-linux-gnu/libwind.so.0 (0x00007ff0731ce000)
	libheimbase.so.1 => /usr/lib/x86_64-linux-gnu/libheimbase.so.1 (0x00007ff072fc0000)
	libhx509.so.5 => /usr/lib/x86_64-linux-gnu/libhx509.so.5 (0x00007ff072d77000)
	libsqlite3.so.0 => /usr/lib/x86_64-linux-gnu/libsqlite3.so.0 (0x00007ff072abe000)
	libcrypt.so.1 => /lib/x86_64-linux-gnu/libcrypt.so.1 (0x00007ff072885000)
debasis@debasis-All-Series:~/lab/test_programs/webserver$ 

