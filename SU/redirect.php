<?php
require_once 'libs/functions.inc';

$target = $_GET['tg'];

$url = is_code_found($target);

if($url !== FALSE){
    header("Location: $url");
}else{
    header("HTTP 1.1/404 Not found.");
    print '<h1>404 ERROR !! URL is not found.</h1>';
}



?>