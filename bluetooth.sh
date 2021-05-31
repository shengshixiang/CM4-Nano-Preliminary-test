#/bin/bash 
#
# Created by andy sheng in Nov 2020
#
#bluetooth test

sudo hciconfig | grep "hci0" >/dev/null 2>&1  
if [ $? -eq 0 ]; then
exit 0
    	#echo -e "\033[32m  PASS \033[0m"
else

exit 1
	    #echo -e "\033[31m  FAIL \033[0m"
fi
