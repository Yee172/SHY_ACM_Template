#!/bin/zsh

folderpath=$(cd `dirname $0`; pwd)
cd $folderpath
printf "compiling ......\n"
g++-9 -o test test.cpp
g++-9 -o standard standard.cpp
printf "compile finished\n"
test=1
while true
do
	python3 random_generator.py > in.txt
	printf %s%02d%s'\n' "-----------test: " $test "-----------"
	test=$[$test+1]
	./standard < in.txt > standard_out.txt
	./test < in.txt > test_out.txt
	python3 special_judge.py > special_judge.txt
	if diff special_judge.txt AC.txt
	then
		printf AC'\n'
	else
		printf WA'\n'
		exit 0
	fi
done
