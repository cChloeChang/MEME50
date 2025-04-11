for file in *
do
	# 檢查是否為檔案，且檔名含有大寫字母
    if [ -f "$file" ] && [ "$file" != "$(echo "$file" | tr 'A-Z' 'a-z')" ]
	then
        lowercase=$(echo "$file" | tr 'A-Z' 'a-z') # 大寫轉小寫
        
        # 檢查是否已存在同名檔案，避免覆蓋
        if [ "$file" != "$lowercase" ]; then
            mv "$file" "$lowercase"
            echo "已將 $file 重新命名為 $lowercase"
        fi
    fi
done
