#!/bin/bash

mkdir -p build/admb
git show -s --format=%H HEAD > build/admb/GITVERSION
git archive --verbose --format zip --prefix=admb/ --output build/admb-"`cat VERSION`"-"`git show -s --format=%h`"-src.zip HEAD .
cd build && zip -u admb-"`cat ../VERSION`"-"`git show -s --format=%h`"-src.zip admb/GITVERSION
