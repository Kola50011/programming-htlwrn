#!/bin/bash
touch output.txt
for filename in ./*.cpp; do
    echo "#############################################################################" >> output.txt
    echo $filename >> output.txt
    echo "#############################################################################" >> output.txt

    nl -b a $filename >> output.txt
done

for filename in ./*.h*; do
    echo "#############################################################################" >> output.txt
    echo $filename >> output.txt
    echo "#############################################################################" >> output.txt
    
    nl -b a $filename >> output.txt
done

for filename in ./*.ui; do
    echo "#############################################################################" >> output.txt
    echo $filename >> output.txt
    echo "#############################################################################" >> output.txt
    
    nl -b a $filename >> output.txt
done

enscript output.txt -2 -q -Ecpp --color --tabsize=4 -r --header="$1 $2 $3 $4 $5 $6|%W|Page $% of $=" -o - | ps2pdf - output.pdf
xdg-open output.pdf
rm -rf output.txt