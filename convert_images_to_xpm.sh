#!/bin/sh

for file in *.png; do convert $file "`basename $file .png`.xpm"; done