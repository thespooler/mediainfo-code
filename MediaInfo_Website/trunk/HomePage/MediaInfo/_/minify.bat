@echo off
pushd %~dp0

cleancss -o CSS/Style.min.css CSS/Style.css && ^
cleancss -o CSS/Tags.min.css CSS/Tags.css && ^
uglifyjs -o JavaScript/Utils.min.js JavaScript/Utils.js && ^
uglifyjs -o JavaScript/Tags.min.js JavaScript/Tags.js
