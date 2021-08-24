#include <iostream>
#include "ltest.h"

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
  void execute() {
    EXE(testfunc_true);
    EXE(testfunc_false);
    EXE(testfunc_error);

  }
ENDSUITE

class A {public: int i = 1;} a;
int main() {
  RunAllTests();
  return 0;
}
