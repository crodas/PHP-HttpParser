--TEST--
Test if class exists
--FILE--
<?php
class FooParser extends HttpParser
{
    function onMessageBegin()
    {
    }

    function onHeadersComplete()
    {
    }

    function onMessageComplete()
    {
    }

}
$obj = new FooParser;
var_dump($obj);
--EXPECTF--
object(FooParser)#%d (%d) {
}
