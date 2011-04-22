--TEST--
Test Parsing HTTP Chunked Responses with large body
--FILE--
<?php
$response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nWebserver: Foobar\r\nTransfer-Encoding: chunked\r\n\r\n";

/* random body */
$body = '';
$len  = rand(1000000, 2000000);
for ($i=0; $i < $len; $i++) {
    $body .= chr(rand(1, 255));
}

for ($i=0; $i < $len; $i += $size) {
    $size = rand(1, 2000 < $len-$i ? 2000 : $len-$i);
    $response .= strtoupper(base_convert($size, 10, 16)) . "\r\n";
    $response .= substr($body, $i, $size) . "\r\n";
}
$response .= "0\r\n\r\n";


var_dump($i == $len);
$parsed = HttpParser::parseStr($response, false);
var_dump($parsed['body'] === $body);
--EXPECTF--
bool(true)
bool(true)
