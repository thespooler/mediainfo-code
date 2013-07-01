<?php

//HTTP
header("Cache-Control: no-cache, must-revalidate, max-age=0");

//HTTPS detection
if (isset($_SERVER['HTTPS'])) 
{
	if ($_SERVER['HTTPS'] == 'on')
        $IsSecure=1;
	else
        $IsSecure=0;
}
else
    $IsSecure=0;

//User config
if (isset($_COOKIE["Language"]))
    $Language=$_COOKIE["Language"];
if (isset($_COOKIE["LastVisited"]))
    $AlreadyVisited='Y';
if (isset($_COOKIE["Donated"]))
    $Donated=$_COOKIE["Donated"]; //time()
if (isset($_COOKIE["NewVersionRequested"]))
    $NewVersionRequested='Y';
if (isset($_SERVER['HTTP_REFERER']) && strpos($_SERVER['HTTP_REFERER'], "/Log")+4==strlen($_SERVER['HTTP_REFERER']))
    $NoStats='Y';

//Page = "/a/b/c"
if (!isset($_SERVER["REQUEST_URI"]))
    exit("error");
$Page=strtok($_SERVER["REQUEST_URI"], "?");
parse_str(strtok("?"), $Argument);

//Language modification
if (!isset($Language)) {
    if (isset($_SERVER["HTTP_ACCEPT_LANGUAGE"])) {
        $Language=strtolower(substr($_SERVER["HTTP_ACCEPT_LANGUAGE"], 0, 2));
        if (($Language=="zh" || $Language=="pt") && strlen($_SERVER["HTTP_ACCEPT_LANGUAGE"])>5 && $_SERVER["HTTP_ACCEPT_LANGUAGE"]{2}=="-") {
            $Language_Country=strtoupper(substr($_SERVER["HTTP_ACCEPT_LANGUAGE"], 3, 2));
            $Language=$Language."-".$Language_Country;
        }
    } else
        $Language="en";
}

//Official website?
if ($_SERVER["HTTP_HOST"]=="mediaarea.net")
    $Official="Y";

//Edit?
if (isset($_REQUEST["Edit"]))
    $Edit=$_REQUEST["Edit"];
?>