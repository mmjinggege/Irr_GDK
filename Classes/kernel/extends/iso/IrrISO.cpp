#include "IrrISO.h"
#include "IrrNode.h"

namespace irr_extends
{

	IrrISO::IrrISO( short row,short col )
		:m_gridRow(row),
		m_gridCol(col),
		m_GridArr(NULL),
		m_pTarget(NULL)
	{
	}

	IrrISO::~IrrISO( void )
	{
	}

	void IrrISO::initGridPropertyArray()
	{
		m_GridArr = new IrrGridProperty*[m_gridCol];
		for (short i = 0;i < m_gridCol;i++)
		{
			m_GridArr[i] = new IrrGridProperty[m_gridCol];
			for (size_t j = 0;j < m_gridRow; j++)
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
}