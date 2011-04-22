--TEST--
Test Parsing HTTP Chunked Responses with large body
--FILE--
<?php
require(dirname(__FILE__) . "/chunked.php");
list($body, $http) = get_random_response();
$parsed = HttpParser::parseStr($http, false);
var_dump($parsed['body'] === $body);
--EXPECTF--
bool(true)
