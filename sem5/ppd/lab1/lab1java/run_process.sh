SCRIPT_PATH=$1
N=$2
M=$3
NN=$4
MM=$5
STRATEGY=$6
THREADS=$7
FILE_OUTPUT=$8
RETRIES=$9
INDEX=1

RESULTS=()

if [ -f "$FILE_OUTPUT" ]; then
    echo "$FILE_OUTPUT exists. Output will be appended"
    INDEX=$(tail -n1 $FILE_OUTPUT | cut -d"," -f1)
    INDEX=$((INDEX+1))
else 
    echo "$FILE_OUTPUT does not exist. A new file will be createdi"
    echo "trial_no,program,N,n,strategy,threads,average_time" > $FILE_OUTPUT
fi

./generator $N $M $NN $MM
java -jar $SCRIPT_PATH 1 "LINE" "correct.txt"

for i in $(seq 1 $RETRIES); do 
	echo "Trial no:" $i "for" $SCRIPT_PATH "with" $THREADS "threads."
	result=$(java -jar $SCRIPT_PATH $THREADS $STRATEGY "output.txt")
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
echo $INDEX","$SCRIPT_PATH","$N","$NN","$STRATEGY","$THREADS","$average >> $FILE_OUTPUT
