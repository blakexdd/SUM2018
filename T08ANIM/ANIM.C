/* FILE NAME: ANIM.C
 * PROGRAMMER: VG6
 * DATE: 08.06.2018
 */

#include "anim.h"

vg6ANIM VG6_Anim;

VOID VG6_AnimInit( HWND hWnd )
{
  VG6_RndInit(hWnd);
}

VOID VG6_AnimStart( VOID )
{
  VG6_RndStart();
}

VOID VG6_AnimClose( VOID )
{
  INT i;
  for (i = 0; i < VG6_Anim.NumOfUnits; i++)
  {
    VG6_Anim.Units[i]->VG6_UnitClose(VG6_Anim.Units[i], &VG6_Anim);
    free(VG6_Anim.Units[i]);
  }
  VG6_Anim.NumOfUnits = 0;
  VG6_RndClose();
}
VOID VG6_AnimResize( INT W, INT H )
{
  VG6_RndResize(W, H);
}
VOID VG6_AnimCopyFrame( HDC hDC )
{
  VG6_RndCopyFrame(hDC);
}
VOID VG6_AnimRender( VOID )
{
  INT i;
  
  for (i = 0; i < VG6_Anim.NumOfUnits; i++)
    VG6_Anim.Units[i]->VG6_UnitResponse(VG6_Anim.Units[i], &VG6_Anim);

  VG6_RndStart();
  VG6_TimerResponse();
  for (i = 0; i < VG6_Anim.NumOfUnits; i++)
    VG6_Anim.Units[i]->VG6_UnitRender(VG6_Anim.Units[i], &VG6_Anim);
  VG6_RndEnd();
}

VOID VG6_AnimUnitAdd( vg6UNIT *Uni )
{
  if (VG6_Anim.NumOfUnits < VG6_MAX_UNITS)
    VG6_Anim.Units[VG6_Anim.NumOfUnits++] = Uni, Uni->VG6_UnitInit(Uni, &VG6_Anim);
}
