while true; do  
./make>tmp.in #出数据  
./tmp<tmp.in>tmp.out #被测程序  
./tmp2<tmp.in>tmp2.out #正确（暴力）程序  
if diff tmp.out tmp2.out; then #比较两个输出文件  
printf AC #结果相同显示AC  
else  
echo WA #结果不同显示WA，并退出  
#cat tmp.out tmp2.out  
exit 0  
fi #if的结束标志,与C语言相反，0为真  
done # while的结束标志  
  
#BY NICK WONG 2014-08-29  
#在终端下，进入当前目录，输入"sh ./nick.sh",（其中nick.sh为当前shell脚本名） '#'表示单行注释  
#diff在两文件相同时返回空串  