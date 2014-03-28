#include "IrrISO.h"
#include "IrrStringUtils.h"
#include "IrrMathUtils.h"

static int isoCount = 15;

static double Correct = irr_utils::IrrMathUtils::IrrCos(-irr_utils::IrrMathUtils::PI / 6) * irr_utils::IrrMathUtils::SQRT2;

namespace irr_extends
{

	IrrISO::IrrISO(short isoWidth,short isoHeight,short row,short col)
		:m_gridRow(row),
		m_isoWidth(isoWidth),
		m_isoHeight(isoHeight),
		m_gridCol(col),
		m_GridArr(NULL),
		m_pTarget(NULL),
		offsetX(0),
		offsetY(0)
	{
		m_leftPoint.setVector2D(0,m_isoHeight * isoCount * .5);
		m_topPoint.setVector2D(m_isoWidth * isoCount * .5, 0);
		m_BottomPoint.setVector2D(m_isoWidth * isoCount * .5,m_isoHeight * isoCount);

		init();
	}

	IrrISO::~IrrISO( void )
	{
	}
	
	bool IrrISO::init()
	{
		if(!IrrLayer::init())
		{
			return false;
		}
		__drawTxt();

		IrrISODelegate* isoDelegate = new IrrISODelegate();
		this->setDelegate(isoDelegate);

		return true;
	}


	void IrrISO::initGridPropertyArray()
	{
		m_GridArr = new IrrGridProperty*[m_gridCol];
		for (short i = 0;i < m_gridCol;i++)
		{
			m_GridArr[i] = new IrrGridProperty[m_gridCol];
			for (short j = 0;j < m_gridRow; j++)
			{
				IrrGridProperty flag;
				m_GridArr[i][j] = flag;
			}
		}
	}

	IrrGridProperty* IrrISO::getGridProperty( short gridX,short gridY )
	{
		if(!isOverflow(gridX,gridY))
		{
			return &m_GridArr[gridX][gridY];
		}
		return NULL;
	}

	bool IrrISO::isOverflow( short gridX,short gridY )
	{
		return ((gridX <0 || gridX >=m_gridCol)|| (gridY <0 || gridY >= m_gridRow));
	}

	IrrGridProperty** IrrISO::getGridPropertyList()
	{
		return m_GridArr;
	}

	void IrrISO::setGridProperty( short gridX,short gridY,unsigned int flag )
	{
		if(!isOverflow(gridX,gridY))
		{
			IrrGridProperty* flagIndex = getGridProperty(gridX,gridY);
			if(flagIndex)
				flagIndex->gridFlag.setBit(flag,true);
		}
	}
	
	void IrrISO::setGridProperty( short beginX,short beginY,short endX,short endY,unsigned int flag )
	{
		for (int i = beginX;i<endX;i++)
		{
			for (int j = beginY;j<endY;j++)
			{
				setGridProperty(i,j,flag);
			}
		}
	}

	void IrrISO::resetGridProperty( short gridX,short gridY )
	{
		if(!isOverflow(gridX,gridY))
		{
			IrrGridProperty* flagIndex= getGridProperty(gridX,gridY);
			if(flagIndex)
				flagIndex->gridFlag.reset();
		}
	}


	bool IrrISO::validateGridProperty( short gridX,short gridY,unsigned int flag )
	{
		IrrGridProperty* flagIndex = getGridProperty(gridX,gridY);
		if(flagIndex)
		{
			return flagIndex->gridFlag.isBitSet(flag);
		}
		return false;
	}

	void IrrISO::setTargetMap( IrrNode* Target )
	{
		m_pTarget = Target;
	}


	void IrrISO::draw()
	{
		CCNode::draw();
		__drawLineGrids();
		__drawLineBorder();
		//__drawTxt();
	}

	void IrrISO::__drawLineBorder()
	{
		for (int i = 0 ; i < isoCount ;i++ )
		{
			glLineWidth(3.0f);//线条宽度
			ccDrawColor4B(255,0,0,255);

			ccDrawLine(ccp(m_isoWidth * isoCount * .5,0),ccp(0,m_isoHeight * isoCount * .5));
			ccDrawLine(ccp(m_isoWidth * isoCount * .5,m_isoHeight * isoCount),ccp(0,m_isoHeight * isoCount * .5));
			ccDrawLine(ccp(m_isoWidth * isoCount * .5,0),ccp(m_isoWidth * isoCount,m_isoHeight * isoCount * .5));
			ccDrawLine(ccp(m_isoWidth * isoCount * .5,m_isoHeight * isoCount),ccp(m_isoWidth * isoCount,m_isoHeight * isoCount * .5));
		}
	}

	void IrrISO::__drawLineGrids()
	{
		glLineWidth(2.0f);//线条宽度
		ccDrawColor4B(255,255,255,255);
		for (int i = 0 ; i < isoCount ;i++ )
		{
			ccDrawLine(ccp(m_leftPoint.X + ( i * m_isoWidth * .5 ),m_leftPoint.Y - ( i * m_isoHeight * .5 )),ccp(m_BottomPoint.X + ( i * m_isoWidth * .5 ), m_BottomPoint.Y - ( i * m_isoHeight * .5)));
			ccDrawLine(ccp(m_leftPoint.X + ( i * m_isoWidth * .5 ), m_leftPoint.Y + ( i * m_isoHeight * .5 )),ccp(m_topPoint.X + ( i * m_isoWidth * .5), m_topPoint.Y + ( i * m_isoHeight * .5)));
		}
	}


	void IrrISO::__drawTxt()
	{
		std::string textVal = "";
		for (int i = 0 ; i < isoCount ; i++ )
		{
			for (int j = 0; j < isoCount ;j++ )
			{
				textVal = irr_utils::IrrStringUtils::IntToString(i);
				textVal += "|";
				textVal += irr_utils::IrrStringUtils::IntToString(j);
				CCLabelTTF* label = CCLabelTTF::create(textVal.c_str(),"黑体",15);
				label->setColor(ccc3(255,0,0));
				label->setPosition(ccp(m_isoWidth * .5 * (isoCount - j + i),m_isoHeight * .5 * (j + i ) + m_isoHeight * .5));
				this->addChild(label);
			}
		}
	}


	IrrVector3D IrrISO::calcVector3D( IrrVector2D& pos )
	{
		float diffX = m_isoWidth * (isoCount >> 1);
		IrrVector2D tmpPos = pos;
		tmpPos.X -= diffX - offsetX;
		tmpPos.Y -= offsetY;
		postion3D = IrrISO::ScreenToIso(tmpPos);
		postion3D.X = irr_utils::IrrMathUtils::RoundToFloat((postion3D.X / m_isoHeight) - 1);
		postion3D.Y = 0;
		postion3D.Z = irr_utils::IrrMathUtils::RoundToFloat(postion3D.X / m_isoHeight);
		return postion3D;
	}

	IrrVector3D IrrISO::ScreenToIso( IrrVector2D& pos )
	{
		return IrrVector3D(pos.Y + pos.X * .5, 0, pos.Y - pos.X * .5);
	}

	IrrVector2D IrrISO::IsoToScreen( IrrVector3D& pos )
	{
		float sceneX = pos.X - pos.Z;
		float sceneY = pos.Y * Correct + pos.X + pos.Z * .5;
		return IrrVector2D(sceneX,sceneY);
	}

	
	//////////////////////////////////////////////////////////////////////////
	void IrrISODelegate::handleMove( IrrLayerEvent& evt )
	{

	}

	void IrrISODelegate::handleDown( IrrLayerEvent& evt )
	{
		ENTERFUNC();
		IrrISO* layer = (IrrISO*)(evt.getTarget());
		if(layer)
		{
			IrrVector3D vec3D = layer->calcVector3D(evt.getPos());
			LOG("[X|Y],%f,%f",vec3D.X,vec3D.Z);
		}
		LVFUNC();
	}

	void IrrISODelegate::handleUp( IrrLayerEvent& evt )
	{

	}

	void IrrISODelegate::handleClick( IrrLayerEvent& evt )
	{

	}
	//////////////////////////////////////////////////////////////////////////
	
}