#!/bin/bash

git show -s --format=%H HEAD > GITVERSION
git archive --verbose --format zip --prefix=admb/ --output admb-"`cat VERSION`"-src.zip HEAD .
