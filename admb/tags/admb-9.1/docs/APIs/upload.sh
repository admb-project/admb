#!/bin/bash
# $Id$
#
# Author: John Sibert
# Copyright (c) 2009 ADMB Foundation
#
WD=$(pwd)
echo $WD
#ssh admbfoun@admb-foundation.org 'ls -lR ~/public_html/documentation/api/default/*; ls -lR ~/public_html/documentation/api/sunsys/*';
cd sunsys-dox/html
pwd
zip -r sunsys.zip *
#unzip -l sunsys.zip
ssh admbfoun@admb-foundation.org 'rm -rfv ~/public_html/documentation/api/sunsys/*';
scp -rv sunsys.zip admbfoun@admb-foundation.org:~/public_html/documentation/api/sunsys
ssh admbfoun@admb-foundation.org 'cd public_html/documentation/api/sunsys; unzip sunsys.zip';
cd $WD
pwd

cd dox/html
pwd
zip  default.zip *
#unzip -l default.zip
ssh admbfoun@admb-foundation.org 'rm -rfv ~/public_html/documentation/api/default/*';
scp -rv default.zip admbfoun@admb-foundation.org:~/public_html/documentation/api/default
ssh admbfoun@admb-foundation.org 'cd public_html/documentation/api/default; unzip default.zip';
cd $WD
pwd

cp -v cadaver-script ~/.cadaver
cadaver -V
rm -fv ~/.cadaver
