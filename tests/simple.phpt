--TEST--
Simple Parsing
--FILE--
<?php
$request = array(
    "POST /some/path HTTP/1.1",
    "Content-Length: 11",
    "",
    "cesar=rodas",
);
$parsed = HttpParser::parseStr(implode("\r\n", $request));
var_dump($parsed);
--EXPECTF--
array(9) {
  ["url"]=>
  string(10) "/some/path"
  ["path"]=>
  string(10) "/some/path"
  ["header_field"]=>
  array(1) {
    [0]=>
    string(14) "content-length"
  }
  ["header_value"]=>
  array(1) {
    [0]=>
    string(2) "11"
  }
  ["body"]=>
  string(11) "cesar=rodas"
  ["method"]=>
  string(4) "POST"
  ["keep-alive"]=>
  bool(true)
  ["version_minor"]=>
  int(1)
  ["version_major"]=>
  int(1)
}
