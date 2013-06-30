@echo off
rem install node.js and then run:
rem npm install -g clean-css
rem npm install -g uglify-js

pushd %~dp0

echo minifying and combining css and js files...
type CSS\bootstrap.css CSS\normalize.css CSS\jquery.fancybox.css CSS\jquery.fancybox-thumbs.css CSS\Style.css CSS\Tags.css | cleancss --s0 -e -o CSS\pack.css
cmd /c uglifyjs JavaScript\jquery.fancybox.js JavaScript\jquery.fancybox-thumbs.js JavaScript\jquery.mousewheel.js JavaScript\Tags.js --compress --mangle -o JavaScript\pack.js

popd
