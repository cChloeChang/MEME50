for file in *.htm; do
    # 檢查是否為檔案(避免空目錄出錯)
    if [ -f "$file" ]; then
        newfile="${file%.htm}.html"  # 把.htm替換成.html，${變數名%字串}在課本45頁
        if [ "$file" != "$newfile" ]; then
            mv "$file" "$newfile"
            echo "已將 $file 重新命名為 $newfile"
        fi
    fi
done
