--TEST--
Test a POST response with chunked body
--FILE--
<?php
require (dirname(__FILE__) . "/chunked.php");
class CustomParser extends HttpParser 
{
    protected $has_body = false;
    protected function onMessageBegin()
    {
        $this->has_body = true;
    }

    protected function onHeadersComplete()
    {
        var_dump($this->getParts());
    }

    protected function onMessageComplete()
    {
        var_dump($this->getBody() === $this->expected_body);
    }
}

$parser = new CustomParser;

list($body, $response)  = get_random_response(); 
list($rheader, $rbody)    = explode("\r\n\r\n", $response, 2);

foreach (explode("\n", $rheader) as $line) {
    $line = trim($line)."\r\n";
    $parser->parse($line);
}
$parser->expected_body = $body;
$parser->parse("\r\n");
$parser->parse($rbody);
--EXPECTF--
array(2) {
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
}
bool(true)
