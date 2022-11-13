#include <iostream>
#include <fcntl.h>
#ifdef WIN32
#include <io.h>
#endif // WIN32

auto main() -> int
{
    setlocale(LC_ALL, "");
    
#ifdef WIN32
    _setmode(_fileno(stdout), _O_U16TEXT);
#endif // WIN32
    
    std::wprintf(L"При помощи wprintf() печатаем число: %i\n", 10);
    std::wcout << L"Алё, wcout на связи???" << std::endl;
    return 0;
}
