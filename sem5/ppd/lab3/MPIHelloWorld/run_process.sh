SCRIPT_PATH=$1
TEST=$2
PROCESS=$3
FILE_OUTPUT=$4
RETRIES=$5
INDEX=1

RESULTS=()

if [ -f "$FILE_OUTPUT" ]; then
    echo "$FILE_OUTPUT exists. Output will be appended"
    INDEX=$(tail -n1 $FILE_OUTPUT | cut -d"," -f1)
    INDEX=$((INDEX+1))
else 
    echo "$FILE_OUTPUT does not exist. A new file will be createdi"
    echo "trial_no,program,test,processes,average_time" > $FILE_OUTPUT
fi

./generator $TEST
./sequential
cp Numar3.txt Correct.txt

for i in $(seq 1 $RETRIES); do 
	echo "Trial no:" $i "for" $SCRIPT_PATH "with" $PROCESS "processes."
    if [ $PROCESS -eq 1 ]; then
        result=$(./$SCRIPT_PATH)
    else
        result=$(mpirun --oversubscribe -np $PROCESS $SCRIPT_PATH)

    fi;
    diff -w ./Numar3.txt ./Correct.txt
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
echo $INDEX","$SCRIPT_PATH","$TEST","$PROCESS","$average >> $FILE_OUTPUT
