#include "IrrTextFieldTTF.h"

irr_ui::IrrTextFieldTTF::IrrTextFieldTTF():m_pLabel(NULL)
{

}

irr_ui::IrrTextFieldTTF::~IrrTextFieldTTF()
{

}

IrrTextFieldTTF* irr_ui::IrrTextFieldTTF::create( const char *string, const char *fontName, float fontSize )
{
	IrrTextFieldTTF* pLabel = new IrrTextFieldTTF();
	if (pLabel->init(string,fontName,fontSize))
	{
		return pLabel;
	}
	CC_SAFE_DELETE(pLabel);
	return NULL;
}

IrrTextFieldTTF* irr_ui::IrrTextFieldTTF::create( const char *string, const char *fontName, float fontSize, const CCSize& dimensions, CCTextAlignment hAlignment )
{
	IrrTextFieldTTF* pLabel = new IrrTextFieldTTF();
	if (pLabel->init(string,fontName,fontSize,dimensions,hAlignment))
	{
		return pLabel;
	}
	CC_SAFE_DELETE(pLabel);
	return NULL;
}

IrrTextFieldTTF* irr_ui::IrrTextFieldTTF::create( const char *string, const char *fontName, float fontSize, const CCSize& dimensions, CCTextAlignment hAlignment, CCVerticalTextAlignment vAlignment )
{
	IrrTextFieldTTF* pLabel = new IrrTextFieldTTF();
	if (pLabel->init(string,fontName,fontSize,dimensions,hAlignment,vAlignment))
	{
		return pLabel;
	}
	CC_SAFE_DELETE(pLabel);
	return NULL;
}

IrrTextFieldTTF* irr_ui::IrrTextFieldTTF::create()
{
	IrrTextFieldTTF* pLabel = new IrrTextFieldTTF();
	if (pLabel->init())
	{
		return pLabel;
	}
	CC_SAFE_DELETE(pLabel);
	return NULL;
}

void irr_ui::IrrTextFieldTTF::setString( const char *label )
{
	m_pLabel->setString(label);
	this->setDimensions(m_pLabel->getContentSize().width, m_pLabel->getContentSize().height);
}

const char* irr_ui::IrrTextFieldTTF::getString( void )
{
	return m_pLabel->getString();
}

cocos2d::CCTextAlignment irr_ui::IrrTextFieldTTF::getHorizontalAlignment()
{
	return m_pLabel->getHorizontalAlignment();
}

void irr_ui::IrrTextFieldTTF::setHorizontalAlignment( CCTextAlignment alignment )
{
	m_pLabel->setHorizontalAlignment(alignment);
}

cocos2d::CCVerticalTextAlignment irr_ui::IrrTextFieldTTF::getVerticalAlignment()
{
	return m_pLabel->getVerticalAlignment();
}

void irr_ui::IrrTextFieldTTF::setVerticalAlignment( CCVerticalTextAlignment verticalAlignment )
{
	m_pLabel->setVerticalAlignment(verticalAlignment);
}

void irr_ui::IrrTextFieldTTF::setDimensions( IrrSize& size )
{
	IrrNode::setDimensions(size);
	m_pLabel->setContentSize(CCSizeMake(size.width,size.height));
	//m_pLabel->setDimensions(CCSizeMake(size.width,size.height));
}

void IrrTextFieldTTF::setDimensions( float width,float height )
{
	IrrNode::setDimensions(width,height);
	//m_pLabel->setDimensions(CCSizeMake(width,height));
	m_pLabel->setContentSize(CCSizeMake(width,height));
}

float irr_ui::IrrTextFieldTTF::getFontSize()
{
	return m_pLabel->getFontSize();
}

void irr_ui::IrrTextFieldTTF::setFontSize( float fontSize )
{
	m_pLabel->setFontSize(fontSize);
}

const char* irr_ui::IrrTextFieldTTF::getFontName()
{
	return m_pLabel->getFontName();
}

void irr_ui::IrrTextFieldTTF::setFontName( const char *fontName )
{
	m_pLabel->setFontName(fontName);
}

void irr_ui::IrrTextFieldTTF::enableShadow( const CCSize &shadowOffset, float shadowOpacity, float shadowBlur, bool mustUpdateTexture /*= true*/ )
{
	m_pLabel->enableShadow(shadowOffset,shadowOpacity,shadowBlur,mustUpdateTexture);
}

void irr_ui::IrrTextFieldTTF::disableShadow( bool mustUpdateTexture /*= true*/ )
{
	m_pLabel->disableShadow(mustUpdateTexture);
}

void irr_ui::IrrTextFieldTTF::enableStroke( const ccColor3B &strokeColor, float strokeSize, bool mustUpdateTexture /*= true*/ )
{
	m_pLabel->enableStroke(strokeColor,strokeSize,mustUpdateTexture);
}

void irr_ui::IrrTextFieldTTF::disableStroke( bool mustUpdateTexture /*= true*/ )
{
	m_pLabel->disableStroke(mustUpdateTexture);
}

void irr_ui::IrrTextFieldTTF::setFontFillColor( const ccColor3B &tintColor, bool mustUpdateTexture /*= true*/ )
{
	m_pLabel->setFontFillColor(tintColor);
}

bool irr_ui::IrrTextFieldTTF::init( const char *string, const char *fontName, float fontSize )
{
	bool ret = false;

	m_pLabel = CCLabelTTF::create(string,fontName,fontSize);
	if (m_pLabel != NULL)
	{
		this->addChild(m_pLabel);
		this->setDimensions(m_pLabel->getContentSize().width, m_pLabel->getContentSize().height);
		ret = true;
	}
	
	return ret;
}

bool irr_ui::IrrTextFieldTTF::init( const char *string, const char *fontName, float fontSize, const CCSize& dimensions, CCTextAlignment hAlignment )
{
	bool ret = false;

	m_pLabel = CCLabelTTF::create(string,fontName,fontSize);
	if (m_pLabel != NULL)
	{
		this->addChild(m_pLabel);
		this->setDimensions(m_pLabel->getContentSize().width, m_pLabel->getContentSize().height);
		ret = true;
	}

	return ret;
}

bool irr_ui::IrrTextFieldTTF::init( const char *string, const char *fontName, float fontSize, const CCSize& dimensions, CCTextAlignment hAlignment, CCVerticalTextAlignment vAlignment )
{
	bool ret = false;

	m_pLabel = CCLabelTTF::create(string,fontName,fontSize);
	if (m_pLabel != NULL)
	{
		this->addChild(m_pLabel);
		this->setDimensions(m_pLabel->getContentSize().width, m_pLabel->getContentSize().height);
		ret = true;
	}

	return ret;
}

bool irr_ui::IrrTextFieldTTF::init()
{
	bool ret = false;

	m_pLabel = CCLabelTTF::create();
	if (m_pLabel != NULL)
	{
		this->addChild(m_pLabel);
		this->setDimensions(m_pLabel->getContentSize().width, m_pLabel->getContentSize().height);
		ret = true;
	}

	return ret;
}

void irr_ui::IrrTextFieldTTF::setLabelDimensions( float width,float height )
{
	m_pLabel->setDimensions(CCSizeMake(width,height));
	this->setDimensions(m_pLabel->getContentSize().width,m_pLabel->getContentSize().height);
}

cocos2d::CCSize irr_ui::IrrTextFieldTTF::getLabelDimensions()
{
	return m_pLabel->getDimensions();
}

