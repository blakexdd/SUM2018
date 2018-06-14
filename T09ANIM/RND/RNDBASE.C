/* FILE NAME: RNDBASE.C
 * PROGRAMMER: VG6
 * DATE: 08.06.2018
 * PURPOSE: Camera and double buf
 */
#include "../anim.h"

VOID VG6_RndInit( HWND hWnd )
{
 INT i;
  PIXELFORMATDESCRIPTOR pfd = {0};

  /* Store window and context handles */
  VG6_Anim.hWnd = hWnd;
  VG6_Anim.hDC = GetDC(VG6_Anim.hWnd);

  /* OpenGL init: pixel format setup */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(VG6_Anim.hDC, &pfd);
  DescribePixelFormat(VG6_Anim.hDC, i, sizeof(pfd), &pfd);
  SetPixelFormat(VG6_Anim.hDC, i, &pfd);

  /* OpenGL init: setup rendering context */
  VG6_Anim.hRC = wglCreateContext(VG6_Anim.hDC);
  wglMakeCurrent(VG6_Anim.hDC, VG6_Anim.hRC);

  /* Set default render parameters */
  glClearColor(0.3, 0.5, 0.7, 1);
  glEnable(GL_DEPTH_TEST);

  if (glewInit() != GLEW_OK)
    exit(0);
  if (!(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader))
    exit(0);


  VG6_RndProjSet();
  VG6_RndCamSet(VecSet(20, 20, 20), VecSet(0, 0, 0), VecSet(0, 1, 0));
}
VOID VG6_RndClose( VOID )
{
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(VG6_Anim.hRC);
  ReleaseDC(VG6_Anim.hWnd, VG6_Anim.hDC);
}

VOID VG6_RndResize( INT W, INT H )
{
  glViewport(0, 0, W, H);

  VG6_Anim.W = W;
  VG6_Anim.H = H;
  VG6_RndProjSet();
  
}

VOID VG6_RndStart( VOID )
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
VOID VG6_RndEnd( VOID )
{
  glFinish();
}

VOID VG6_RndCopyFrame( HDC hDC )
{
  SwapBuffers(VG6_Anim.hDC);
}

VOID VG6_RndProjSet( VOID )
{
  FLT ratio_x, ratio_y;

  ratio_x = ratio_y = VG6_RndProjSize / 2;
  if (VG6_Anim.W > VG6_Anim.H) 
    ratio_x *= (FLT)VG6_Anim.W / VG6_Anim.H;
  else
    ratio_y *= (FLT)VG6_Anim.H / VG6_Anim.W;

  VG6_RndMatrProj = MatrViewFrustum(-ratio_x, ratio_x, -ratio_y, ratio_y,
    VG6_RndProjDist, VG6_RndProjFarClip);
  VG6_RndMatrVP = MatrMulMatr(VG6_RndMatrView, VG6_RndMatrProj);
}

VOID VG6_RndCamSet( VEC Loc, VEC At, VEC Up1 )
{
  VG6_RndMatrView = MatrView(Loc, At, Up1);
  VG6_RndMatrVP = MatrMulMatr(VG6_RndMatrView, VG6_RndMatrProj);
}