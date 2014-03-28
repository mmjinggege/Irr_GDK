#include "IrrPngLabel.h"
#include "utf8.h"
const std::string irr_ui::IrrPngLabel::FONT_FILE = "sysFont.fnt";

IrrPngLabel* irr_ui::IrrPngLabel::create( const char* label )
{
	IrrPngLabel *pRet = new IrrPngLabel();
	if(pRet && pRet->initWithString(label))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

irr_ui::IrrPngLabel::IrrPngLabel( void )
	:m_pFontLabel(NULL)
	,m_pEventTarget(NULL)
	,m_pClickSelector(NULL)
	,m_baseContent("")
	,m_Align(kCCTextAlignmentCenter)
	,m_vectorAlign(kCCVerticalTextAlignmentCenter)
	,m_Scale(1.0f)
	,m_fSize(36)
	,m_curContent("")
{

}

irr_ui::IrrPngLabel::~IrrPngLabel( void )
{
	removeFromParentAndCleanup(true);
	CC_SAFE_RELEASE(m_pFontLabel);
}

const char* irr_ui::IrrPngLabel::getFontName()
{
	return m_pFontLabel->getConfiguration()->getAtlasName();
}

float irr_ui::IrrPngLabel::getFontSize()
{
	return m_fSize;
}

void irr_ui::IrrPngLabel::setFontSize( float size )
{
	m_fSize = size;
	switch((int)m_fSize)
	{
	case 15:
		{
		 	m_Scale =0.67f;
		 	break;
		}
	case 16:
		{
			m_Scale = 0.7f;
			break;
		}
	case 18:
		{
			m_Scale = 0.76f;
			break;
		}
	case 20:
		{
			m_Scale = 0.8f;
		}
	case 24:
		{
			m_Scale =0.9f;
			break;
		}
	case 22:
		{
			m_Scale = 0.85f;
			break;
		}
	case 30:
		{
			m_Scale = 1.3f;
			break;
		}
	case 36:
		{
			m_Scale =1.5f;
			break;
		}
	}
	m_pFontLabel->setScale(m_Scale);

	resetCurContent();
	setStrByCurContent();
	updateLabelPos();
}

void irr_ui::IrrPngLabel::setColor( const cocos2d::ccColor3B &_value )
{
	m_pFontLabel->setColor(_value);
}

const cocos2d::ccColor3B irr_ui::IrrPngLabel::getColor()
{
	return m_pFontLabel->getColor();
}

void irr_ui::IrrPngLabel::setTextAlign( cocos2d::CCTextAlignment align )
{
	m_Align = align;
	//m_pFontLabel->setAlignment(align);

	switch(align)
	{
	case kCCTextAlignmentCenter:
		{
			m_pFontLabel->setPositionX((getDimensions().width - m_pFontLabel->getContentSize().width)/2);
			break;
		}
	case kCCTextAlignmentRight:
		{
			m_pFontLabel->setPositionX(getDimensions().width - m_pFontLabel->getContentSize().width);
			break;
		}
	case kCCTextAlignmentLeft:
		{
			m_pFontLabel->setPositionX(0);
			break;
		}
	}
}

void irr_ui::IrrPngLabel::setVerticalTextAlign( cocos2d::CCVerticalTextAlignment align )
{
	m_vectorAlign = align;

	switch(align)
	{
	case kCCVerticalTextAlignmentTop:
		{
			m_pFontLabel->setPositionY(getDimensions().height - m_pFontLabel->getContentSize().height);
			break;
		}
	case kCCVerticalTextAlignmentCenter:
		{
			m_pFontLabel->setPositionY((getDimensions().height - m_pFontLabel->getContentSize().height)/2);
			break;
		}
	case kCCVerticalTextAlignmentBottom:
		{
			m_pFontLabel->setPositionY(0);
			break;
		}
	default:
		{
			m_pFontLabel->setPositionY(0);
			break;
		}
	}
}

cocos2d::CCTextAlignment irr_ui::IrrPngLabel::getTextAlignment()
{
	return  m_Align;
}

cocos2d::CCVerticalTextAlignment irr_ui::IrrPngLabel::getVerticalTextAlignment()
{
	return m_vectorAlign;
}


cocos2d::CCSize irr_ui::IrrPngLabel::getCharSize( unsigned int index )
{
	CCSize size;
	if(m_pFontLabel)
	{
		std::vector<CCSize> mCharsVec = m_pFontLabel->m_CharsVec;
		if(mCharsVec.empty())
		{
			return size;
		}
		if(index >= mCharsVec.size())
		{
			return size;
		}
		size = mCharsVec[index];
		size.width *= m_Scale;
		size.height *= m_Scale;
	}
	return size;
}

bool irr_ui::IrrPngLabel::initWithString( const char* label )
{
	if(m_pFontLabel == NULL)
	{
		m_pFontLabel = CCLabelBMFont::create(label,FONT_FILE.c_str());
		m_pFontLabel->retain();
		m_pFontLabel->setAnchorPoint(ccp(0,0));
		this->addChild(m_pFontLabel);
		//this->setAnchorPoint(ccp(0.5,0.5));
	}
	setString(label);
	return true;
}

void irr_ui::IrrPngLabel::setDimensions( IrrSize& size )
{
	IrrNode::setDimensions(size);
	this->setContentSize(CCSizeMake(this->getDimensions().width,this->getDimensions().height));

	resetCurContent();
	setStrByCurContent();
	updateLabelPos();
}

void irr_ui::IrrPngLabel::setDimensions( float width,float height )
{
	IrrNode::setDimensions(width,height);
	this->setContentSize(CCSizeMake(this->getDimensions().width,this->getDimensions().height));

	resetCurContent();
	setStrByCurContent();
	updateLabelPos();
}

void irr_ui::IrrPngLabel::updateContentSize()
{
	CCSize contentSize = m_pFontLabel->getContentSize();
	contentSize.width *= m_Scale;
	contentSize.height *= m_Scale;
	m_pFontLabel->setContentSize(contentSize);
}

int irr_ui::IrrPngLabel::getTxtLen( const std::string& txt )
{
	char* tmpChar = (char*)txt.c_str();
	return u8_strlen(tmpChar);
}

bool irr_ui::IrrPngLabel::isEnglish( char txt )
{
	if ((txt>='a'&& txt<='z')||(txt>='A' && txt<='Z'))
	{
		return true;
	}
	return false;
}

std::string irr_ui::IrrPngLabel::splitTxt( std::string txt,int count,int offset/*=0*/ )
{
	char* tmpChar = (char*)txt.c_str();
	int txtLen = getTxtLen(txt);
	if (count > txtLen)
		count = txtLen;

	int off = u8_offset(tmpChar,offset);
	int tmp = txt.length()-off;
	std::string tmpStr  =txt.substr(off,tmp);
	tmpChar = (char*)tmpStr.c_str();

	int coutOff = u8_offset(tmpChar,count);

	std::string txtTmp = tmpStr.substr(0,coutOff);
	return txtTmp;
}

void irr_ui::IrrPngLabel::resetCurContent()
{
	if (getDimensions().width == 0)
	{
		m_pFontLabel->setString(m_baseContent.c_str());
		updateLabelPos();
		return;
	}

	if (getDimensions().width <= getCharSize(0).width)
	{
		m_pFontLabel->setString(m_baseContent.c_str());
		updateLabelPos();
		return;
	}

	m_pFontLabel->setString(m_baseContent.c_str());

	std::string txt = m_baseContent;
	int txtLen = getTxtLen(txt);
	int curLabelWidth = 0;
	int idx = 0;
	int lineCharCount = 0;
	m_curContent = "";
	for (int i = 0;i < txtLen; i++)
	{
		std::string tmpStr = splitTxt(m_baseContent, 1, idx);
		if (tmpStr == "\n")//»»ÐÐ·û
		{
			m_curContent += tmpStr;
			curLabelWidth = 0;
			idx++;
			continue;
		}
		int charWith = getCharSize(idx).width;
		if (charWith > getDimensions().width)
		{
			m_pFontLabel->setString(m_baseContent.c_str());
			return;
		}
		if(charWith + curLabelWidth > getDimensions().width)
		{
			m_curContent += "\n";
			lineCharCount = 0 ;
			txtLen ++;
			curLabelWidth = 0;
			continue;
		}
		m_curContent += tmpStr;
		curLabelWidth += getCharSize(idx++).width;
		lineCharCount++;
	}
}

void irr_ui::IrrPngLabel::draw()
{
	IrrNode::draw();
	glLineWidth(1);
	ccDrawColor4B(255,0,0,255);
	const CCSize& s = this->getContentSize();
	CCPoint vertices[4]={
	 	ccp(0,0),ccp(s.width,0),
	 	ccp(s.width,s.height),ccp(0,s.height),
	};
	ccDrawPoly(vertices, 4, true);
}

void irr_ui::IrrPngLabel::setString( const char* string )
{
	m_baseContent = string;
	if(m_pFontLabel)
	{
		resetCurContent();
		setStrByCurContent();
		updateLabelPos();
	}
}

void irr_ui::IrrPngLabel::setStrByCurContent()
{
	m_pFontLabel->setString(m_curContent.c_str());
	updateContentSize();
}


void irr_ui::IrrPngLabel::updateLabelPos()
{
	setVerticalTextAlign(m_vectorAlign);
	setTextAlign(m_Align);
}


void irr_ui::IrrPngLabel::handleDown( IrrUIEvent& event )
{
	this->setScale(m_pFontLabel->getScale() - 0.05f);
	event.setHandled(true);
}

void irr_ui::IrrPngLabel::handleUp( IrrUIEvent& event )
{
	this->setScale(m_pFontLabel->getScale() + 0.05f);
}

void irr_ui::IrrPngLabel::handleClick( IrrUIEvent& event )
{

}

void irr_ui::IrrPngLabel::addClickEvent( CCObject* target,Irr_GUI_SEL_ClickEvent selector )
{

}


