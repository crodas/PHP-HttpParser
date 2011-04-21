--TEST--
Test a POST request with body
--FILE--
<?php
$query = "POST /path/script.cgi HTTP/1.0
From: frog@jmarshall.com
User-Agent: HTTPTool/1.0
Content-Type: application/x-www-form-urlencoded
Content-Length: 32

home=Cosby&favorite+flavor=flies";
for ($i=0; $i < 100000; $i++) {
    HttpParser::parseStr($query);
}
$parsed = HttpParser::parseStr($query);
var_dump($parsed);
--EXPECTF--
array(9) {
  ["url"]=>
  string(16) "/path/script.cgi"
  ["path"]=>
  string(16) "/path/script.cgi"
  ["header_field"]=>
  array(4) {
    [0]=>
    string(4) "From"
    [1]=>
    string(10) "User-Agent"
    [2]=>
    string(12) "Content-Type"
    [3]=>
    string(14) "Content-Length"
  }
  ["header_value"]=>
  array(4) {
    [0]=>
    string(18) "frog@jmarshall.com"
    [1]=>
    string(12) "HTTPTool/1.0"
    [2]=>
    string(33) "application/x-www-form-urlencoded"
    [3]=>
    string(2) "32"
  }
  ["body"]=>
  string(32) "home=Cosby&favorite+flavor=flies"
  ["method"]=>
  string(4) "POST"
  ["keep-alive"]=>
  bool(false)
  ["version_minor"]=>
  int(0)
  ["version_major"]=>
  int(1)
}
