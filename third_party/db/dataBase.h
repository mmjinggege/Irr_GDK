#ifndef __DATA_BASE_H__
#define __DATA_BASE_H__
#include "sqlite/sqlite3.h"
#include <string>
#include <vector>
//#include "commonInc.h"

//!!需要使用sqlite库
class dataBase;

class dbEnumerator
{
public:
	dbEnumerator(void);
	~dbEnumerator(void);

	//////////////////////////////////////////////////////////////////////////
	bool moveNext(void);
	//colIndex start from 0
	bool getIntAt(int col,int& value);
	bool getDoubleAt(int col,double& value);
	bool getStringAt(int col,std::string& str); 
	bool getFloatAt(int col,float& value);

	int  getTotalLineCount(void);
	std::vector<std::string>* getCurrLineValues();
public://read only
	int  m_iTotalLine;
	int  m_colCount;
	std::vector< std::vector<std::string>* > m_colValues;
	//////////////////////////////////////////////////////////////////////////
	int m_currentLine;
};

//////////////////////////////////////////////////////////////////////////
class dbStatement
{
public:
	dbStatement(void);
	~dbStatement(void);
	//////////////////////////////////////////////////////////////////////////
	//you can bind different values
	//colIndex start from 0
	bool bindInt(int colIndex,int value);
	bool bindDouble(int colIndex,double value);
	bool bindString(int colIndex,std::string& str);
	bool bindNull(int colIndex);
	bool bindBytes(int colIndex,const void* pBuffer,int size);
private:
	friend class dataBase;
	sqlite3_stmt*	m_pstmt;
};
//////////////////////////////////////////////////////////////////////////
class dataBase
{
public:
	dataBase(void);
	virtual ~dataBase(void);
	//////////////////////////////////////////////////////////////////////////
	//open a db
	//utf-8 encoding
	bool openDB(const char* strdbName,const std::string& strkey);
	//execute sql
	bool executeSql(const char* strSql);
	//query
	dbEnumerator* query(const char* strSql);
	//transaction
	bool beginTransaction(void);
	bool endTransaction(void);
	bool rollBackTransaction(void);
	//create and execute statement
	dbStatement* createStatement(const char* strSql);
	bool executeStatement(dbStatement* pStmt);
private:
	sqlite3* m_sqlHandle;
	//////////////////////////////////////////////////////////////////////////
};

#endif //__DATA_BASE_H__
