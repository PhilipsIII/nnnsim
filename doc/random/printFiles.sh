#!/bin/bash

if [ -z "$1" ]; then
    echo "Must use a find complaint search expression!"
    exit 1
fi

find . -name $1 | sed "s/^.\///" | sed "s/^/\'/" | sed "s/$/\',/"
