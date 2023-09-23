#!/bin/bash
# 
# uninstall.sh
# 
# Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
#
# Description: This is the uninstallation script of log C Library.
#
# Date: 2023-09-22
#

rm -r /usr/include/log
rm -r /usr/lib/liblog.so
rm -r /usr/share/man/man1/log.1.gz
rm -r /usr/share/doc/log

