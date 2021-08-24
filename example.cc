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
};


int main() {
  LTestTest lt;
  try {
    throw "fail";
  }
  catch(const char * e) {
    cout << e << endl;
  }
  catch(...) {
    cout << "ERROR" << endl;
  }
  lt.testfunc_error();
  lt.testfunc_true();
  lt.testfunc_false();
  return 0;
}
