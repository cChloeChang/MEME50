if [ $# -eq 0 ]
then
echo "$0 : you must give/supply one integer"
exit 1
fi

if test $1 -gt 0
then
echo "$1 number is positive"
else
echo "$1 number is negative"
fi
