#include "ltest.h"

using namespace std;

TESTSUITE(TestMultipleUse)
    void execute() {
        testlog("Hello %d", __LINE__);
    }
ENDSUITE(TestMultipleUse)
