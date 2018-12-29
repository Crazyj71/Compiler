P4 OPTION USED: Storage = Local (160 pts)
__________________________________________________________

P3 OPTION USED: LOCAL SCOPE OPTION (100 pts)
The stack functions are located in 'stack.cpp'
The semantic info is checked in 'static_semantics.cpp'
____________________________________________________________

P1 OPTION USED:	3 (FSA table + driver)

The FSA table is located in 'scanner.cpp'.
The FSA driver is located in 'scannner.cpp'.
--named 'int FATableDriver(char)'


P4 Running:

	[user@delmar P4]$ make
	[user@delmar P4]$ ./comp < [filename].fs18

	or
	
        [user@delmar P4]$ make
        [user@delmar P4]$ ./comp  [filename].fs18

	then

	[user@delmar P4]$ make clean

P4 Testing:

	Included are some tests for the parser, based on the Canvas
	programs for testing.

	GOOD PROGRAMS
	There are test files called P3_test1_good.fs18
	to P3_test3_good.fs18

	BAD PROGRAMS
	They are called P2_test4_bad.fs18 to P2_test7_bad.fs18
