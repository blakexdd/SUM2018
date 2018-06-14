/* FILE NAME: ANIM.H
 * PROGRAMMER: VG6
 * DATE: 08.06.2018
 */
#ifndef __ANIM_H_
#define __ANIM_H_
#include "rnd/rnd.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm")
#define UNIT_BASE_FIELDS \
  VOID (*VG6_UnitInit)( vg6UNIT *Uni, vg6ANIM *Ani );      \
  VOID (*VG6_UnitClose)( vg6UNIT *Uni, vg6ANIM *Ani );     \
  VOID (*VG6_UnitResponse)( vg6UNIT *Uni, vg6ANIM *Ani );  \
  VOID (*VG6_UnitRender)( vg6UNIT *Uni, vg6ANIM *Ani );    \
  VEC Camera

#define VG6_GET_JOYSTICK_AXIS(A)\
  (2.0 * (ji.dw ## A ## pos - jc.w ## A ## min) / (jc.w ## A ## max - jc.w ## A ## min) - 1)
#define VG6_MAX_UNITS 3000

typedef struct tagvg6UNIT vg6UNIT;
typedef struct tagvg6ANIM
{
  HWND hWnd;                     /* Work window handle */
  HDC hDC;                       /* Memory device context */
  HBITMAP Bm;
  INT W, H;                      /* Frame size */
  HGLRC hRC;
  vg6UNIT *Units[VG6_MAX_UNITS]; /* Array of animation units */
  INT NumOfUnits;                /* Animation units array size */

  FLT GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
    Time, DeltaTime,             /* Time with pause and interframe interval */
    FPS;                         /* Frames per second value */
  BOOL IsPause;                     /* Pause flag */

  INT Mx, My, Mz, Mdx, Mdy, Mdz;
  POINT pt;
  BYTE
    JBut[32], JButOld[32], JButClick[32]; /* Joystick button state */
  INT JPov;                               /* Joystick point-of-view control [-1,0..7] */
  FLT
    JX, JY, JZ, JR;                       /* Joystick axes */

   BYTE Keys[256],
     KeysOld[256],
     KeysClick[256]; 

} vg6ANIM;

extern vg6ANIM VG6_Anim;
extern FLT VG6_RndProjSize;
extern FLT VG6_RndProjDist;
extern FLT VG6_RndProjFarClip;
extern MATR VG6_RndMatrView;
extern MATR VG6_RndMatrProj;
extern MATR VG6_RndMatrVP;
extern INT VG6_MouseWheel;

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

VOID VG6_TimerInit ( VOID );
VOID VG6_TimerResponse( VOID );
VOID VG6_AnimInputInit( VOID );

#endif