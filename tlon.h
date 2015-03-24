//
//		Tex like Object Notation
//   
//		Qinka 
//
//		qinka@live.com
//

//
//version
//

#include"tlon_define.h"

#pragma once
#ifndef _TLON_H_
#define _TLON_H_

// include
#include"map"
#include"string"
#include"vector"

_QINKA_BEGIN_
class TLONObject;
class TLONReader;
typedef __STD__ map <__STD__ string, TLONObject> tlonMap;
typedef __STD__ vector< TLONObject> tlonVector;

class TLONObject
{
	friend class TLONReader;
private:
	bool isNewData;
	void* _dataPointer;
	TLON_DATA_Type _type;
	TLONObject(bool);
	TLONObject(__STD__ string);
	TLONObject(tlonVector);
	TLONObject(uint64);
	TLONObject(sint64);
	TLONObject(float64);
	TLONObject(tlonMap);
public:
	TLONObject();
	~TLONObject();
	void const *GetPointer()const;
	const TLONObject& operator[](const char* inedx)const;
	const TLONObject& operator[](__STD__ string inedx)const;
	const TLONObject& operator[](int index)const;
	operator const uint64()const;
	operator const sint64()const;
	operator const float64()const;
	operator const __STD__ string()const;
	operator const bool()const;
};

class  TLONReader
{
public:
	void Reader(TLONObject &in, __STD__ string src);
private:
	void SkipSpace(__STD__ string &src);
	void _reader(TLONObject &in, __STD__ string src);
};

_QINKA_END_

#endif //_TLON_H_ END