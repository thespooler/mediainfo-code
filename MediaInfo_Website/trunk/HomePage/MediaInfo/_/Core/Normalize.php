<?php
//-Adding .html
if (strlen($Page)==3 || (strlen($Page)==6 && $Page{3}=="-")) {
	if (stristr($_SERVER['HTTP_USER_AGENT'], "macintosh"))
		$Page.="/About_MacAppStore.html";
	else
		$Page.="/About.html";
}
if (strlen($Page)<=6 || $Page{strlen($Page)-5}!=".")
	$Page.=".html";
$Page_Exploded=explode("/", $Page); //first item is always empty

if (!isset($Page_Exploded[1])) {
	//Bad URL, need at least one item
	header ("HTTP/1.1 301 Moved Permanently");
	header ("Location: http://".$_SERVER['HTTP_HOST']."/".$Language);
	exit;
}


 //Test if this is with language
if (strlen($Page_Exploded[1])!=2 && !(strlen($Page_Exploded[1])==5 && $Page_Exploded[1]{2}=="-")) {
	if (!is_file($Path."/en".$Page)) {
		header ("HTTP/1.1 302 Found");
		header("Location: http://".$_SERVER['HTTP_HOST']);
	} else
		header("Location: http://".$_SERVER['HTTP_HOST']."/".$Language.$_SERVER["REQUEST_URI"]); //Adding Language
	exit;
}

$Language=$Page_Exploded[1];
//-Special case : old pages
if (isset($Page_Exploded[2]) && $Page_Exploded[2]=="Help.html") {
	header("Location: http://".$_SERVER['HTTP_HOST']."/".$Language."/Donate", true, 301);
	exit;
}
if (isset($Page_Exploded[2]) && $Page_Exploded[2]=="Price.html") {
	header("Location: http://".$_SERVER['HTTP_HOST']."/".$Language."/Prices", true, 301);
	exit;
}

//-PageFinal - With a page in the good language or english
$PageFinal=$Page;
$PageFinal_Exploded=$Page_Exploded;
$NotUpdated="";
if (!is_file($Path.$PageFinal)) {
	//file in language doesn't exist
	$NotUpdated="Not translated";

	$PageFinal_Exploded[1]="en";
	$PageFinal=implode("/", $PageFinal_Exploded);

	//file exist in English?
	if (!is_file($Path.$PageFinal)) {
		//No file, in language or in English
		header ("HTTP/1.1 301 Moved Permanently");
		header("Location: http://".$_SERVER['HTTP_HOST']);
		exit;
	}
}
?>