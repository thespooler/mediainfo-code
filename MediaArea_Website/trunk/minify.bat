@echo off
rem install node.js and then run:
rem npm install -g clean-css
rem npm install -g uglify-js

pushd %~dp0

pushd "www\_"

echo minifying and combining css and js files...
type css\bootstrap.css css\normalize.css css\jquery.fancybox.css css\jquery.fancybox-thumbs.css css\Style.css css\Tags.css | cleancss --s0 -e -o css\pack.css
cmd /c uglifyjs js\jquery.fancybox.js js\jquery.fancybox-thumbs.js js\jquery.mousewheel.js js\Tags.js --compress --mangle -o js\pack.js

popd

popd
