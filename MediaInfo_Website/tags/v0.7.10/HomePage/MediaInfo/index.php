<?php
//Variables
if (isset($_COOKIE["LastVisited"]))
 $AlreadyVisited='Y';
//AdditionnalPath
//-Path
if (!isset($_SERVER["SCRIPT_FILENAME"]))
  exit("error");
$Path=$_SERVER["SCRIPT_FILENAME"];
$Path=substr($Path, 0, strrpos($Path, "/"));
//-Page = "/a/b/c"
if (!isset($_SERVER["REQUEST_URI"]))
  exit("error");
$Page=strtok($_SERVER["REQUEST_URI"], "?");
//-Argument
parse_str(strtok("?"), $Argument);
//-Language
if (isset($_SERVER["HTTP_ACCEPT_LANGUAGE"]))
{
 $Language=strtolower(substr($_SERVER["HTTP_ACCEPT_LANGUAGE"], 0, 2));
 if (($Language=="zh" || $Language=="pt") && strlen($_SERVER["HTTP_ACCEPT_LANGUAGE"])>5 && $_SERVER["HTTP_ACCEPT_LANGUAGE"]{2}=="-")
 {
   $Language_Country=strtoupper(substr($_SERVER["HTTP_ACCEPT_LANGUAGE"], 3, 2));
   $Language=$Language."-".$Language_Country;
 } 
}
else
 $Language="en";
//-Special case : new.html
if ($Page=="" || $Page=="/")
{
 header("Location: http://".$_SERVER['HTTP_HOST']."/".$Language);
 exit; 
}
if ($Page=="/Log")
{
 include $Path."/_/ChangeLog.html";
 exit; 
}
//-Special case : is a directory
if ($Page{strlen($Page)-1}=="/")
{
 $Page=rtrim($Page, "/");
 header ("HTTP/1.1 301 Moved Permanently");
 header ("Location: http://".$_SERVER['HTTP_HOST'].$Page);
 exit;
}
//-Adding .html
if (strlen($Page)==3 || (strlen($Page)==6 && $Page{3}=="-"))
 $Page.="/About.html";
if (strlen($Page)<=6 || $Page{strlen($Page)-5}!=".")
 $Page.=".html";
$Page_Exploded=explode("/", $Page); //first item is always empty
//-Official website?
if ($_SERVER["HTTP_HOST"]=="mediainfo.sourceforge.net")
 $Official="Y";
//-Edit?
if (isset($_REQUEST["Edit"]))
 $Edit=$_REQUEST["Edit"];

if (!isset($Page_Exploded[1])) 
{
 //Bad URL, need at least one item
 header ("HTTP/1.1 301 Moved Permanently");
 header ("Location: http://".$_SERVER['HTTP_HOST']."/".$Language);
 exit;
}

//Test if this is with language
if (strlen($Page_Exploded[1])!=2 && !(strlen($Page_Exploded[1])==5 && $Page_Exploded[1]{2}=="-")) 
{
 if (!is_file($Path."/en".$Page))
 {
  header ("HTTP/1.1 302 Found");
  header("Location: http://".$_SERVER['HTTP_HOST']);
 }
 else
  header("Location: http://".$_SERVER['HTTP_HOST']."/".$Language.$_SERVER["REQUEST_URI"]); //Adding Language
 exit;
}
$Language=$Page_Exploded[1];

//-PageFinal - With a page in the good language or english
$PageFinal=$Page;
$PageFinal_Exploded=$Page_Exploded;
$NotUpdated="";
if (!is_file($Path.$PageFinal))
{
 //file in language doesn't exist
 $NotUpdated="Not translated";

 $PageFinal_Exploded[1]="en";
 $PageFinal=implode("/", $PageFinal_Exploded);

 //file exist in English?
 if (!is_file($Path.$PageFinal))
 {
  //No file, in language or in English
  header ("HTTP/1.1 301 Moved Permanently");
  header("Location: http://".$_SERVER['HTTP_HOST']);
  exit;
 }
}

//test subfolder per subfolder : /a/_.html, /a/b/_.html...
include $Path."/_/index.0.html";
$Level=0;
$i=1;
while ($i<10 && isset($PageFinal_Exploded[$i+1]))
{
 $Temp="/";
 for ($j=1; $j<=$i; $j++)
  $Temp.=$Page_Exploded[$j]."/";
 $Menu_Link[$Level]=$Page_Exploded[$i];
 $Temp.="_.html";
 if (file_exists($Path.$Temp))
  include $Path.$Temp;
 else
 {
  //Not found, use english
  $Temp="/";
  for ($j=1; $j<=$i; $j++)
   $Temp.=$PageFinal_Exploded[$j]."/";
  $Temp.="_.html";
  if (file_exists($Path.$Temp))
   include $Path.$Temp;
 }
 $Menu_Link[$Level]=$PageFinal_Exploded[$i];
 $Level++;
 $i++;
}

//Top
$Page_Exploded[1]="";
$Top=implode("/", $Page_Exploded);;
$Top=str_replace("//", "/", $Top);
$Top=str_replace("/About.html", "/", $Top);
$Top=str_replace(".html", "", $Top);

//Contents of the page in a variable
ob_start();
include $Path.$PageFinal;
$Contents = ob_get_contents();
ob_end_clean();

if (!isset($Edit))
{
 //Substring between <title> and </title>
 $Title_Start=strpos($Contents, "<title>");
 if ($Title_Start!==false)
 {
  $Title_End=strpos($Contents, "</title>");
  $Title=substr($Contents, $Title_Start+7, $Title_End-$Title_Start-7);
 }
 else
  $Title="";

 //<link> with CSS
 $Link_Start=strpos($Contents, "<link href=");
 if ($Link_Start!==false)
 {
  $Link_End=strpos($Contents, ".css");
  $Link=substr($Contents, $Link_Start+12, $Link_End-$Link_Start-12);
  $Head_ToAdd=' <link href="/_/CSS/External/'.$Link.'.css" rel="stylesheet" type="text/css" />
';
 }

 //<script> with JavaSript
 $Script_Start=strpos($Contents, "<script src=");
 if ($Script_Start!==false)
 {
  $Script_End=strpos($Contents, ".js");
  $Script=substr($Contents, $Script_Start+13, $Script_End-$Script_Start-13);
  $Head_ToAdd.=' <script src="/_/JavaScript/External/'.$Link.'.js" type="text/javascript"></script>
';
 }

 //Substring between <body> and </body>
 $Body_Start=strpos($Contents, "<body>");
 if ($Body_Start!==false)
 {
  $Body_End=strpos($Contents, "</body>");
  $Contents=substr($Contents, $Body_Start+6, $Body_End-$Body_Start-6);
 }
 else
 {
  //if <body> contains information, filling $Body_Tag too
  $Body_Start=strpos($Contents, "<body ");
  if (!isset($Edit) && $Body_Start!==false)
  {
   $Body_End=strpos($Contents, "</body>");
   $Contents=substr($Contents, $Body_Start+6, $Body_End-$Body_Start-6);
   $Body_Tag_End=strpos($Contents, ">");
   $Body_Tag=substr($Contents, 0, $Body_Tag_End);
   $Contents=substr($Contents, $Body_Tag_End+1);
  }
 }

 if ($NotUpdated=="" && isset($Page_Exploded[$Level+1]) && isset($Updates[$Page_Exploded[$Level+1]]))
  $NotUpdated=$Updates[$Page_Exploded[$Level+1]];
}

if (!isset($Edit))
 include $Path."/_/index.1.html";
echo $Contents;
if (!isset($Edit))
 include $Path."/_/index.9.html";
?>