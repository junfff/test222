#/*================================================================
#*   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
#*   
#*   文件名称：sample.sh
#*   创 建 者：LiuJunFeng
#*   创建日期：2018年07月01日 17:02(Sunday) 
#*   描    述：
#*
#================================================================*/

#!/bin/zsh

#zhu shi 

if [ -f testa.sh ]; then
	echo "is file !!"
elif [ -d test.sh ]; then
	echo "is dir !!"
else 
	echo "not file!!"
fi

if :
then
	echo "always true"
fi
read YOU_INPUT
echo "you input: $YOU_INPUT"

case "$YOU_INPUT" in
	yse|y|YES)
		echo "you say yes !!!";;
	[nN-nB]*)
		echo "you say no !!!";;
	*)
		echo "what you say ????";;
esac
