if [ -z $1 ]
then
	rental="***unknown vehicle***"
elif [ -n $1 ]
then
	rental=$1
fi

case $rental in
	"car"|"Car")
		echo "for $rental rs.20 per k/m"
		;;
	"van"|"Van")
		echo "for $rental rs.10 per k/m"
		;;
	"jeep"|"Jeep")
		echo "for $rental rs.5 per k/m"
		;;
	"bicycle"|"Bicycle")
		echo "for $rental rs.20 paisa k/m"
		;;
	*)
		echo "sorry, I cannot get a $rental for you"
		;;
esac
