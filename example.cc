#include <iostream>
#include "ltest.h"
#include "main.cc"

using namespace std;

TESTSUITE(LTSuite)
  CASE(testfunc_true) {
    assertTrue(true);
  }

  CASE(testfunc_false) {
    assertTrue(false);
  }

  bool throwstr() {
    throw "error string";
  }

  CASE(testfunc_error) {
    assertTrue(throwstr());
  }

  CASE(test_assertEqual) {
    testlog("Log information %d + %d = %d .", 1, 1, 1 + 1);
    assertEqual(1 + 1, 2);
  }

  void execute() {
    EXE(testfunc_true);
    EXE(testfunc_false);
    EXE(testfunc_error);
    EXE(test_assertEqual);
  }
ENDSUITE(LTSuite)

TESTSUITE(LT_Pass)
    
    CASE(test_pass) {
        assertEqual(1 + 1, 2);
    }

    CASE (test_pass_2) {
        assertTrue(true);
    }

    void execute() {
        EXE(test_pass);
        EXE(test_pass_2);
    }
ENDSUITE(LT_Pass)

int main() {
  return RunAllTests();
}
