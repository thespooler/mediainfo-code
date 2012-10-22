@echo off
pushd %~dp0

cleancss -o CSS/Default.min.css CSS/Default.css && ^
cleancss -o CSS/External/Tags.min.css CSS/External/Tags.css && ^
cleancss -o CSS/Internal/Tags.min.css CSS/Internal/Tags.css && ^
uglifyjs -o JavaScript/Utils.min.js JavaScript/Utils.js && ^
uglifyjs -o JavaScript/External/Tags.min.js JavaScript/External/Tags.js
