osch=0
echo "1. UNIX (Sun OS)"
echo "2. Linux (Red Hat)"
echo -n "select your OS choice [1 or 2]?"
read osch
if [ $osch -eq 1 ]; then
	echo "You pick up UNIX (Sun OS)"
else
	if [ $osch -eq 2 ]; then
		echo "You pick up Linux (Red Hat)"
	else
		echo "What you don't like UNIX/Linux OS"
	fi
fi
