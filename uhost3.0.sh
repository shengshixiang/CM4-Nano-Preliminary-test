
#/bin/bash 
#
# Created by andy sheng in Nov 2021
#






	
function uhost3.0()
{
	
   #Class=Mass Storage, Driver=usb-storage, 5000M
	lsusb -t | grep "Class=Mass Storage, Driver=usb-storage, 5000M" >/dev/null 2>&1  
	if [ $?  -eq 0 ]; then                 
		return 0
	else
		return 1
	fi
	
  
}
uhost3.0
if [ $? -eq 0 ]; then
	exit 0
else

	exit 1
fi



