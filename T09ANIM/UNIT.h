/* FILE NAME: UNIT.H
 * PROGRAMMER: VG6
 * DATE: 08.06.2018
 */
#ifndef __UNIT_H_
#define __UNIT_H_

#include "anim.h"

vg6UNIT * VG6_UnitCreateCow( VOID );
vg6UNIT * VG6_AnimUnitCreate( INT Size );
vg6UNIT * VG6_AnimUnitCtrl( VOID );

VOID VG6_AnimInputInit( VOID );
#endif
