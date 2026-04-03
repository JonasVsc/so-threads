#pragma once
#include <print>
#include <utility>

namespace canvas
{

	template <typename... Args>
	void log(std::format_string<Args...> fmt, Args&&... args) 
	{
		std::println(fmt, std::forward<Args>(args)...);
	}

} // namespace canvas