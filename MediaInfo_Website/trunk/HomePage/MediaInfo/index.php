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


 //OS detection
   if (stristr($_SERVER['HTTP_USER_AGENT'], "macintosh"))
 {
  $Version='0.7.14'; //Mac OS X
  $Link='http://downloads.sourceforge.net/mediainfo/MediaInfo_GUI_'.$Version.'_Mac_10.5_Universal.dmg';
  $OS='Mac OS X 10.5 (Leopard), Universal';
  $Installer=true;
  $Size='3.6';
 }
 else if (stristr($_SERVER['HTTP_USER_AGENT'], "linux"))
 {
    if (stristr($_SERVER['HTTP_USER_AGENT'], "debian"))
  {
        if (stristr($_SERVER['HTTP_USER_AGENT'], "etch"))       $OS='Debian_4';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "lenny"))      $OS='Debian_5';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "sid"))        $OS='Debian_5';


        if (stristr($_SERVER['HTTP_USER_AGENT'], "i386"))       $CPU='i386';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "i486"))       $CPU='i386';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "i586"))       $CPU='i386';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "i686"))       $CPU='i386';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "x86_64"))     $CPU='amd64';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "amd64"))      $CPU='amd64';

   if (isset($OS) and isset($CPU))
   {
    $Link=$Language.'/Download#'.$OS.'.'.$CPU;
         if ($Link==$Language.'/Download#Debian_4.i386')                   $Version='0.7.15';
    else if ($Link==$Language.'/Download#Debian_4.amd64')                  $Version='0.7.15';
    else if ($Link==$Language.'/Download#Debian_5.i386')                   $Version='0.7.15';
    else if ($Link==$Language.'/Download#Debian_5.amd64')                  $Version='0.7.15';
         if ($OS=='Ubuntu_7.10')                                $OS='Debian 4 (Etch)';
    else if ($OS=='Ubuntu_8.04')                                $OS='Debian 5 (Lenny)';
    $OS=$OS.', '.$CPU;
   }
   else
   {
    $Version='0.7.15'; //Debian
    $Link=$Language.'/Download#Debian';
    $OS='Debian';
   }
   $Size='2';
  }
  else if (stristr($_SERVER['HTTP_USER_AGENT'], "ubuntu"))
  {
        if (stristr($_SERVER['HTTP_USER_AGENT'], "warty"))      $OS='Ubuntu_7.10';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "4.10"))       $OS='Ubuntu_7.10';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "hoary"))      $OS='Ubuntu_7.10';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "5.04"))       $OS='Ubuntu_7.10';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "breezy"))     $OS='Ubuntu_7.10';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "5.10"))       $OS='Ubuntu_7.10';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "dapper"))     $OS='Ubuntu_7.10';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "6.06"))       $OS='Ubuntu_7.10';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "dapper"))     $OS='Ubuntu_7.10';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "6.10"))       $OS='Ubuntu_7.10';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "edgy"))       $OS='Ubuntu_7.10';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "7.04"))       $OS='Ubuntu_7.10';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "gusty"))      $OS='Ubuntu_7.10';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "7.10"))       $OS='Ubuntu_7.10';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "hardy"))      $OS='Ubuntu_8.04';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "8.04"))       $OS='Ubuntu_8.04';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "intrepid"))   $OS='Ubuntu_8.10';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "8.10"))       $OS='Ubuntu_8.10';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "jaunty"))     $OS='Ubuntu_9.04';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "9.04"))       $OS='Ubuntu_9.04';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "karmik"))     $OS='Ubuntu_9.04';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "9.10"))       $OS='Ubuntu_9.04';

     if (stristr($_SERVER['HTTP_USER_AGENT'], "i386"))          $CPU='i386';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "i486"))       $CPU='i386';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "i586"))       $CPU='i386';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "i686"))       $CPU='i386';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "x86_64"))     $CPU='amd64';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "amd64"))      $CPU='amd64';

   if (isset($OS) and isset($CPU))
   {
    $Link=$Language.'/Download#'.$OS.'.'.$CPU;
         if ($Link==$Language.'/Download#Ubuntu_7.10.i386')                $Version='0.7.15';
    else if ($Link==$Language.'/Download#Ubuntu_7.10.amd64')               $Version='0.7.15';
    else if ($Link==$Language.'/Download#Ubuntu_8.04.i386')                $Version='0.7.15';
    else if ($Link==$Language.'/Download#Ubuntu_8.04.amd64')               $Version='0.7.15';
    else if ($Link==$Language.'/Download#Ubuntu_8.10.i386')                $Version='0.7.15';
    else if ($Link==$Language.'/Download#Ubuntu_8.10.amd64')               $Version='0.7.15';
    else if ($Link==$Language.'/Download#Ubuntu_9.04.i386')                $Version='0.7.15';
    else if ($Link==$Language.'/Download#Ubuntu_9.04.amd64')               $Version='0.7.15';
         if ($OS=='Ubuntu_7.10')                                $OS='Ubuntu 7.10 (Gusty)';
    else if ($OS=='Ubuntu_8.04')                                $OS='Ubuntu 8.04 (Hardy)';
    else if ($OS=='Ubuntu_8.10')                                $OS='Ubuntu 8.10 (Intrepid)';
    else if ($OS=='Ubuntu_9.04')                                $OS='Ubuntu 9.04 (Jaunty)';
    $OS=$OS.', '.$CPU;
   }
   else
   {
    $Version='0.7.15'; //Ubuntu
    $Link=$Language.'/Download#Ubuntu';
    $OS='Ubuntu';
   }
   $Size='2';
  }
  else if (stristr($_SERVER['HTTP_USER_AGENT'], "centos") or stristr($_SERVER['HTTP_USER_AGENT'], "red hat"))
  {
        if (stristr($_SERVER['HTTP_USER_AGENT'], "el4"))        $OS='CentOS_4';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "el5"))        $OS='CentOS_5';


        if (stristr($_SERVER['HTTP_USER_AGENT'], "i386"))       $CPU='i386';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "i486"))       $CPU='i386';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "i586"))       $CPU='i386';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "i686"))       $CPU='i386';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "x86_64"))     $CPU='x86_64';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "amd64"))      $CPU='x86_64';

   if (isset($OS) and isset($CPU))
   {
    $Link=$Language.'/Download#'.$OS.'.'.$CPU;
         if ($Link==$Language.'/Download#CentOS_4.i386')                   $Version='0.7.15';
    else if ($Link==$Language.'/Download#CentOS_4.x86_64')                 $Version='0.7.15';
    else if ($Link==$Language.'/Download#CentOS_5.i386')                   $Version='0.7.15';
    else if ($Link==$Language.'/Download#CentOS_5.x86_64')                 $Version='0.7.15';
    $OS=$OS.', '.$CPU;
   }
   else
   {
    $Version='0.7.15'; //CentOS
    $Link=$Language.'/Download#CentOS';
    $OS='CentOS';
   }
   $Size='2';
  }
  else if (stristr($_SERVER['HTTP_USER_AGENT'], "fedora"))
  {
        if (stristr($_SERVER['HTTP_USER_AGENT'], "fc1 "))       $OS='Fedora_8';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc2 "))       $OS='Fedora_8';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc 3"))       $OS='Fedora_8';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc4"))        $OS='Fedora_8';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc5"))        $OS='Fedora_8';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc6"))        $OS='Fedora_8';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc7"))        $OS='Fedora_8';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc8"))        $OS='Fedora_8';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc9"))        $OS='Fedora_9';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc10"))       $OS='Fedora_10';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc11"))       $OS='Fedora_10';


        if (stristr($_SERVER['HTTP_USER_AGENT'], "i386"))       $CPU='i386';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "i486"))       $CPU='i386';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "i586"))       $CPU='i386';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "i686"))       $CPU='i386';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "x86_64"))     $CPU='x86_64';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "amd64"))      $CPU='x86_64';

   if (isset($OS) and isset($CPU))
   {
    $Link=$Language.'/Download#'.$OS.'.'.$CPU;
         if ($Link==$Language.'/Download#Fedora_8.i386')                   $Version='0.7.15';
    else if ($Link==$Language.'/Download#Fedora_8.x86_64')                 $Version='0.7.15';
    else if ($Link==$Language.'/Download#Fedora_9.i386')                   $Version='0.7.15';
    else if ($Link==$Language.'/Download#Fedora_9.x86_64')                 $Version='0.7.15';
    else if ($Link==$Language.'/Download#Fedora_10.i386')                  $Version='0.7.15';
    else if ($Link==$Language.'/Download#Fedora_10.x86_64')                $Version='0.7.15';
         if ($OS=='Fedora_8')                                   $OS='Fedora 8 (Wereworlf)';
    else if ($OS=='Fedora_9')                                   $OS='Fedora 9 (Sulphur)';
    else if ($OS=='Fedora_10')                                  $OS='Fedora 10 (Cambridge)';
    $OS=$OS.', '.$CPU;
   }
   else
   {
    $Version='0.7.15'; //Fedora
    $Link=$Language.'/Download#Fedora';
    $OS='Fedora';
   }
   $Size='2';
  }
  else if (stristr($_SERVER['HTTP_USER_AGENT'], "suse"))
  {
                                                                $OS='OpenSuSE_11.1';

        if (stristr($_SERVER['HTTP_USER_AGENT'], "i386"))       $CPU='i586';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "i486"))       $CPU='i586';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "i586"))       $CPU='i586';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "i686"))       $CPU='i586';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "x86_64"))     $CPU='x86_64';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "amd64"))      $CPU='x86_64';

   if (isset($OS) and isset($CPU))
   {
    $Link=$Language.'/Download#'.$OS.'.'.$CPU;
         if ($Link==$Language.'/Download#OpenSuSE_11.1.i586')   $Version='0.7.15';
    else if ($Link==$Language.'/Download#OpenSuSE_11.1.x86_64') $Version='0.7.15';
         if ($OS=='OpenSuSE_11.1')                              $OS='OpenSuSE 11.1';
    $OS=$OS.', '.$CPU;
   }
   else
   {
    $Version='0.7.15'; //OpenSuSE
    $Link=$Language.'/Download#OpenSuSE';
    $OS='OpenSuSE';
   }
   $Size='2';
  }
  else if (stristr($_SERVER['HTTP_USER_AGENT'], "mandriva"))
  {
        if (stristr($_SERVER['HTTP_USER_AGENT'], "20060mdk"))   $OS='Mandriva_2008';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "2006.0"))     $OS='Mandriva_2008';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "mdv2007"))    $OS='Mandriva_2008';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "mdv2008"))    $OS='Mandriva_2008';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "mdv2009"))    $OS='Mandriva_2009';


        if (stristr($_SERVER['HTTP_USER_AGENT'], "i386"))       $CPU='i586';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "i486"))       $CPU='i586';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "i586"))       $CPU='i586';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "i686"))       $CPU='i586';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "x86_64"))     $CPU='x86_64';
   else if (stristr($_SERVER['HTTP_USER_AGENT'], "amd64"))      $CPU='x86_64';

   if (isset($OS) and isset($CPU))
   {
    $Link=$Language.'/Download#'.$OS.'.'.$CPU;
         if ($Link==$Language.'/Download#Mandriva_2008.i586')              $Version='0.7.15';
    else if ($Link==$Language.'/Download#Mandriva_2008.x86_64')            $Version='0.7.15';
    else if ($Link==$Language.'/Download#Mandriva_2009.i586')              $Version='0.7.15';
    else if ($Link==$Language.'/Download#Mandriva_2009.x86_64')            $Version='0.7.15';
    $OS=$OS.', '.$CPU;
   }
   else
   {
    $Version='0.7.15'; //Mandriva
    $Link=$Language.'/Download#Mandriva';
    $OS='Mandriva';
   }
   $Size='2';
  }
  else
  {
   $Version='0.7.15'; //Linux
   $Link=$Language.'/Download#Source.AllInOne';
   $OS='Linux';
   $Size='2';
  }
 }
 else if (stristr($_SERVER['HTTP_USER_AGENT'], "bsd"))
 {
  $Version='0.7.15'; //Linux
  $Link=$Language.'/Download#Source.AllInOne';
  $OS='Linux';
  $Size='2';
 }
   else
 {
  $Version='0.7.15'; //Windows.i386
  $Link='http://downloads.sourceforge.net/mediainfo/MediaInfo_GUI_'.$Version.'_Windows_i386.exe';
  $OS='Windows, 32'; $Bits=true;
  $Installer=true;
  $Size='1.7';
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