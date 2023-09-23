#!/bin/bash
# 
# install.sh
# 
# Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
#
# Description: This script remove *.log files created in the current direcotry.
#
# Date: 2023-09-22
#

if test -f *.log; then
  rm -r *.log
fi

