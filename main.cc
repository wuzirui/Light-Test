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
    testfunc_true();
    testfunc_false();
    testfunc_error();
  }
};


int main() {
  LTestTest lt;
  lt();
  return 0;
}
