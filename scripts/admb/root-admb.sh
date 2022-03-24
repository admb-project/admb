#!sh
#
# Copyright (c) 2013-2014 ADMB Foundation
#
shopt -s expand_aliases

if [ -z "$ADMB_VER" ]; then
  ADMB_VER=admb
fi
SCRIPT_DIR=$(cd `dirname $0` && pwd)

if [ -f "$SCRIPT_DIR/build/$ADMB_VER/bin/admb.sh" ]; then
  declare -rx ADMB_HOME="$SCRIPT_DIR/build/$ADMB_VER"
  $ADMB_HOME/bin/admb.sh $*
  exit 0
fi

if [ -f "$SCRIPT_DIR/bin/admb.sh" ]; then
  declare -rx ADMB_HOME="$SCRIPT_DIR"
  $ADMB_HOME/bin/admb.sh $*
  exit 0
fi

echo "Error: Unable to find 'admb.sh'."
exit 0
