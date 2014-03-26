#include "IrrMathUtils.h"

#include <math.h>
#include <time.h>
#include <stdlib.h>

namespace irr_utils
{

	const float IrrMathUtils::E = 2.718282f;
	const float IrrMathUtils::Log10E = 0.4342945f;
	const float IrrMathUtils::Log2E = 1.442695f;
	const float IrrMathUtils::Pi = 3.141593f;
	const float IrrMathUtils::PiOver2 = 1.570796f;
	const float IrrMathUtils::PiOver4 = 0.7853982f;
	const float IrrMathUtils::TwoPi = 6.283185f;
	const float IrrMathUtils::MaxFloat = 3.402823E+38f;
	const float IrrMathUtils::MinFloat = -3.402823E+38f;
	const float IrrMathUtils::Epsilon = 0.000001f;
	const float IrrMathUtils::SQRT2  = 1.4142135623730951;

	
	float IrrMathUtils::ToDegrees( float radians )
	{
		return (radians * 57.29578f);
	}

	float IrrMathUtils::ToRadians( float degrees )
	{
		return (degrees * 0.01745329f);
	}

	int IrrMathUtils::RoundToInt( double x )
	{
		return ((int)(floor(x+0.5)));
	}

	int IrrMathUtils::RandomInt( int maximum )
	{
		static bool firstTime = true;
		if (firstTime) 
		{
			firstTime = false;
			srand((int)time(NULL));
		}
		if (maximum <= 0) 
		{
			return 0;
		}
		return (rand() % maximum);
	}


	int IrrMathUtils::RandomIntInRange( int min, int max )
	{
		return RandomInt(max-min) + min;
	}

	int IrrMathUtils::RandomIntWithError( int target, int error )
	{
		return RandomIntInRange(target-error, target+error);
	}

	float IrrMathUtils::RandomFloat( float maximum/*=1.0f*/ )
	{
		const float bigNumber = 10000.0f;
		float randFloat = (float)RandomInt((int)bigNumber);
		randFloat = randFloat/bigNumber;
		return randFloat*maximum;
	}

	float IrrMathUtils::RandomFloatInRange( float min, float max )
	{
		return RandomFloat(max-min) + min;
	}

	float IrrMathUtils::RandomFloatWithError( float target, float error )
	{
		return RandomFloatInRange(target-error, target+error);
	}

	bool IrrMathUtils::RandomBool()
	{
		return IrrMathUtils::RandomInt(2) > 0;
	}

	bool IrrMathUtils::FuzzyEquals( float value1, float value2, float epsilon/*=Epsilon*/ )
	{
		float a = value1 - value2;
		if (fabs(a) < epsilon)
		{
			return true;
		}
		return false;
	}


	float IrrMathUtils::IrrCos( float angle )
	{
		return cos(angle);
	}

	float IrrMathUtils::IrrSin( float angle )
	{
		return sin(angle);
	}

}