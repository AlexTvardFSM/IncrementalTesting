Converting test input sequences of FSM abstraction to timed input sequences for the FSM with timeouts and (optional) removing sequences under the assemption that only a part of the transitions needs to be checked (Incremental testing).

The application has a three parameters 
(1) the name of the given TFSM file.
The application works with .fsm files (More information are given in the link http://www.fsmtestonline.ru/ ). 
An example of an FSM with timeouts in the .fsm format is in the repository (file 0.fsm). 
In addition to classical FSM transitions, for a TFSM we also specify timeout transitions at states in the form “s1 t s2”, where 
s1 is a starting state of the transition, 
t is timeout value, 
s2 is an end state of the transition.
As an example "0 2 1" is timeout at state 0 in file 0.fsm. 
The fifth component of the transitions is the delay and it is ignored in this implementation.

(2) the name of the test file.
Every line of the file is a sequence of the test where the inputs are represented by integers from 0 to n (n is number of TFSM inputs). Input n is a special abstract input.
An example of the test is in the repository (file test.txt). 

(3) the name of the file with the modified transitions numbers.
First line contains numbers of modified transitions.
Second line contains numbers of modified timeouts.
If this parameter is set, then sequences that do not cover the marked transitions will be deleted.
An example of the modified transitions is in the repository (file mod.txt). 

The application returns the timed test suite where every line of the file is a timed input sequence.
The obtained test file contains a postfix “_res” in the filename.

Example of running an application:
in_time_test.exe D:\0.fsm D:\test.txt D:\mod.txt 
in_time_test.exe D:\0.fsm D:\test.txt (trasformation test to timed test without removing sequences)

Note: We also provide the code of the tool which is written in C++ and can run under operating system Windows.