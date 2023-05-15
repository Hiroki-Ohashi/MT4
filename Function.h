#pragma once
#include <Windows.h>
#include <cstdint>
#include <format>
#include <string>


class Convert {
public:
	std::wstring ConvertString(const std::string& str);

	std::string ConvertString(const std::wstring& str);
};