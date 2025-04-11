# 檢查是否有參數
if [ $# -eq 0 ]; then
    echo "請輸入至少一個檔案名稱。"
    exit 1
fi

while [ $# -gt 0 ]
do
    file=$1
	
	# 檢查檔案是否存在
    if [ -e $file ]; then
        cp $file $file.bak
        echo "已將 $file 複製為 $file.bak"
    else
        echo "警告：檔案 '$file' 不存在，已跳過。"
    fi

    shift  # 移除當前參數，讓下一個參數成為 `$1`
done
