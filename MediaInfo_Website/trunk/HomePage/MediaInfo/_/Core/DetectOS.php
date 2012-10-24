<?php
	//OS detection
	if (stristr($_SERVER['HTTP_USER_AGENT'], "macintosh")) {
		$Version='0.7.60'; //Mac OS X
		$Link='http://downloads.sourceforge.net/mediainfo/MediaInfo_GUI_'.$Version.'_Mac_Universal.dmg';
		$OS='Mac OS X, Universal';
		$Installer=true;
		$Size='3.6';
	}
	else if (stristr($_SERVER['HTTP_USER_AGENT'], "linux")) {
		if (stristr($_SERVER['HTTP_USER_AGENT'], "debian")) {
				 if (stristr($_SERVER['HTTP_USER_AGENT'], "etch"))			$OS_Version='4';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "lenny"))			$OS_Version='5';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "squeeze"))		$OS_Version='6.0';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "wheezy"))		$OS_Version='6.0';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "sid"))			$OS_Version='6.0';

				 if (stristr($_SERVER['HTTP_USER_AGENT'], "i386"))			$CPU='i386';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "i486"))			$CPU='i386';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "i586"))			$CPU='i386';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "i686"))			$CPU='i386';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "x86_64"))		$CPU='amd64';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "amd64"))			$CPU='amd64';

			if (isset($OS_Version) and isset($CPU)) {
				$Link=$Language.'/Download/Debian#'.$OS_Version.'.'.$CPU;
					 if ($Link==$Language.'/Download/Debian#4.i386')		$Version='0.7.28';
				else if ($Link==$Language.'/Download/Debian#4.amd64')		$Version='0.7.28';
				else if ($Link==$Language.'/Download/Debian#5.i386')		$Version='0.7.61';
				else if ($Link==$Language.'/Download/Debian#5.amd64')		$Version='0.7.61';
				else if ($Link==$Language.'/Download/Debian#6.0.i386')		$Version='0.7.61';
				else if ($Link==$Language.'/Download/Debian#6.0.amd64')		$Version='0.7.61';
				$OS='Debian '.$OS_Version.', '.$CPU;
			} else {
				$Version='0.7.61'; //Debian
				$Link=$Language.'/Download/Debian';
				$OS='Debian';
			}
			$Size='2';
		}
		else if (stristr($_SERVER['HTTP_USER_AGENT'], "ubuntu")) {
				 if (stristr($_SERVER['HTTP_USER_AGENT'], "warty"))			$OS_Version='7.10';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "4.10"))			$OS_Version='7.10';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "hoary"))			$OS_Version='7.10';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "5.04"))			$OS_Version='7.10';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "breezy"))		$OS_Version='7.10';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "5.10"))			$OS_Version='7.10';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "dapper"))		$OS_Version='7.10';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "6.06"))			$OS_Version='7.10';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "dapper"))		$OS_Version='7.10';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "6.10"))			$OS_Version='7.10';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "edgy"))			$OS_Version='7.10';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "7.04"))			$OS_Version='7.10';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "gusty"))			$OS_Version='7.10';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "7.10"))			$OS_Version='7.10';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "hardy"))			$OS_Version='8.04';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "8.04"))			$OS_Version='8.04';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "intrepid"))		$OS_Version='8.10';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "8.10"))			$OS_Version='8.10';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "jaunty"))		$OS_Version='9.04';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "9.04"))			$OS_Version='9.04';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "karmik"))		$OS_Version='9.10';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "9.10"))			$OS_Version='9.10';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "lucid"))			$OS_Version='10.04';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "10.04"))			$OS_Version='10.04';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "maverick"))		$OS_Version='10.10';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "10.10"))			$OS_Version='10.10';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "natty"))			$OS_Version='11.04';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "11.04"))			$OS_Version='11.04';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "oneiric"))		$OS_Version='11.10';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "11.10"))			$OS_Version='11.10';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "precise"))		$OS_Version='12.04';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "12.04"))			$OS_Version='12.04';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "quantal"))		$OS_Version='12.10';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "12.10"))			$OS_Version='12.10';

				 if (stristr($_SERVER['HTTP_USER_AGENT'], "i386"))			$CPU='i386';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "i486"))			$CPU='i386';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "i586"))			$CPU='i386';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "i686"))			$CPU='i386';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "x86_64"))		$CPU='amd64';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "amd64"))			$CPU='amd64';

			if (isset($OS_Version) and isset($CPU)) {
				$Link=$Language.'/Download/Ubuntu#'.$OS_Version.'.'.$CPU;
					 if ($Link==$Language.'/Download/Ubuntu#7.10.i386')		$Version='0.7.28';
				else if ($Link==$Language.'/Download/Ubuntu#7.10.amd64')	$Version='0.7.28';
				else if ($Link==$Language.'/Download/Ubuntu#8.04.i386')		$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#8.04.amd64')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#8.10.i386')		$Version='0.7.28';
				else if ($Link==$Language.'/Download/Ubuntu#8.10.amd64')	$Version='0.7.28';
				else if ($Link==$Language.'/Download/Ubuntu#9.04.i386')		$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#9.04.amd64')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#9.10.i386')		$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#9.10.amd64')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#10.04.i386')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#10.04.amd64')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#10.10.i386')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#10.10.amd64')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#11.04.i386')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#11.04.amd64')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#11.10.i386')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#11.10.amd64')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#12.04.i386')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#12.04.amd64')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#12.10.i386')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#12.10.amd64')	$Version='0.7.61';
					 if ($OS_Version=='7.10')								$OS_Version='7.10 (Gusty)';
				else if ($OS_Version=='8.04')								$OS_Version='8.04 (Hardy)';
				else if ($OS_Version=='8.10')								$OS_Version='8.10 (Intrepid)';
				else if ($OS_Version=='9.04')								$OS_Version='9.04 (Jaunty)';
				else if ($OS_Version=='9.10')								$OS_Version='9.10 (Karmic)';
				else if ($OS_Version=='10.04')								$OS_Version='10.04 (Lucid)';
				else if ($OS_Version=='10.10')								$OS_Version='10.10 (Maverick)';
				else if ($OS_Version=='11.04')								$OS_Version='11.04 (Natty)';
				else if ($OS_Version=='11.10')								$OS_Version='11.10 (Oneiric)';
				else if ($OS_Version=='12.04')								$OS_Version='12.04 (Precise)';
				else if ($OS_Version=='12.10')								$OS_Version='12.10 (Quantal)';
				$OS='Ubuntu '.$OS_Version.', '.$CPU;
			} else {
				$Version='0.7.61'; //Ubuntu
				$Link=$Language.'/Download/Ubuntu';
				$OS='Ubuntu';
			}
			$Size='2';
		}
		else if (stristr($_SERVER['HTTP_USER_AGENT'], "Linux Mint")) {
				 if (stristr($_SERVER['HTTP_USER_AGENT'], "Elyssa"))		$OS_Version='8.04'; //5
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "Mint/5"))		$OS_Version='8.04'; //5
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "Felicia"))		$OS_Version='8.10'; //6
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "Mint/6"))		$OS_Version='8.10'; //6
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "Gloria"))		$OS_Version='9.04'; //7
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "Mint/7"))		$OS_Version='9.04'; //7
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "Helena"))		$OS_Version='9.10'; //8
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "Mint/8"))		$OS_Version='9.10'; //8
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "Isadora"))		$OS_Version='10.04'; //9
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "Mint/9"))		$OS_Version='10.04'; //9
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "Julia"))			$OS_Version='10.10'; //10
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "Mint/10"))		$OS_Version='10.10'; //10
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "Katya"))			$OS_Version='11.04'; //11
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "Mint/11"))		$OS_Version='11.04'; //11
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "Lisa"))			$OS_Version='11.10'; //12
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "Mint/12"))		$OS_Version='11.10'; //12
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "Maya"))			$OS_Version='12.04'; //13
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "Mint/13"))		$OS_Version='12.04'; //13
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "Nadia"))			$OS_Version='12.10'; //14
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "Mint/14"))		$OS_Version='12.10'; //14

				 if (stristr($_SERVER['HTTP_USER_AGENT'], "i386"))			$CPU='i386';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "i486"))			$CPU='i386';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "i586"))			$CPU='i386';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "i686"))			$CPU='i386';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "x86_64"))		$CPU='amd64';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "amd64"))			$CPU='amd64';

			if (isset($OS_Version) and isset($CPU)) {
				$Link=$Language.'/Download/Ubuntu#'.$OS_Version.'.'.$CPU;
					 if ($Link==$Language.'/Download/Ubuntu#8.04.i386')		$Version='0.7.28';
				else if ($Link==$Language.'/Download/Ubuntu#8.04.amd64')	$Version='0.7.28';
				else if ($Link==$Language.'/Download/Ubuntu#8.10.i386')		$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#8.10.amd64')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#9.04.i386')		$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#9.04.amd64')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#9.10.i386')		$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#9.10.amd64')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#10.04.i386')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#10.04.amd64')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#10.10.i386')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#10.10.amd64')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#11.04.i386')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#11.04.amd64')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#11.10.i386')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#11.10.amd64')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#12.04.i386')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#12.04.amd64')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#12.10.i386')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Ubuntu#12.10.amd64')	$Version='0.7.61';
					 if ($OS_Version=='8.04')								$OS_Version='5 (Elyssa)';
				else if ($OS_Version=='8.10')								$OS_Version='6 (Felicia)';
				else if ($OS_Version=='9.04')								$OS_Version='7 (Gloria)';
				else if ($OS_Version=='9.10')								$OS_Version='8 (Helena)';
				else if ($OS_Version=='10.04')								$OS_Version='9 (Isadora)';
				else if ($OS_Version=='10.10')								$OS_Version='10 (Julia)';
				else if ($OS_Version=='11.04')								$OS_Version='11 (Katya)';
				else if ($OS_Version=='11.10')								$OS_Version='11 (Lisa)';
				else if ($OS_Version=='12.04')								$OS_Version='11 (Maya)';
				else if ($OS_Version=='12.04')								$OS_Version='12 (Nadia)';
				$OS='Linux Mint '.$OS_Version.', '.$CPU;
			} else {
				$Version='0.7.61'; //Ubuntu
				$Link=$Language.'/Download/Ubuntu';
				$OS='Ubuntu';
			}
			$Size='2';
		}
		else if (stristr($_SERVER['HTTP_USER_AGENT'], "centos")) {
				 if (stristr($_SERVER['HTTP_USER_AGENT'], "el4"))		$OS_Version='4';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "el5"))		$OS_Version='5';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "el6"))		$OS_Version='5';

				 if (stristr($_SERVER['HTTP_USER_AGENT'], "i386"))		$CPU='i386';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "i486"))		$CPU='i386';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "i586"))		$CPU='i386';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "i686"))		$CPU='i386';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "x86_64"))	$CPU='x86_64';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "amd64"))		$CPU='x86_64';

			if (isset($OS_Version) and isset($CPU)) {
				$Link=$Language.'/Download/CentOS#'.$OS_Version.'.'.$CPU;
					 if ($Link==$Language.'/Download/CentOS#4.i386')		$Version='0.7.26';
				else if ($Link==$Language.'/Download/CentOS#4.x86_64')		$Version='0.7.26';
				else if ($Link==$Language.'/Download/CentOS#5.i386')		$Version='0.7.61';
				else if ($Link==$Language.'/Download/CentOS#5.x86_64')		$Version='0.7.61';
				else if ($Link==$Language.'/Download/CentOS#6.i386')		$Version='0.7.61';
				else if ($Link==$Language.'/Download/CentOS#6.x86_64')		$Version='0.7.61';
				$OS='CentOS '.$OS_Version.', '.$CPU;
			} else {
				$Version='0.7.61'; //CentOS
				$Link=$Language.'/Download/CentOS';
				$OS='CentOS';
			}
			$Size='2';
		}
		else if (stristr($_SERVER['HTTP_USER_AGENT'], "red hat")) {
				 if (stristr($_SERVER['HTTP_USER_AGENT'], "el4"))		$OS_Version='4';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "el5"))		$OS_Version='5';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "el6"))		$OS_Version='6';

				 if (stristr($_SERVER['HTTP_USER_AGENT'], "i386"))		$CPU='i386';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "i486"))		$CPU='i386';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "i586"))		$CPU='i386';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "i686"))		$CPU='i386';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "x86_64"))	$CPU='x86_64';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "amd64"))		$CPU='x86_64';

			if (isset($OS_Version) and isset($CPU)) {
				$Link=$Language.'/Download/RHEL#'.$OS_Version.'.'.$CPU;
					 if ($Link==$Language.'/Download/RHEL#4.i386')			$Version='0.7.26';
				else if ($Link==$Language.'/Download/RHEL#4.x86_64')		$Version='0.7.26';
				else if ($Link==$Language.'/Download/RHEL#5.i386')			$Version='0.7.61';
				else if ($Link==$Language.'/Download/RHEL#5.x86_64')		$Version='0.7.61';
				else if ($Link==$Language.'/Download/RHEL#6.i386')			$Version='0.7.61';
				else if ($Link==$Language.'/Download/RHEL#6.x86_64')		$Version='0.7.61';
				$OS='RHEL '.$OS_Version.', '.$CPU;
			} else {
				$Version='0.7.61'; //RHEL
				$Link=$Language.'/Download/RHEL';
				$OS='RHEL';
			}
			$Size='2';
		}
		else if (stristr($_SERVER['HTTP_USER_AGENT'], "fedora")) {
				if (stristr($_SERVER['HTTP_USER_AGENT'], "fc2"))		$OS_Version='8';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc3"))		$OS_Version='8';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc4"))		$OS_Version='8';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc5"))		$OS_Version='8';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc6"))		$OS_Version='8';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc7"))		$OS_Version='8';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc8"))		$OS_Version='8';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc9"))		$OS_Version='9';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc10"))		$OS_Version='10';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc11"))		$OS_Version='11';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc12"))		$OS_Version='12';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc13"))		$OS_Version='13';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc14"))		$OS_Version='14';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc15"))		$OS_Version='15';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "fc16"))		$OS_Version='16';

				if (stristr($_SERVER['HTTP_USER_AGENT'], "i386"))		$CPU='i386';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "i486"))		$CPU='i386';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "i586"))		$CPU='i386';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "i686"))		$CPU='i386';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "x86_64"))	$CPU='x86_64';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "amd64"))		$CPU='x86_64';

			if (isset($OS_Version) and isset($CPU)) {
				$Link=$Language.'/Download/Fedora#'.$OS_Version.'.'.$CPU;
					 if ($Link==$Language.'/Download/Fedora#8.i386')		$Version='0.7.24';
				else if ($Link==$Language.'/Download/Fedora#8.x86_64')		$Version='0.7.24';
				else if ($Link==$Language.'/Download/Fedora#9.i386')		$Version='0.7.34';
				else if ($Link==$Language.'/Download/Fedora#9.x86_64')		$Version='0.7.34';
				else if ($Link==$Language.'/Download/Fedora#10.i386')		$Version='0.7.34';
				else if ($Link==$Language.'/Download/Fedora#10.x86_64')		$Version='0.7.34';
				else if ($Link==$Language.'/Download/Fedora#11.i386')		$Version='0.7.34';
				else if ($Link==$Language.'/Download/Fedora#11.x86_64')		$Version='0.7.34';
				else if ($Link==$Language.'/Download/Fedora#12.i386')		$Version='0.7.45';
				else if ($Link==$Language.'/Download/Fedora#12.x86_64')		$Version='0.7.45';
				else if ($Link==$Language.'/Download/Fedora#13.i386')		$Version='0.7.45';
				else if ($Link==$Language.'/Download/Fedora#13.x86_64')		$Version='0.7.45';
				else if ($Link==$Language.'/Download/Fedora#14.i386')		$Version='0.7.53';
				else if ($Link==$Language.'/Download/Fedora#14.x86_64')		$Version='0.7.53';
				else if ($Link==$Language.'/Download/Fedora#15.i386')		$Version='0.7.61';
				else if ($Link==$Language.'/Download/Fedora#15.x86_64')		$Version='0.7.61';
				else if ($Link==$Language.'/Download/Fedora#16.i386')		$Version='0.7.61';
				else if ($Link==$Language.'/Download/Fedora#16.x86_64')		$Version='0.7.61';
					 if ($OS_Version=='8')									$OS='8 (Wereworlf)';
				else if ($OS_Version=='9')									$OS='9 (Sulphur)';
				else if ($OS_Version=='10')									$OS='10 (Cambridge)';
				else if ($OS_Version=='11')									$OS='11 (Leonidas)';
				else if ($OS_Version=='12')									$OS='12 (Constantine)';
				else if ($OS_Version=='13')									$OS='13 (Goddard)';
				else if ($OS_Version=='14')									$OS='14 (Laughlin)';
				else if ($OS_Version=='15')									$OS='15 (Lovelock)';
				else if ($OS_Version=='15')									$OS='16 (Verne)';
				$OS='Fedora '.$OS_Version.', '.$CPU;
			} else {
				$Version='0.7.61'; //Fedora
				$Link=$Language.'/Download/Fedora';
				$OS='Fedora';
			}
			$Size='2';
		}
		else if (stristr($_SERVER['HTTP_USER_AGENT'], "suse")) {
																		$OS_Version='12.1';

				 if (stristr($_SERVER['HTTP_USER_AGENT'], "i386"))		$CPU='i586';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "i486"))		$CPU='i586';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "i586"))		$CPU='i586';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "i686"))		$CPU='i586';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "x86_64"))	$CPU='x86_64';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "amd64"))		$CPU='x86_64';

			if (isset($OS_Version) and isset($CPU)) {
				$Link=$Language.'/Download/openSUSE#'.$OS_Version.'.'.$CPU;
					 if ($Link==$Language.'/Download/openSUSE#11.3.i586')	$Version='0.7.53';
				else if ($Link==$Language.'/Download/openSUSE#11.3.x86_64')	$Version='0.7.53';
				else if ($Link==$Language.'/Download/openSUSE#11.4.i586')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/openSUSE#11.4.x86_64')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/openSUSE#12.1.i586')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/openSUSE#12.1.x86_64')	$Version='0.7.61';
				$OS='openSUSE '.$OS_Version.', '.$CPU;
			} else {
				$Version='0.7.61'; //openSUSE
				$Link=$Language.'/Download/openSUSE';
				$OS='openSUSE';
			}
			$Size='2';
		}
		else if (stristr($_SERVER['HTTP_USER_AGENT'], "mandriva")) {
				 if (stristr($_SERVER['HTTP_USER_AGENT'], "20060mdk"))	$OS_Version='2008';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "2006.0"))	$OS_Version='2008';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "mdv2007"))	$OS_Version='2008';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "mdv2008"))	$OS_Version='2008';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "mdv2009"))	$OS_Version='2009.1';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "mdv2010"))	$OS_Version='2010.1';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "mdv2011"))	$OS_Version='2011';

				 if (stristr($_SERVER['HTTP_USER_AGENT'], "i386"))		$CPU='i586';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "i486"))		$CPU='i586';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "i586"))		$CPU='i586';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "i686"))		$CPU='i586';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "x86_64"))	$CPU='x86_64';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "amd64"))		$CPU='x86_64';

			if (isset($OS_Version) and isset($CPU)) {
				$Link=$Language.'/Download/Mandriva#'.$OS_Version.'.'.$CPU;
					 if ($Link==$Language.'/Download/Mandriva#2008.i586')	$Version='0.7.31';
				else if ($Link==$Language.'/Download/Mandriva#2008.x86_64')	$Version='0.7.31';
				else if ($Link==$Language.'/Download/Mandriva#2009.1.i586')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Mandriva#2009.1.x86_64') $Version='0.7.61';
				else if ($Link==$Language.'/Download/Mandriva#2010.i586')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Mandriva#2010.x86_64')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Mandriva#2010.1.i586')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Mandriva#2010.1.x86_64') $Version='0.7.61';
				else if ($Link==$Language.'/Download/Mandriva#2011.i586')	$Version='0.7.61';
				else if ($Link==$Language.'/Download/Mandriva#2011.x86_64')	$Version='0.7.61';
				$OS='Mandriva '.$OS_Version.', '.$CPU;
			} else {
				$Version='0.7.61'; //Mandriva
				$Link=$Language.'/Download/Mandriva';
				$OS='Mandriva';
			}
			$Size='2';
		}
		else if (stristr($_SERVER['HTTP_USER_AGENT'], "arch linux")) {
																		$OS_Version='';

				 if (stristr($_SERVER['HTTP_USER_AGENT'], "i386"))		$CPU='i586';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "i486"))		$CPU='i586';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "i586"))		$CPU='i586';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "i686"))		$CPU='i586';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "x86_64"))	$CPU='x86_64';
			else if (stristr($_SERVER['HTTP_USER_AGENT'], "amd64"))		$CPU='x86_64';

			$Version='0.7.41'; //Arch Linux
			$Link=$Language.'/Download/Arch_Linux';
			$OS='Arch Linux';
			$Size='2';
		} else {
			$Version='0.7.61'; //Linux
			$Link=$Language.'/Download';
			$OS='Linux';
			$Size='2';
		}
	}
	else if (stristr($_SERVER['HTTP_USER_AGENT'], "bsd")) {
		$Version='0.7.61'; //Linux
		$Link=$Language.'/Download/Source#AllInOne';
		$OS='Linux';
		$Size='2';
	} else {
		$Version='0.7.61'; //Windows
		$CPU='i386'; //default
			 if (stristr($_SERVER['HTTP_USER_AGENT'], "WOW64"))		$CPU='x64';
		else if (stristr($_SERVER['HTTP_USER_AGENT'], "Win64"))		$CPU='x64';
		else if (stristr($_SERVER['HTTP_USER_AGENT'], "x64"))		$CPU='x64';

		if (isset($Donated))
			//$Link='http://mediaarea.net/download/donors/'.$Version.'/MediaInfo_GUI_'.$Version.'_Windows_'.$CPU.'.exe';
			$Link='http://mediaarea.net/download/donors/'.$Version.'/MediaInfo_GUI_'.$Version.'_Windows.exe';
		else if (isset($NewVersionRequested) && $Language=="en" ) {
			$Link='/Download_Donate';
			//setcookie("WantedDownload", 'http://downloads.sourceforge.net/mediainfo/MediaInfo_GUI_'.$Version.'_Windows_'.$CPU.'.exe', time()+60*60*1, "/");
			//setcookie("WantedDownload", 'http://mediaarea.net/download/binary/mediainfo-gui/'.$Version.'/MediaInfo_GUI_'.$Version.'_Windows_'.$CPU.'.exe', time()+60*60*1, "/");
			setcookie("WantedDownload", 'http://mediaarea.net/download/binary/mediainfo-gui/'.$Version.'/MediaInfo_GUI_'.$Version.'_Windows.exe', time()+60*60*1, "/");
		} else {
			//$Link='http://downloads.sourceforge.net/mediainfo/MediaInfo_GUI_'.$Version.'_Windows_'.$CPU.'.exe';
			//$Link='http://download.mediaarea.net/current/MediaInfo_GUI_'.$Version.'_Windows_'.$CPU.'.exe';
			//$Link='http://mediaarea.net/download/binary/mediainfo-gui/'.$Version.'/MediaInfo_GUI_'.$Version.'_Windows_'.$CPU.'.exe';
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