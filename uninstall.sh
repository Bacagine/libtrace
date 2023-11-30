#!/bin/bash
# 
# uninstall.sh
# 
# Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
#
# Description: This is the uninstallation script of trace C Library.
#
# Date: 2023-09-22
#

rm -r /usr/include/trace
rm -r /usr/lib/libtrace.so
rm -r /usr/share/man/man1/trace.1.gz
rm -r /usr/share/doc/trace

