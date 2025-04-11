read -p "please input(Y/N): " yn
[ "$yn" == "Y" -o "$yn" == "y" ] && echo "ok, continue" && exit 0
[ "$yn" == "N" -o "$yn" == "n" ] && echo "oh, interrupt!" && exit 0
echo "I don't know what your choice is" && exit 0
