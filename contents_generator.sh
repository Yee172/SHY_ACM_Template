#!/bin/zsh

folderpath=$(cd `dirname $0`; pwd)
cd $folderpath
tree > ./Contents/CONTENTS.txt
echo ------------------------------------
echo " Successfully generated CONTENT.txt"
echo ------------------------------------
cd Contents
python3 dot_generator.py
echo "   Successfully generated tmp.dot"
echo ------------------------------------
dot tmp.dot -T png -o CONTENTS.png
echo " Successfully generated CONTENTS.png"
echo ------------------------------------
rm tmp.dot
echo "              Finished"
echo ------------------------------------
