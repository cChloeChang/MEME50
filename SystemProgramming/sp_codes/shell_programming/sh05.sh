echo -e "please input a filename, I will check the filename's type and permission. \n\n"
read -p "input a filename: " filename
test -z $filename && echo "you must input a filename." && exit 0

# 判斷檔案是否存在，若不存在則顯示訊息並結束腳本
test ! -e $filename && echo "The filename '$filename' DO NOT exist" && exit 0

# 判斷檔案類型與屬性
test -f $filename && filetype="regular file"
test -d $filename && filetype="directory"
test -r $filename && perm="readable"
test -w $filename && perm="$perm writable"
test -x $filename && perm="$perm executable"

# 輸出資訊
echo "The filename: $filename is a $filetype"
echo "And the permissions are: $perm"
