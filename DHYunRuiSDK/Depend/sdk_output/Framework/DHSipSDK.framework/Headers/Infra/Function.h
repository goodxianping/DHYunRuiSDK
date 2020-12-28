//
//  "$Id: Function.h 117279 2013-05-20 08:25:44Z zhao_zhiding $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INFRA3_TFUNCTION_H__
#define __INFRA3_TFUNCTION_H__

#if defined(_MSC_VER)
	#pragma warning (push)
	#pragma warning (disable : 4786)
#endif

#include <assert.h>
#include <typeinfo>
#include "Defs.h"
#include <stdio.h>
#include "IntTypes.h"


namespace Dahua {
namespace Infra {

namespace Detail {

template<class R> struct function_return_type {typedef R type;};

#if defined(_MSC_VER) && (_MSC_VER < 1300)

struct unusable
{
	unusable() {}
	template<class T> unusable(T const&) {}
};

template<> struct function_return_type<void> {typedef unusable type;};

#define DAHUA_FUNCTION_RETURN(X) X; return Detail::unusable ()

#else

#define DAHUA_FUNCTION_RETURN(X) X

#endif

// from http://www.codeproject.com/cpp/FastDelegate.asp by Don Clugston
//		horrible_cast< >
// This is truly evil. It completely subverts C++'s type system, allowing you
// to cast from any class to any other class. Technically, using a union
// to perform the cast is undefined behaviour (even in C). But we can see if
// it is OK by checking that the union is the same size as each of its members.
// horrible_cast<> should only be used for compiler-specific workarounds.
// Usage is identical to reinterpret_cast<>.

// This union is declared outside the horrible_cast because BCC 5.5.1
// can't inline a function with a nested class, and gives a warning.
template <class OutputClass, class InputClass>
union horrible_union{
	OutputClass out;
	InputClass in;
};

template <class OutputClass, class InputClass>
inline OutputClass horrible_cast(const InputClass input){
	horrible_union<OutputClass, InputClass> u;
	// Cause a compile-time error if in, out and u are not the same size.
	// If the compile fails here, it means the compiler has peculiar
	// unions which would prevent the cast from working.
	typedef int ERROR_CantUseHorrible_cast[sizeof(InputClass)==sizeof(u)
		/*&&  sizeof(InputClass)==sizeof(OutputClass)*/ ? 1 : -1];
	u.in = input;
	return u.out;
}

/// 设置当前线程函数复用ID
void INFRA_API setCurrentFunctionReuse(uint32_t reuse);

} // namespace Detail


/// 获取当前线程函数复用ID
uint32_t INFRA_API getCurrentFunctionReuse( );

//TFuction0
#define FUNCTION_NUMBER 0
#define FUNCTION_CLASS_TYPES typename R
#define FUNCTION_TYPES
#define FUNCTION_TYPE_ARGS
#define FUNCTION_ARGS
#include "FunctionTemplate.h"
#undef  FUNCTION_NUMBER
#undef  FUNCTION_CLASS_TYPES
#undef	FUNCTION_TYPES
#undef	FUNCTION_TYPE_ARGS
#undef	FUNCTION_ARGS

//TFuction1
#define FUNCTION_NUMBER 1
#define FUNCTION_CLASS_TYPES typename R, typename T1
#define FUNCTION_TYPES T1
#define FUNCTION_TYPE_ARGS T1 a1
#define FUNCTION_ARGS a1
#include "FunctionTemplate.h"
#undef  FUNCTION_NUMBER
#undef  FUNCTION_CLASS_TYPES
#undef	FUNCTION_TYPES
#undef	FUNCTION_TYPE_ARGS
#undef	FUNCTION_ARGS

//TFuction2
#define FUNCTION_NUMBER 2
#define FUNCTION_CLASS_TYPES typename R, typename T1, typename T2
#define FUNCTION_TYPES T1, T2
#define FUNCTION_TYPE_ARGS T1 a1, T2 a2
#define FUNCTION_ARGS a1, a2
#include "FunctionTemplate.h"
#undef  FUNCTION_NUMBER
#undef  FUNCTION_CLASS_TYPES
#undef	FUNCTION_TYPES
#undef	FUNCTION_TYPE_ARGS
#undef	FUNCTION_ARGS

//TFuction3
#define FUNCTION_NUMBER 3
#define FUNCTION_CLASS_TYPES typename R, typename T1, typename T2, typename T3
#define FUNCTION_TYPES T1, T2, T3
#define FUNCTION_TYPE_ARGS T1 a1, T2 a2, T3 a3
#define FUNCTION_ARGS a1, a2, a3
#include "FunctionTemplate.h"
#undef  FUNCTION_NUMBER
#undef  FUNCTION_CLASS_TYPES
#undef	FUNCTION_TYPES
#undef	FUNCTION_TYPE_ARGS
#undef	FUNCTION_ARGS

//TFuction4
#define FUNCTION_NUMBER 4
#define FUNCTION_CLASS_TYPES typename R, typename T1, typename T2, typename T3, typename T4
#define FUNCTION_TYPES T1, T2, T3, T4
#define FUNCTION_TYPE_ARGS T1 a1, T2 a2, T3 a3, T4 a4
#define FUNCTION_ARGS a1, a2, a3, a4
#include "FunctionTemplate.h"
#undef  FUNCTION_NUMBER
#undef  FUNCTION_CLASS_TYPES
#undef	FUNCTION_TYPES
#undef	FUNCTION_TYPE_ARGS
#undef	FUNCTION_ARGS

//TFuction5
#define FUNCTION_NUMBER 5
#define FUNCTION_CLASS_TYPES typename R, typename T1, typename T2, typename T3, typename T4, typename T5
#define FUNCTION_TYPES T1, T2, T3, T4, T5
#define FUNCTION_TYPE_ARGS T1 a1, T2 a2, T3 a3, T4 a4, T5 a5
#define FUNCTION_ARGS a1, a2, a3, a4, a5
#include "FunctionTemplate.h"
#undef  FUNCTION_NUMBER
#undef  FUNCTION_CLASS_TYPES
#undef	FUNCTION_TYPES
#undef	FUNCTION_TYPE_ARGS
#undef	FUNCTION_ARGS

//TFuction6
#define FUNCTION_NUMBER 6
#define FUNCTION_CLASS_TYPES typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6
#define FUNCTION_TYPES T1, T2, T3, T4, T5, T6
#define FUNCTION_TYPE_ARGS T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6
#define FUNCTION_ARGS a1, a2, a3, a4, a5, a6
#include "FunctionTemplate.h"
#undef  FUNCTION_NUMBER
#undef  FUNCTION_CLASS_TYPES
#undef	FUNCTION_TYPES
#undef	FUNCTION_TYPE_ARGS
#undef	FUNCTION_ARGS

} // namespace Infra
} // namespace Dahua

#if defined(_MSC_VER)
	#pragma warning (pop)
#endif

#endif //__INFRA3_TFUNCTION_H__
