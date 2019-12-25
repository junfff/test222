#!/bin/zsh

#================================================================
#   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
#   
#   文件名称：func.sh
#   创 建 者：LiuJunFeng
#   创建日期：2018年07月11日 19:07(Wednesday) 
#   描    述：
#
#================================================================
echo $0
echo $1
echo $2
echo $#
echo $@
foo()
{
	echo $0
	echo $1
	echo $2
	echo $#
	echo $@
	echo "---function-----"
}

echo "-------start-------"
foo 11 22 
echo "-------end-------"
