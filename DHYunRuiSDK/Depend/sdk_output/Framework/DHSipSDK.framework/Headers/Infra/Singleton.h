//
//  "$Id: Singleton.h 337184 2016-04-08 03:57:00Z 20429 $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:	
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __PATTERN_SINGLETON_H__
#define __PATTERN_SINGLETON_H__

#include <stdio.h>
#include "Infra/Guard.h"
#include <memory>
#include <stdlib.h>

#if __ARM_ARCH_5TE__


#undef PATTERN_SINGLETON_DECLARE
#define PATTERN_SINGLETON_DECLARE(classname)	\
public:											\
static classname * instance();					\
private:										\
classname();									\
~classname();									\
friend class std::auto_ptr<classname>;				\

/// 单件模式实现宏，放到类实现处
#undef PATTERN_SINGLETON_IMPLEMENT
#define PATTERN_SINGLETON_IMPLEMENT(classname)	\
static std::auto_ptr<classname> instance##classname(NULL);		\
void exit##classname(void)						\
{												\
	instance##classname = std::auto_ptr<classname>(NULL);					\
}												\
classname * classname::instance()				\
{												\
	if(NULL == instance##classname.get())						\
	{										\
		static ::Dahua::Infra::CMutex sm_mutex##classname;			\
		::Dahua::Infra::CGuard lock(sm_mutex##classname);		\
		if (NULL == instance##classname.get())					\
		{										\
			instance##classname = std::auto_ptr<classname>(new classname);			\
			if(0 != atexit(exit##classname))	\
			{									\
				infof("%s:%s atexit failed, line : %d\n", __FILE__, __FUNCTION__, __LINE__);	\
			}									\
		}										\
	}											\
	return instance##classname.get();							\
}												


#else // __ARM_ARCH_5TE__




/// 单件模式申明宏，放到类定义中
#undef PATTERN_SINGLETON_DECLARE
#define PATTERN_SINGLETON_DECLARE(classname)	\
public:											\
static classname * instance();					\
private:										\
classname();									\
~classname();									\
friend class std::auto_ptr<classname>;				\

/// 单件模式实现宏，放到类实现处
#undef PATTERN_SINGLETON_IMPLEMENT
#define PATTERN_SINGLETON_IMPLEMENT(classname)	\
static ::Dahua::Infra::CMutex sm_mutex##classname;			\
static std::auto_ptr<classname> instance##classname(NULL);		\
void exit##classname(void)						\
{												\
	instance##classname = std::auto_ptr<classname>(NULL);					\
}												\
classname * classname::instance()				\
{												\
	if(NULL == instance##classname.get())						\
	{											\
		::Dahua::Infra::CGuard lock(sm_mutex##classname);		\
		if (NULL == instance##classname.get())					\
		{										\
			instance##classname = std::auto_ptr<classname>(new classname);			\
			if(0 != atexit(exit##classname))	\
			{									\
				infof("%s:%s atexit failed, line : %d\n", __FILE__, __FUNCTION__, __LINE__);	\
			}									\
		}										\
	}											\
	return instance##classname.get();							\
}												

#endif // __ARM_ARCH_5TE__






#endif // __PATTERN_SINGLETON_H__


