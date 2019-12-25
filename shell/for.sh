#!/bin/zsh

#================================================================
#   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
#   
#   文件名称：for.sh
#   创 建 者：LiuJunFeng
#   创建日期：2018年07月03日 23:07(Tuesday) 
#   描    述：
#
#================================================================

for FRUIT in apple banana pear
do
	echo "i like $FRUIT"
done

for f in $(ls) 
do
	#echo "filename: $f"
	if [ -d "$f" ]
	then
		echo "it is dir -> $f"
	elif [ -f "$f" ] 
	then
		echo "it is file -> $f"
		sudo chmod +x $f
	else
		echo "is other !!"
	fi
done
