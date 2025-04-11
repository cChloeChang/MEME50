# 檢查是否為數字
case $1 in
    ''|*[!0-9]*) 
		echo "輸入錯誤"
		exit 1
		;;
    *) ;;  # 如果是數字，繼續
esac

if [ $1 -le 100 -a $1 -ge 90 ]; then
	echo "優等"
elif [ $1 -le 89 -a $1 -ge 80  ]; then
	echo "甲等"
elif [ $1 -le 79 -a $1 -ge 70  ]; then
	echo "乙等"
elif [ $1 -le 69 -a $1 -ge 60 ]; then
	echo "丙等"
elif [ $1 -le 50 -a $1 -ge 0 ]; then
	echo "不及格"
else
	echo "輸入錯誤"
fi
