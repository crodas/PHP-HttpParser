--TEST--
Test if class exists
--FILE--
<?php
class FooParser extends HttpParser
{
    protected function onMessageBegin()
    {
    }

    protected function onHeadersComplete()
    {
    }

    protected function onMessageComplete()
    {
    }

}
$obj = new FooParser;
var_dump($obj);
--EXPECTF--
object(FooParser)#%d (%d) {
  ["status":"httpparser":private]=>
  string(4) "idle"
  ["type":"httpparser":private]=>
  string(7) "unknown"
  ["parts"]=>
  array(0) {
  }
}
