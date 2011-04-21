--TEST--
Testing Invalid HTTP
--FILE--
<?php
$query = "GET foo/bar BARBARBAR";
$parsed = HttpParser::parseStr($query);
--EXPECTF--
Fatal error: Uncaught exception 'httpparser_exception' with message 'Error while parsing HTTP at char %d' in %s/invalid.php:%d
Stack trace:
#0 %s/invalid.php(%d): httpparser::parseStr('%s')
#1 {main}
  thrown in %s/invalid.php on line %d
