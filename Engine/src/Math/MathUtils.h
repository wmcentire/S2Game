#pragma once

namespace pb {
	const float PI = 3.141592653589793238462643f; // 180
	const float TWOPI = PI * 2.0f; // 360
	const float HALFPI = PI / 2.0f; // 90

	inline float DegToRad(float degrees) {
		return degrees * (PI / 180);
	}
	inline float RadToDeg(float radians) {
		return radians * (180 / PI);
	}

	int sqr(int i);
	inline int half(int v) { return v / 2; }
	
}

