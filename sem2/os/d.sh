if [ $# -eq 0 ]
then
    echo INVALID
fi

declare -i A=$1

read B

echo $(($A+$B))


