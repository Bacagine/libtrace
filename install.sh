#!/bin/bash
# 
# install.sh
# 
# Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
#
# Description: This is the installation script of trace C Library.
#
# Date: 2023-09-22
#

gzip ./man/trace.1
gzip ./doc/libtrace-user-guide.pdf
gzip ./ChangeLog
gzip ./LICENSE
gzip ./AUTHORS
gzip ./NEWS
gzip ./README
gzip ./INSTALL

cp -r include/trace/ /usr/include/
cp -r lib/libtrace.so /usr/lib/libtrace.so
cp -r ./man/trace.1.gz /usr/share/man/man1

mkdir /usr/share/doc/trace
cp -r ./doc/*.gz /usr/share/doc/trace
cp -r ./ChangeLog.gz ./LICENSE.gz ./AUTHORS.gz ./NEWS.gz ./README.gz ./INSTALL.gz /usr/share/doc/trace

