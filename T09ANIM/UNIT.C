/* FILE NAME: UNIT.H
 * PROGRAMMER: VG6
 * DATE: 08.06.2018
 */

#include "unit.h"


static VOID VG6_UnitInit( vg6UNIT *Uni, vg6ANIM *Ani )
{

}

static VOID VG6_UnitClose( vg6UNIT *Uni, vg6ANIM *Ani )
{

}

static VOID VG6_UnitResponse( vg6UNIT *Uni, vg6ANIM *Ani )
{

}

static VOID VG6_UnitRender( vg6UNIT *Uni, vg6ANIM *Ani )
{

}

vg6UNIT * VG6_AnimUnitCreate( INT Size )
{
  vg6UNIT *Uni;

  if (Size < sizeof(vg6UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);
  Uni->VG6_UnitInit = VG6_UnitInit;
  Uni->VG6_UnitClose = VG6_UnitClose;
  Uni->VG6_UnitResponse = VG6_UnitResponse;
  Uni->VG6_UnitRender = VG6_UnitRender;
  return Uni;
}

