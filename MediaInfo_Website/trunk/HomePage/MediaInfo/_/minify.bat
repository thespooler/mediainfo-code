@echo off
rem install node.js and then run:
rem npm install -g clean-css
rem npm install -g uglify-js

pushd %~dp0

echo minifying and combining css and js files...
type CSS\normalize.css CSS\Style.css CSS\Tags.css | cleancss --s0 -o CSS\pack.css
type JavaScript\Utils.js JavaScript\Tags.js | uglifyjs -o JavaScript\pack.js

popd
