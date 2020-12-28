//
//  "$Id: Support.h 20211 2011-02-24 02:50:44Z wang_haifeng $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INFRA3_SYSTEM_H__
#define __INFRA3_SYSTEM_H__

#include "Defs.h"
#include "IntTypes.h"

namespace Dahua {
namespace Infra {

/// \defgroup System System
/// 一些系统相关辅助函数。
/// @{

/// 得到整数的底数为2的对数值的整数部分
/// 系统调用接口
int INFRA_API systemCall(const char* command);


///	\ 获取当前进程id
uint64_t INFRA_API getCurrectProcessID();


/// @} end of group

} // namespace Infra
} // namespace Dahua

#endif //__INFRA_SUPPORT_H__


