#include "IrrGeom.h"
#include "IrrMathUtils.h"

using namespace irr_utils;

namespace irr_core
{

	irr_core::IrrVector2D IrrVector2D::IrrZero(0.0f,0.0f);
	irr_core::IrrVector2D IrrVector2D::UnitX(1.0f,0.0f);
	irr_core::IrrVector2D IrrVector2D::UnitY(0.0f,1.0f);
	irr_core::IrrVector2D IrrVector2D::IrrOne(1.0f,1.0f);

	IrrVector2D::IrrVector2D( void )
	{
		X = Y = 0.0f;
	}

	IrrVector2D::IrrVector2D( const IrrVector2D& other )
	{
		X = other.X;
		Y = other.Y;
	}

	IrrVector2D::IrrVector2D( float x,float y )
	{
		X = x;
		Y = y;
	}

	IrrVector2D::~IrrVector2D( void )
	{
		
	}

	IrrVector2D& IrrVector2D::operator=( const IrrVector2D& other )
	{
		X = other.X;
		Y = other.Y;
		return *this;
	}

	bool IrrVector2D::operator==( const IrrVector2D &v ) const
	{
		return this->X == v.X &&this->Y == v.Y;
	}

	bool IrrVector2D::operator!=( const IrrVector2D &v ) const
	{
		return !(*this == v);
	}

	IrrVector2D IrrVector2D::operator-() const
	{
		return IrrVector2D::IrrZero - *this;
	}

	IrrVector2D IrrVector2D::operator-( const IrrVector2D &v ) const
	{
		return IrrVector2D(X - v.X, Y - v.Y);
	}

	IrrVector2D IrrVector2D::operator+( const IrrVector2D &v ) const
	{
		return IrrVector2D(X + v.X, Y + v.Y);
	}

	IrrVector2D IrrVector2D::operator/( float divider ) const
	{
		return IrrVector2D(X / divider, Y / divider);
	}

	IrrVector2D IrrVector2D::operator*( float scaleFactor ) const
	{
		return IrrVector2D(X * scaleFactor, Y * scaleFactor);
	}

	float IrrVector2D::Length()
	{
		return sqrt(LengthSquared());
	}

	float IrrVector2D::LengthSquared()
	{
		return (X * X) + (Y * Y);
	}

	float IrrVector2D::Distance( const IrrVector2D& value1, const IrrVector2D& value2 )
	{
		return IrrVector2D(value1 - value2).Length();
	}

	float IrrVector2D::DistanceSquared( const IrrVector2D& value1, const IrrVector2D& value2 )
	{
		return IrrVector2D(value1 - value2).LengthSquared();
	}

	float IrrVector2D::Dot( const IrrVector2D& value1, const IrrVector2D& value2 )
	{
		return ((value1.X * value2.X) + (value1.Y * value2.Y));
	}

	IrrVector2D IrrVector2D::Min( const IrrVector2D& value1,const IrrVector2D& value2 )
	{
		return IrrVector2D(IrrMathUtils::Min(value1.X,value2.X),IrrMathUtils::Min(value1.Y,value2.Y));
	}

	IrrVector2D IrrVector2D::Max( const IrrVector2D& value1,const IrrVector2D& value2 )
	{
		return IrrVector2D(IrrMathUtils::Max(value1.X,value2.X),IrrMathUtils::Max(value1.Y,value2.Y));
	}

	IrrVector2D IrrVector2D::Clamp( const IrrVector2D& value, const IrrVector2D& min, const IrrVector2D& max )
	{
		return IrrVector2D(IrrMathUtils::Clamp(value.X,min.X,max.X),IrrMathUtils::Clamp(value.Y,min.Y,max.Y));
	}

	IrrVector2D IrrVector2D::Lerp( const IrrVector2D& value1, const IrrVector2D& value2, float amount )
	{
		return IrrVector2D( IrrMathUtils::Lerp( value1.X, value2.X, amount ), IrrMathUtils::Lerp( value1.Y, value2.Y, amount ) );
	}

	IrrVector2D IrrVector2D::Negate( const IrrVector2D& value )
	{
		return -value;
	}

	IrrVector2D IrrVector2D::Rotate( const IrrVector2D& value, const float radians )
	{
		float c = cos(radians);
		float s = sin(radians);
		return IrrVector2D(value.X*c-value.Y*s,value.Y*c+value.X*s);
	}

	IrrVector2D IrrVector2D::Reflect( const IrrVector2D& vector, const IrrVector2D& normal )
	{
		return vector - (normal * 2.0f * Dot(vector, normal));
	}

	IrrVector2D IrrVector2D::Normalize( const IrrVector2D& value )
	{
		IrrVector2D retVal(value);
		retVal.Normalize();
		return retVal;
	}

	void IrrVector2D::Normalize()
	{
		float len = Length();
		if( len < 1e-7f )
		{
			if( Y > X )
				*this = UnitY;
			else
				*this = UnitX;
		}
		else
		{
			*this = *this / len;
		}
	}

	void IrrVector2D::setVector2D( float x,float y )
	{
		X = x;
		Y = y;
	}

	
	//////////////////////////////////////////////////////////////////////////
	//IrrSize
	IrrSize::IrrSize( void )
	{
		width = height = 0;
	}

	IrrSize::IrrSize( float width,float height )
	{
		this->width = width;
		this->height = height;
	}

	IrrSize::IrrSize( const IrrSize& size )
	{
		this->width = size.width;
		this->height = size.height;
	}

	IrrSize::~IrrSize( void )
	{
	}

	IrrSize& IrrSize::operator=( const IrrSize& size )
	{
		this->width = size.width;
		this->height = size.height;
		return *this;
	}

	void IrrSize::setSize( float width,float height )
	{
		this->width = width;
		this->height = height;
	}

	bool IrrSize::equals( const IrrSize& size ) const
	{
		return (this->width == size.width && this->height == size.height);
	}


	bool IrrSize::operator==( const IrrSize &v ) const
	{
		return equals(v);
	}

	bool IrrSize::operator!=( const IrrSize &v ) const
	{
		return !(*this == v);
	}
	
	IrrSize IrrSize::operator-( const IrrSize &v ) const
	{
		return IrrSize(width - v.width, height - v.height );
	}

	IrrSize IrrSize::operator+( const IrrSize &v ) const
	{
		return IrrSize(width + v.width, height + v.height );
	}

	IrrSize IrrSize::operator/( float divider ) const
	{
		return IrrSize(width / divider, height / divider);
	}

	IrrSize IrrSize::operator*( float scaleFactor ) const
	{
		return IrrSize(width * scaleFactor, height * scaleFactor);
	}
	//////////////////////////////////////////////////////////////////////////

	

	//////////////////////////////////////////////////////////////////////////
	IrrRect::IrrRect( void )
	{
	}
	
	IrrRect::IrrRect( float x,float y,float width,float height )
	{
		origin.X = x;
		origin.Y = y;
		size.width = width;
		size.height = height;
	}

	IrrRect::IrrRect( const IrrRect& rect )
	{
		origin = rect.origin;
		size = rect.size;
	}

	IrrRect& IrrRect::operator=( const IrrRect& rect )
	{
		origin = rect.origin;
		size = rect.size;
		return *this;
	}

	void IrrRect::setRect( float x,float y,float width,float height )
	{
		origin.X = x;
		origin.Y = y;
		size.width = width;
		size.height = height;
	}

	float IrrRect::getMinX() const
	{
		return origin.X;
	}

	float IrrRect::getMidX() const
	{
		return origin.X + size.width * 0.5;
	}

	float IrrRect::getMaxX() const
	{
		return origin.X + size.width;
	}

	float IrrRect::getMinY() const
	{
		return origin.Y;
	}

	float IrrRect::getMidY() const
	{
		return origin.Y + size.height * 0.5;
	}

	float IrrRect::getMaxY() const
	{
		return origin.Y + size.height;
	}

	bool IrrRect::equal( const IrrRect& rect ) const
	{
		return (origin == rect.origin && size == rect.size );
	}

	bool IrrRect::containsVector2D( const IrrVector2D& pot ) const
	{
		//return (pot.X >=getMinX()  && pot.Y <=getMaxY() && pot.Y >=getMinX() && pot.Y <= getMaxY());
		return (pot.X >=getMinX()  && pot.Y >= getMinY() && pot.X <= getMaxX() && pot.Y <= getMaxY());
	}

	bool IrrRect::containsVector2D( float x,float y ) const
	{
		return (x >=getMinX()  && y <=getMaxY() && y >=getMinX() && y <= getMaxY());
	}

	bool IrrRect::intersectsRect( const IrrRect& rect ) const
	{
		return !(getMaxX() < rect.getMinX() || rect.getMaxX() < getMinX() || getMaxY() < rect.getMinY() || rect.getMaxY() < getMinY());
	}

	IrrRect::~IrrRect( void )
	{

	}

	float IrrRect::getOriginX() const
	{
		return origin.X;
	}

	float IrrRect::getOriginY() const
	{
		return origin.Y;
	}


	//////////////////////////////////////////////////////////////////////////
	IrrClipRect::IrrClipRect( void )
	{
		origin.X = 0;
		origin.Y = 0;
		size.width = 0;
		size.height = 0;
		m_fXOffset = 0;
		m_fYOffset = 0;
	}

	IrrClipRect::IrrClipRect( float x,float y,float width,float height,float xOffset,float yOffset )
	{
		origin.X = x;
		origin.Y = y;
		size.width = width;
		size.height = height;
		m_fXOffset = xOffset;
		m_fYOffset = yOffset;
	}

	IrrClipRect::~IrrClipRect( void )
	{

	}

	const IrrClipRect& IrrClipRect::operator=( const IrrRect& other )
	{
		origin = other.origin;
		size   = other.size;
		return *this;
	}
}


namespace irr_core
{
	IrrVector3D::IrrVector3D( void )
	{
		X = Y = Z = 0;
	}

	IrrVector3D::IrrVector3D( const IrrVector3D& other )
	{
		X = other.X;
		Y = other.Y;
		Z = other.Z;
	}

	IrrVector3D::IrrVector3D( float x,float y,float z )
		:X(x),
		Y(y),
		Z(z)
	{
	}

	IrrVector3D::~IrrVector3D( void )
	{

	}

	bool IrrVector3D::operator==( const IrrVector3D &v ) const
	{
		return (X == v.X && Y == v.Y && Z == v.Z);
	}

	bool IrrVector3D::operator!=( const IrrVector3D &v ) const
	{
		return !(*this == v);
	}

	
	IrrVector3D IrrVector3D::operator-( const IrrVector3D &v ) const
	{
		return IrrVector3D(X - v.X,Y - v.Y,Z - v.Z);
	}


	IrrVector3D IrrVector3D::operator+( const IrrVector3D &v ) const
	{
		return IrrVector3D(X + v.X,Y - v.Y,Z - v.Z);
	}


	IrrVector3D IrrVector3D::operator/( float divider ) const
	{
		return IrrVector3D(X / divider,Y / divider,Z /divider);
	}

	IrrVector3D IrrVector3D::operator*( float scaleFactor ) const
	{
		return IrrVector3D(X * scaleFactor,Y * scaleFactor,Z  * scaleFactor);
	}

	void IrrVector3D::setVector3D( float x,float y,float z )
	{
		X = x;
		Y = y;
		Z = z;
	}
}