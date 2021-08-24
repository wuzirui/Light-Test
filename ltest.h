#ifndef __LTest_H__
#define __LTest_H__

#include <iostream>


class LTestCase {
  public:
    virtual void execute() {}
    void operator() () {
      test_num = test_pass = test_error = 0;
      std::cout << "##################" << std::endl;
      std::cout << "#  Test Running  #" << std::endl;
      std::cout << "##################" << std::endl;

      execute();
      std::cout << "##################" << std::endl;
      if (test_num == test_pass) {
        std::cout << "Test Passed" << std::endl;
      }
      else {
        std::cout << "Pass " << test_pass << ", Fail " << test_num - test_error - test_pass;
        std::cout << ", Error " << test_error << std::endl;
      }
    }
#define CurPos "( " << __FILE__ << " : " << __LINE__ << " )"

#define ERRMSG(msg)\
  std::cout << "Error " << CurPos << ": " << msg << "." << std::endl; \
  running_result = -1; \
  return;

#define ENV( statements ) \
  try {\
    statements \
  } catch(exception & e) {\
    ERRMSG(e.what()) \
  } catch(std::string & e) {\
    ERRMSG(e) \
  } catch(const char * e) {\
    ERRMSG(e) \
  } catch(int e) {\
    ERRMSG("ErrCode = " << e) \
  } catch(...) {\
    ERRMSG("Unknown Error") \
  }

#define CASE(name) void SUITE_##name()

#define EXE(testname) \
    std::cout << "Running: case=" << #testname << "... " << std::endl; \
    running_result = 0; \
    SUITE_##testname(); \
    test_pass += running_result == 0; \
    test_num++; \
    test_error += running_result == -1;

#define assertTrue(cond) \
  ENV(\
    if (!(cond)) {\
      std::cout << "Assertion Failed" << CurPos << " : suppose " << #cond << " == true, but got false instead." << std::endl; \
      running_result = 1; \
      return; \
    })
  protected:
    int test_num, test_pass, test_error;
    int running_result;
};

#endif
