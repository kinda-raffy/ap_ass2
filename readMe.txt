All tests are held in /testCases/<testName>

To run the tests, use the script runTest.sh

The script will prompt you to input the name of the test, which is the name of the folder that the test files are held in.

Differences are only expected when they are due to randomness, and not related to the test itself. (Such as a random bag on a test which tests the menu)

Tests with clrf line endings may not work correctly.

Tests saveGame and multipleSaves's saves will not be checked by this script. A full script will be needed in this circumstance.

example:
$ ./runTest.sh
enter name of test to run:
$ <testName>
Differences are:
<differences>   <---- These are the differences between the .output file and the actual output.
Done!
$ <--- program finished.