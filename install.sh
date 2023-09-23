#!/bin/bash
# 
# install.sh
# 
# Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
#
# Description: This is the installation script of log C Library.
#
# Date: 2023-09-22
#

gzip ./man/log.1
#gzip ./doc/*
gzip ./ChangeLog
gzip ./LICENSE
gzip ./AUTHORS
gzip ./NEWS
gzip ./README
gzip ./INSTALL

cp -r include/log/ /usr/include/
cp -r lib/liblog.so /usr/lib/liblog.so
cp -r ./man/log.1.gz /usr/share/man/man1

mkdir /usr/share/doc/log
cp -r ./doc/* /usr/share/doc/log
cp -r ./ChangeLog.gz ./LICENSE.gz ./AUTHORS.gz ./NEWS.gz ./README.gz ./INSTALL.gz /usr/share/doc/log

