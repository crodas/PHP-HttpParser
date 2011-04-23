<?php

function get_random_response()
{
    $response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nWebserver: Foobar\r\nTransfer-Encoding: chunked\r\n\r\n";

    $body = '';
    $len  = rand(100000, 200000);
    for ($i=0; $i < $len; $i++) {
        $body .= chr(rand(0, 255));
    }
    for ($i=0; $i < $len; $i += $size) {
        $size = rand(1, 2000 < $len-$i ? 2000 : $len-$i);
        $response .= strtoupper(base_convert($size, 10, 16)) . "\r\n";
        $response .= substr($body, $i, $size) . "\r\n";
    }
    $response .= "0\r\n\r\n";

    return array($body, $response);
}
