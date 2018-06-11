/* FILE NAME: ANIM.C
 * PROGRAMMER: VG6
 * DATE: 08.06.2018
 */

#include "anim.h"

vg6ANIM VG6_Anim;


VOID VG6_AnimInit( HWND hWnd )
{

}
VOID VG6_AnimClose(VOID)
{
  INT i;

  for (i = 0; i < VG6_Anim.NumOfUnits; i++)
  {
    VG6_Anim.Units[i]->Close(VG6_Anim.Units[i], &VG6_Anim);
    free(VG6_Anim.Units[i]);
  }
  VG6_Anim.NumOfUnits = 0;
  VG6_RndClose();
}
VOID VG6_AnimResize(INT W, INT H)
{
  VG6_RndResize(W, H);
}
VOID VG6_AnimCopyFrame(HDC hDC)
{

}
VOID VG6_AnimRender( VOID )
{
  INT i;

  for (i = 0; i < VG6_Anim.NumOfUnits; i++)
    VG6_Anim.Units[i]->Response(VG6_Anim.Units[i], &VG6_Anim);

  VG6_RndStart();

  for (i = 0; i < VG6_Anim.NumOfUnits; i++)
    VG6_Anim.Units[i]->Render(VG6_Anim.Units[i], &VG6_Anim);

  VG6_RndEnd();
}

VG6_AnimAddUnit( vg6UNIT *Uni )
{

}