#pragma once
#include <cstdint>

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
	};

	inline std::istream& operator >> (std::istream& stream, Color& c)
	{
		std::string line;
		std::getline(stream, line);

		std::string str;

		// red
		str = line.substr(line.find("{") + 1, line.find(",")-line.find("{")-1);

		//std::cout << "red: " << str << std::endl;

		c.r = (uint8_t)(std::stof(str) * 255);

		//std::cout << "r: " << std::stof(str) << std::endl;

		// green 
		str = line.substr(line.find(",") + 1, line.find_last_of(",") - line.find(",")-1);		
		c.g = (uint8_t)(std::stof(str) * 255);


		// blue 
		str = line.substr(line.find_last_of(",") + 1,line.find("}") - line.find_last_of(",") - 1);
		c.b = (uint8_t)(std::stof(str) * 255);

		// alpha
		c.a = 255;

		return stream;
	}
}