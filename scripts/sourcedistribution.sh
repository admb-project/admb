#!/bin/bash

mkdir -p build/admb
git show -s --format=%H HEAD > build/admb/GITVERSION
mkdir -p build/sourcedistribution
git archive --verbose --format zip --prefix=admb/ --output build/sourcedistribution/admb-"`cat VERSION`"-"`git show -s --format=%h`"-src.zip HEAD .
cd build && zip -u sourcedistribution/admb-"`cat ../VERSION`"-"`git show -s --format=%h`"-src.zip admb/GITVERSION
cd build/sourcedistribution && ln -sf admb-"`cat ../VERSION`"-"`git show -s --format=%h`"-src.zip admb-latest-src.zip
