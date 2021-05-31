#/bin/bash 
#
# Created by andy sheng in Nov 2020
#
ls  /sys/class/gpio/gpio6 >/dev/null 2>&1  #检测是否存在GPIO6配置文件
	if [ $?  -ne 0 ]; then                  #没有
     sudo echo 6 > /sys/class/gpio/export           
	fi

function buzzer()
{
    sudo echo out > /sys/class/gpio/gpio6/direction
	sudo echo 1 > /sys/class/gpio/gpio6/value
	sleep 0.3
	sudo echo 0 > /sys/class/gpio/gpio6/value 
}
buzzer
if [ $?  -eq 0 ]; then   
	exit 0
else
	exit 1
fi
#询问蜂鸣器




