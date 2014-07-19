@echo off
rem install node.js and then run:
rem npm install -g clean-css
rem npm install -g uglify-js

pushd %~dp0

pushd "www\_"

echo minifying and combining css and js files...
cmd /c cleancss --s0 --compatibility ie8 css\normalize.css css\bootstrap.css css\jquery.fancybox.css css\jquery.fancybox-thumbs.css css\Style.css css\Tags.css -o css\pack.css
cmd /c uglifyjs js\bootstrap.js js\jquery.fancybox.js js\jquery.fancybox-thumbs.js js\jquery.mousewheel.js js\Tags.js --compress --mangle -o js\pack.js

popd

popd
