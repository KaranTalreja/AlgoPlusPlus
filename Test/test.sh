#!/bin/sh

EXEC=$1
TESTCASELIST=$2
count=0
WORK=`pwd`/Work
mkdir -p $WORK
while read LINE ; do
count=$(($count + 1))
GOLD=`echo $LINE | awk -F ':' '{print $1}'`
INPUT_ARGS=`echo $LINE | awk -F ':' '{print $2}'`
TEST=`basename $GOLD`
TEST="TEST_$TEST"
DIFF_FILE="DIFF_$TEST"
$EXEC $INPUT_ARGS > $WORK/$TEST
DIFF=`diff $GOLD $WORK/$TEST`
if [ -z "$DIFF" ]; then
    echo "TESTCASE $count:PASSED"
    rm $WORK/$TEST
else 
    echo "TESTCASE $count:FAILED $GOLD <=!=> $INPUT_ARGS"
    echo "$DIFF" > $WORK/$DIFF_FILE 
fi
done < $TESTCASELIST
find $WORK -type d -empty -delete 
