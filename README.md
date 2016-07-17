<p>Notes:</p>
l<p>Simple Web-server in C++, using library libmicrohttpd and libcurl</p>
<p>1) Enter a URL, and a text to search in the webpage</p>
<p>The result displays all the lines in containing the searched text</p>
<p>Command: e.g. ./server 8080</p>
<hr /><br />Makefile: <br /><br />CC=g++ <br />OPT = -O1 <br />CFLAGS = -std=c++11 <br />DEPS = common.h OBJ = main.o server.o algo.o <br />LDFLAGS = -L/home/debasis/lab/libmicrohttpd/libmicrohttpd-0.9.50/src/microhttpd/.libs -L/home/debasis/lab/curl-7.49.1/lib/.libs <br />INCLUDEDIRS = -I. -I/home/debasis/lab/libmicrohttpd/libmicrohttpd-0.9.50/src/include <br /><br />%.o: %.cc $(DEPS) $(CC) -c -o $@ $&lt; $(OPT) $(CFLAGS) $(INCLUDEDIRS) <br />server: $(OBJ) $(CC) -o $@ $^ $(OPT) $(CFLAGS) $(LDFLAGS) -lmicrohttpd -lcurl <br />PHONY: clean clean: rm server $(OBJ)
<br>
<br><p>ldd ./server<br /> linux-vdso.so.1 =&gt; (0x00007ffd07782000)<br /> libmicrohttpd.so.12 =&gt; /home/debasis/lab/libmicrohttpd/libmicrohttpd-0.9.50/src/microhttpd/.libs/libmicrohttpd.so.12 (0x00007ff0772bc000)<br /> libcurl.so.4 =&gt; /home/debasis/lab/curl-7.49.1/lib/.libs/libcurl.so.4 (0x00007ff077057000)<br /> libstdc++.so.6 =&gt; /usr/lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007ff076d53000)<br /> libgcc_s.so.1 =&gt; /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007ff076b3d000)<br /> libc.so.6 =&gt; /lib/x86_64-linux-gnu/libc.so.6 (0x00007ff076778000)<br /> libgnutls.so.26 =&gt; /usr/lib/x86_64-linux-gnu/libgnutls.so.26 (0x00007ff0764ba000)<br /> libgcrypt.so.11 =&gt; /lib/x86_64-linux-gnu/libgcrypt.so.11 (0x00007ff07623a000)<br /> libpthread.so.0 =&gt; /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007ff07601c000)<br /> libidn.so.11 =&gt; /usr/lib/x86_64-linux-gnu/libidn.so.11 (0x00007ff075de9000)<br /> librtmp.so.0 =&gt; /usr/lib/x86_64-linux-gnu/librtmp.so.0 (0x00007ff075bcf000)<br /> liblber-2.4.so.2 =&gt; /usr/lib/x86_64-linux-gnu/liblber-2.4.so.2 (0x00007ff0759c0000)<br /> libldap_r-2.4.so.2 =&gt; /usr/lib/x86_64-linux-gnu/libldap_r-2.4.so.2 (0x00007ff07576f000)<br /> libz.so.1 =&gt; /lib/x86_64-linux-gnu/libz.so.1 (0x00007ff075556000)<br /> libm.so.6 =&gt; /lib/x86_64-linux-gnu/libm.so.6 (0x00007ff075250000)<br /> /lib64/ld-linux-x86-64.so.2 (0x00007ff0774d5000)<br /> libtasn1.so.6 =&gt; /usr/lib/x86_64-linux-gnu/libtasn1.so.6 (0x00007ff07503c000)<br /> libp11-kit.so.0 =&gt; /usr/lib/x86_64-linux-gnu/libp11-kit.so.0 (0x00007ff074dfa000)<br /> libgpg-error.so.0 =&gt; /lib/x86_64-linux-gnu/libgpg-error.so.0 (0x00007ff074bf5000)<br /> libresolv.so.2 =&gt; /lib/x86_64-linux-gnu/libresolv.so.2 (0x00007ff0749da000)<br /> libsasl2.so.2 =&gt; /usr/lib/x86_64-linux-gnu/libsasl2.so.2 (0x00007ff0747bf000)<br /> libgssapi.so.3 =&gt; /usr/lib/x86_64-linux-gnu/libgssapi.so.3 (0x00007ff074581000)<br /> libffi.so.6 =&gt; /usr/lib/x86_64-linux-gnu/libffi.so.6 (0x00007ff074379000)<br /> libdl.so.2 =&gt; /lib/x86_64-linux-gnu/libdl.so.2 (0x00007ff074175000)<br /> libheimntlm.so.0 =&gt; /usr/lib/x86_64-linux-gnu/libheimntlm.so.0 (0x00007ff073f6c000)<br /> libkrb5.so.26 =&gt; /usr/lib/x86_64-linux-gnu/libkrb5.so.26 (0x00007ff073ce4000)<br /> libasn1.so.8 =&gt; /usr/lib/x86_64-linux-gnu/libasn1.so.8 (0x00007ff073a43000)<br /> libcom_err.so.2 =&gt; /lib/x86_64-linux-gnu/libcom_err.so.2 (0x00007ff07383f000)<br /> libhcrypto.so.4 =&gt; /usr/lib/x86_64-linux-gnu/libhcrypto.so.4 (0x00007ff07360c000)<br /> libroken.so.18 =&gt; /usr/lib/x86_64-linux-gnu/libroken.so.18 (0x00007ff0733f7000)<br /> libwind.so.0 =&gt; /usr/lib/x86_64-linux-gnu/libwind.so.0 (0x00007ff0731ce000)<br /> libheimbase.so.1 =&gt; /usr/lib/x86_64-linux-gnu/libheimbase.so.1 (0x00007ff072fc0000)<br /> libhx509.so.5 =&gt; /usr/lib/x86_64-linux-gnu/libhx509.so.5 (0x00007ff072d77000)<br /> libsqlite3.so.0 =&gt; /usr/lib/x86_64-linux-gnu/libsqlite3.so.0 (0x00007ff072abe000)<br /> libcrypt.so.1 =&gt; /lib/x86_64-linux-gnu/libcrypt.so.1 (0x00007ff072885000)</p>
</article>
</div>
</div>
</div>
</div>
</div>
<div class="container site-footer-container">&nbsp;</div>
