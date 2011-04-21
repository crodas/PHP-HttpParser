--TEST--
Test Parsing HTTP Response 
--FILE--
<?php
$string = "HTTP/1.1 302 Found
Location: http://www.google.com.py/
Cache-Control: private
Content-Type: text/html; charset=UTF-8
Set-Cookie: PREF=ID=bfbb0039d418b16f:FF=0:TM=1303377851:LM=1303377851:S=2m8PhitCB8pLWZc4; expires=Sat, 20-Apr-2013 09:24:11 GMT; path=/; domain=.google.com
Date: Thu, 21 Apr 2011 09:24:11 GMT
Server: gws
Content-Length: 222
X-XSS-Protection: 1; mode=block
";
for ($i=0; $i < 100000; $i++) {
    HttpParser::parseStr($string, false);
}
$parsed = HttpParser::parseStr($string, false);
var_dump($parsed);
--EXPECTF--
array(6) {
  ["header_field"]=>
  array(8) {
    [0]=>
    string(8) "location"
    [1]=>
    string(13) "cache-control"
    [2]=>
    string(12) "content-type"
    [3]=>
    string(10) "set-cookie"
    [4]=>
    string(4) "date"
    [5]=>
    string(6) "server"
    [6]=>
    string(14) "content-length"
    [7]=>
    string(16) "x-xss-protection"
  }
  ["header_value"]=>
  array(8) {
    [0]=>
    string(25) "http://www.google.com.py/"
    [1]=>
    string(7) "private"
    [2]=>
    string(24) "text/html; charset=UTF-8"
    [3]=>
    string(143) "PREF=ID=bfbb0039d418b16f:FF=0:TM=1303377851:LM=1303377851:S=2m8PhitCB8pLWZc4; expires=Sat, 20-Apr-2013 09:24:11 GMT; path=/; domain=.google.com"
    [4]=>
    string(29) "Thu, 21 Apr 2011 09:24:11 GMT"
    [5]=>
    string(3) "gws"
    [6]=>
    string(3) "222"
    [7]=>
    string(13) "1; mode=block"
  }
  ["status_code"]=>
  int(302)
  ["keep-alive"]=>
  bool(true)
  ["version_minor"]=>
  int(1)
  ["version_major"]=>
  int(1)
}
