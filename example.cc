#include <iostream>
#include "ltest.h"

using namespace std;

class LTestTest : public LTestCase {
public:
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
};


int main() {
  LTestTest lt;
  lt();
  return 0;
}
