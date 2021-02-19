#!sh

TARGET=$1

echo # target: ${TARGET}

if [ -e ${TARGET}.std ]; then cat ${TARGET}.std; fi
if [ -e ${TARGET}.par ]; then cat ${TARGET}.par; fi
if [ -e ${TARGET}.p01 ]; then cat ${TARGET}.p01; fi
if [ -e ${TARGET}.cor ]; then cat ${TARGET}.cor; fi
if [ -e ${TARGET}.eva ]; then cat ${TARGET}.eva; fi
if [ -e ${TARGET}.prf ]; then cat ${TARGET}.prf; fi
