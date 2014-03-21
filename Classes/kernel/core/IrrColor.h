#ifndef _IRRCOLOR_H_
#define _IRRCOLOR_H_

#include "IrrTypeDef.h"

namespace irr_core
{
	class IrrColor
	{
	public:
		float R;
		float G;
		float B;
		float A;
		IrrColor();
		IrrColor(float r, float g, float b, float a=1.0f, bool clamp=true);

		IrrColor(int r, int g, int b, int a=255, bool clamp=true);

		IrrColor(IrrString hexString);
	
		IrrBool operator==(const IrrColor &c) const;
		IrrBool operator!=(const IrrColor &c) const;
	
		IrrColor operator-(const IrrColor &c) const;
		IrrColor operator+(const IrrColor &c) const;
		IrrColor operator/(float divider) const;
		IrrColor operator*(float scaleFactor) const;
		
	private:
		static IrrInt HexToInteger(IrrString hex);
		void ClampMe();
	};
}

#endif	//_IRRCOLOR_H_