#pragma once
#include <Windows.h>
#include <cstdint>
#include <format>
#include <string>


class Convert {
public:
	static std::wstring ConvertString(const std::string& str);

	static std::string ConvertString(const std::wstring& str);

	static void Log(const std::string& message);
};