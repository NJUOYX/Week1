//
// pch.h
// Header for standard system include files.
//

#pragma once

#include<string>
#include<vector>
#include<map>
#include<set>
#include<algorithm>
#include<iostream>
#include<fstream>
#include<stdlib.h>
using WString = std::string;
using String = std::string;
using Str_Vec = std::vector<String>;
using WStr_Vec = std::vector<String>;
using Int2_Vec = std::vector<int32_t>;
using Int32_Vec = std::vector<int32_t>;
using IFStream = std::ifstream;
using OFStream = std::ofstream;
using WIFStream = std::ifstream;
using WOFStream = std::ofstream;
constexpr int STOP_SIGNAL = 1;
#define BASE_TEST