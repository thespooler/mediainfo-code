<?php
//-Special case : new.html
if (empty($Page) || $Page=="/" || $Page=="/MediaInfo") {
    header ("Location: ".($IsSecure?"https://":"http://").$_SERVER['HTTP_HOST']."/".$Language."/MediaInfo");
    exit;
}

//-Special case : is a directory
if ($Page{strlen($Page)-1}=="/") {
    $Page=rtrim($Page, "/");
    $PathTemp=$_SERVER["SCRIPT_FILENAME"]; $PathTemp=substr($PathTemp, 0, strrpos($PathTemp, "/")); $PathTemp.=$Page;

    header ("HTTP/1.1 301 Moved Permanently");
    if (file_exists($PathTemp))
        header ("Location: ".($IsSecure?"https://":"http://").$_SERVER['HTTP_HOST']); //Should not access it directly
    else
        header ("Location: ".($IsSecure?"https://":"http://").$_SERVER['HTTP_HOST'].$Page);
    exit;
}

?>