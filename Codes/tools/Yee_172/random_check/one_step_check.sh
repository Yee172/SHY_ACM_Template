#!/bin/zsh

folderpath=$(cd `dirname $0`; pwd)
cd $folderpath
printf "compiling ......\n"
g++-9 -o test test.cpp
g++-9 -o standard standard.cpp
printf "compile finished\n"
./standard < in.txt > standard_out.txt
./test < in.txt > test_out.txt
if diff standard_out.txt test_out.txt
then
	printf AC'\n'
elif diff -B -b standard_out.txt test_out.txt
then
	printf PE'\n'
else
	printf WA'\n'
	exit 0
fi
