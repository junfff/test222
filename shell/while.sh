#!/bin/zsh

#================================================================
#   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
#   
#   文件名称：while.sh
#   创 建 者：LiuJunFeng
#   创建日期：2018年07月03日 23:44(Tuesday) 
#   描    述：
#
#================================================================
try=NULL
while [ "$try" != "123" ]
do
	if [ "$try" != NULL ]
	then
		echo "sorry try again !!"
	fi
	read try
done

echo "you are ok !!"
