<?php
//Has just donated
if (isset($Argument["Donated"])
	|| isset($Argument["merchant_return_link"])) {
		setcookie("Donated", time(), time()+60*60*24*365*5, "/");
		echo '
		<html>
			<head>
				<meta name="robots" content="noindex, nofollow, noarchive">
				<meta http-equiv="refresh" content="0;url=http://'.$_SERVER['HTTP_HOST'].'/'.$Language.'/Download_Donate">
			</head>
			<body>
				You will be redirected shortly, if not click <a href="http://'.$_SERVER['HTTP_HOST'].'/'.$Language.'/Download_Donate">here</a>.
			</body>
		</html>
		';
		exit;
}

//Has just donated (paypal)
if (isset($Argument["tx"])) {
	//Paypal return: tx (Transaction number)
	//		 st (Completed)
	//		 amt (Amount)
	//		 cc (Currency)
	//		 cm (Empty)
	//		 item_number
	//		 sig (Signature)
	setcookie("Donated", "true", time()+60*60*24*365*5, "/");
	if (isset($_COOKIE["WantedDownload"]))
		$Link='/Download_Donate';
	else
		$Link='/Donate';
	echo '
		<html>
			<head>
				<meta name="robots" content="noindex, nofollow, noarchive">
				<meta http-equiv="refresh" content="0;url=http://'.$_SERVER['HTTP_HOST'].'/'.$Language.$Link.'">
			</head>
			<body>
				You will be redirected shortly, if not click <a href="http://'.$_SERVER['HTTP_HOST'].'/'.$Language.$Link.'">here</a>.
			</body>
		</html>
		';
		exit;
}
?>