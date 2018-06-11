/* FILE NAME: ANIM.H
 * PROGRAMMER: VG6
 * DATE: 08.06.2018
 */
#ifndef __ANIM_H_
#define __ANIM_H_

#define UNIT_BASE_FIELDS \
  VOID (*Init)( UNIT *Uni, ANIM *Ani );      \
  VOID (*Close)( UNIT *Uni, ANIM *Ani );     \
  VOID (*Response)( UNIT *Uni, ANIM *Ani );  \
  VOID (*Render)( UNIT *Uni, ANIM *Ani )

#define VG6_MAX_UNITS 3000

#include "rnd/rnd.h"

typedef struct tagvg6UNIT vg6UNIT;
typedef struct tagvg6ANIM
{
  HWND hWnd;
  HDC hDC;
  INT W, H;
  vg6UNIT *Units[VG6_MAX_UNITS];
  INT NumOfUnits;

} vg6ANIM;
 typedef struct tagvg6UNIT UNIT;
struct tagvg6UNIT
{
  UNIT_BASE_FIELDS;
};

typedef struct tagvg6UNIT UNIT;
struct tagvg6UNIT
{
  VOID (*Init)( UNIT *Uni, ANIM *Ani );
  VOID (*Close)( UNIT *Uni, ANIM *Ani );
  VOID (*Response)( UNIT *Uni, ANIM *Ani );
  VOID (*Render)( UNIT *Uni, ANIM *Ani );
};

extern UNIT *Units[VG6_MAX_UNITS];
extern INT NumOfUnits;



VOID AnimInit(HWND hWnd);
VOID AnimClose();
VOID AnimResize(INT W, INT H);
VOID AnimCopyFrame(HDC hDC);
VOID AnimRender();
VOID VG6_AnimAddUnit( vg6UNIT *Uni );
#endif
