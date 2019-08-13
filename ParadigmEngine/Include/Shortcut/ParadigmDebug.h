#ifndef _PARADIGMDEBUG_H_
#define _PARADIGMDEBUG_H_

#include <FPrint.h>
#include <ParadigmException.h>
#include <SUnitTest.h>

#define PRINT(X, log_level) FPrint::Print(X, log_level);

/** After this the nexts unit test functions of this file will be considered like member fonctions of the specified class.
Untill another UNIT_TEST_CLASS is specified or use UNIT_TEST_END_CLASS*/
#define UNIT_TEST_CLASS(CLASSNAME, ...)

/** Stop to Use the previous specified class for fuctions. 
If no classes have been specified do nothing*/
#define UNIT_TEST_END_CLASS

/** Set a unit test for the specified function approved if no crash append*/
#define UNIT_TEST_NOCRASH(FUNCNAME, ...)
/** Set a unit test for the specified function approved if a crash append*/
#define UNIT_TEST_CRASH(FUNCNAME, ...)

/** Set a unit test for the specified function approved if function return is equal to attempted result.
Attempted result need to be specified on the same line with UNIT_TEST_EXPECTEDRESULT.
UNIT_TEST_NOCRASH is included whith this test.*/
#define UNIT_TEST_COMPARE(FUNCNAME, ...)
/** Set a unit test for the specified function approved if the float returned by function is equal to attempted result.
Attempted result need to be specified on the same line with UNIT_TEST_EXPECTEDRESULT.
UNIT_TEST_NOCRASH is included whith this test.*/
#define UNIT_TEST_COMPARE_scalarS(FUNCNAME, ...)
/** Specify an attempted result for the just previous UNIT_TEST_COMPARE*/
#define UNIT_TEST_EXPECTEDRESULT(AttemptdedResult, ...)

/** Set a unit test for the specified function approved if the function return true.
UNIT_TEST_NOCRASH is included whith this test.*/
#define UNIT_TEST_ISTRUE(FUNCNAME, ...)
/** Set a unit test for the specified function approved if the function return false.
UNIT_TEST_NOCRASH is included whith this test.*/
#define UNIT_TEST_ISFALSE(FUNCNAME, ...)

//this is an using example
//UNIT_TEST_COMPARE(Foo,10,"Fooparam2") UNIT_TEST_EXPECTEDRESULT(10) 

#endif