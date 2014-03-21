#include "IrrColor.h"
#include "IrrMathUtils.h"

namespace irr_core
{
	
	IrrColor::IrrColor()
	{
		R = G = B = A = 1.0f;
	}

	IrrColor::IrrColor( float r, float g, float b, float a/*=1.0f*/, bool clamp/*=true*/ )
	{
		R = r;
		G = g;
		B = b;
		A = a;
		if(clamp)
		{
			ClampMe();
		}
	}

	IrrColor::IrrColor( int r, int g, int b, int a/*=255*/, bool clamp/*=true*/ )
	{
		R = (float)r / 255.0f;
		G = (float)g / 255.0f;
		B = (float)b / 255.0f;
		A = (float)a / 255.0f;
		if(clamp)
		{
			ClampMe();
		}
	}

	IrrColor::IrrColor( IrrString hexString )
	{
		bool isHex = false;
		if(hexString[0] == '#')
		{
			hexString = hexString.substr(1);
			isHex = true;
		}
		if((hexString.substr(0,2) == "0x") || (hexString.substr(0,2) == "0X"))
		{
			hexString = hexString.substr(2);
			isHex = true;
		}
		if(isHex)
		{
			if ( (hexString.length() != 3) && (hexString.length() != 6) )
			{
				//invalid length, set to white
				R = G = B = A = 1.0f;
				return;
			}

			if (hexString.length() == 3)
			{
				IrrString newString = "";
				newString += hexString.substr(0,1) + hexString.substr(0,1);
				newString += hexString.substr(1,1) + hexString.substr(1,1);
				newString += hexString.substr(2,1) + hexString.substr(2,1);
				hexString = newString;
			}

			IrrString rString = hexString.substr(0,2);
			IrrString gString = hexString.substr(2,2);
			IrrString bString = hexString.substr(4,2);

			int rInt = HexToInteger(rString);
			int gInt = HexToInteger(gString);
			int bInt = HexToInteger(bString);

			R = (float)rInt / 255.0f;
			G = (float)gInt / 255.0f;
			B = (float)bInt / 255.0f;
			A = 1.0f;

			this->ClampMe();
		}
		else
		{
			R = G = B = A = 1.0f;
			return;
		}
	}

	bool IrrColor::operator==( const IrrColor &c ) const
	{
		return R == c.R && G == c.G && B == c.B && A == c.A;
	}

	bool IrrColor::operator!=( const IrrColor &c ) const
	{
		return !(*this == c);
	}

	irr_core::IrrColor IrrColor::operator-( const IrrColor &c ) const
	{
		return IrrColor(R-c.R,G-c.G,B-c.B,A-c.A,false);
	}

	irr_core::IrrColor IrrColor::operator+( const IrrColor &c ) const
	{
		return IrrColor(R+c.R,G+c.G,B+c.B,A+c.A,false);
	}

	irr_core::IrrColor IrrColor::operator/( float divider ) const
	{
		return IrrColor(R / divider,G / divider,B / divider,A /divider,false);
	}

	irr_core::IrrColor IrrColor::operator*( float scaleFactor ) const
	{
		return IrrColor(R * scaleFactor,G * scaleFactor,B * scaleFactor,A * scaleFactor,false);
	}

	int IrrColor::HexToInteger( IrrString hex )
	{
		int hexInt;
		sscanf(hex.c_str(),"%x",&hexInt);
		return hexInt;
	}

	void IrrColor::ClampMe()
	{
		R = irr_utils::IrrMathUtils::Clamp(R,0.0f,1.0f);
		G = irr_utils::IrrMathUtils::Clamp(G,0.0f,1.0f);
		B = irr_utils::IrrMathUtils::Clamp(B,0.0f,1.0f);
		A = irr_utils::IrrMathUtils::Clamp(A,0.0f,1.0f);
	}

}