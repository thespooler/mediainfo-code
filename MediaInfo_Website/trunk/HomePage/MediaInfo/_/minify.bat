@echo off
pushd %~dp0

cleancss -o CSS/Default.min.css CSS/Default.css && ^
cleancss -o CSS/Tags.min.css CSS/Tags.css && ^
uglifyjs -o JavaScript/Utils.min.js JavaScript/Utils.js && ^
uglifyjs -o JavaScript/Tags.min.js JavaScript/Tags.js
