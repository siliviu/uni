SCRIPT_PATH=$1
THREADS=$2
THREADS_R=$3
MAX_CAP=$4
FILE_OUTPUT=$5
RETRIES=$6
INDEX=1

THREADS_W=$(($THREADS-$THREADS_R))

RESULTS=()


echo "TW $THREADS_W"

if [ -f "$FILE_OUTPUT" ]; then
    echo "$FILE_OUTPUT exists. Output will be appended"
    INDEX=$(tail -n1 $FILE_OUTPUT | cut -d"," -f1)
    INDEX=$((INDEX+1))
else 
    echo "$FILE_OUTPUT does not exist. A new file will be createdi"
    echo "trial_no,program,threads_w,threads_r,max_cap,average_time" > $FILE_OUTPUT
fi

./generator
./sequential correct.txt

for i in $(seq 1 $RETRIES); do 
	echo "Trial no:" $i "for" $SCRIPT_PATH "with" $THREADS "threads."
    if [ $THREADS -eq 1 ]; then
        result=$(./sequential output.txt)
    else
        result=$(./$SCRIPT_PATH $THREADS_R $THREADS_W $MAX_CAP output.txt)

    fi;
    diff -w ./output.txt ./correct.txt
    if [ $? -eq 1 ]; then
        echo "Incorrect answer"
    # else
        # echo "Correct answer " $result
    fi;
    RESULTS+=($result)
done

total=0
sum=0
for i in "${RESULTS[@]}"
do
	sum=`expr $sum + $i`
        total=`expr $total + 1`
done
average=`expr $sum / $total`
echo $INDEX","$SCRIPT_PATH","$THREADS_W","$THREADS_R","$MAX_CAP","$average >> $FILE_OUTPUT
