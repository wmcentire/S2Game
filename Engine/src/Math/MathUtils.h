#pragma once
#include <cmath>

namespace pb {
	constexpr float PI = 3.141592653589793238462643f; // 180
	constexpr float TWOPI = PI * 2.0f; // 360
	constexpr float HALFPI = PI / 2.0f; // 90

	inline float DegToRad(float degrees) {
		return degrees * (PI / 180);
	}
	inline float RadToDeg(float radians) {
		return radians * (180 / PI);
	}

	
	template <typename T>
	T Clamp(T value, T min, T max)
	{
		if (value < min) return min;
		if (value > max) return max;

		return value;
	}
	template <typename T>
	T Lerp(T min, T max, float t)
	{
		t = Clamp(t, 0.0f, 1.0f);

		return min + ((max - min) * t);
	}
	template <typename T>
	T Normalize(T value, T min, T max)
	{
		return (value - min) / (max - min);
	}
	template <typename T>
	T Remap(T value, T inMin, T inMax, T outMin, T outMax)
	{
		return Lerp(outMin, outMax, Normalize(value, inMin, inMax));
	}
	template <typename T>
	T mod(T numerator, T denominator)
	{
		return std::fmod(numerator, denominator);
	}

	template <>
	inline int mod(int numerator, int denominator)
	{
		return numerator % denominator;
	}

	template <typename T>
	T Wrap(T value, T min, T max)
	{
		if (value < min) return max - mod((min - value), (max - min));
		if (value > max) return min + mod((value - min), (max - min));

		return value;
	}
}

