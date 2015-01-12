#!/bin/bash

#
# Sets the ADMB Home directory.
#
export ADMB_HOME=~/admb

#
# Adds the ADMB bin directory to $PATH.
#
export PATH=$ADMB_HOME/bin:$PATH

printf "Set the ADMB Home directory to $ADMB_HOME\n"
