#ifndef _IRRMATHUTILS_H_
#define _IRRMATHUTILS_H_

namespace irr_utils
{
	class IrrMathUtils
	{
	public:
		static const float E;

		static const float Log10E;

		static const float Log2E;

		static const float Pi;
	
		static const float PiOver2;
	
		static const float PiOver4;

		static const float TwoPi;
	
		static const float MaxFloat;
	
		static const float MinFloat;
	
		static const float Epsilon;
	
		static const float SQRT2;

		template<typename T>
		static T Abs(T val )
		{
			return val >= 0 ? val : -val;
		}

		template<typename T>
		static T Max(T value1, T value2)
		{
			return value1 > value2 ? value1 : value2;
		}

		template<typename T>
		static T Min(T value1, T value2)
		{
			return value1 < value2 ? value1 : value2;
		}
		template<typename T>
		static T Distance(T value1, T value2)
		{
			return Abs(value1 - value2);
		}
	
		template<typename T>
		static T Lerp(T value1, T value2, float amount)
		{
			return T(value1 + ((T)(value2 - value1) * amount ));
		}
	
		template<typename T>
		static T SmoothStep(T value1, T value2, float amount)
		{
			float num = Clamp(amount, 0.0f, 1.0f);
			return Lerp(value1, value2, (num * num) * (3.0f - (2.0f * num)));
		}

		static int Clamp(int value, int min, int max)
		{
			return Max(min, Min(max, value));
		}
	
		static float Clamp(float value, float min, float max)
		{
			return Max(min, Min(max, value));
		}

		static double Clamp(double value, double min, double max)
		{
			return Max(min, Min(max, value));
		}
	
		static float ToDegrees(float radians);

		static float ToRadians(float degrees);

		static int RoundToInt(double x);
	
		static int RandomInt(int maximum);

		static int RandomIntInRange(int min, int max);

		static int RandomIntWithError(int target, int error);

		static float RandomFloat(float maximum=1.0f);

		static float RandomFloatInRange(float min, float max);
	
		static float RandomFloatWithError(float target, float error);

		static bool RandomBool();

		static bool FuzzyEquals(float value1, float value2, float epsilon=Epsilon);

		static float IrrCos(float angle);
		static float IrrSin(float angle);
	};
}

#endif	//_IRRMATHUTILS_H_