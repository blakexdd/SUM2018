/* FILE NAME: RNDBASE.C
 * PROGRAMMER: VG6
 * DATE: 08.06.2018
 * PURPOSE: Camera and double buf
 */
#include "../anim.h"

VOID VG6_RndInit( HWND hWnd )
{
  HDC hDC;
  VG6_Anim.hWnd = hWnd;
  hDC = GetDC(VG6_Anim.hWnd);
  VG6_Anim.hDC = CreateCompatibleDC(hDC);
  ReleaseDC(VG6_Anim.hWnd, hDC);

  VG6_RndProjSet();
  VG6_RndCamSet(VecSet(20, 20, 20), VecSet(0, 0, 0), VecSet(0, 1, 0));
}
VOID VG6_RndClose( VOID )
{
  DeleteObject(VG6_Anim.Bm);
  DeleteDC(VG6_Anim.hDC);
}

VOID VG6_RndResize( INT W, INT H )
{
  HDC hDC;
  
  if (VG6_Anim.Bm != NULL)
    DeleteObject(VG6_Anim.Bm);
  hDC = GetDC(VG6_Anim.hWnd);
  VG6_Anim.Bm = CreateCompatibleBitmap(hDC, W, H);
  ReleaseDC(VG6_Anim.hWnd, hDC);
  SelectObject(VG6_Anim.hDC, VG6_Anim.Bm);
 
  VG6_Anim.W = W;
  VG6_Anim.H = H;
  VG6_RndProjSet();
  
}

VOID VG6_RndStart( VOID )
{
  SelectObject(VG6_Anim.hDC, GetStockObject(NULL_PEN));
  SelectObject(VG6_Anim.hDC, GetStockObject(LTGRAY_BRUSH));
  Rectangle(VG6_Anim.hDC, 0, 0, VG6_Anim.W, VG6_Anim.H);

  SelectObject(VG6_Anim.hDC, GetStockObject(BLACK_PEN));
  SelectObject(VG6_Anim.hDC, GetStockObject(NULL_BRUSH));
}
VOID VG6_RndEnd( VOID )
{

}

VOID VG6_RndCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, VG6_Anim.W, VG6_Anim.H, VG6_Anim.hDC, 0, 0,
    SRCCOPY);
}

VOID VG6_RndProjSet( VOID )
{
  DBL ratio_x, ratio_y;

  ratio_x = ratio_y = VG6_RndProjSize / 2;
  if (VG6_Anim.W > VG6_Anim.H) 
    ratio_x *= (DBL)VG6_Anim.W / VG6_Anim.H;
  else
    ratio_y *= (DBL)VG6_Anim.H / VG6_Anim.W;

  VG6_RndMatrProj = MatrViewFrustum(-ratio_x, ratio_x, -ratio_y, ratio_y,
    VG6_RndProjDist, VG6_RndProjFarClip);
  VG6_RndMatrVP = MatrMulMatr(VG6_RndMatrView, VG6_RndMatrProj);
}

VOID VG6_RndCamSet( VEC Loc, VEC At, VEC Up1 )
{
  VG6_RndMatrView = MatrView(Loc, At, Up1);
  VG6_RndMatrVP = MatrMulMatr(VG6_RndMatrView, VG6_RndMatrProj);
}