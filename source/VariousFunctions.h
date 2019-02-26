#pragma once
#include <math.h>

static float GetHorPlusFOV(float horizontalFOV, float aspectRatio)
{
	float PI = 3.14f;
	return (2 * atanf(tanf((2 * atanf(tanf((PI * horizontalFOV / 180.0f) / 2) * 0.75f)) / 2) * aspectRatio) * (180.0f / PI));
}

static int GetValueWithinLimits(int bottomLimit, int topLimit, int safeValue, int CheckedValue)
{
	if (CheckedValue >= bottomLimit && CheckedValue <= topLimit)
		return CheckedValue;
	else
		return safeValue;
}