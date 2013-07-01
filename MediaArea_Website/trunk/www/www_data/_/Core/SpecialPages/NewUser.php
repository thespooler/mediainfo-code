<?php
//-Special case : new.html
if (empty($Page) || $Page=="/" || $Page=="/MediaInfo") {
    header ("Location: ".($IsSecure?"https://":"http://").$_SERVER['HTTP_HOST']."/".$Language."/MediaInfo");
    exit;
}

//-Special case : is a directory
if ($Page{strlen($Page)-1}=="/") {
    $Page=rtrim($Page, "/");
    header ("HTTP/1.1 301 Moved Permanently");
    header ("Location: ".($IsSecure?"https://":"http://").$_SERVER['HTTP_HOST'].$Page);
    exit;
}

?>