/* FILE NAME: VEC.H
 * PROGRAMMER: VG6
 * DATE: 08.06.2018
 * PURPOSE: Libary for graphics
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>

#define PI       3.14159265358979323846
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian (a) D2R(a)

typedef float FLT;
typedef double DBL;

typedef struct tagVEC
{
  FLT X, Y, Z;
} VEC;


/* Plane vector representation type */
typedef struct tagVEC2
{
  FLT X, Y; /* Vector components */
} VEC2;

/* 4-components vector representation type */
typedef struct tagVEC4
{
  FLT X, Y, Z, W; /* Vector components */
} VEC4;

typedef struct tagMATR
{
  FLT M[4][4];
} MATR;

static MATR UnitMatrix =
{
  {
    { 1, 0, 0, 0 },
    { 0, 1, 0, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 0, 1 }
  }
};


__inline VEC VecSet(FLT X, FLT Y, FLT Z)
{
  VEC v = { X, Y, Z };
  return v;
}


__inline VEC RotateY(VEC V, FLT Angled)
{
  FLT a = Angled * PI / 180, co = cos(a), si = sin(a);

  return VecSet(V.Z * si + V.X * co, V.Y, V.Z * co - V.X * si);
} 

__inline VEC RotateX(VEC V, FLT Angled)
{
  FLT a = Angled * PI / 180, co = cos(a), si = sin(a);

  return VecSet(V.X, V.Y * co + V.Z * si, V.Z * co - V.Y * si);
} 

__inline VEC VecAddVec(VEC V1, VEC V2)
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
}

__inline VEC VecSubVec(VEC V1, VEC V2)
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
} 

__inline VEC VecMulNum(VEC V1, FLT N)
{
  return VecSet(V1.X * N, V1.Y * N, V1.Z * N);
} 

__inline VEC VecDivNum(VEC V1, FLT N)
{
  return VecSet(V1.X / N, V1.Y / N, V1.Z / N);
}

__inline VEC VecNeg(VEC V)
{
  return VecSet(-V.X, -V.Y, -V.Z);
} 

__inline FLT VecDotVec(VEC V1, VEC V2)
{
  return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
} 

__inline VEC VecCrossVec(VEC V1, VEC V2)
{
  return VecSet(V1.Y * V2.Z - V1.Z * V2.Y, V1.Z * V2.X - V1.X * V2.Z, V1.X * V2.Y - V1.Y * V2.X);
} 

__inline FLT VecLen2(VEC V)
{
  return VecDotVec(V, V);
}

__inline FLT VecLen(VEC V)
{
  return sqrt(VecLen2(V));
} 

__inline VEC VecNormalize(VEC V)
{
  FLT len = VecDotVec(V, V);

  if (len == 0 || len == 1)
    return V;
  return VecDivNum(V, sqrt(len));
} 

__inline VEC PointTransform(VEC V, MATR M)
{
  return VecSet(M.M[0][0] * V.X + M.M[0][1] * V.Y + M.M[0][2] * V.Z + M.M[0][3],
    M.M[1][0] * V.X + M.M[1][1] * V.Y + M.M[1][2] * V.Z + M.M[1][3],
    M.M[2][0] * V.X + M.M[2][1] * V.Y + M.M[2][2] * V.Z + M.M[2][3]);
} 

__inline VEC VectorTransform(VEC V, MATR M)
{
  return VecSet(M.M[0][0] * V.X + M.M[0][1] * V.Y + M.M[0][2] * V.Z,
    M.M[1][0] * V.X + M.M[1][1] * V.Y + M.M[1][2] * V.Z,
    M.M[2][0] * V.X + M.M[2][1] * V.Y + M.M[2][2] * V.Z);
} 

__inline MATR MatrIdentity(VOID)
{
  return UnitMatrix;
} 

__inline MATR MatrTranslate(VEC T)
{
  MATR m = UnitMatrix;

  m.M[3][0] = T.X;
  m.M[3][1] = T.Y;
  m.M[3][2] = T.Z;

  return m;
}

__inline MATR MatrScale(VEC S)
{
  MATR m = UnitMatrix;

  m.M[0][0] = S.X;
  m.M[1][1] = S.Y;
  m.M[2][2] = S.Z;
  return m;
}


__inline MATR MatrRotateX(FLT AngleInDegree)
{
  FLT A = D2R(AngleInDegree), si = sin(A), co = cos(A);

  MATR M =
  {
    {
      { 1, 0, 0, 0 },
      { 0, co, si, 0 },
      { 0, -si, co, 0 },
      { 0, 0, 0, 1 }
    }
  };

  return M;
}

__inline MATR MatrRotateY(FLT AngleInDegree)
{
  FLT A = D2R(AngleInDegree), si = sin(A), co = cos(A);

  MATR M =
  {
    {
      { co, 0, -si, 0 },
      { 0, 1, 0, 0 },
      { si, 0, co, 0 },
      { 0, 0, 0, 1 }
    }
  };

  return M;
}

__inline MATR MatrRotateZ(FLT AngleInDegree)
{
  FLT A = D2R(AngleInDegree), si = sin(A), co = cos(A);

  MATR M =
  {
    {
      { co, si, 0, 0 },
      { -si, co, 0, 0 },
      { 0, 0, 1, 0 },
      { 0, 0, 0, 1 }
    }
  };

  return M;
}

__inline MATR MatrRotate(FLT AngleInDegree, VEC R)
{
  FLT A = D2R(AngleInDegree), si = sin(A), co = cos(A);
  VEC V = VecNormalize(R);

  MATR M =
  {
    {
      { co + V.X * V.X * (1 - co), V.X * V.Y * (1 - co) + V.Z * si, V.X * V.Z * (1 - co) - V.Y * si, 0 },
      { V.Y * V.X * (1 - co) - V.Z * si, co + V.Y * V.Y * (1 - co), V.Y * V.Z * (1 - co) + V.X * si, 0 },
      { V.Z * V.X * (1 - co) + V.Y * si, V.Z * V.Y * (1 - co) - V.X * si, co + V.Z * V.Z * (1 - co), 0 },
      { 0, 0, 0, 1 }
    }
  };

  return M;
}

__inline MATR MatrMulMatr(MATR M1, MATR M2)
{
  MATR r;
  INT i, j, k;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (r.M[i][j] = 0, k = 0; k < 4; k++)
        r.M[i][j] += M1.M[i][k] * M2.M[k][j];
  return r;
}

__inline MATR MatrTranspose(MATR M)
{
  INT i, j;
  MATR M1;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      M1.M[j][i] = M.M[i][j];
  return M1;
}

__inline FLT MatrDeterm3x3(FLT M11, FLT M12, FLT M13,
                           FLT M21, FLT M22, FLT M23,
                           FLT M31, FLT M32, FLT M33)
{
  return M11 * M22 * M33 - M11 * M23 * M32 - M12 * M21 * M33 +
    M12 * M23 * M31 + M13 * M21 * M32 - M13 * M22 * M31;
}

__inline FLT MatrDeterm(MATR M)
{
  return
    M.M[0][0] * MatrDeterm3x3(M.M[1][1], M.M[1][2], M.M[1][3],
    M.M[2][1], M.M[2][2], M.M[2][3],
    M.M[3][1], M.M[3][2], M.M[3][3]) -
    M.M[0][1] * MatrDeterm3x3(M.M[1][0], M.M[1][2], M.M[1][3],
    M.M[2][0], M.M[2][2], M.M[2][3],
    M.M[3][0], M.M[3][2], M.M[3][3]) +
    M.M[0][2] * MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][3],
    M.M[2][0], M.M[2][1], M.M[2][3],
    M.M[3][0], M.M[3][1], M.M[3][3]) -
    M.M[0][3] * MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][2],
    M.M[2][0], M.M[2][1], M.M[2][2],
    M.M[3][0], M.M[3][1], M.M[3][2]);
}
__inline MATR MatrInverse(MATR M)
{
  MATR r;
  FLT det = MatrDeterm(M);

  if (det == 0)
    return UnitMatrix;

  r.M[0][0] =
    MatrDeterm3x3(M.M[1][1], M.M[1][2], M.M[1][3],
    M.M[2][1], M.M[2][2], M.M[2][3],
    M.M[3][1], M.M[3][2], M.M[3][3]);
  r.M[1][0] =
    -MatrDeterm3x3(M.M[1][0], M.M[1][2], M.M[1][3],
    M.M[2][0], M.M[2][2], M.M[2][3],
    M.M[3][0], M.M[3][2], M.M[3][3]);
  r.M[2][0] =
    MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][3],
    M.M[2][0], M.M[2][1], M.M[2][3],
    M.M[3][0], M.M[3][1], M.M[3][3]);
  r.M[3][0] =
    -MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][2],
    M.M[2][0], M.M[2][1], M.M[2][2],
    M.M[3][0], M.M[3][1], M.M[3][2]);
  r.M[0][1] =
    -MatrDeterm3x3(M.M[0][1], M.M[0][2], M.M[0][3],
    M.M[2][1], M.M[2][2], M.M[2][3],
    M.M[3][1], M.M[3][2], M.M[3][3]);
  r.M[1][1] =
    MatrDeterm3x3(M.M[0][0], M.M[0][2], M.M[0][3],
    M.M[2][0], M.M[2][2], M.M[2][3],
    M.M[3][0], M.M[3][2], M.M[3][3]);
  r.M[2][1] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][3],
    M.M[2][0], M.M[2][1], M.M[2][3],
    M.M[3][0], M.M[3][1], M.M[3][3]);
  r.M[3][1] =
    MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][2],
    M.M[2][0], M.M[2][1], M.M[2][2],
    M.M[3][0], M.M[3][1], M.M[3][2]);
  r.M[0][2] =
    MatrDeterm3x3(M.M[0][1], M.M[0][2], M.M[0][3],
    M.M[1][1], M.M[1][2], M.M[1][3],
    M.M[3][1], M.M[3][2], M.M[3][3]);
  r.M[1][2] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][2], M.M[0][3],
    M.M[1][0], M.M[1][2], M.M[1][3],
    M.M[3][0], M.M[3][2], M.M[3][3]);
  r.M[2][2] =
    MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][3],
    M.M[1][0], M.M[1][1], M.M[1][3],
    M.M[3][0], M.M[3][1], M.M[3][3]);
  r.M[3][2] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][2],
    M.M[1][0], M.M[1][1], M.M[1][2],
    M.M[3][0], M.M[3][1], M.M[3][2]);
  r.M[0][3] =
    -MatrDeterm3x3(M.M[0][1], M.M[0][2], M.M[0][3],
    M.M[1][1], M.M[1][2], M.M[1][3],
    M.M[2][1], M.M[2][2], M.M[2][3]);
  r.M[1][3] =
    MatrDeterm3x3(M.M[0][0], M.M[0][2], M.M[0][3],
    M.M[1][0], M.M[1][2], M.M[1][3],
    M.M[2][0], M.M[2][2], M.M[2][3]);
  r.M[2][3] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][3],
    M.M[1][0], M.M[1][1], M.M[1][3],
    M.M[2][0], M.M[2][1], M.M[2][3]);
  r.M[3][3] =
    MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][2],
    M.M[1][0], M.M[1][1], M.M[1][2],
    M.M[2][0], M.M[2][1], M.M[2][2]);

  r.M[0][0] /= det;
  r.M[1][0] /= det;
  r.M[2][0] /= det;
  r.M[3][0] /= det;
  r.M[0][1] /= det;
  r.M[1][1] /= det;
  r.M[2][1] /= det;
  r.M[3][1] /= det;
  r.M[0][2] /= det;
  r.M[1][2] /= det;
  r.M[2][2] /= det;
  r.M[3][2] /= det;
  r.M[0][3] /= det;
  r.M[1][3] /= det;
  r.M[2][3] /= det;
  r.M[3][3] /= det;

  return r;
}

__inline MATR MatrView(VEC Loc, VEC At, VEC Up1)
{
  VEC
    Dir = VecNormalize(VecSubVec(At, Loc)),
    Right = VecNormalize(VecCrossVec(Dir, Up1)),
    Up = VecNormalize(VecCrossVec(Right, Dir));

  MATR m =
  {
    {
      { Right.X, Up.X, -Dir.X, 0 },
      { Right.Y, Up.Y, -Dir.Y, 0 },
      { Right.Z, Up.Z, -Dir.Z, 0 },
      { -VecDotVec(Loc, Right), -VecDotVec(Loc, Up), VecDotVec(Loc, Dir), 1 }
    }
  };

  return m;
}

__inline MATR MatrViewFrustum(FLT l, FLT r, FLT b, FLT t, FLT n, FLT f)
{
  MATR m =
  {
    {
      { 2 * n / (r - l), 0, 0, 0 },
      { 0, 2 * n / (t - b), 0, 0 },
      { (r + l) / (r - l), (t + b) / (t - b), -(f + n) / (f - n), -1 },
      { 0, 0, -2 * n * f / (f + n), 0 }
    }
  };

  return m;
}

__inline VEC VecMulMatr4x4(VEC V, MATR M)
{
  FLT w = V.X * M.M[0][3] + V.Y * M.M[1][3] + V.Z * M.M[2][3] + M.M[3][3];

  return VecSet((M.M[0][0] * V.X + M.M[1][0] * V.Y + M.M[2][0] * V.Z + M.M[3][0]) / w,
    (M.M[0][1] * V.X + M.M[1][1] * V.Y + M.M[2][1] * V.Z + M.M[3][1]) / w,
    (M.M[0][2] * V.X + M.M[1][2] * V.Y + M.M[2][2] * V.Z + M.M[3][2]) / w);
}
