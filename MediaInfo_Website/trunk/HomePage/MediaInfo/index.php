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

//Non-HTML files
$FileName_Exploded=explode(".", $PageFinal_Exploded[sizeof($PageFinal_Exploded)-1]);
$FileExtension=$FileName_Exploded[sizeof($FileName_Exploded)-1];
if ($FileExtension!="html")
{
    if ($FileExtension=="png")
        header('Content-type: image/png;');
    else if ($FileExtension=="css")
        header('Content-type: text/css;');
    else if ($FileExtension=="js")
        header('Content-type: application/javascript;');
    else
        header('Content-type:;');
    include $Path.$PageFinal;
    return;
}

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
    $Head_End=0;
    $Head_Max=strpos($Contents, "</head>");
    //<link>
    for (; ; )
    {
        $Head_Start=strpos($Contents, "<link ", $Head_End);
        if ($Head_Start===false)
            break;
        $Head_End1=strpos($Contents, ">", $Head_Start);
        $Head_End2=strpos($Contents, "</link>", $Head_Start);
        if ($Head_End1+1==$Head_End2) $Head_End=$Head_End2+7; else $Head_End=$Head_End1+1;
        if ($Head_Start<$Head_Max && $Head_End<$Head_Max)
        {
            $Data=substr($Contents, $Head_Start, $Head_End-$Head_Start);
            $Head_ToAdd.=$Data.'
    ';
        }
    }
    //<script>
    $Head_End=0;
    for (; ; )
    {
        $Head_Start=strpos($Contents, "<script ", $Head_End);
        if ($Head_Start===false)
            break;
        $Head_End1=strpos($Contents, ">", $Head_Start);
        $Head_End2=strpos($Contents, "</script>", $Head_Start);
        if ($Head_End1+1==$Head_End2) $Head_End=$Head_End2+9; else $Head_End=$Head_End1+1;
        if ($Head_Start<$Head_Max && $Head_End<$Head_Max)
        {
            $Data=substr($Contents, $Head_Start, $Head_End-$Head_Start);
            $Head_ToAdd.=$Data.'
    ';
        }
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

    if (empty($NotUpdated) && isset($Page_Exploded[$Level+1]) && isset($Updates[$Page_Exploded[$Level+1]]))
        $NotUpdated=$Updates[$Page_Exploded[$Level+1]];
}

if (!isset($Edit))
    include $Path."/_/index.1.html";
echo $Contents;
if (!isset($Edit))
    include $Path."/_/index.9.html";
?>
