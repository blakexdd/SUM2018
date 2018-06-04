/* FILENAME: T02EYES2.C
 * PROGRAMMER: VG6
 * DATE: 01.06.2018
 */

#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define WND_CLASS_NAME "My window class"
#define M_PI       3.14159265358979323846

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

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
    "EYE",
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

VOID DrowHand( HDC hMemDC, INT x0, INT y0, DOUBLE Angle, INT L, INT W, DOUBLE si, DOUBLE co )
{
  POINT 
    pts[] = {{0, L}, {-W, 0}, {0, -W}, {W, 0}},
    pts1[sizeof(pts) / sizeof(pts[0])];
  INT N = sizeof(pts) / sizeof(pts[0]), i;

  for (i = 0; i < N; i++)
  {
    pts1[i].x = x0 + pts[i].x * co - pts[i].y * si;
    pts1[i].y = y0 + pts[i].x * si + pts[i].y * co;
  }
  SelectObject(hMemDC, GetStockObject(DC_BRUSH));
  SelectObject(hMemDC, GetStockObject(DC_PEN));
  SetDCPenColor(hMemDC, RGB(255, 255, 255));
  SetDCBrushColor(hMemDC, RGB(0, 0, 0));

  Polygon(hMemDC, pts1, N);
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
  static HDC hMemDC, hClock;
  static HBITMAP hBm, hBClock;
  static HFONT hFnt;
  static CHAR Buf[1000];

  switch (Msg)
  {
  case WM_CREATE:
    hDc = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDc);
    hClock = CreateCompatibleDC(hDc);
    ReleaseDC(hWnd, hDc);

    /*Uploading immage from the file */
    hBClock = LoadImage(NULL, "clockface1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    /* Setting up the Font */
    hFnt = CreateFont(40, 0, 0, 0, FW_BOLD, TRUE, FALSE, FALSE, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
      PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "Arial"); 
   
    SelectObject(hClock, hBClock);
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
    SetDCBrushColor(hMemDC, RGB(255, 255, 255));
    Rectangle(hMemDC, 0, 0, W, H);

    /* Hands */
    GetLocalTime(&tm);
    sec = 2 * M_PI * tm.wSecond / 60 + tm.wMilliseconds / 10000.0;
    min = 2 * M_PI * tm.wMinute / 60 + sec / 60;
    hour = (tm.wHour % 12) * 2 * M_PI / 12 + min / 12;
    GetObject(hBClock, sizeof(BITMAP), &bm);
    BitBlt(hMemDC, W / 2 - bm.bmWidth / 2, H / 2 - bm.bmHeight / 2, bm.bmWidth, bm.bmHeight, hClock, 0, 0, SRCCOPY);
    MoveToEx(hMemDC, W / 2, H / 2, NULL);
    LineTo(hMemDC, (INT)(bm.bmWidth * 0.47 * sin(sec) + W / 2), (INT)(H / 2 - cos(sec) * bm.bmWidth * 0.47));
    MoveToEx(hMemDC, W / 2, H / 2, NULL);
    LineTo(hMemDC, (INT)(bm.bmWidth * 0.32 * sin(min) + W / 2), (INT)(H / 2 - cos(min) * bm.bmWidth * 0.32));
    MoveToEx(hMemDC, W / 2, H / 2, NULL);
    LineTo(hMemDC, (INT)(bm.bmWidth * 0.25 * sin(hour) + W / 2), (INT)(H / 2 - cos(hour) * bm.bmWidth * 0.25));

    /* Output text */
    SelectObject(hMemDC, hFnt);
    SetDCBrushColor(hMemDC, RGB(0, 0, 0));
    GetTextExtentPoint(hMemDC, Buf, len, &s);
    len = sprintf(Buf, "%02i.%02i.%i %02i:%02i:%02i", tm.wDay, tm.wMonth, tm.wYear, tm.wHour, tm.wMinute, tm.wSecond);
    SetBkMode(hMemDC, TRANSPARENT);
    TextOut(hMemDC, W / 2 - s.cx / 2, H / 2 + bm.bmHeight / 2 - 5 * s.cy, Buf, len);

    /* Drawing first hand */
    sec = 2 * M_PI * tm.wSecond / 60 + tm.wMilliseconds / 10000.0;
    a = sin(sec);
    DrowHand(hMemDC, W / 2, H / 2, a, -200, -20, sin(sec), cos(sec));

    /* Drawing second hand */
    min = 2 * M_PI * tm.wMinute / 60 + sec / 60;
    a = sin(sec);
    DrowHand(hMemDC, W / 2, H / 2, a, -160, -20, sin(min), cos(min));

    /* Drawing third hand */
    hour = (tm.wHour % 12) * 2 * M_PI / 12 + min / 12;
    a = sin(sec);
    DrowHand(hMemDC, W / 2, H / 2, a, -140, -20, sin(hour), cos(hour));

    /* Clear */
    InvalidateRect(hWnd, NULL, FALSE);

    return 0;
  case WM_PAINT:
    /*Udating front */
    hDc = BeginPaint(hWnd, &ps);
    BitBlt(hDc, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;
    case WM_GETMINMAXINFO:
    minmax = (MINMAXINFO *)lParam;
    minmax->ptMaxTrackSize.y =
      GetSystemMetrics(SM_CYMAXTRACK) + GetSystemMetrics(SM_CYCAPTION) +
      GetSystemMetrics(SM_CYBORDER) * 2 + 500;
    return 0;
  case WM_ERASEBKGND:
    return 1;
  case WM_DESTROY:
    DeleteObject(hBm);
    DeleteObject(hFnt);
    DeleteDC(hMemDC);
    DeleteDC(hClock);
    PostMessage(hWnd, WM_QUIT, 0, 0);
    KillTimer(hWnd, 47);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}