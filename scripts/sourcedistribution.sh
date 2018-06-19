#!/bin/bash

mkdir -p build/admb
git show -s --format=%H HEAD > build/admb/GITVERSION
git archive --verbose --format zip --prefix=admb/ --output admb-"`cat VERSION`"-src.zip HEAD .
cd build && zip -u ../admb-"`cat ../VERSION`"-src.zip admb/GITVERSION
