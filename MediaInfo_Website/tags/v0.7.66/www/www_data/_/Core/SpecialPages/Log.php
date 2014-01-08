<?php
if ($Page=="/Log" || $Page=="/MediaInfo/ChangeLog") {
    setcookie("NewVersionRequested", "true", time() + 60 * 60 * 24 * 30 * 6, "/");
    include $Path."/_/ChangeLog.html";
    exit;
}
?>