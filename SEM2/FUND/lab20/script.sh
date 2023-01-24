#!/bin/bash
indexes=$(awk -F"\n" '/TaskInProgress=*/ {
x = $0
if (index(x,"no") == 0)
{
    printf "yes"
} else {
    printf "no"
}
}' Task.txt)
if [ $indexes = no ]
then
name=$(awk -F"\n" '/CreateDir=*/ {
x = $0
printf "%s", substr(x, 11, length(x) - 10)
}' Task.txt)
mkdir ~/Projects/$name
files=$(awk -F"\n" '/CreateFiles:/ {
printf "start"
}' Task.txt)
if [ $files = "start" ]
then
namefile=$(awk -F"\n" '/-*.*[.,]/ {
x = $0
printf "%s ", substr(x, 0, length(x) - 1)
}' Task.txt)
cd ..
cd $name
touch $namefile
cd ..
cd lab20
awk -F"\n" '{
    if ($0 ~ /TaskInProgress=no/) {
        print "TaskInProgress=yes"
    } else {
        print $0
    }
}' Task.txt > New.txt
rm Task.txt
mv New.txt Task.txt
fi
else
name=$(awk -F"\n" '/CreateDir=*/ {
x = $0
printf "%s", substr(x, 11, length(x) - 10)
}' Task.txt)
files=$(awk -F"\n" '/Flags:/ {
printf "start"
}' Task.txt)
if [ $files = start ] 
then
flags=$(awk -F"\n" '/(\-)+/ {
x = $0
printf "%s ", x
}' Task.txt)
gcc $flags ~/Projects/$name/main ~/Projects/$name/main.c 
cd ..
cd $name
./main
fi
fi
