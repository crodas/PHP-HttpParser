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

class CustomParser extends HttpParser 
{
    protected function onMessageBegin()
    {
    }

    protected function onHeadersComplete()
    {
        var_dump($this->parts);
    }

    protected function onMessageComplete()
    {
    }
}

$parser = new CustomParser;

foreach (explode("\r\n", $query) as $line) {
    $parser->parse($line . "\r\n");
}
--EXPECTF--
object(CustomParser)#%d (%d) {
  ["status":"httpparser":private]=>
  string(4) "idle"
  ["type":"httpparser":private]=>
  string(7) "unknown"
  ["parts"]=>
  array(5) {
    ["url"]=>
    string(16) "/path/script.cgi"
    ["path"]=>
    string(16) "/path/script.cgi"
    ["header_field"]=>
    array(4) {
      [0]=>
      string(4) "from"
      [1]=>
      string(10) "user-agent"
      [2]=>
      string(12) "content-type"
      [3]=>
      string(14) "content-length"
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
  }
}
