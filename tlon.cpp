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

#include"stdafx.h"
#include"tlon.h"

_QINKA_BEGIN_

TLONObject::~TLONObject()
{
	if (isNewData)
		delete _dataPointer;
}
TLONObject::TLONObject(bool boolean)
{
	_type = boolT;
	_dataPointer = new bool(boolean);
	isNewData = true;
}
TLONObject::TLONObject(__STD__ string str)
{
	_type = stringT;
	_dataPointer = new __STD__ string(str);
	isNewData = true;
}
TLONObject::TLONObject(uint64 u64)
{
	_type = uintT;
	_dataPointer = new uint64(u64);
	isNewData = true;
}
TLONObject::TLONObject(sint64 s64)
{
	_type = sintT;
	_dataPointer = new sint64(s64);
	isNewData = true;
}
TLONObject::TLONObject(float64 f64)
{
	_type = realT;
	_dataPointer = new float64(f64);
	isNewData = true;
}
TLONObject::TLONObject(tlonMap tm)
{
	_type = nodeT;
	_dataPointer = new tlonMap(tm);
	isNewData = true;
}
TLONObject::TLONObject(tlonVector tv)
{
	_type = arrayT;
	_dataPointer = new tlonVector(tv);
	isNewData = true;
}
TLONObject::TLONObject()
{
	_type = nullT;
	_dataPointer = nullptr;
	isNewData = false;
}
void const * TLONObject::GetPointer() const
{
	return _dataPointer;
}
const TLONObject& TLONObject::operator[](__STD__ string index)const
{
	if (_type != nodeT || ((tlonMap*)_dataPointer)->count(index) == 0)
	{
		//抛出异常
	}
	return (*((tlonMap*)_dataPointer))[index];
}
const TLONObject& TLONObject::operator[](const char * index)const
{
	if (_type != nodeT || ((tlonMap*)_dataPointer)->count(index) == 0)
	{
		//抛出异常
	}
	return (*((tlonMap*)_dataPointer))[index];
}
const TLONObject& TLONObject::operator[](int index)const
{
	if (_type != arrayT || ((tlonVector*)_dataPointer)->size() >= index)
	{
		//抛出异常
	}
	return (*((tlonVector*)_dataPointer))[index];
}
TLONObject::operator const Qinka::float64()const
{
	if (_type == realT)
		return *((float64*)_dataPointer);
	else
	{
		//抛出异常
	}
}
TLONObject::operator const bool()const
{
	if (_type == nullT || _type == nodeT || _type == arrayT)
	{
		//抛出异常
	}
	else if (_type == uintT)
	{
		return (*((uint64*)_dataPointer)) != 0;
	}
	else if (_type == sintT)
	{
		return (*((sint64*)_dataPointer)) != 0;
	}
	else if (_type == realT)
	{
		return (*((float64*)_dataPointer)) != 0.0;
	}
	else if (_type == boolT)
	{
		return *((bool*)_dataPointer);
	}
	else if (_type == stringT)
	{
		if (*((__STD__ string*)_dataPointer) == "true")
		{
			return true;
		}
		else if (*((__STD__ string*)_dataPointer) == "false")
		{
			return false;
		}
		else
		{
			//抛出异常
		}
	}
	else
	{
		//抛出异常
	}
}
TLONObject::operator const Qinka::sint64()const
{
	if (_type == sintT)
		return *((sint64*)_dataPointer);
	else if (_type == uintT)
		return uint64(*((sint64*)_dataPointer));
	else
	{
		//抛出异常
	}
}
TLONObject::operator const Qinka::uint64()const
{
	if (_type == uintT)
		return *((uint64*)_dataPointer);
	else
	{
		//抛出异常
	}
}
TLONObject::operator const __STD__ string()const
{
	if (_type == stringT)
		return *((__STD__ string*)_dataPointer);
	else
	{
		//抛出异常
	}
}
void TLONReader::SkipSpace(__STD__ string& src)
{
	//
	//	预留检查语法,仅用于debug
	//
	auto item = src.begin();
	while (item != src.end())
	{
		switch (*item)
		{
#define DEL(x) case x:src.erase(item);break;
			DEL('\t')
				DEL('\f')
				DEL('\n')
				DEL('\r')
				DEL('\v')
				DEL('\0')
#undef DEL
				break;
default:
	++item;
		}

	}
}
void TLONReader::Reader(TLONObject& in, __STD__ string src)
{
	in._type = nodeT;
	in._dataPointer = new tlonMap();
	in.isNewData = true;
	SkipSpace(src);
	_reader(in, src);
}
void TLONReader::_reader(TLONObject& in, __STD__ string src)
{
	auto item = src.begin();
	while (item != src.end())
	{
		if (*item == '}')
		{
			if ((src.end() - 1) == item)
			{
				break;
			}
			else
				++item;
		}
		if (*item == '\\')
		{
			++item;
		}

		__STD__ string tmpName;
		while (*item != '{'&&*item != ':'&&*item != '['&&item != src.end())
		{
			tmpName += *item;
			++item;
		}
		if (tmpName.length() == 0) //有序匿名域
		{
			if (in._type != arrayT)
			{
				//抛出异常
			}
			//有序匿名域处理
			__STD__ string tmpStr;
			int tmpCount = 1;
			++item;
			while (tmpCount&&item != src.end())
			{
				switch (*item)
				{
				case '}':
					tmpCount--;
					if (tmpCount)
					{
						tmpStr += *item;
						++item;
					}
					break;
				case '{':
					tmpCount++;
				default:
					tmpStr += *item;
					++item;
					break;
				}
			}
			((tlonVector*)in._dataPointer)->push_back(TLONObject());
			//((tlonMap*)in._dataPointer)->insert(tlonMap::value_type(tmpName, TLONObject()));
			auto _end = ((tlonVector*)in._dataPointer)->end();
			--_end;
			_end->_type = nodeT;
			//(*((tlonMap*)in._dataPointer))[tmpName]._type = nodeT;
			_end->_dataPointer = new tlonMap();
			//(*((tlonMap*)in._dataPointer))[tmpName]._dataPointer = new tlonMap();
			_end->isNewData = true;
			//(*((tlonMap*)in._dataPointer))[tmpName].isNewData = true;
			_reader(*_end, tmpStr);
			continue;
		}
		else
		{
			if (in._type == arrayT)
			{
				//抛出异常
			}
		}
		if (*item == '{')
		{
			__STD__ string tmpStr;
			int tmpCount = 1;
			++item;
			while (tmpCount&&item != src.end())
			{
				switch (*item)
				{
				case '}':
					tmpCount--;
					if (tmpCount)
					{
						tmpStr += *item;
						++item;
					}
					break;
				case '{':
					tmpCount++;
				default:
					tmpStr += *item;
					++item;
					break;
				}
			}
			((tlonMap*)in._dataPointer)->insert(tlonMap::value_type(tmpName, TLONObject()));
			(*((tlonMap*)in._dataPointer))[tmpName]._type = nodeT;
			(*((tlonMap*)in._dataPointer))[tmpName]._dataPointer = new tlonMap();
			(*((tlonMap*)in._dataPointer))[tmpName].isNewData = true;
			_reader((*((tlonMap*)in._dataPointer))[tmpName], tmpStr);
			continue;
		}
		else if (*item == ':')
		{
			++item;
			if (*item == '\"')
			{
				__STD__ string tmpValue;
				++item;
				while (*item != '\"'&&item != src.end())
				{
					if (*item == '\\')
					{
						++item;
						switch (*item)
						{
						case 'a':
							tmpValue += '\a';
							break;
						case 'b':
							tmpValue += '\b';
							break;
						case 'f':
							tmpValue += '\f';
							break;
						case 'n':
							tmpValue += '\n';
							break;
						case 'r':
							tmpValue += '\r';
							break;
						case 't':
							tmpValue += '\t';
							break;
						case 'v':
							tmpValue += '\v';
							break;
						case '\\':
							tmpValue += '\\';
							break;
						case '\'':
							tmpValue += '\'';
							break;
						case '\"':
							tmpValue += '\"';
							break;
						case '0':
							tmpValue += '\0';
							break;
						}
					}
					else
					{
						tmpValue += *item;
					}
					++item;
				}
				((tlonMap*)in._dataPointer)->insert(tlonMap::value_type(tmpName, TLONObject()));
				(*((tlonMap*)in._dataPointer))[tmpName]._type = stringT;
				(*((tlonMap*)in._dataPointer))[tmpName]._dataPointer = new __STD__ string(tmpValue);
				(*((tlonMap*)in._dataPointer))[tmpName].isNewData = true;
				if (item != src.end())
				{
					++item;
				}
			}
			else
			{
				__STD__ string tmpValue;
				while (item != src.end() && *item != '\\')//CTON 中使用的是 *item != '\"'
				{
					tmpValue += *item;
					++item;
				}
				if (tmpValue == "true")
				{
					((tlonMap*)in._dataPointer)->insert(tlonMap::value_type(tmpName, TLONObject()));
					(*((tlonMap*)in._dataPointer))[tmpName]._type = boolT;
					(*((tlonMap*)in._dataPointer))[tmpName]._dataPointer = new bool(true);
					(*((tlonMap*)in._dataPointer))[tmpName].isNewData = true;
					if (item != src.end())
					{
						++item;
					}
				}
				else if (tmpValue == "false")
				{
					((tlonMap*)in._dataPointer)->insert(tlonMap::value_type(tmpName, TLONObject()));
					(*((tlonMap*)in._dataPointer))[tmpName]._type = boolT;
					(*((tlonMap*)in._dataPointer))[tmpName]._dataPointer = new bool(false);
					(*((tlonMap*)in._dataPointer))[tmpName].isNewData = true;
					if (item != src.end())
					{
						++item;
					}
				}
				else if (__STD__ string::npos == tmpValue.find('.'))
				{
					if (__STD__ string::npos != tmpValue.find('-')) //CTON 中是使用 ==
					{
						((tlonMap*)in._dataPointer)->insert(tlonMap::value_type(tmpName, TLONObject()));
						(*((tlonMap*)in._dataPointer))[tmpName]._type = sintT;
						(*((tlonMap*)in._dataPointer))[tmpName]._dataPointer = new sint64(atoll(tmpValue.c_str()));
						(*((tlonMap*)in._dataPointer))[tmpName].isNewData = true;
						if (item != src.end())
						{
							++item;
						}
					}
					else
					{
						((tlonMap*)in._dataPointer)->insert(tlonMap::value_type(tmpName, TLONObject()));
						(*((tlonMap*)in._dataPointer))[tmpName]._type = uintT;
						(*((tlonMap*)in._dataPointer))[tmpName]._dataPointer = new uint64(atoll(tmpValue.c_str()));
						(*((tlonMap*)in._dataPointer))[tmpName].isNewData = true;
						if (item != src.end())
						{
							++item;
						}
					}
				}
				else
				{
					((tlonMap*)in._dataPointer)->insert(tlonMap::value_type(tmpName, TLONObject()));
					(*((tlonMap*)in._dataPointer))[tmpName]._type = realT;
					(*((tlonMap*)in._dataPointer))[tmpName]._dataPointer = new float64(atof(tmpValue.c_str()));
					(*((tlonMap*)in._dataPointer))[tmpName].isNewData = true;
					if (item != src.end())
					{
						++item;
					}
				}
			}
			continue;
		}
		else if (*item == '[')
		{

			__STD__ string tmpStr;
			int tmpCount = 1;
			++item;
			while (tmpCount&&item != src.end())
			{
				switch (*item)
				{
				case ']':
					tmpCount--;
					if (tmpCount)
					{
						tmpStr += *item;
						++item;
					}
					break;
				case '[':
					tmpCount++;
				default:
					tmpStr += *item;
					++item;
					break;
				}
			}
			((tlonMap*)in._dataPointer)->insert(tlonMap::value_type(tmpName, TLONObject()));
			(*((tlonMap*)in._dataPointer))[tmpName]._type = arrayT;
			(*((tlonMap*)in._dataPointer))[tmpName]._dataPointer = new tlonVector();
			(*((tlonMap*)in._dataPointer))[tmpName].isNewData = true;
			_reader((*((tlonMap*)in._dataPointer))[tmpName], tmpStr);
			continue;
		}
		else
		{
			//抛出异常,见鬼了
		}
	}
}

_QINKA_END_