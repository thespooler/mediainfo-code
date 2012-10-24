<?php
//Old cookie
if (isset($_COOKIE["NewVersionRequest"])) {
	setcookie("NewVersionRequest", "", time()-60*60, "/");
	setcookie("NewVersionRequested", "true", time()+60*60*24*30*6, "/");

	//Redirecting
	echo '
	<html>
		<head>
			<meta name="robots" content="noindex, nofollow, noarchive">
			<meta http-equiv="refresh" content="0;url=http://'.$_SERVER['HTTP_HOST'].$_SERVER["REQUEST_URI"].'">
		</head>
		<body>
			You will be redirected shortly, if not click <a href="http://'.$_SERVER['HTTP_HOST'].$_SERVER["REQUEST_URI"].'">here</a>.
		</body>
	</html>
	';
	exit;
}
?>