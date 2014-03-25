#include "IrrGraphic.h"

namespace irr_core
{

	IrrGraphic::IrrGraphic( void )
		:m_Width(0),
		m_Height(0),
		m_pShader(NULL)
	{
		m_pShader = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor);
		IRR_SAFE_RETAIN(m_pShader);
	}

	IrrGraphic::~IrrGraphic( void )
	{
		IRR_SAFE_DELETE(m_pShader);
	}

	void IrrGraphic::setGraphicSize( float iWidth,float iHeight )
	{
		m_Width  = iWidth;
		m_Height = iHeight;
	}

	void IrrGraphic::setColor( IrrColor& color )
	{
		m_Color = color;
	}

	void IrrGraphic::drawPoint( float x, float y )
	{
		if (!m_ClipStack.empty())
		{
			const IrrClipRect& top = m_ClipStack.top();
			x += top.m_fXOffset;
			y += top.m_fYOffset;
			IrrVector2D pt;
			pt.setVector2D(x,m_Height - y);
			//ccDrawPoint(pt);
		}
	}

	void IrrGraphic::drawLine( float x1, float y1, float x2, float y2 )
	{
		if (!m_ClipStack.empty())
		{
			const IrrClipRect& top = m_ClipStack.top();

			x1 += top.m_fXOffset;
			y1 += top.m_fYOffset;
			x2 += top.m_fXOffset;
			y2 += top.m_fYOffset;

			IrrVector2D ptStart;
			ptStart.setVector2D(x1,m_Height - y1);

			IrrVector2D ptEnd;
			ptEnd.setVector2D(x2,m_Height - y2);
			//ccDrawLine(ptStart,ptEnd);	
		}
	}

	void IrrGraphic::drawRectangle( const IrrRect& rectangle )
	{
		if (!m_ClipStack.empty())
		{

			const IrrClipRect& top = m_ClipStack.top();

			IrrVector2D pt;
			pt.X = rectangle.origin.X + top.m_fXOffset;
			pt.Y = m_Height - (rectangle.origin.X+ top.m_fYOffset);
			//////////////////////////////////////////////////////////////////////////
			IrrVector2D ptDemesion;
			ptDemesion.X = pt.X + rectangle.size.width;
			ptDemesion.X = pt.Y - rectangle.size.height;
			
			ccDrawColor4B(m_Color.R,m_Color.G,m_Color.B,m_Color.A);
			//ccDrawRect(pt,ptDemesion);
		}
	}

	void IrrGraphic::fillRectangle( const IrrRect& rectangle )
	{
		if (!m_ClipStack.empty())
		{
			const IrrClipRect& top = m_ClipStack.top();
			IrrVector2D pt;
			pt.X = rectangle.origin.X + top.m_fXOffset;
			pt.Y = m_Height - (rectangle.origin.Y + top.m_fYOffset);
			//////////////////////////////////////////////////////////////////////////
			IrrVector2D ptDemesion;
			ptDemesion.X = pt.X + rectangle.size.width;
			ptDemesion.Y = pt.Y - rectangle.size.height;
			
			ccColor4F  color;
			color.r = m_Color.R/255.0f;
			color.g = m_Color.G/255.0f;
			color.b = m_Color.B/255.0f;
			color.a = m_Color.A/255.0f;
			//ccDrawSolidRect(pt,ptDemesion,color);
		}
	}

	bool IrrGraphic::pushClipArea( IrrRect area )
	{
		bool result =  false;
//////////////////////////////////////////////////////////////////////////
		//compute clip area
		result = pushClipAreaInner(area);
//////////////////////////////////////////////////////////////////////////
		CCEGLView::sharedOpenGLView()->setScissorInPoints(m_ClipStack.top().origin.X,
			m_Height - m_ClipStack.top().origin.X - m_ClipStack.top().size.height,
			m_ClipStack.top().size.width,
			m_ClipStack.top().size.height);
		return true;
	}

	void IrrGraphic::popClipArea( void )
	{
		if (!m_ClipStack.empty())
		{
			m_ClipStack.pop();

			if (!m_ClipStack.empty())
			{
				IrrClipRect& topClip = m_ClipStack.top();
				CCEGLView::sharedOpenGLView()->setScissorInPoints(topClip.origin.X,
					m_Height - topClip.origin.Y - topClip.size.height,
					topClip.size.width,
					topClip.size.height);
			}
			else
			{
				;//do nothing
			}
		}
	}

	const IrrClipRect& IrrGraphic::getCurrentClipArea( void )
	{
		return m_ClipStack.top();
	}

	void IrrGraphic::reset( void )
	{

	}

	void IrrGraphic::beginDraw()
	{
		glEnable(GL_SCISSOR_TEST);
		pushClipArea(CreateIrrRect(0, 0, m_Width, m_Height));
	}

	void IrrGraphic::endDraw()
	{
		glDisable(GL_SCISSOR_TEST);
		popClipArea();
	}


	bool IrrGraphic::pushClipAreaInner( IrrRect area )
	{
		if (area.size.width < 0 || area.size.height < 0)
		{
			IrrClipRect carea;
			m_ClipStack.push(carea);
			return true;
		}

		if (m_ClipStack.empty())
		{
			IrrClipRect carea;
			carea = area;
			carea.m_fXOffset = area.origin.X;
			carea.m_fYOffset = area.origin.Y;
			m_ClipStack.push(carea);
			return true; 
		}

		const IrrClipRect &top = m_ClipStack.top();
		IrrClipRect carea;
		carea = area;
		carea.m_fXOffset = top.m_fXOffset + carea.origin.X;
		carea.m_fYOffset = top.m_fYOffset + carea.origin.Y;
		carea.origin.X += top.m_fXOffset;
		carea.origin.Y += top.m_fYOffset;

		// Clamp the pushed clip rectangle.
		if (carea.origin.X < top.origin.X)
		{
			carea.origin.X = top.origin.X;
		}

		if (carea.origin.Y < top.origin.Y)
		{
			carea.origin.Y = top.origin.Y;            
		}

		if (carea.origin.X + carea.size.width > top.origin.X + top.size.width)
		{
			carea.size.width = top.origin.X + top.size.width - carea.origin.X;

			if (carea.size.width < 0)
			{
				carea.size.width = 0;
			}
		}

		if (carea.origin.Y + carea.size.height > top.origin.Y + top.size.height)
		{
			carea.size.height = top.origin.Y + top.size.height - carea.origin.Y;

			if (carea.size.height < 0)
			{
				carea.size.height = 0;
			}
		}
		bool result = carea.intersectsRect(top);
		m_ClipStack.push(carea);
		return result;
	}


	void IrrGraphic::drawImage( const CCTexture2D* image,int srcX,int srcY,int dstX,int dstY,int width,int height,unsigned char alpha /*= 255*/ )
	{
		if(image && ! m_ClipStack.empty())
		{
			const IrrClipRect& topRect = m_ClipStack.top();

			dstX += topRect.m_fXOffset;
			dstY += topRect.m_fYOffset;
			ccV3F_C4B_T2F_Quad sQuad = {0};
//////////////////////////////////////////////////////////////////////////
			ccColor4B color4 = { 255, 255, 255,255 };
			color4.a = alpha;
			sQuad.bl.colors = color4;
			sQuad.br.colors = color4;
			sQuad.tl.colors = color4;
			sQuad.tr.colors = color4;
//////////////////////////////////////////////////////////////////////////
			float x1 = dstX;
			float y1 = m_Height - dstY;
			float x2 = x1 + width;
			float y2 = y1 - height;
			// Don't update Z.
			sQuad.tl.vertices = vertex3(x1, y1, 0);

			sQuad.bl.vertices = vertex3(x1, y2, 0);

			sQuad.br.vertices = vertex3(x2, y2, 0);

			sQuad.tr.vertices = vertex3(x2, y1, 0);
			//////////////////////////////////////////////////////////////////////////
			//update 
			float atlasWidth = (float)((CCTexture2D*)image)->getPixelsWide();
			float atlasHeight = (float)((CCTexture2D*)image)->getPixelsHigh();
			float left, right, top, bottom;
			left	= srcX/atlasWidth;
			right	= (((CCTexture2D*)image)->getContentSize().width)/atlasWidth;
			top		= srcY/atlasHeight;
			bottom	= (((CCTexture2D*)image)->getContentSize().height)/atlasHeight;


			sQuad.bl.texCoords.u = left;
			sQuad.bl.texCoords.v = bottom;
			sQuad.br.texCoords.u = right;
			sQuad.br.texCoords.v = bottom;
			sQuad.tl.texCoords.u = left;
			sQuad.tl.texCoords.v = top;
			sQuad.tr.texCoords.u = right;
			sQuad.tr.texCoords.v = top;
			//////////////////////////////////////////////////////////////////////////

			ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );

#define kQuadSize sizeof(sQuad.bl)
			m_pShader->use();
			m_pShader->setUniformsForBuiltins();
			ccGLBindTexture2D(((CCTexture2D*)image)->getName());
			ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );
			long offset = (long)&sQuad;

			// vertex
			int diff = offsetof( ccV3F_C4B_T2F, vertices);
			glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));

			// texCoods
			diff = offsetof( ccV3F_C4B_T2F, texCoords);
			glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

			// color
			diff = offsetof( ccV3F_C4B_T2F, colors);
			glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

			//////////////////////////////////////////////////////////////////////////
			// draw bounding box
			//for clip rect ,modify this position
			IrrRect rc(dstX - topRect.m_fXOffset + 1,
				dstY - topRect.m_fYOffset + 1,
				width - 2,height - 2);
			this->drawRectangle(rc);
		}
	}
}


#if 0//this is for rotation
//do not implement all the logic
void CGAffineToGL(const CCAffineTransform *t, GLfloat *m)
{
	// | m[0] m[4] m[8]  m[12] |     | m11 m21 m31 m41 |     | a c 0 tx |
	// | m[1] m[5] m[9]  m[13] |     | m12 m22 m32 m42 |     | b d 0 ty |
	// | m[2] m[6] m[10] m[14] | <=> | m13 m23 m33 m43 | <=> | 0 0 1  0 |
	// | m[3] m[7] m[11] m[15] |     | m14 m24 m34 m44 |     | 0 0 0  1 |

	m[2] = m[3] = m[6] = m[7] = m[8] = m[9] = m[11] = m[14] = 0.0f;
	m[10] = m[15] = 1.0f;
	m[0] = t->a; m[4] = t->c; m[12] = t->tx;
	m[1] = t->b; m[5] = t->d; m[13] = t->ty;
}
void CGraphic::drawImage2(const CCTexture2D* image,int srcX,int srcY,int dstX,int dstY,int width,int height)
{
	kmGLPushMatrix();

	float cx = 1, sx = 0, cy = 1, sy = 0,m_fRotationX = 60,m_fRotationY = 60;
	if (m_fRotationX || m_fRotationY)
	{
		float radiansX = -CC_DEGREES_TO_RADIANS(m_fRotationX);
		float radiansY = -CC_DEGREES_TO_RADIANS(m_fRotationY);
		cx = cosf(radiansX);
		sx = sinf(radiansX);
		cy = cosf(radiansY);
		sy = sinf(radiansY);
	}
	float m_fScaleY = 1.0f;
	float m_fScaleX = 1.0f;
	// Build Transform Matrix
	// Adjusted transform calculation for rotational skew
	CCAffineTransform m_sTransform;     ///< transform

	float x = dstX;
	float y = m_Height - dstY;

	CCPoint ptAnchor(0,1); 
	CCPoint m_obAnchorPointInPoints;
	m_obAnchorPointInPoints.x = ptAnchor.x * width;
	m_obAnchorPointInPoints.y = ptAnchor.y * height;


	x += cy * -m_obAnchorPointInPoints.x * m_fScaleX + -sx * -m_obAnchorPointInPoints.y * m_fScaleY;
	y += sy * -m_obAnchorPointInPoints.x * m_fScaleX +  cx * -m_obAnchorPointInPoints.y * m_fScaleY;


	m_sTransform = CCAffineTransformMake( cy * m_fScaleX,  sy * m_fScaleX,
		-sx * m_fScaleY, cx * m_fScaleY,x,y);


	kmMat4 transfrom4x4;

	CGAffineToGL(&m_sTransform, transfrom4x4.mat);

	// Update Z vertex manually
	transfrom4x4.mat[14] = 0.0f;

	kmGLMultMatrix( &transfrom4x4 );



	ccV3F_C4B_T2F_Quad sQuad = {0};
	//////////////////////////////////////////////////////////////////////////
	ccColor4B color4 = { 255, 255, 255,255 };

	sQuad.bl.colors = color4;
	sQuad.br.colors = color4;
	sQuad.tl.colors = color4;
	sQuad.tr.colors = color4;
	//////////////////////////////////////////////////////////////////////////
	float x1 = 0 ;
	float y1 = 0 ;
	float x2 = width;
	float y2 = height;

	// Don't update Z.
	sQuad.bl.vertices = vertex3(x1, y1, 0);
	sQuad.br.vertices = vertex3(x2, y1, 0);
	sQuad.tl.vertices = vertex3(x1, y2, 0);
	sQuad.tr.vertices = vertex3(x2, y2, 0);

	//////////////////////////////////////////////////////////////////////////
	//update 
	float atlasWidth = (float)((CCTexture2D*)image)->getPixelsWide();
	float atlasHeight = (float)((CCTexture2D*)image)->getPixelsHigh();
	float left, right, top, bottom;
	left	= srcX/atlasWidth;
	right	= (((CCTexture2D*)image)->getContentSize().width)/atlasWidth;
	top		= srcY/atlasHeight;
	bottom	= (((CCTexture2D*)image)->getContentSize().height)/atlasHeight;


	sQuad.bl.texCoords.u = left;
	sQuad.bl.texCoords.v = bottom;
	sQuad.br.texCoords.u = right;
	sQuad.br.texCoords.v = bottom;
	sQuad.tl.texCoords.u = left;
	sQuad.tl.texCoords.v = top;
	sQuad.tr.texCoords.u = right;
	sQuad.tr.texCoords.v = top;
	//////////////////////////////////////////////////////////////////////////


	ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );

#define kQuadSize sizeof(sQuad.bl)
	m_pShader->use();
	m_pShader->setUniformsForBuiltins();
	ccGLBindTexture2D(((CCTexture2D*)image)->getName());
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );
	long offset = (long)&sQuad;

	// vertex
	int diff = offsetof( ccV3F_C4B_T2F, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));

	// texCoods
	diff = offsetof( ccV3F_C4B_T2F, texCoords);
	glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

	// color
	diff = offsetof( ccV3F_C4B_T2F, colors);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	kmGLPopMatrix();
}
#endif