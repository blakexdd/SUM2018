/* FILE NAME: ANIM.H
 * PROGRAMMER: VG6
 * DATE: 08.06.2018
 */
#ifndef __ANIM_H_
#define __ANIM_H_
#include "rnd/rnd.h"

#define UNIT_BASE_FIELDS \
  VOID (*VG6_UnitInit)( vg6UNIT *Uni, vg6ANIM *Ani );      \
  VOID (*VG6_UnitClose)( vg6UNIT *Uni, vg6ANIM *Ani );     \
  VOID (*VG6_UnitResponse)( vg6UNIT *Uni, vg6ANIM *Ani );  \
  VOID (*VG6_UnitRender)( vg6UNIT *Uni, vg6ANIM *Ani )


#define VG6_MAX_UNITS 3000

typedef struct tagvg6UNIT vg6UNIT;
typedef struct tagvg6ANIM
{
  HWND hWnd;                     /* Work window handle */
  HDC hDC;                       /* Memory device context */
  HBITMAP Bm;
  INT W, H;                      /* Frame size */
  vg6UNIT *Units[VG6_MAX_UNITS]; /* Array of animation units */
  INT NumOfUnits;                /* Animation units array size */
} vg6ANIM;

extern vg6ANIM VG6_Anim;
extern DBL VG6_RndProjSize;
extern DBL VG6_RndProjDist;
extern DBL VG6_RndProjFarClip;
extern MATR VG6_RndMatrView;
extern MATR VG6_RndMatrProj;
extern MATR VG6_RndMatrVP;

struct tagvg6UNIT
{
  UNIT_BASE_FIELDS;
};

extern vg6ANIM VG6_Anim;

VOID VG6_AnimInit( HWND hWnd );
VOID VG6_AnimStart( VOID );
VOID VG6_AnimClose( VOID );
VOID VG6_AnimResize( INT W, INT H );
VOID VG6_AnimCopyFrame( HDC hDC );
VOID VG6_AnimRender( VOID );
VOID VG6_AnimUnitAdd( vg6UNIT *Uni );

vg6UNIT * VG6_AnimUnitCreate( INT Size );
#endif