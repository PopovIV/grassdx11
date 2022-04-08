#pragma once

class SMath
{
private:
	static float lerp(const float a, const float b, float t);
	static float smoothstep(const float a, const float b, float t);
	static float fract(float num);
	static float hashNoise(float x, float y);
	static float perlinNoiseLayer(const float x, const float y);

public:
	static const float PI;
	static float clamp(const float _val, const float _min, const float _max);
	static float perlinNoise(const float x, const float y = 0.0f);
};