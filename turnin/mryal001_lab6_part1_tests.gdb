# Test file for "Lab6_synchSMs"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Example test:
test "State: Start, Period: 1, PORTB => 0x01"
# Set state
set state = Start
# Continue for several ticks
timeContinue 1
# Set expect values
expectPORTB 0x01
expect state light1
# Check pass/fail
checkResult

# Add tests below
test "State: Start, Period: 2, PORTB => 0x02"
set state = Start
timeContinue 2
expectPORTB 0x02
expect state light2
checkResult

test "State: Start, Period: 3, PORTB => 0x04"
set state = Start
timeContinue 3
expectPORTB 0x04
expect state light3
checkResult

test "State: Start, Period: 4, PORTB => 0x01"
set state = Start
timeContinue 4
expectPORTB 0x01
expect state light1
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
