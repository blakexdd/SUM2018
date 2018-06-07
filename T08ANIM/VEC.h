/* FILE NAME: T08ANIME.c
 * PROGRAMMER: VG6
 * DATE: 06.06.2018
 */

#include <math.h>

#define PI       3.14159265358979323846
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian(a) D2R(a)

typedef double DBL;

typedef struct tagVEC
{
  DBL X, Y, Z;
} VEC;

typedef struct tagMATR
{
  DBL M[4][4];
} MATR;

__inline VEC VecSet(DBL X, DBL Y, DBL Z)
{
  VEC r = { X, Y, Z };
  return r;
}

__inline VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
}

__inline VEC VecSubVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
}

__inline VEC VecMulNum( VEC V1, DBL N )
{
  return VecSet(V1.X * N, V1.Y * N, V1.Z * N);
}

__inline VEC VecDivNum( VEC V1, DBL N )
{
  return VecSet(V1.X / N, V1.Y / N, V1.Z / N);
}

__inline VEC VecNeg( VEC V )
{
  return VecSet(-V.X, -V.Y, -V.Z);
}

__inline DBL VecDotVec ( VEC V1, VEC V2 )
{
  return V1.X * V2.X, V1.Y * V2.Y, V1.Z * V2.Z;
}

__inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  return VecSet(V1.Y * V2.Z - V1.Z * V2.Y, V1.Z * V2.X - V1.X * V2.Z, V1.X * V2.Y - V1.Y * V2.X);
}

__inline DBL VecLen2( VEC V )
{
  DBL len = VecDotVec(V, V);
  return len;
}

__inline DBL VecLen( VEC V )
{
  return sqrt(VecLen2(V));
}

__inline VEC VecNormalize( VEC V )
{
  DBL len = VecDotVec(V, V);

  if (len == 0 || len == 1)
    return V;
  return VecDivNum(V, len);
}


__inline VEC PointTransform( VEC V, MATR M )
{
  return VecMulMatr(V, M);
}

__inline VEC VectorTransform( VEC V, MATR M )
{
   return VecSet(M.M[0][0] * V.X + M.M[0][1] * V.Y + M.M[0][2] * V.Z,
                M.M[1][0] * V.X + M.M[1][1] * V.Y + M.M[1][2] * V.Z,
                M.M[2][0] * V.X + M.M[2][1] * V.Y + M.M[2][2] * V.Z);
}

MATR Q = MatrTranspose(MatrInverse(M));
N1 = VectorTransform(N, Q);

__inline MATR MatrIdentity( VOID )
{
  return UnitMatrix;
}

__inline MATR MatrTranslate( VEC T )
{
  MATR m = UnitMatrix;

  m.A[3][0] = T.X;
  m.A[3][1] = T.Y;
  m.A[3][2] = T.Z;
  return m;
}
__inline MATR MatrTranslate( VEC T )
{
  MATR m =
  {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {T.X, T.Y, T.Z, 1},
  };
  return m;
}

__inline MATR MatrScale( VEC S )
{

}
__inline MATR MatrRotateX( DBL AngleInDegree )
{
  DBL A = D2R(AngleToDegree), si = sin(A), co = cos(A);
  VEC V = VecNormalize(R);

  MATR M =
  {
    {
      {V.X, V.X, V.X, 0},
      {V.Y * V.X * (1 - co) - V.Z * si, co + V.Y * V.Y * (1 - co), V.Y * V.Z * (1 - co) + V.X * si, 0},
      {V.Z * V.X * (1 - co) + V.Y * si, V.Z * V.Y * (1 - co) - V.X * si, co + V.Z * V.Z * (1 - co), 0},
      {0, 0, 0, 1}
    }
  };

  return M;
}
__inline MATR MatrRotateY( DBL AngleInDegree )
{
  DBL A = D2R(AngleToDegree), si = sin(A), co = cos(A);
  VEC V = VecNormalize(R);

  MATR M =
  {
    {
      {co + V.X * V.X * (1 - co), V.X * V.Y * (1 - co) + V.Z * si, V.X * V.Z * (1 - co) - V.Y * si, 0},
      {V.Y, V.Y, V.Y, 0},
      {V.Z * V.X * (1 - co) + V.Y * si, V.Z * V.Y * (1 - co) - V.X * si, co + V.Z * V.Z * (1 - co), 0},
      {0, 0, 0, 1}
    }
  };

  return M;
}
__inline MATR MatrRotateZ( DBL AngleInDegree )
{
  DBL A = D2R(AngleToDegree), si = sin(A), co = cos(A);
  VEC V = VecNormalize(R);

  MATR M =
  {
    {
      {co + V.X * V.X * (1 - co), V.X * V.Y * (1 - co) + V.Z * si, V.X * V.Z * (1 - co) - V.Y * si, 0},
      {V.Y * V.X * (1 - co) - V.Z * si, co + V.Y * V.Y * (1 - co), V.Y * V.Z * (1 - co) + V.X * si, 0},
      {V.Z, V.Z , V.Z, 0},
      {0, 0, 0, 1}
    }
  };

  return M;
}
__inline MATR MatrRotate( DBL AngleInDegree, VEC R )
{
  DBL A = D2R(AngleToDegree), si = sin(A), co = cos(A);
  VEC V = VecNormalize(R);

  MATR M =
  {
    {
      {co + V.X * V.X * (1 - co), V.X * V.Y * (1 - co) + V.Z * si, V.X * V.Z * (1 - co) - V.Y * si, 0},
      {V.Y * V.X * (1 - co) - V.Z * si, co + V.Y * V.Y * (1 - co), V.Y * V.Z * (1 - co) + V.X * si, 0},
      {V.Z * V.X * (1 - co) + V.Y * si, V.Z * V.Y * (1 - co) - V.X * si, co + V.Z * V.Z * (1 - co), 0},
      {0, 0, 0, 1}
    }
  };

  return M;
}

__inline MATR MatrMulMatr( MATR M1, MATR M2 )
{
  MATR r;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (r.M[i][j] = 0, k = 0; k < 4; k++)
        r.M[i][j] += M1.M[i][k] * M2.M[k][j];
}
__inline MATR MatrTranspose( MATR M )
{
  INT i, j;
  MATR M1;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      M1.M[j][i] = M.M[i][j];
}


__inline DBL MatrDeterm3x3( DBL M11, DBL M12, DBL M13,
                   DBL M21, DBL M22, DBL M23,
                   DBL M31, DBL M32, DBL M33 )
{
  return M11 * M22 * M33 - M11 * M23 * M32 - M12 * M21 * M33 + 
         M12 * M23 * M31 + M13 * M21 * M32 - M13 * M22 * M31;
}

__inline DBL MatrDeterm( MATR M )
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
__inline MATR MatrInverse( MATR M )
{
  Matr r;
  DBL det = MatrDeterM(M);

  if (det == 0)
    return UnitMatrix;

  /* строим присоединенную матрицу */
  /* build Mdjoint Matrix */
  r.M[0][0] =
    MatrDeterM3x3(M.M[1][1], M.M[1][2], M.M[1][3],
                  M.M[2][1], M.M[2][2], M.M[2][3],
                  M.M[3][1], M.M[3][2], M.M[3][3]);
  r.M[1][0] =
    -MatrDeterM3x3(M.M[1][0], M.M[1][2], M.M[1][3],
                   M.M[2][0], M.M[2][2], M.M[2][3],
                   M.M[3][0], M.M[3][2], M.M[3][3]);
  r.M[2][0] =
    MatrDeterM3x3(M.M[1][0], M.M[1][1], M.M[1][3],
                  M.M[2][0], M.M[2][1], M.M[2][3],
                  M.M[3][0], M.M[3][1], M.M[3][3]);
  r.M[3][0] =
    -MatrDeterM3x3(M.M[1][0], M.M[1][1], M.M[1][2],
                   M.M[2][0], M.M[2][1], M.M[2][2],
                   M.M[3][0], M.M[3][1], M.M[3][2]);

  r.M[0][1] =
    -MatrDeterM3x3(M.M[0][1], M.M[0][2], M.M[0][3],
                  M.M[2][1], M.M[2][2], M.M[2][3],
                  M.M[3][1], M.M[3][2], M.M[3][3]);
  r.M[1][1] =
    MatrDeterM3x3(M.M[0][0], M.M[0][2], M.M[0][3],
                  M.M[2][0], M.M[2][2], M.M[2][3],
                  M.M[3][0], M.M[3][2], M.M[3][3]);
  r.M[2][1] =
    -MatrDeterM3x3(M.M[0][0], M.M[0][1], M.M[0][3],
                   M.M[2][0], M.M[2][1], M.M[2][3],
                   M.M[3][0], M.M[3][1], M.M[3][3]);
  r.M[3][1] =
    MatrDeterM3x3(M.M[0][0], M.M[0][1], M.M[0][2],
                  M.M[2][0], M.M[2][1], M.M[2][2],
                  M.M[3][0], M.M[3][1], M.M[3][2]);

  r.M[0][2] =
    MatrDeterM3x3(M.M[0][1], M.M[0][2], M.M[0][3],
                 M.M[1][1], M.M[1][2], M.M[1][3],
                 M.M[3][1], M.M[3][2], M.M[3][3]);
  r.M[1][2] =
    -MatrDeterM3x3(M.M[0][0], M.M[0][2], M.M[0][3],
                   M.M[1][0], M.M[1][2], M.M[1][3],
                   M.M[3][0], M.M[3][2], M.M[3][3]);
  r.M[2][2] =
    MatrDeterM3x3(M.M[0][0], M.M[0][1], M.M[0][3],
                  M.M[1][0], M.M[1][1], M.M[1][3],
                  M.M[3][0], M.M[3][1], M.M[3][3]);
  r.M[3][2] =
    -MatrDeterM3x3(M.M[0][0], M.M[0][1], M.M[0][2],
                   M.M[1][0], M.M[1][1], M.M[1][2],
                   M.M[3][0], M.M[3][1], M.M[3][2]);

  r.M[0][3] =
    -MatrDeterM3x3(M.M[0][1], M.M[0][2], M.M[0][3],
                  M.M[1][1], M.M[1][2], M.M[1][3],
                  M.M[2][1], M.M[2][2], M.M[2][3]);
 
  r.M[1][3] =
    MatrDeterM3x3(M.M[0][0], M.M[0][2], M.M[0][3],
                  M.M[1][0], M.M[1][2], M.M[1][3],
                  M.M[2][0], M.M[2][2], M.M[2][3]);
  r.M[2][3] =
    -MatrDeterM3x3(M.M[0][0], M.M[0][1], M.M[0][3],
                   M.M[1][0], M.M[1][1], M.M[1][3],
                   M.M[2][0], M.M[2][1], M.M[2][3]);
  r.M[3][3] =
    MatrDeterM3x3(M.M[0][0], M.M[0][1], M.M[0][2],
                  M.M[1][0], M.M[1][1], M.M[1][2],
                  M.M[2][0], M.M[2][1], M.M[2][2]);

  /* делим на определитель */
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

__inline MATR MatrInverse( MATR M )
{
  MATR r;
  DBL det = MatrDeterm(M);
  /* перестановки для индексов алгебраических дополнений/миноров */
  INT p[4][3] = {{1, 2, 3}, {0, 2, 3}, {0, 1, 3}, {0, 1, 2}};

  if (det == 0)
    return UnitMatrix;
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++, sign = -sign)
      r.M[j][i] = sign *
        MatrDeterm3x3(
          M.M[p[i][0]][p[j][0]], M.M[p[i][0]][p[j][1]], M.M[p[i][0]][p[j][2]],
          M.M[p[i][1]][p[j][0]], M.M[p[i][1]][p[j][1]], M.M[p[i][1]][p[j][2]],
          M.M[p[i][2]][p[j][0]], M.M[p[i][2]][p[j][1]], M.M[p[i][2]][p[j][2]]) /
        det;
  return r;
}

/* проверка (вариант)
void main( void )
{
  MATR m =
  {
    {1, 1, 1, 0},
    {1, 1, 2, 0},
    {1, 2, 1, 1},
    {2, 1, 1, 1}
  }, m1, m2;

  m1 = MatrInverse(m);
  m2 = MatrMulMatr(m, m1);
  m2 = MatrMulMatr(m1, m);

  m = MatrRotate(90, 0, 1, 0);
  m1 = MatrInverse(m);
}


static MATR UnitMatrix =
{
  {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }
};

__inline MATR MatrIdentity( VOID )
{
  return UnitMatrix;
}
