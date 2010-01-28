#!/bin/bash
# $Id: upload.sh 229 2009-05-19 23:36:35Z jsibert $
#
# Author: John Sibert
# Copyright (c) 2009 ADMB Foundation
#
WD=$(pwd)
echo $WD
#ssh admbfoun@admb-foundation.org 'ls -lR ~/public_html/replacement_documentation/api/default/*; ls -lR ~/public_html/replacement_documentation/api/sunsys/*';
cd sunsys-dox/html
pwd
zip -r sunsys.zip *
#unzip -l sunsys.zip
ssh admbfoun@admb-foundation.org 'rm -rfv ~/public_html/replacement_documentation/api/sunsys/*';
scp -rv sunsys.zip admbfoun@admb-foundation.org:~/public_html/replacement_documentation/api/sunsys
ssh admbfoun@admb-foundation.org 'cd public_html/replacement_documentation/api/sunsys; unzip sunsys.zip';
cd $WD
pwd

cd dox/html
pwd
zip  default.zip *
#unzip -l default.zip
ssh admbfoun@admb-foundation.org 'rm -rfv ~/public_html/replacement_documentation/api/default/*';
scp -rv default.zip admbfoun@admb-foundation.org:~/public_html/replacement_documentation/api/default
ssh admbfoun@admb-foundation.org 'cd public_html/replacement_documentation/api/default; unzip default.zip';
cd $WD
pwd
#
#cp -v cadaver-script ~/.cadaver
#cadaver -V
#rm -fv ~/.cadaver
