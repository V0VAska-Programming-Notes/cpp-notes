#include <functional>
#include <iostream>

#include "lambda_pack.h"

void lambda_test() noexcept
{
	// vg - variadic generic
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
}
