rem This script runs a G++ compiler against a provided file;
rem and reports success if compilation failed, and failure when compilation succeeded
g++ %1 2> NUL
if %errorLevel% NEQ 0 (echo TEST PASSED: compilation failed) else (echo TEST FAILED: compilation succeeded)
