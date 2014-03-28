#ifndef _IRRGEOM_H_
#define _IRRGEOM_H_

#include "IrrTypeDef.h"

namespace irr_core
{
	//////////////////////////////////////////////////////////////////////////
	//IrrVector2D
	class IrrVector2D
	{
	public:
		IrrVector2D(void);
		IrrVector2D(const IrrVector2D& other);
		IrrVector2D(float x,float y);
		~IrrVector2D(void);

		IrrVector2D& operator=(const IrrVector2D& other);
		bool operator==(const IrrVector2D &v) const;
		bool operator!=(const IrrVector2D &v) const;

		IrrVector2D operator-() const;
		IrrVector2D operator-(const IrrVector2D &v) const;
		IrrVector2D operator+(const IrrVector2D &v) const;
		IrrVector2D operator/(float divider) const;
		IrrVector2D operator*(float scaleFactor) const;

		void setVector2D(float x,float y);
	public:
		IrrFloat Length();
		IrrFloat LengthSquared();
		static IrrFloat Distance(const IrrVector2D& value1, const IrrVector2D& value2);
		static IrrFloat DistanceSquared(const IrrVector2D& value1, const IrrVector2D& value2);
		static IrrFloat Dot(const IrrVector2D& value1, const IrrVector2D& value2);
		static IrrVector2D Min(const IrrVector2D& value1,const IrrVector2D& value2);
		static IrrVector2D Max(const IrrVector2D& value1,const IrrVector2D& value2);
		static IrrVector2D Clamp(const IrrVector2D& value, const IrrVector2D& min, const IrrVector2D& max);
		static IrrVector2D Lerp(const IrrVector2D& value1, const IrrVector2D& value2, float amount);
		static IrrVector2D Negate(const IrrVector2D& value);
		static IrrVector2D Rotate(const IrrVector2D& value, const IrrFloat radians);
		static IrrVector2D Reflect(const IrrVector2D& vector, const IrrVector2D& normal);
		static IrrVector2D Normalize(const IrrVector2D& value);
		void Normalize();
	public:
		float X;
		float Y;
		static IrrVector2D IrrZero;
		static IrrVector2D IrrOne;
		static IrrVector2D UnitX;
		static IrrVector2D UnitY;
	};
	//////////////////////////////////////////////////////////////////////////
	
	class IrrVector3D
	{
	public:
		float X;
		float Y;
		float Z;
	public:
		IrrVector3D(void);
		IrrVector3D(const IrrVector3D& other);
		IrrVector3D(float x,float y,float z);
		~IrrVector3D(void);

		bool operator==(const IrrVector3D &v) const;
		bool operator!=(const IrrVector3D &v) const;
		
		IrrVector3D operator-(const IrrVector3D &v) const;
		IrrVector3D operator+(const IrrVector3D &v) const;
		IrrVector3D operator/(float divider) const;
		IrrVector3D operator*(float scaleFactor) const;

		void setVector3D(float x,float y,float z);
	};

	//////////////////////////////////////////////////////////////////////////
	class IrrSize
	{
	public:
		IrrSize(void);
		~IrrSize(void);
		IrrSize(float width,float height);
		IrrSize(const IrrSize& size);
		IrrSize& operator=(const IrrSize& size);
		bool operator==(const IrrSize &v) const;
		bool operator!=(const IrrSize &v) const;
		void setSize(float width,float height);
		bool equals(const IrrSize& size) const;

		IrrSize operator-(const IrrSize &v) const;
		IrrSize operator+(const IrrSize &v) const;
		IrrSize operator/(float divider) const;
		IrrSize operator*(float scaleFactor) const;
	public:
		float width;
		float height;
	private:
	};



	//////////////////////////////////////////////////////////////////////////
	//IrrRect
	class IrrRect
	{
	public:
		IrrRect(void);
		IrrRect(float x,float y,float width,float height);
		IrrRect(const IrrRect& rect);
		IrrRect& operator=(const IrrRect& rect);
		void setRect(float x,float y,float width,float height);
		float getOriginX() const;
		float getOriginY() const;
		float getMinX() const;
		float getMidX() const;
		float getMaxX()  const;
		float getMinY() const;
		float getMidY() const;
		float getMaxY() const;
		bool equal(const IrrRect& rect) const;
		bool containsVector2D(const IrrVector2D& pot) const;
		bool containsVector2D(float x,float y) const;
		bool intersectsRect(const IrrRect& rect) const;
		~IrrRect(void);
	public:
		IrrVector2D origin;
		IrrSize size;
	};



	//////////////////////////////////////////////////////////////////////////
	class IrrClipRect : public IrrRect
	{
	public:
		IrrClipRect(void);
		IrrClipRect(float x,float y,float width,float height,float xOffset,float yOffset);
		~IrrClipRect(void);
		const IrrClipRect& operator=(const IrrRect& other);
		float m_fXOffset;
		float m_fYOffset;
	};
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
}

#define CreateIrrVector2D(x, y)				IrrVector2D((float)(x), (float)(y))
#define CreateIrrSize(width, height)		IrrSize((float)(width), (float)(height))
#define CreateIrrRect(x, y, width, height)	IrrRect((float)(x), (float)(y), (float)(width), (float)(height))
#define CreateIrrColor(r,g,b,a)				IrrColor((r),(g),(b),(a))

// const IrrVector2D PointZero = CreateIrrVector2D(0,0);
// const IrrSize SizeZero = CreateIrrSize(0,0);
// const IrrRect RectZero = CreateIrrRect(0,0,0,0);

#endif	//_IRRGEOM_H_