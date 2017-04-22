#!/bin/bash
# This script runs a G++ compiler against a provided file;
# and reports success if compilation failed, and failure when compilation succeeded
g++ $1 2>/dev/null
if [ $? -eq 0 ]
then
	echo TEST FAILED: compilation succeeded
else
	echo TEST PASSED: compilation failed
fi
