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
}
