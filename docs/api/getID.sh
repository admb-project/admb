#!/bin/bash
echo "Git Commit: `git log -1 $1 | grep commit | awk '{print $2}'`; Last Changed: `git log -1 $1 | grep Date | awk '{for (i=2; i<=NF; i++) print $i}'`"
