<?php
//-Special case : new.html
if ($Page=="" || $Page=="/") {
    header("Location: http://".$_SERVER['HTTP_HOST']."/".$Language);
    exit;
}

//-Special case : is a directory
if ($Page{strlen($Page)-1}=="/") {
    $Page=rtrim($Page, "/");
    header ("HTTP/1.1 301 Moved Permanently");
    header ("Location: http://".$_SERVER['HTTP_HOST'].$Page);
    exit;
}
?>