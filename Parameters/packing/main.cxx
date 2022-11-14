#include <iostream>

#include "simple.h"
#include "template_pack.h"
#include "lambda_pack.h"

int main()
{
    std::cout << "\n--- simple ---\n";
    simple_demo();

    std::cout << "\n--- template pack ---\n";
    template_pack_test1();
    template_pack_test2();

    std::cout << "\n--- lambda pack ---\n";
    lambda_test();

    return 0;
}
