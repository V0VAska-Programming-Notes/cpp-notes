# М~~ы~~ашинная возня.
Про обычные исключения и их обработку говорить нечего, а вот о так называемых "машинных" стоит упомянуть. К этому типу исключений относятся, например, деление на ноль, косяк с попыткой доступа к памяти, скажем, через неинициализированный указатель. Или как в одном из предыдущих [примеров](../Parameters/params-jokes)...

Начнём с такого кода:

```c++
#include <iostream>

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

    try
    {
        classA b{2};
        int zero = 0;
        int result;
        result = test_math(zero);
        //test_mem(10);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch(...)
    {
        std::cerr << "Something happened" << std::endl;
    }
    
    std::cout << "Normal termination" << std::endl;

    return EXIT_SUCCESS;
}
```

Экземпляры классов нам нужны просто для оценки корректности завершения программы. Запустив сиё творение, словим "деление на нуль" и аварийное завершение программы. Заметим, что деструкторы вызваны не были.

Для проверки в начало функции test_math() вставим оператор `throw std::exception{"oops"};`. Вот так получим желаемое:

```
classA::classA(), val = 1
classA::classA(), val = 2
classA::~classA(), val = 2
oops
Normal termination
classA::~classA(), val = 1
```

Очерёдность наглядная - в контролируемом блоке сработал вызов деструктора.

# MSVC

Как правило в винде используется MSVC, а из CMake можно управлять [опциями](https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-by-category?view=msvc-170), предаваемыми компилятору. Поэтому проблему можно решить сменой дефолтной -EHs опции на -EHa, включающую обработку всех исключений. Для этого в CMakeLists.txt добавим строчки:

```cmake
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(${PROJECT_NAME}
    PRIVATE
        "$<${msvc_cxx}:$<BUILD_INTERFACE:-EHa>>"
)
```

Запустив наш пример, получим на выходе:

```
classA::classA(), val = 1
classA::classA(), val = 2
classA::~classA(), val = 2
Something happened
Normal termination
classA::~classA(), val = 1
```

# Ещё варианты?!

В линуксе сколько не искал, так и не нашёл подобной опции. Но у линукс и форточек есть общее средство - сигналы (signals).

> Ежели юзаем виндовс и включили опцию -EHa, то следует выключить её для продолжения. Но тут мелкомягкие пакостники умудрились ["нагадить"](https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/signal?view=msvc-170), как минимум, в отношении SIGFPE. Ломы разбираться, что почём, поэтому переходим на резервный вариант - попытаемся засрать память.

Внесём изменения в main.cxx:

```c++
#include <iostream>
#include <signal.h>

void signal_SIGFPE_handler(int signum)
{
    std::cout << "Oops, math!!!" << std::endl;
    exit(signum);
}

void signal_SIGSEGV_handler(int signum)
{
    std::cout << "Oops, memory!!!" << std::endl;
    exit(signum);
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

    try
    {
        classA b{2};
        //int zero = 0;
        //int result;
        //result = test_math(zero);
        test_mem(10);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch(...)
    {
        std::cerr << "Something happened" << std::endl;
    }

    // Set default handlers
    signal(SIGFPE, SIG_DFL);
    signal(SIGSEGV, SIG_DFL);
    
    std::cout << "Normal termination" << std::endl;


    return EXIT_SUCCESS;
}
```

Результатом работы будет:

```
classA::classA(), val = 1
classA::classA(), val = 2
Oops, memory!!!
```

Хоть что-то... перехватить нам всё-таки удалось. При помощи exit() всё-таки завершаем программу аварийно, информируя кодом возврата о возникшей ошибке. Не рискуя напороться на подводные камни, пространства для маневра внутри обработчика сигнала - кот наплакал. Любопытно? [Тогда - добро пожаловать!](https://en.cppreference.com/w/cpp/utility/program/signal).

По умолчанию, ежели в обработчике не вызвать exit(), а просто выйти, то управление вернётся в место возникновения сигнала (и потеха пойдёт по-новой?). Поэтому при помощи longjump() вернёмся в "контролируемый блок", чтбы по Си-шному симулировать обработку исключений.

```c++
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
```

Недостатков у данного метода - уйма. Начнём с того, что переместив оператор `classA b{2};` внутрь блока if, хрена с два будет вызван деструктор. Ежели во время возникновения ошибки какие-то данные хранились в регистрах, то нет гарантии, что с возвращением из "обработчика" эти данные не похерятся. Всем подописать volatile? И т.д. и т.п.

Фактически else ветвь представляет собой подобие catch, правда и с урезанным функционалом (вспомним про `classA b{2};`). Даже сгенерированное самостоятельно при помощи throw уже нормальное исключение в ветви else проблемы с уничтожением `classA b{2};` из ветви if не решит.

Также нельзя заново вызвать машинное исключение - курим мануалы дальше... направление куда курить указано.
