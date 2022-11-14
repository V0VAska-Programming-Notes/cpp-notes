# Parameters pack.

Функциями с переменным количеством аргументов никого, пожалуй, не удивишь. А вот как генерики и вариадики применимы к шаблонам и лямбдам?

Для разминки коротко вспомним о шаблонах и передаче в них функций как параметров.

## Простенько

В директории '/simple' демонстрируются два шаблона:

```c++
template<typename T>
void do_smth(T&&);

template<typename T>
auto do_smth_ret(T&& fn) -> decltype(fn());
```

С первым всё просто и очевидно - может принимать в качестве параметра функции и не возвращает ничего.

Второй на основе возвращаемого функцией значения формирует тип возврата "на лету".

## От'printf'туем?

В директории '/template_pack' вызов `fn(1.0, 5);` наглядно продемонстрирует "упаковку" параметров в шаблоне.

```c++
void fn_handle(float param1, int param2)
{
	std::cout << param1 << " " << param2 << std::endl;
}

template<typename... Targs>
void fn(Targs... args)
{
	std::cout << "params count: " << sizeof...(args) << std::endl;
	fn_handle(args...);
}
```

В На основе приведённого примера замутим некий аналог функции printf:

```c++
void tprintf(const char* format) // base function
{
	std::cout << format;
}

template<typename T, typename... Targs>
void tprintf(const char* format, T value, Targs... args) // recursive variadic function
{
	for (; *format != 0; format++)
	{
		if (*format == '%')
		{
			std::cout << value;
			tprintf(format + 1, args...); // recursive call
			return;
		}
		std::cout << *format;
	}
}
```

Протестируем вызовом `tprintf("% world% %\n", "Hello", '!', 123)`.

# На закуску - лямбды.

'/lambda-pack'

```c++
	auto vglambda = [](auto printer)
	{
		return [=](auto&&... ts)
		{
			printer(std::forward<decltype(ts)>(ts)...);
			return [=]
			{
				printer(ts...);
			};
		};
	};

	auto p = vglambda(
		[](auto v1, auto v2, auto v3)
		{
			std::cout << v1 << v2 << v3 << std::endl;
		}
	);

	auto q = p(1, 'a', 3.14);
```

На первый взгляд кажется немного сложным... или запутанным... Кому как. На самом деле стоит лишь последовательно пройтись шаг за шагом и упростить себе задачу.

Что нам возвращает "первый" return нашей vglambda? Правильно, лямбду примерно следующего содержания:

```c++
	auto p1 = [](auto&&... ts)
	{
		// получили этот "принтер" в качестве параметра.
		auto printer = [](auto v1, auto v2, auto v3)
		{
			std::cout << v1 << v2 << v3 << std::endl;
		};
		printer(std::forward<decltype(ts)>(ts)...); // (1)
		// пока что лишнее
		return [=]
		{
			printer(ts...);
		};
	};
	...
	auto q1 = p1(1, 'a', 3.14);
```

(1) - именно здесь осуществляется "вывод" на консоль.

Что это за "последний" return? Это то, что "получает" переменная **q**, которая есть, но никак не задействована, - там содержится и "принтер" и переданные параметры. Прверить легко - достаточно добавить оператор `q();` в конец функции 'lambda_test()', так продублируем выведенный в (1) результат.
