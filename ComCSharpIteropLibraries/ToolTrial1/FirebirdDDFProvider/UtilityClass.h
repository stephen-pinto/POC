#pragma once
#include <iostream>
#include <cstdlib>
#include <wchar.h>
#include <algorithm>

#ifndef __UTILITY_CLASS_HEADER
#define __UTILITY_CLASS_HEADER

//#define DEBUG_WINDOW_PRINT(x) OutputDebugString(x);
#define DEBUG_WINDOW_PRINT_NL(x) OutputDebugString(x); OutputDebugString("\n");
//#define DEBUG_WINDOW_PRINT(x) print(x);

class UtilClass
{

public :
	static std::string __stdcall TrimString(std::string target_str)
	{
		std::string res_str = target_str;
		res_str.erase(std::remove_if(res_str.begin(), res_str.end(), isspace), res_str.end());
		return res_str;
	}

	static std::string __stdcall TrimEnds(std::string target_str)
	{
		std::string res_str = target_str;
		res_str.erase(std::remove(res_str.begin(), res_str.end(), ' '), res_str.end());
		return res_str;
	}

	static bool __stdcall IsStringNullOrEmpty(std::string target_str)
	{
		std::string temp_str = target_str;
		temp_str.erase(std::remove_if(temp_str.begin(), temp_str.end(), isspace), temp_str.end());

		if (temp_str == "")
			return true;
		else
			return false;
	}
};

#endif