<?php
    //OS detection
    if (stristr($_SERVER['HTTP_USER_AGENT'], "macintosh")) {
        $Version='0.7.68'; //Mac OS X
        $Link='http://mediaarea.net/download/binary/mediainfo-gui/MediaInfo_GUI_'.$Version.'_Mac_Universal.dmg';
        $OS='Mac OS X, Universal';
        $Installer=true;
        $Size='3.6';
    }
    else if (stristr($_SERVER['HTTP_USER_AGENT'], "linux")) {
        if (stristr($_SERVER['HTTP_USER_AGENT'], "debian")) {
                 if (stristr($_SERVER['HTTP_USER_AGENT'], "etch"))          $OS_Version='4';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "lenny"))         $OS_Version='5';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "squeeze"))       $OS_Version='6.0';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "wheezy"))        $OS_Version='7.0';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "sid"))           $OS_Version='8.0';

                 if (stristr($_SERVER['HTTP_USER_AGENT'], "i386"))          $CPU='i386';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "i486"))          $CPU='i386';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "i586"))          $CPU='i386';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "i686"))          $CPU='i386';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "x86_64"))        $CPU='amd64';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "amd64"))         $CPU='amd64';

            if (isset($OS_Version) and isset($CPU)) {
                $Link='MediaInfo/Download/Debian#'.$OS_Version.'.'.$CPU;
                     if ($Link=='MediaInfo/Download/Debian#4.i386')        $Version='0.7.28';
                else if ($Link=='MediaInfo/Download/Debian#4.amd64')       $Version='0.7.28';
                else if ($Link=='MediaInfo/Download/Debian#5.i386')        $Version='0.7.62';
                else if ($Link=='MediaInfo/Download/Debian#5.amd64')       $Version='0.7.62';
                else if ($Link=='MediaInfo/Download/Debian#6.0.i386')      $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Debian#6.0.amd64')     $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Debian#7.0.i386')      $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Debian#7.0.amd64')     $Version='0.7.68';
                $OS='Debian '.$OS_Version.', '.$CPU;
            } else {
                $Version='0.7.62'; //Debian
                $Link='MediaInfo/Download/Debian';
                $OS='Debian';
            }
            $Size='2';
        }
        else if (stristr($_SERVER['HTTP_USER_AGENT'], "ubuntu")) {
                 if (stristr($_SERVER['HTTP_USER_AGENT'], "warty"))         $OS_Version='7.10';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "4.10"))          $OS_Version='7.10';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "hoary"))         $OS_Version='7.10';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "5.04"))          $OS_Version='7.10';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "breezy"))        $OS_Version='7.10';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "5.10"))          $OS_Version='7.10';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "dapper"))        $OS_Version='7.10';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "6.06"))          $OS_Version='7.10';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "dapper"))        $OS_Version='7.10';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "6.10"))          $OS_Version='7.10';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "edgy"))          $OS_Version='7.10';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "7.04"))          $OS_Version='7.10';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "gusty"))         $OS_Version='7.10';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "7.10"))          $OS_Version='7.10';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "hardy"))         $OS_Version='8.04';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "8.04"))          $OS_Version='8.04';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "intrepid"))      $OS_Version='8.10';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "8.10"))          $OS_Version='8.10';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "jaunty"))        $OS_Version='9.04';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "9.04"))          $OS_Version='9.04';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "karmik"))        $OS_Version='9.10';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "9.10"))          $OS_Version='9.10';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "lucid"))         $OS_Version='10.04';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "10.04"))         $OS_Version='10.04';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "maverick"))      $OS_Version='10.10';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "10.10"))         $OS_Version='10.10';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "natty"))         $OS_Version='11.04';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "11.04"))         $OS_Version='11.04';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "oneiric"))       $OS_Version='11.10';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "11.10"))         $OS_Version='11.10';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "precise"))       $OS_Version='12.04';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "12.04"))         $OS_Version='12.04';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "quantal"))       $OS_Version='12.10';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "12.10"))         $OS_Version='12.10';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "wheezy"))        $OS_Version='13.04';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "13.04"))         $OS_Version='13.04';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "saucy"))         $OS_Version='13.10';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "13.10"))         $OS_Version='13.10';

                 if (stristr($_SERVER['HTTP_USER_AGENT'], "i386"))          $CPU='i386';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "i486"))          $CPU='i386';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "i586"))          $CPU='i386';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "i686"))          $CPU='i386';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "x86_64"))        $CPU='amd64';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "amd64"))         $CPU='amd64';

            if (isset($OS_Version) and isset($CPU)) {
                $Link='MediaInfo/Download/Ubuntu#'.$OS_Version.'.'.$CPU;
                     if ($Link=='MediaInfo/Download/Ubuntu#7.10.i386')     $Version='0.7.28';
                else if ($Link=='MediaInfo/Download/Ubuntu#7.10.amd64')    $Version='0.7.28';
                else if ($Link=='MediaInfo/Download/Ubuntu#8.04.i386')     $Version='0.7.62';
                else if ($Link=='MediaInfo/Download/Ubuntu#8.04.amd64')    $Version='0.7.62';
                else if ($Link=='MediaInfo/Download/Ubuntu#8.10.i386')     $Version='0.7.28';
                else if ($Link=='MediaInfo/Download/Ubuntu#8.10.amd64')    $Version='0.7.28';
                else if ($Link=='MediaInfo/Download/Ubuntu#9.04.i386')     $Version='0.7.62';
                else if ($Link=='MediaInfo/Download/Ubuntu#9.04.amd64')    $Version='0.7.62';
                else if ($Link=='MediaInfo/Download/Ubuntu#9.10.i386')     $Version='0.7.62';
                else if ($Link=='MediaInfo/Download/Ubuntu#9.10.amd64')    $Version='0.7.62';
                else if ($Link=='MediaInfo/Download/Ubuntu#10.04.i386')    $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Ubuntu#10.04.amd64')   $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Ubuntu#10.10.i386')    $Version='0.7.62';
                else if ($Link=='MediaInfo/Download/Ubuntu#10.10.amd64')   $Version='0.7.62';
                else if ($Link=='MediaInfo/Download/Ubuntu#11.04.i386')    $Version='0.7.62';
                else if ($Link=='MediaInfo/Download/Ubuntu#11.04.amd64')   $Version='0.7.62';
                else if ($Link=='MediaInfo/Download/Ubuntu#11.10.i386')    $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Ubuntu#11.10.amd64')   $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Ubuntu#12.04.i386')    $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Ubuntu#12.04.amd64')   $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Ubuntu#12.10.i386')    $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Ubuntu#12.10.amd64')   $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Ubuntu#13.04.i386')    $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Ubuntu#13.04.amd64')   $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Ubuntu#13.10.i386')    $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Ubuntu#13.10.amd64')   $Version='0.7.68';
                     if ($OS_Version=='7.10')                               $OS_Version='7.10 (Gusty)';
                else if ($OS_Version=='8.04')                               $OS_Version='8.04 (Hardy)';
                else if ($OS_Version=='8.10')                               $OS_Version='8.10 (Intrepid)';
                else if ($OS_Version=='9.04')                               $OS_Version='9.04 (Jaunty)';
                else if ($OS_Version=='9.10')                               $OS_Version='9.10 (Karmic)';
                else if ($OS_Version=='10.04')                              $OS_Version='10.04 (Lucid)';
                else if ($OS_Version=='10.10')                              $OS_Version='10.10 (Maverick)';
                else if ($OS_Version=='11.04')                              $OS_Version='11.04 (Natty)';
                else if ($OS_Version=='11.10')                              $OS_Version='11.10 (Oneiric)';
                else if ($OS_Version=='12.04')                              $OS_Version='12.04 (Precise)';
                else if ($OS_Version=='12.10')                              $OS_Version='12.10 (Quantal)';
                else if ($OS_Version=='13.04')                              $OS_Version='13.04 (Raring)';
                else if ($OS_Version=='13.10')                              $OS_Version='13.04 (Saucy)';
                $OS='Ubuntu '.$OS_Version.', '.$CPU;
            } else {
                $Version='0.7.68'; //Ubuntu
                $Link='MediaInfo/Download/Ubuntu';
                $OS='Ubuntu';
            }
            $Size='2';
        }
        else if (stristr($_SERVER['HTTP_USER_AGENT'], "Linux Mint")) {
                 if (stristr($_SERVER['HTTP_USER_AGENT'], "Elyssa"))        $OS_Version='8.04'; //5
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "Mint/5"))        $OS_Version='8.04'; //5
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "Felicia"))       $OS_Version='8.10'; //6
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "Mint/6"))        $OS_Version='8.10'; //6
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "Gloria"))        $OS_Version='9.04'; //7
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "Mint/7"))        $OS_Version='9.04'; //7
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "Helena"))        $OS_Version='9.10'; //8
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "Mint/8"))        $OS_Version='9.10'; //8
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "Isadora"))       $OS_Version='10.04'; //9
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "Mint/9"))        $OS_Version='10.04'; //9
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "Julia"))         $OS_Version='10.10'; //10
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "Mint/10"))       $OS_Version='10.10'; //10
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "Katya"))         $OS_Version='11.04'; //11
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "Mint/11"))       $OS_Version='11.04'; //11
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "Lisa"))          $OS_Version='11.10'; //12
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "Mint/12"))       $OS_Version='11.10'; //12
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "Maya"))          $OS_Version='12.04'; //13
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "Mint/13"))       $OS_Version='12.04'; //13
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "Nadia"))         $OS_Version='12.10'; //14
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "Mint/14"))       $OS_Version='12.10'; //14
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "Olivia"))        $OS_Version='13.04'; //15
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "Mint/15"))       $OS_Version='13.04'; //15
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "Petra"))         $OS_Version='13.10'; //16
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "Mint/16"))       $OS_Version='13.10'; //16

                 if (stristr($_SERVER['HTTP_USER_AGENT'], "i386"))          $CPU='i386';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "i486"))          $CPU='i386';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "i586"))          $CPU='i386';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "i686"))          $CPU='i386';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "x86_64"))        $CPU='amd64';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "amd64"))         $CPU='amd64';

            if (isset($OS_Version) and isset($CPU)) {
                $Link='MediaInfo/Download/Ubuntu#'.$OS_Version.'.'.$CPU;
                     if ($Link=='MediaInfo/Download/Ubuntu#8.04.i386')     $Version='0.7.28';
                else if ($Link=='MediaInfo/Download/Ubuntu#8.04.amd64')    $Version='0.7.28';
                else if ($Link=='MediaInfo/Download/Ubuntu#8.10.i386')     $Version='0.7.62';
                else if ($Link=='MediaInfo/Download/Ubuntu#8.10.amd64')    $Version='0.7.62';
                else if ($Link=='MediaInfo/Download/Ubuntu#9.04.i386')     $Version='0.7.62';
                else if ($Link=='MediaInfo/Download/Ubuntu#9.04.amd64')    $Version='0.7.62';
                else if ($Link=='MediaInfo/Download/Ubuntu#9.10.i386')     $Version='0.7.62';
                else if ($Link=='MediaInfo/Download/Ubuntu#9.10.amd64')    $Version='0.7.62';
                else if ($Link=='MediaInfo/Download/Ubuntu#10.04.i386')    $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Ubuntu#10.04.amd64')   $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Ubuntu#10.10.i386')    $Version='0.7.62';
                else if ($Link=='MediaInfo/Download/Ubuntu#10.10.amd64')   $Version='0.7.62';
                else if ($Link=='MediaInfo/Download/Ubuntu#11.04.i386')    $Version='0.7.62';
                else if ($Link=='MediaInfo/Download/Ubuntu#11.04.amd64')   $Version='0.7.62';
                else if ($Link=='MediaInfo/Download/Ubuntu#11.10.i386')    $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Ubuntu#11.10.amd64')   $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Ubuntu#12.04.i386')    $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Ubuntu#12.04.amd64')   $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Ubuntu#12.10.i386')    $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Ubuntu#12.10.amd64')   $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Ubuntu#13.04.i386')    $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Ubuntu#13.04.amd64')   $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Ubuntu#13.10.i386')    $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Ubuntu#13.10.amd64')   $Version='0.7.68';
                     if ($OS_Version=='8.04')                               $OS_Version='5 (Elyssa)';
                else if ($OS_Version=='8.10')                               $OS_Version='6 (Felicia)';
                else if ($OS_Version=='9.04')                               $OS_Version='7 (Gloria)';
                else if ($OS_Version=='9.10')                               $OS_Version='8 (Helena)';
                else if ($OS_Version=='10.04')                              $OS_Version='9 (Isadora)';
                else if ($OS_Version=='10.10')                              $OS_Version='10 (Julia)';
                else if ($OS_Version=='11.04')                              $OS_Version='11 (Katya)';
                else if ($OS_Version=='11.10')                              $OS_Version='12 (Lisa)';
                else if ($OS_Version=='12.04')                              $OS_Version='13 (Maya)';
                else if ($OS_Version=='12.10')                              $OS_Version='14 (Nadia)';
                else if ($OS_Version=='13.04')                              $OS_Version='15 (Olivia)';
                else if ($OS_Version=='13.10')                              $OS_Version='16 (Petra)';
                $OS='Linux Mint '.$OS_Version.', '.$CPU;
            } else {
                $Version='0.7.68'; //Ubuntu
                $Link='MediaInfo/Download/Ubuntu';
                $OS='Ubuntu';
            }
            $Size='2';
        }
        else if (stristr($_SERVER['HTTP_USER_AGENT'], "centos")) {
                 if (stristr($_SERVER['HTTP_USER_AGENT'], "el4"))       $OS_Version='4';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "el5"))       $OS_Version='5';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "el6"))       $OS_Version='6';

                 if (stristr($_SERVER['HTTP_USER_AGENT'], "i386"))      $CPU='i386';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "i486"))      $CPU='i386';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "i586"))      $CPU='i386';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "i686"))      $CPU='i386';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "x86_64"))    $CPU='x86_64';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "amd64"))     $CPU='x86_64';

            if (isset($OS_Version) and isset($CPU)) {
                $Link='MediaInfo/Download/CentOS#'.$OS_Version.'.'.$CPU;
                     if ($Link=='MediaInfo/Download/CentOS#4.i386')        $Version='0.7.26';
                else if ($Link=='MediaInfo/Download/CentOS#4.x86_64')      $Version='0.7.26';
                else if ($Link=='MediaInfo/Download/CentOS#5.i386')        $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/CentOS#5.x86_64')      $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/CentOS#6.i386')        $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/CentOS#6.x86_64')      $Version='0.7.68';
                $OS='CentOS '.$OS_Version.', '.$CPU;
            } else {
                $Version='0.7.68'; //CentOS
                $Link='MediaInfo/Download/CentOS';
                $OS='CentOS';
            }
            $Size='2';
        }
        else if (stristr($_SERVER['HTTP_USER_AGENT'], "red hat")) {
                 if (stristr($_SERVER['HTTP_USER_AGENT'], "el4"))       $OS_Version='4';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "el5"))       $OS_Version='5';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "el6"))       $OS_Version='6';

                 if (stristr($_SERVER['HTTP_USER_AGENT'], "i386"))      $CPU='i386';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "i486"))      $CPU='i386';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "i586"))      $CPU='i386';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "i686"))      $CPU='i386';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "x86_64"))    $CPU='x86_64';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "amd64"))     $CPU='x86_64';

            if (isset($OS_Version) and isset($CPU)) {
                $Link='MediaInfo/Download/RHEL#'.$OS_Version.'.'.$CPU;
                     if ($Link=='MediaInfo/Download/RHEL#4.i386')          $Version='0.7.26';
                else if ($Link=='MediaInfo/Download/RHEL#4.x86_64')        $Version='0.7.26';
                else if ($Link=='MediaInfo/Download/RHEL#5.i386')          $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/RHEL#5.x86_64')        $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/RHEL#6.i386')          $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/RHEL#6.x86_64')        $Version='0.7.68';
                $OS='RHEL '.$OS_Version.', '.$CPU;
            } else {
                $Version='0.7.68'; //RHEL
                $Link='MediaInfo/Download/RHEL';
                $OS='RHEL';
            }
            $Size='2';
        }
        else if (stristr($_SERVER['HTTP_USER_AGENT'], "fedora")) {
                 if (stristr($_SERVER['HTTP_USER_AGENT'], "fc2"))       $OS_Version='8';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc3"))       $OS_Version='8';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc4"))       $OS_Version='8';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc5"))       $OS_Version='8';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc6"))       $OS_Version='8';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc7"))       $OS_Version='8';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc8"))       $OS_Version='8';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc9"))       $OS_Version='9';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc10"))      $OS_Version='10';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc11"))      $OS_Version='11';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc12"))      $OS_Version='12';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc13"))      $OS_Version='13';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc14"))      $OS_Version='14';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc15"))      $OS_Version='15';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc16"))      $OS_Version='16';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc17"))      $OS_Version='17';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc18"))      $OS_Version='18';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc19"))      $OS_Version='19';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc20"))      $OS_Version='20';

                 if (stristr($_SERVER['HTTP_USER_AGENT'], "i386"))      $CPU='i386';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "i486"))      $CPU='i386';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "i586"))      $CPU='i386';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "i686"))      $CPU='i386';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "x86_64"))    $CPU='x86_64';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "amd64"))     $CPU='x86_64';

            if (isset($OS_Version) and isset($CPU)) {
                $Link='MediaInfo/Download/Fedora#'.$OS_Version.'.'.$CPU;
                     if ($Link=='MediaInfo/Download/Fedora#8.i386')        $Version='0.7.24';
                else if ($Link=='MediaInfo/Download/Fedora#8.x86_64')      $Version='0.7.24';
                else if ($Link=='MediaInfo/Download/Fedora#9.i386')        $Version='0.7.34';
                else if ($Link=='MediaInfo/Download/Fedora#9.x86_64')      $Version='0.7.34';
                else if ($Link=='MediaInfo/Download/Fedora#10.i386')       $Version='0.7.34';
                else if ($Link=='MediaInfo/Download/Fedora#10.x86_64')     $Version='0.7.34';
                else if ($Link=='MediaInfo/Download/Fedora#11.i386')       $Version='0.7.34';
                else if ($Link=='MediaInfo/Download/Fedora#11.x86_64')     $Version='0.7.34';
                else if ($Link=='MediaInfo/Download/Fedora#12.i386')       $Version='0.7.45';
                else if ($Link=='MediaInfo/Download/Fedora#12.x86_64')     $Version='0.7.45';
                else if ($Link=='MediaInfo/Download/Fedora#13.i386')       $Version='0.7.45';
                else if ($Link=='MediaInfo/Download/Fedora#13.x86_64')     $Version='0.7.45';
                else if ($Link=='MediaInfo/Download/Fedora#14.i386')       $Version='0.7.53';
                else if ($Link=='MediaInfo/Download/Fedora#14.x86_64')     $Version='0.7.53';
                else if ($Link=='MediaInfo/Download/Fedora#15.i386')       $Version='0.7.62';
                else if ($Link=='MediaInfo/Download/Fedora#15.x86_64')     $Version='0.7.62';
                else if ($Link=='MediaInfo/Download/Fedora#16.i386')       $Version='0.7.62';
                else if ($Link=='MediaInfo/Download/Fedora#16.x86_64')     $Version='0.7.62';
                else if ($Link=='MediaInfo/Download/Fedora#17.i386')       $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Fedora#17.x86_64')     $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Fedora#18.i386')       $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Fedora#18.x86_64')     $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Fedora#19.i386')       $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Fedora#19.x86_64')     $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Fedora#20.i386')       $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Fedora#20.x86_64')     $Version='0.7.68';
                     if ($OS_Version=='8')                                  $OS='8 (Wereworlf)';
                else if ($OS_Version=='9')                                  $OS='9 (Sulphur)';
                else if ($OS_Version=='10')                                 $OS='10 (Cambridge)';
                else if ($OS_Version=='11')                                 $OS='11 (Leonidas)';
                else if ($OS_Version=='12')                                 $OS='12 (Constantine)';
                else if ($OS_Version=='13')                                 $OS='13 (Goddard)';
                else if ($OS_Version=='14')                                 $OS='14 (Laughlin)';
                else if ($OS_Version=='15')                                 $OS='15 (Lovelock)';
                else if ($OS_Version=='16')                                 $OS='16 (Verne)';
                else if ($OS_Version=='17')                                 $OS='17 (Beefy Miracle)';
                else if ($OS_Version=='18')                                 $OS='18 (Spherical Cow)';
                else if ($OS_Version=='19')                                 $OS='19 (Schrödinger\'s Cat)';
                else if ($OS_Version=='20')                                 $OS='19 (Heisenbug)';
                $OS='Fedora '.$OS_Version.', '.$CPU;
            } else {
                $Version='0.7.68'; //Fedora
                $Link='MediaInfo/Download/Fedora';
                $OS='Fedora';
            }
            $Size='2';
        }
        else if (stristr($_SERVER['HTTP_USER_AGENT'], "suse")) {
                                                                        $OS_Version='13.1';

                 if (stristr($_SERVER['HTTP_USER_AGENT'], "i386"))      $CPU='i586';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "i486"))      $CPU='i586';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "i586"))      $CPU='i586';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "i686"))      $CPU='i586';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "x86_64"))    $CPU='x86_64';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "amd64"))     $CPU='x86_64';

            if (isset($OS_Version) and isset($CPU)) {
                $Link='MediaInfo/Download/openSUSE#'.$OS_Version.'.'.$CPU;
                     if ($Link=='MediaInfo/Download/openSUSE#11.3.i586')   $Version='0.7.53';
                else if ($Link=='MediaInfo/Download/openSUSE#11.3.x86_64') $Version='0.7.53';
                else if ($Link=='MediaInfo/Download/openSUSE#11.4.i586')   $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/openSUSE#11.4.x86_64') $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/openSUSE#12.1.i586')   $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/openSUSE#12.1.x86_64') $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/openSUSE#12.2.i586')   $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/openSUSE#12.2.x86_64') $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/openSUSE#12.3.i586')   $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/openSUSE#12.3.x86_64') $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/openSUSE#13.1.i586')   $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/openSUSE#13.1.x86_64') $Version='0.7.68';
                $OS='openSUSE '.$OS_Version.', '.$CPU;
            } else {
                $Version='0.7.68'; //openSUSE
                $Link='MediaInfo/Download/openSUSE';
                $OS='openSUSE';
            }
            $Size='2';
        }
        else if (stristr($_SERVER['HTTP_USER_AGENT'], "mandriva")) {
                 if (stristr($_SERVER['HTTP_USER_AGENT'], "20060mdk"))  $OS_Version='2008';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "2006.0"))    $OS_Version='2008';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "mdv2007"))   $OS_Version='2008';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "mdv2008"))   $OS_Version='2008';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "mdv2009"))   $OS_Version='2009.1';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "mdv2010"))   $OS_Version='2010.1';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "mdv2011"))   $OS_Version='2011';

                 if (stristr($_SERVER['HTTP_USER_AGENT'], "i386"))      $CPU='i586';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "i486"))      $CPU='i586';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "i586"))      $CPU='i586';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "i686"))      $CPU='i586';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "x86_64"))    $CPU='x86_64';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "amd64"))     $CPU='x86_64';

            if (isset($OS_Version) and isset($CPU)) {
                $Link='MediaInfo/Download/Mandriva#'.$OS_Version.'.'.$CPU;
                     if ($Link=='MediaInfo/Download/Mandriva#2008.i586')   $Version='0.7.31';
                else if ($Link=='MediaInfo/Download/Mandriva#2008.x86_64') $Version='0.7.31';
                else if ($Link=='MediaInfo/Download/Mandriva#2009.1.i586') $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Mandriva#2009.1.x86_64') $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Mandriva#2010.i586')   $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Mandriva#2010.x86_64') $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Mandriva#2010.1.i586') $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Mandriva#2010.1.x86_64') $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Mandriva#2011.i586')   $Version='0.7.68';
                else if ($Link=='MediaInfo/Download/Mandriva#2011.x86_64') $Version='0.7.68';
                $OS='Mandriva '.$OS_Version.', '.$CPU;
            } else {
                $Version='0.7.68'; //Mandriva
                $Link='MediaInfo/Download/Mandriva';
                $OS='Mandriva';
            }
            $Size='2';
        }
        else if (stristr($_SERVER['HTTP_USER_AGENT'], "arch linux")) {
                                                                        $OS_Version='';

                 if (stristr($_SERVER['HTTP_USER_AGENT'], "i386"))      $CPU='i586';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "i486"))      $CPU='i586';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "i586"))      $CPU='i586';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "i686"))      $CPU='i586';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "x86_64"))    $CPU='x86_64';
            else if (stristr($_SERVER['HTTP_USER_AGENT'], "amd64"))     $CPU='x86_64';

            $Version='0.7.41'; //Arch Linux
            $Link='MediaInfo/Download/Arch_Linux';
            $OS='Arch Linux';
            $Size='2';
        } else {
            $Version='0.7.68'; //Linux
            $Link='MediaInfo/Download';
            $OS='Linux';
            $Size='2';
        }
    }
    else if (stristr($_SERVER['HTTP_USER_AGENT'], "bsd")) {
        $Version='0.7.68'; //Linux
        $Link='MediaInfo/Download/Source#AllInOne';
        $OS='Linux';
        $Size='2';
    } else {
        $Version='0.7.68'; //Windows
        $CPU='i386'; //default
             if (stristr($_SERVER['HTTP_USER_AGENT'], "WOW64"))     $CPU='x64';
        else if (stristr($_SERVER['HTTP_USER_AGENT'], "Win64"))     $CPU='x64';
        else if (stristr($_SERVER['HTTP_USER_AGENT'], "x64"))       $CPU='x64';

        if (isset($Donated))
        {
            $Link='http://mediaarea.net/download/donors/'.$Version.'/MediaInfo_GUI_'.$Version.'_Windows.exe';
        }
        else
        {
            $Link='http://mediaarea.net/download/binary/mediainfo-gui/'.$Version.'/MediaInfo_GUI_'.$Version.'_Windows.exe';
        }

        if ($CPU=='i386') {
            $OS='Windows, 32/64'; $Bits=true;
            $Size='5';
        } else {
            $OS='Windows, 32/64'; $Bits=true;
            $Size='5';
        }
        $Installer=true;
    }
?>