#!/bin/bash
echo "Input Commits--Info:"  
read input  
echo "Your input is: $input"  
git add ./
git commit -m "update--> $input "
git push origin master
echo "finish !!!"
sleep 3s
exit 1
