#ifndef H_COLORWHEEL
#define H_COLORWHEEL

/*  forked from https://github.com/Totoditoto/colorwheel */

#include <unistd.h>
#include <stdio.h>

#define CW_TRACE(hd, ...)                                      \
    do                                                         \
    {                                                          \
        fprintf(stderr, "%s:%d/%s(): " hd, __FILE__, __LINE__, \
                __func__, ##__VA_ARGS__);                      \
        fflush(stderr);                                        \
    } while (0)

#define CW_CMD(color_code) "\033[1;" #color_code "m"

/* Style */
#define CW_BRIGHT CW_CMD(1)
#define CW_DIM CW_CMD(2)

/* Foreground colors */
#define CW_RESET CW_CMD(0)
#define CW_BLACK CW_CMD(30)
#define CW_RED CW_CMD(31)
#define CW_GREEN CW_CMD(32)
#define CW_YELLOW CW_CMD(33)
#define CW_BLUE CW_CMD(34)
#define CW_PURPLE CW_CMD(35)
#define CW_CYAN CW_CMD(36)
#define CW_WHITE CW_CMD(37)

/* Special commands */
#define CW_ITALIC CW_CMD(03)
#define CW_UNDERLINE CW_CMD(04)

/* Background colors */
#define CW_BG_BLACK CW_CMD(40)
#define CW_BG_RED CW_CMD(41)
#define CW_BG_GREEN CW_CMD(42)
#define CW_BG_YELLOW CW_CMD(43)
#define CW_BG_BLUE CW_CMD(44)
#define CW_BG_PURPLE CW_CMD(45)
#define CW_BG_CYAN CW_CMD(46)
#define CW_BG_WHITE CW_CMD(47)

/* Predefined message styles */

// Normal colored text
#define CW_NORMAL(msg, ...) CW_RESET " " msg " " CW_RESET "\n"

// White text over red background for extreme warning information
#define CW_ALARM(msg, ...) CW_BRIGHT CW_WHITE CW_BG_RED " " msg " " CW_RESET "\n"

// Red text over normal background for critical fault information
#define CW_CRITICAL(msg, ...) CW_BRIGHT CW_RED " " msg " " CW_RESET "\n"

// Yellow text over grey background for fault information
#define CW_FAULT(msg, ...) CW_BRIGHT CW_YELLOW CW_BG_BLACK " " msg " " CW_RESET "\n"

// Green text over grey background for confirmation/success information
#define CW_VALID(msg, ...) CW_BRIGHT CW_GREEN CW_BG_BLACK " " msg " " CW_RESET "\n"

// Blue text over normal background for noticeable information
#define CW_INFO(msg, ...) CW_BRIGHT CW_BLUE " " msg " " CW_RESET "\n"

/* Predefined printf styled messages */
#define CW_PRINT_NORMAL(msg, ...) printf(CW_NORMAL(msg), ##__VA_ARGS__);
#define CW_PRINT_ALARM(msg, ...) printf(CW_ALARM(msg), ##__VA_ARGS__);
#define CW_PRINT_CRITICAL(msg, ...) printf(CW_CRITICAL(msg), ##__VA_ARGS__);
#define CW_PRINT_FAULT(msg, ...) printf(CW_FAULT(msg), ##__VA_ARGS__);
#define CW_PRINT_VALID(msg, ...) printf(CW_VALID(msg), ##__VA_ARGS__);
#define CW_PRINT_INFO(msg, ...) printf(CW_INFO(msg), ##__VA_ARGS__);

/* Predefined CW_ styled messages */
#define CW_TRACE_NORMAL(msg, ...) CW_TRACE(CW_NORMAL(msg), ##__VA_ARGS__);
#define CW_TRACE_ALARM(msg, ...) CW_TRACE(CW_ALARM(msg), ##__VA_ARGS__);
#define CW_TRACE_CRITICAL(msg, ...) CW_TRACE(CW_CRITICAL(msg), ##__VA_ARGS__);
#define CW_TRACE_FAULT(msg, ...) CW_TRACE(CW_FAULT(msg), ##__VA_ARGS__);
#define CW_TRACE_VALID(msg, ...) CW_TRACE(CW_VALID(msg), ##__VA_ARGS__);
#define CW_TRACE_INFO(msg, ...) CW_TRACE(CW_INFO(msg), ##__VA_ARGS__);

#endif
#ifndef __LTest_H__
#define __LTest_H__

#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

class LTestCase;
std::vector<LTestCase *> ltest_cases;

#define TESTSUITE(name) \
class name : public LTestCase { \
public: \
    name() { \
        ltest_cases.push_back(this); \
        suitename = #name; \
    } \
    ~ name() {\
        dtor(); \
    }


#define ENDSUITE(name) \
} caseEntity##name;



#define ERRMSG(msg)\
    CW_TRACE_CRITICAL("Error: %s", msg); \
    running_result = -1; \
    return;

#define ENV( statements ) \
    try {\
        statements \
    } catch(std::exception & e) {\
        ERRMSG(e.what()) \
    } catch(std::string & e) {\
        ERRMSG(e) \
    } catch(const char * e) {\
        ERRMSG(e) \
    } catch(...) {\
        ERRMSG("Unknown Error") \
    }

#define CASE(name) void SUITE_##name()

#define EXE(testname) \
    CW_TRACE_NORMAL("Running Case = " #testname "..."); \
    running_result = 0; \
    SUITE_##testname(); \
    test_pass += running_result == 0; \
    test_num++; \
    test_error += running_result == -1; \
    if (running_result == 0) \
        CW_TRACE_VALID("PASS");

#define assertTrue(cond) \
ENV(\
    if (!(cond)) {\
        CW_TRACE_CRITICAL("Assertion Failed: suppose " #cond " == true, but got false instead."); \
        running_result = 1; \
        return; \
    })

#define assertEqual(a, b) \
ENV(\
    if ((a) != (b)) {\
        CW_TRACE_CRITICAL("Assertion Failed: " #a " != " #b); \
        running_result = 1;\
        return;\
    } \
)

// CW_TRACE_NORMAL("This is a normal information");
// CW_TRACE_INFO("This is a noticeable information");
// CW_TRACE_FAULT("Ooops something might have gone wrong");
// CW_TRACE_VALID("Finally it's okay, don't worry");
// //CW_TRACE_NORMAL("Nevermind");
// int value = 10;
// CW_TRACE_CRITICAL("It was way worse than expected! Computer will explode in %d s", value);
// CW_TRACE_ALARM("IT IS TOO LATE RUN AWAY");



#define testlog(msgStr, args...) \
    CW_TRACE_INFO("LOG" msgStr, args)


class LTestCase {
public:
    virtual void execute() = 0;

    virtual void ctor() {}
    virtual void dtor() {}

    void operator() () {
        test_num = test_pass = test_error = 0;
        
        
        CW_TRACE_NORMAL("Suite: %s", suitename.c_str());
      
        ctor();
        execute();
        
        if (test_num == test_pass) {
            CW_TRACE_INFO ("%d Tests Passes In Total.");
            CW_TRACE_VALID("Test Completed!");
        }
        else {
            CW_TRACE_CRITICAL("Test Suite Failed, Passed = %d, Failed = %d, Err = %d", test_pass, test_num - test_error - test_pass, test_error);
        }
    }

protected:
    int test_num, test_pass, test_error;
    int running_result;
    std::string suitename;
};

int RunAllTests() {
    for (auto c : ltest_cases)  {
        (*c) ();
    }
    return 0;
}

#endif
