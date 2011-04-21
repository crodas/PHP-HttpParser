--TEST--
Test if class exists
--FILE--
<?php
$obj = new HttpParser;
var_dump($obj);
--EXPECTF--
object(httpparser)#%d (%d) {
}
