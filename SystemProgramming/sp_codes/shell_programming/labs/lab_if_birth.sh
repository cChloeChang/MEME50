read -p "please input your birthday (MMDD, ex&gt; 0709): " bir
now=`date +%m%d` #指定格式
if [ "$bir" == "$now" ]; then
	echo "Happy Birthday to You!!!!"
elif [ "$bir" -gt "$now" ]; then #-gt:greater than，如果bir>now，表示今年生日還沒過
	year=`date +%Y`
	total_d=$(( $((`date --date="$year$bir" +%s`-`date +%s`)) /60/60/24 )) #輸入的日期-今天日期
	echo "your birthday will be $total_d days later"
else #今年生日已過，就要算從現在到明年生日還有幾天
	year=$((`date +%Y+1`))
	total_d=$(($((`date --date="$year$bir" +%s`-`date +%s`))    /60/60/24))
	echo "your birthday will be $total_d days later"
fi
