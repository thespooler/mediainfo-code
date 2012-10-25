<?php
//Config (base)
if (!isset($_SERVER["SCRIPT_FILENAME"]))
	exit("error");
$Path=$_SERVER["SCRIPT_FILENAME"]; $Path=substr($Path, 0, strrpos($Path, "/"));
include $Path.'/_/Core/Config.php';
include $Path.'/_/Core/Old.php';

//Specific pages
include $Path.'/_/Core/SpecialPages/Log.php';
include $Path.'/_/Core/SpecialPages/Donated.php';
include $Path.'/_/Core/SpecialPages/NewVersionRequested.php';
include $Path.'/_/Core/SpecialPages/NewUser.php';
include $Path.'/_/Core/SpecialPages/Testimonials.php';
include $Path.'/_/Core/SpecialPages/Prices.php';

//Config (specific)
include $Path.'/_/Core/DetectOS.php';
include $Path.'/_/Core/Normalize.php';


//test subfolder per subfolder : /a/_.html, /a/b/_.html...
include $Path."/_/index.0.html";
$Level=0;
$i=1;

while ($i<10 && isset($PageFinal_Exploded[$i+1])) {
	$Temp="/";
	for ($j=1; $j<=$i; $j++)
		$Temp.=$Page_Exploded[$j]."/";
	$Menu_Link[$Level]=$Page_Exploded[$i];
	$Temp.="_.html";
	if (file_exists($Path.$Temp))
		include $Path.$Temp;
	else {
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
$Top=str_replace("/About_MacAppStore.html", "/", $Top);
$Top=str_replace(".html", "", $Top);

//Contents of the page in a variable
ob_start();
include $Path.$PageFinal;
$Contents = ob_get_contents();
ob_end_clean();

if (!isset($Edit)) {
	//Substring between <title> and </title>
	$Title_Start=strpos($Contents, "<title>");
	if ($Title_Start!==false) {
		$Title_End=strpos($Contents, "</title>");
		$Title=substr($Contents, $Title_Start+7, $Title_End-$Title_Start-7);
	} else
		$Title="";

	$Head_ToAdd='';
	//<link> with CSS
	$Link_Start=strpos($Contents, "<link href=");
	if ($Link_Start!==false) {
		$Link_End=strpos($Contents, ".css");
		$Link=substr($Contents, $Link_Start+12, $Link_End-$Link_Start-12);
		$Head_ToAdd.=' <link href="/_/CSS/'.$Link.'.css" rel="stylesheet" type="text/css" />
	';
		//$Link_Start=strpos($Contents, "<link href=", $Link_Start+1);
	}
	$Link_Start=strpos($Contents, '<link href="doxygen.css"');
	if ($Link_Start!==false) { //Ugly, quick hack for Doxygen
		$Head_ToAdd.=' <link href="/_/CSS/doxygen.css" rel="stylesheet" type="text/css" />
	';
	}

	//<script> with JavaSript
	$Script_Start=strpos($Contents, "<script src=");
	if ($Script_Start!==false) {
		$Script_End=strpos($Contents, ".js");
		$Script=substr($Contents, $Script_Start+13, $Script_End-$Script_Start-13);
		$Footer_ToAdd.=' <script src="/_/JavaScript/'.$Link.'.js" type="text/javascript"></script>
	';
	}

	//<meta>
	$Meta_Start=strpos($Contents, '<meta http-equiv="refresh"');
	if ($Meta_Start!==false) {
		$Meta_End=strpos($Contents, '>', $Meta_Start);
		$Meta=substr($Contents, $Meta_Start, $Meta_End-$Meta_Start+1);
		$Head_ToAdd.=' '.$Meta.'
	';
	}

	//Substring between <body> and </body>
	$Body_Start=strpos($Contents, "<body>");
	if ($Body_Start!==false) {
		$Body_End=strpos($Contents, "</body>");
		$Contents=substr($Contents, $Body_Start+6, $Body_End-$Body_Start-6);
	} else {
		//if <body> contains information, filling $Body_Tag too
		$Body_Start=strpos($Contents, "<body ");
		if (!isset($Edit) && $Body_Start!==false) {
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