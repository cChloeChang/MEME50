for file in *.html; do
	if [ -f "$file" ]; then
		echo "處理檔案: $file"
		head -2 "$file" >> file_heads # >>不覆蓋原內容
		echo "" >> file_heads  # 在每個檔案的內容之後加上換行
	fi
done
echo "done"
