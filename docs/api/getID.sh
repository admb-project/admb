#!/bin/bash
echo "Last Changed on `git log --date='format:%B %d, %Y' -1 $1 | grep Date | awk '{for (i=2; i<=NF; i++) print $i}'` for git-revision `git log -1 $1 | grep commit | awk '{print $2}'`."
