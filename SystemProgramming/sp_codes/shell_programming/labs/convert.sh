# 一個十進位數字轉換成指定的進位制(二進位、八進位或十六進位)，並輸出結果
while [ "$1" ] # 有傳入參數時進入迴圈
do
	if [ "$1" == "-b" ]; then # 檢查第一個參數是否為 -b，表示user指定的進位制
		ob="$2" # 把第二個參數$2(進位制的值，例如 16、8 或 2）存入變數 ob

		case $ob in
			16) basesystem="Hex";;
			8) basesystem="Oct";;
			2) basesystem="bin";;
			*) basesystem="Unknown";;
		esac
		shift 2 # 將命令列參數向左移動兩位。例如，原本 $1=-b, $2=2, $3=-n, $4=100，執行後 $1=-n, $2=100，這樣下一輪迴圈就能處理下一個參數
	elif [ "$1" == "-n" ] # 檢查第一個參數是否為-n，表示要待轉換的十進位數字
	then
		num="$2" # 將第二個參數$2(十進位數字，例如100)存入num
		shift 2 # 同樣將參數左移兩位，準備處理下一個參數
	else # 如果$1不是-b也不是-n，則進入else
		echo "Program $0 does not recognize option $1"
		exit 1
	fi
done

output=`echo "obase=$ob; ibase=10; $num;"|bc` # obase=$ob輸出進位制，ibase=10輸入進位制為10進位，$num為要轉換的數字
# |bc：將指令傳給bc工具執行，計算結果並存入output
echo "$num Decimal number = $output in $basesystem number system(base=$ob)"
