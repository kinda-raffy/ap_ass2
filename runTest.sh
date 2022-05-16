#!/bin/bash
echo $PWD
echo "enter name of test to run: "
read testName

echo "Differences are: "

./scrabble < testCases/$testName/$testName.input > testCases/$testName/$testName.gameout;
diff -w testCases/$testName/$testName.output testCases/$testName/$testName.gameout;
 
echo "Done!"