#include <iostream>
#include <csignal>
#include <csetjmp>

namespace
{
    thread_local jmp_buf *gJumpData;
}

void signal_SIGFPE_handler(int signum)
{
    std::cout << "Oops, math!!!" << std::endl;
    longjmp(*gJumpData, signum);
}

void signal_SIGSEGV_handler(int signum)
{
    std::cout << "Oops, memory!!!" << std::endl;
    longjmp(*gJumpData, signum);
}

class classA
{
private:
    int val;
public:
    classA(int i): val{i}
    {
        std::cout << "classA::classA(), val = "<< val << std::endl;
    }

    ~classA()
    {
        std::cout << "classA::~classA(), val = "<< val << std::endl;
    }
};

int test_math(int param)
{
    int result = 10/param;
    return result;
}

void test_mem(int param)
{
    int *i = nullptr;
    *i = param;
}

int main(int argc, char *argv[])
{
    classA a{1};

    // set own handlers
    signal(SIGFPE, signal_SIGFPE_handler);
    signal(SIGSEGV, signal_SIGSEGV_handler);
    // machine state will be saved here
    gJumpData = (jmp_buf *)(new jmp_buf);

    try
    {
        classA b{2};

        // save machine state
        int signum = setjmp(*gJumpData);
        if (!signum)
        {
            int zero = 0;
            int result;
            //result = test_math(zero);
            test_mem(10);
        }
        else
        {
            std::cout << "signal = " << signum << std::endl;
            
            // perform cleaning here
        }

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch(...)
    {
        std::cerr << "Something happened" << std::endl;
    }
    
    delete gJumpData;

    // Set default handlers
    signal(SIGFPE, SIG_DFL);
    signal(SIGSEGV, SIG_DFL);
    
    std::cout << "Normal termination" << std::endl;


    return EXIT_SUCCESS;
}
