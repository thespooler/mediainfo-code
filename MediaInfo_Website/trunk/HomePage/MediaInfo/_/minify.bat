@echo off
rem install node.js and then run:
rem npm install -g clean-css
rem npm install -g uglify-js

pushd %~dp0

echo minifying and combining css and js files...
type CSS\normalize.css CSS\Style.css CSS\Tags.css | cleancss --s0 -o css\pack.css
cmd /c uglifyjs -o JavaScript/Utils.min.js JavaScript/Utils.js && ^
cmd /c uglifyjs -o JavaScript/Tags.min.js JavaScript/Tags.js

popd
