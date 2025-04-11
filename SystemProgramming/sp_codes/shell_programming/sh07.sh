echo "The script name is    ==> $0"
echo "Total parameter number is ==> $#"
[ "$#" -lt 2 ] && echo "The number of parameteris less than 2. Stop here." && exit 0
echo "Your whole parameter is  ==> '$@'"
echo "The first parameter    ==> $1"
echo "The second parameter    ==> $2"
