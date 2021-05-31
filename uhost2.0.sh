
#/bin/bash 
#
# Created by andy sheng in Nov 2020
#
	
function uhost2.0()
{
	echo "input "
    read -t 2 key_value
	#echo "get $key_value "
}
uhost2.0
if [ $? -eq 0 ]; then
	exit 0
else
	exit 1
fi



