#!/bin/bash

set -eo pipefail

OPT_NOCHECK_ADD="--nocheck-add"

git status
echo "Here are your changes."
read -rp "Changes to add: " changes
git add "$changes"

if [[ "$1" == "$OPT_NOCHECK_ADD" ]]; then
    git status
    read -rp "Confirm add (y/n): " confirm

    if [[ "$confirm" != "y" ]]; then
        git rm --cached "$changes"
        echo "Cancelled."
        exit 0
    fi
fi

git commit

read -rp "Push? (y/n): " push_confirm
if [[ "$push_confirm" == 'y' ]]; then
    git push -u origin master
fi