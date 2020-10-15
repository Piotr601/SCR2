#!/bin/bash

tar cfv $3 `find -name "$1" -mtime -$2`
exit
