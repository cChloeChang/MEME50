if [ $1 -gt 0 ]; then
	echo "$1 is positive"
elif [ $1 -lt 0 ]; then
	echo "$1 is negative"
elif [ $1 -eq 0 ]; then
    echo "$1 is zero"
else
	echo "oops! $1 is not a number, please try again"
fi
