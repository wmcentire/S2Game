#pragma once
#include <cstdint>
#include<iostream>
#include <string>

namespace pb
{
	//typedef unsigned char u8_t;
	//using u8_t = unsigned char;

	struct Color
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;

		static const Color white;
		static const Color black;
		static const Color red;
		static const Color green;
		static const Color blue;

		friend std::istream& operator >> (std::istream& stream, Color& c);
	};
	std::istream& operator >> (std::istream& stream, Color& c);
}