#include <iostream>
#include "ltest.h"

using namespace std;

class LTestTest : public LTestCase {
public:
  bool testfunc_true() {
    assertTrue(true);
    return true;
  }

  bool testfunc_false() {
    assertTrue(false);
    return false;
  }

  bool throwstr() {
    throw "test";
  }
  bool testfunc_error() {
    assertTrue(throwstr());
    return false;
  }

  virtual void execute() {
    EXE(testfunc_error);
    EXE(testfunc_true);
    EXE(testfunc_false);
  }
};


int main() {
  LTestTest lt;
  lt();
  return 0;
}
