# 1) 檢查 /ispan/test/logical 是否存在
logical="/home/ispan/test/logical"

if [ ! -e $logical ]; then
	# 2) 若不存在，則使用 touch 建立檔案並離開
	mkdir -p /home/ispan/test # -p: parents directory，用於遞迴創建目錄
	touch $logical
	echo "檔案 $logical 已建立"
	exit 0
fi

# 3) 若存在，判斷是否為檔案
if [ -f $logical ]; then # -f: file
	# 若為檔案，刪除檔案logical，接著建立logical目錄並離開
	rm $logical
	mkdir -p /home/ispan/test/logical
	echo "原有檔案已刪除，目錄 $logical 已建立"
	exit 0
fi

# 4) 若存在且為目錄，則移除此目錄
if [ -d $logical ]; then # -d: directory
    rm -r $logical
    echo "目錄 $logical 已移除"
    exit 0
fi
