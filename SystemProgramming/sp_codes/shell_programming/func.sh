function printit(){
	echo -n "Your choice is "
}

echo "This program will print your selection"
case $1 in
	"one")
		printit; echo $1|tr 'a-z' 'A-Z' #將參數做大小寫轉換
		;;
	"two")
		printit; echo $1|tr 'a-z' 'A-Z'
		;;
	"three")
		printit; echo $1|tr 'a-z' 'A-Z'
		;;
	*)
		echo "Usage $0 {one|two|three}"
		;;
esac
