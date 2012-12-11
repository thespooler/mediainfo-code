<?php
//Want a specific version
if (isset($Argument["NewVersionRequest"]) //Old version, should remove it later
    || isset($Argument["NewVersionRequested"])) {
        setcookie("NewVersionRequested", "true", time()+60*60*24*365*1, "/");
        echo '
        <html>
            <head>
                <meta name="robots" content="noindex, nofollow, noarchive">
                <meta http-equiv="refresh" content="0;url=http://'.$_SERVER['HTTP_HOST'].'/'.$Language.'">
            </head>
            <body>
                You will be redirected shortly, if not click <a href="http://'.$_SERVER['HTTP_HOST'].'/'.$Language.'">here</a>.
            </body>
        </html>
        ';
        exit;
}
?>