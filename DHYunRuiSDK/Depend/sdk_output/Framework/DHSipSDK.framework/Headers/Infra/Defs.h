//
//  "$Id: Defs.h 129930 2013-08-02 07:51:01Z sun_xiaohui $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//


#ifndef __INFRA3_DEFS_H__
#define __INFRA3_DEFS_H__


// WIN32 Dynamic Link Library
#ifdef _MSC_VER

#ifdef INFRA_DLL_BUILD
#define  INFRA_API _declspec(dllexport)
#elif defined INFRA_DLL_USE
#define  INFRA_API _declspec(dllimport)
#else
#define INFRA_API
#endif

#else

#define INFRA_API

#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef __GNUC__
#define __attribute__(x)
#endif

//////////////////////////////////////////////////////////////////////////
// useful definition

#define DAHUA_BITMSK(bit)		((unsigned int)1 << (bit))

#ifndef BITMSK
// 为兼容老接口保留，请勿使用
#define BITMSK(bit)				((unsigned int)1 << (bit))
#endif
//////////////////////////////////////////////////////////////////////////
// Join two variables
#define DAHUA_JOIN( X, Y ) DAHUA_DO_JOIN( X, Y )
#define DAHUA_DO_JOIN( X, Y ) DAHUA_DO_JOIN2(X,Y)
#define DAHUA_DO_JOIN2( X, Y ) X##Y

// 为兼容老接口保留，请勿使用
#define MACRO_JOIN( X, Y ) MACRO_DO_JOIN( X, Y )
#define MACRO_DO_JOIN( X, Y ) MACRO_DO_JOIN2(X,Y)
#define MACRO_DO_JOIN2( X, Y ) X##Y


//////////////////////////////////////////////////////////////////////////
// use the unified 'DEBUG' macro
#if (!defined(NDEBUG)) && !defined(DEBUG)
#	define DEBUG
#endif


#endif //__INFRA_DEFS_H__
