--TEST--
Test Parsing HTTP Response 
--FILE--
<?php
$string = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nWebserver: Foobar\r\nTransfer-Encoding: chunked\r\n\r\n25\r\nThis is the data in the first chunk\r\n\r\n1C\r\nand this is the second one\r\n\r\n3\r\ncon\r\n8\r\nsequence\r\n0\r\n\r\n";
for ($i=0; $i < 100000; $i++) {
    HttpParser::parseStr($string, false);
}
$parsed = HttpParser::parseStr($string, false);
var_dump($parsed);
--EXPECTF--
array(7) {
  ["header_field"]=>
  array(3) {
    [0]=>
    string(12) "content-type"
    [1]=>
    string(9) "webserver"
    [2]=>
    string(17) "transfer-encoding"
  }
  ["header_value"]=>
  array(3) {
    [0]=>
    string(10) "text/plain"
    [1]=>
    string(6) "Foobar"
    [2]=>
    string(7) "chunked"
  }
  ["body"]=>
  string(76) "This is the data in the first chunk
and this is the second one
consequence"
  ["status_code"]=>
  int(200)
  ["keep-alive"]=>
  bool(true)
  ["version_minor"]=>
  int(1)
  ["version_major"]=>
  int(1)
}
