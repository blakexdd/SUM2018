/* FILE NAME: UNIT.H
 * PROGRAMMER: VG6
 * DATE: 08.06.2018
 */
#ifndef __UNIT_H_
#define __UNIT_H_

#include "anim.h"

typedef struct tagUNIT_COW UNIT_COW;
struct tagUNIT_COW
{
  UNIT_BASE_FIELDS;
  VEC Pos;
  PRIM Cow;
};
