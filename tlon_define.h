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

#pragma once
#ifndef _TLON_DEFINE_H_
#define _TLON_DEFINE_H_

#define _QINKA_BEGIN_	namespace Qinka{
#define _QINKA_END_						}
#define __STD__			::std:: 
#define _QINKA_			::Qinka::


#include<typeinfo>
#include<typeindex>


_QINKA_BEGIN_

#ifndef _NOT_DEFINE_TYPE_
#include<stdint.h>
#include<float.h>
typedef char byte;
typedef int8_t sint8;
typedef int16_t sint16;
typedef int32_t sint32;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

typedef uint64_t uint64;
typedef int64_t sint64;

typedef const char* CStringPointer;
typedef void* _Pointer;
typedef float float32;
typedef double float64;


#define _BYTE_MIN INT8_MIN
#define _SINT8_MIN  INT8_MIN
#define _UINT8_MIN 0
#define _SINT16_MIN INT16_MIN
#define _UINT16_MIN 0
#define _SINT32_MIN INT32_MIN
#define _UINT32_MIN 0
#define _SINT64_MIN INT64_MIN
#define _UINT64_MIN 0
#define _FLOAT32_MIN FLT_MIN
#define _FLOAT64_MIN DBL_MIN
#define _BYTE_MAX INT8_MAX
#define _SINT8_MAX  INT8_MAX
#define _UINT8_MAX UINT8_MAX
#define _SINT16_MAX INT16_MAX
#define _UINT16_MAX UINT16_MAX
#define _SINT32_MAX INT32_MAX
#define _UINT32_MAX UINT32_MAX
#define _SINT64_MAX INT64_MAX
#define _FLOAT32_MAX FLT_MAX
#define _FLOAT64_MAX DBL_MAX
#define _UINT64_MAX UINT64_MAX
#endif //_NOT_DEFINE_TYPE_

enum TLON_DATA_Type
{
	nullT,
	boolT,
	stringT,
	uintT,
	sintT,
	realT,
	nodeT,
	arrayT
};

_QINKA_END_


#endif //_TLON_DEFINE_H_