//
//  "$Id: Types.h 16720 2010-12-01 09:51:53Z wang_haifeng $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//


#ifndef __DAHUA3_TYPES_H__
#define __DAHUA3_TYPES_H__


#include "Infra/IntTypes.h"

////////////////////////////////////////////////////////////////////////////////

namespace Dahua {

/// 矩形
typedef struct Rect
{
	int left;
	int top;
	int right;
	int bottom;
} Rect;

/// 点
typedef struct Point
{
	int x;
	int y;
} Point;

/// 尺寸
typedef struct Size
{
	int w;
	int h;
} Size;

/// 颜色
typedef struct Color
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} Color;

/// 直线
typedef struct Line
{
	Point start;
	Point end;
} Line;

/// 时间段结构
struct TimeSection
{
	int enable;			///< 使能
	int startHour;		///< 开始时间:小时
	int	startMinute;	///< 开始时间:分钟
	int	startSecond;	///< 开始时间:秒钟
	int	endHour;		///< 结束时间:小时
	int	endMinute;		///< 结束时间:分钟
	int	endSecond;		///< 结束时间:秒钟
};

/// IP 地址结构
union IpAddress
{
	uint8_t		c[4];
	uint16_t	s[2];
	uint32_t	l;
};

} // namespace Dahua

#endif// __DAHUA_TYPES_H__

