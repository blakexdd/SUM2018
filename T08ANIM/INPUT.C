/* FILE NAME: INPUT.C
 * PROGRAMMER: VG6
 * DATE: 08.06.2018
 */

#include "unit.h"

VOID VG6_AnimInputInit( VOID )
{
   INT i;
   GetKeyboardState(VG6_Anim.Keys);
   for (i = 0; i < 256; i++)
   {
     VG6_Anim.Keys[i] >>= 7;
     VG6_Anim.KeysClick[i] = VG6_Anim.Keys[i] && !VG6_Anim.KeysOld[i];
   }
   memcpy(VG6_Anim.KeysOld, VG6_Anim.Keys, 256);
    /* Joystick */
  if (joyGetNumDevs() > 0)
  {
    JOYCAPS jc;

    /* Get joystick info */
    if (joyGetDevCaps(JOYSTICKID1, &jc, sizeof(jc)) == JOYERR_NOERROR)
    {
      JOYINFOEX ji;

      ji.dwSize = sizeof(JOYINFOEX);
      ji.dwFlags = JOY_RETURNALL;
      if (joyGetPosEx(JOYSTICKID1, &ji) == JOYERR_NOERROR)
      {
        /* Buttons */
        for (i = 0; i < 32; i++)
        {
          VG6_Anim.JBut[i] = (ji.dwButtons >> i) & 1;
          VG6_Anim.JButClick[i] = VG6_Anim.JBut[i] && !VG6_Anim.JButOld[i];
          VG6_Anim.JButOld[i] = VG6_Anim.JBut[i];
        }

        /* Axes */
        VG6_Anim.JX = VG6_GET_JOYSTICK_AXIS(X);
        VG6_Anim.JY = VG6_GET_JOYSTICK_AXIS(Y);
        VG6_Anim.JZ = VG6_GET_JOYSTICK_AXIS(Z);
        VG6_Anim.JR = VG6_GET_JOYSTICK_AXIS(R);

        /* Point of view */
        VG6_Anim.JPov = ji.dwPOV == 0xFFFF ? -1 : ji.dwPOV / 4500;
      }
    }
  }


}