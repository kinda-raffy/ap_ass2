#!/bin/bash
echo "enter name of test to create output of: "
read testName

./scrabble < testCases/$testName/$testName.input > testCases/$testName/$testName.output;
 
echo "Done!"
