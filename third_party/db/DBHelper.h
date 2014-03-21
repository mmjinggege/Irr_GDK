#ifndef __DB_HELPER_H__
#define __DB_HELPER_H__
#include "dataBase.h"
#ifndef byte
typedef unsigned char byte;
#endif
/*
数据库帮助类，模拟安卓的实现
author:frikezhao
contact:frikezhao@qq.com
date:2012-9-10
how to use:
//first you should create a db 
//then use ContentValues to do thing interesting as in android 
			//create a table
			ContentValues values;
			values.put(std::string("m_strID"),std::string("TEXT PRIMARY KEY"));
			values.put(std::string("m_strPWD"),std::string("TEXT"));
			values.put(std::string("m_bAutoLogin"),std::string("INTEGER"));
			values.put(std::string("m_bSaveUserPWD"),std::string("INTEGER"));		
			values.put(std::string("m_time"),std::string("INTEGER"));
			ret = m_pDB->createTable(CONFIG_TABLE_NAME,&values);
			
			//query
			dbEnumerator* pEnum = m_pDB->query(CONFIG_TABLE_NAME,"*","","m_time desc limit 1");
			if (pEnum)
			{
					if(pEnum->moveNext())
					{
						pEnum->getStringAt(0,m_strID);
						pEnum->getStringAt(1,m_strPWD);
						pEnum->getIntAt(2,itemp);
						pEnum->getIntAt(3,itemp);
					}
					delete pEnum;
					pEnum = NULL;
			}
			
			//insert
			ContentValues values;
			//transaction
			m_pDb->beginTransaction();
			std::vector<ZLZ::stMsg*>& vcStMsg;
			ZLZ::stMsg* pMsg = NULL;
			for (;index < count;index++)
			{
				pMsg = vcStMsg.at(index);
				values.put(std::string("iSenderId"),pMsg->sSenderId);
				values.put(std::string("sSenderName"),pMsg->sSenderName);
				values.put(std::string("iSendTime"),pMsg->iSendTime);
				m_pDb->insert(pstrTableName,&values);
				values.clear();
			}
			//commit the transaction
			m_pDb->endTransaction();
*/
class ContentValues
{
public:
	enum
	{
		VALUE_TYPE_BYTE,
		VALUE_TYPE_BOOL,
		VALUE_TYPE_SHORT,
		VALUE_TYPE_INT,
		VALUE_TYPE_BYTE_ARRAY,
		VALUE_TYPE_FLOAT,
		VALUE_TYPE_LONG,
		VALUE_TYPE_STRING,
		VALUE_TYPE_NULL
	};

	ContentValues();
	~ContentValues();
	//////////////////////////
	bool containsKey(std::string key);
	int  size(void);
	void clear(void);
	std::vector<std::pair<std::string,std::pair<std::string,int> > >* getContentMap(void);
	void put(std::string key, int value);
	void put(std::string key, short value);
	void put(std::string key, std::vector<char> value);
	void put(std::string key, byte value);
	void put(std::string key, std::string value);
	void put(std::string key, long value);
	void put(std::string key, bool value);
	void put(std::string key, float value);
	void putNULL(std::string key); 

	std::string getAsString(std::string key);
	bool		getAsBool(std::string key);
	int			getAsInt(std::string key);
	short       getAsShort(std::string key);
	bool		getAsByteArray(std::string key,std::string& strByteBuffer);
	long        getAsLong(std::string key);
	float       getAsfloat(std::string key);
	byte        getAsByte(std::string key);

	void remove(std::string key);
	//////////////////////////
private:
	std::pair<std::string,std::pair<std::string,int> >* findKey(std::string key);
	//std::map<std::string,std::pair<std::string,int> >* m_pValues;
	std::vector<std::pair<std::string,std::pair<std::string,int> > >* m_pValues;
};



class PropertyHelper
{
public:
	static	float	stringToFloat(const std::string& str);
	static	unsigned int	stringToUint(const std::string& str);
	static	int		stringToInt(const std::string& str);

	//16进制
	static	int		stringToIntOX(const std::string& str);
	static	bool	stringToBool(const std::string& str);
	static  char    stringToChar(const std::string& str);
	static  byte    stringToByte(const std::string& str);
	static  long    stringToLong(const std::string& str);
	//////////////////////////////////////////////////////////////////////////
	static std::string	floatToString(float val);
	static std::string	floatToString1(float val);//保留1位小数
	static std::string	floatToString2(float val);//保留2位小数
	static std::string	uintToString(unsigned int val);
	static std::string	intToString(int val);
	static std::string  oxToString(int val);
	static std::string	boolToString(bool val);
	static std::string  longToString(long val);
	static std::string  ulongToString(unsigned long val);
};


//数据库默认加密的KEY
#define DEFAULT_KEY "xiaoruyu*$@"
class DBHelper
{
public:
	DBHelper(void);
	~DBHelper(void);
	bool init(const char* strDBName,std::string strRelativePath="",std::string strKey =DEFAULT_KEY);
	bool createTable(const char* strTableName,ContentValues* pContentValues);
	//bReplace 是否使用replace 语句
	bool insert(const char* strTableName,ContentValues* pContentValues,bool bReplace = false);
	dbEnumerator* query(const char* strTabName,std::string strCols,std::string strSeletion = std::string(""),std::string strOrderBy = std::string(""));
	bool update(const char* strTabeName,ContentValues* pContentValues,std::string strSeletion);
	bool del(const char* strTabName,std::string strSeletion = "");
	////////////////
	bool beginTransaction(void);
	bool endTransaction(void);
	bool rollBackTransaction(void);
	const dataBase* getDataBase(void);
private:
	dataBase* m_pDataBase;
};
#endif //__DB_HELPER_H__