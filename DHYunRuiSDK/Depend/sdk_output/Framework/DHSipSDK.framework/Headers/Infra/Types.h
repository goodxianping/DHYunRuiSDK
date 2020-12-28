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

/// ����
typedef struct Rect
{
	int left;
	int top;
	int right;
	int bottom;
} Rect;

/// ��
typedef struct Point
{
	int x;
	int y;
} Point;

/// �ߴ�
typedef struct Size
{
	int w;
	int h;
} Size;

/// ��ɫ
typedef struct Color
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} Color;

/// ֱ��
typedef struct Line
{
	Point start;
	Point end;
} Line;

/// ʱ��νṹ
struct TimeSection
{
	int enable;			///< ʹ��
	int startHour;		///< ��ʼʱ��:Сʱ
	int	startMinute;	///< ��ʼʱ��:����
	int	startSecond;	///< ��ʼʱ��:����
	int	endHour;		///< ����ʱ��:Сʱ
	int	endMinute;		///< ����ʱ��:����
	int	endSecond;		///< ����ʱ��:����
};

/// IP ��ַ�ṹ
union IpAddress
{
	uint8_t		c[4];
	uint16_t	s[2];
	uint32_t	l;
};

} // namespace Dahua

#endif// __DAHUA_TYPES_H__

