#!/bin/bash
echo "git add . && git commit -m \"${1}\""
git add .
Message="nothing special"
if [ $# = 2 ]; then
	Message="${2}"
fi

git commit -m "${Message}"
git push origin master

