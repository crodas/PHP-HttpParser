--TEST--
Test if class exists
--FILE--
<?php
$request = array(
    "POST /some/path HTTP/1.1",
    "Content-Length: 11",
    "",
    "cesar=rodas",
);
$obj = new HttpParser;
$parsed = $obj->parse(implode("\r\n", $request));
var_dump($parsed);
--EXPECTF--
array(8) {
  ["url"]=>
  string(10) "/some/path"
  ["path"]=>
  string(10) "/some/path"
  ["header_field"]=>
  array(1) {
    [0]=>
    string(14) "Content-Length"
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
  ["version_minor"]=>
  int(1)
  ["version_major"]=>
  int(1)
}
