/* FILE NAME: T07SPHERE.C
 * PROGRAMMER: VG6
 * DATE: 06.06.2018
 * PURPOSE: For 3d graphics in the furute
 */
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define WND_CLASS_NAME "My window class"
#define M_PI       3.14159265358979323846

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

VOID DrawSphere( HDC hDc, INT x, INT y, INT R)
{
  INT i, x1, y1, N = 1000, M = 1000, j, tet = 0, alpha = 0;
  for (j = 0; j < M;j++)
  {
    tet += j * M_PI / M;
    for (i = 0; i < N; i++) 
    {
      alpha += i * 2 * M_PI / N;
      x1 = x + R * sin(tet) * cos(alpha);
      y1 = y - R * sin(tet) * sin(alpha);
      SetPixel(hDc, x1, y1, RGB(255, 0, 0));
    }
  }
}

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hIcon = LoadIcon(NULL, IDI_ERROR);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
    return 0;
  }
  hWnd =
    CreateWindow(WND_CLASS_NAME,
    "SPHERE",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT,
    CW_USEDEFAULT, CW_USEDEFAULT,
    NULL,
    NULL,
    hInstance,
    NULL);
  
  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
}

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDc;
  PAINTSTRUCT ps;
  BITMAP bm;
  SIZE s;
  SYSTEMTIME tm;
  DOUBLE sec, min, hour, a;
  MINMAXINFO *minmax;
  static INT W, H, len;
  static HDC hMemDC;
  static HBITMAP hBm;
  static HFONT hFnt;
  static CHAR Buf[1000];

  switch (Msg)
  {
  case WM_CREATE:
    hDc = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDc);
    ReleaseDC(hWnd, hDc);

    SetTimer(hWnd, 47, 30, NULL);
    return 0;
  case WM_SIZE:
    H = HIWORD(lParam);
    W = LOWORD(lParam);

    if (hBm != NULL)
      DeleteObject(hBm);

    hDc = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDc, W, H);
    ReleaseDC(hWnd, hDc);

    SelectObject(hMemDC, hBm);
    return 0;
  case WM_TIMER:
    /* Font */
    SelectObject(hMemDC, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hMemDC, RGB(0, 0, 0));
    Rectangle(hMemDC, 0, 0, W, H);

    DrawSphere(hMemDC, W / 2, H / 2, 200);
    /* Clear */
    InvalidateRect(hWnd, NULL, FALSE);

    return 0;
  case WM_PAINT:
    /*Udating front */
    hDc = BeginPaint(hWnd, &ps);
    BitBlt(hDc, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_ERASEBKGND:
    return 1;
  case WM_DESTROY:
    DeleteObject(hBm);
    DeleteObject(hFnt);
    DeleteDC(hMemDC);
    PostMessage(hWnd, WM_QUIT, 0, 0);
    KillTimer(hWnd, 47);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}