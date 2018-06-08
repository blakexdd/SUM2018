/* FILE NAME: VEC.H
 * PROGRAMMER: VG6
 * DATE: 08.06.2018
 * PURPOSE: Libary for graphics
 */

#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define PI       3.14159265358979323846
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian (a) D2R(a)

typedef double DBL;

typedef struct tagVEC
{
  DBL X, Y, Z;
} VEC;

typedef struct tagMATR
{
  DBL M[4][4];
} MATR;

static MATR UnitMatrix = 
{
  {
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 0}
  }
};

/* Vector set function.
 * ARGUMENTS:
 *   - vector coordinates:
 *       DBL X, Y, Z;
 * RETURNS:
 *   (VECT) result vector.
 */
__inline VEC VecSet( DBL X, DBL Y, DBL Z )
{
  VEC v = {X, Y, Z};
  return v;
} /* End of 'VecSet' function */

/* Vector add vector function.*/
__inline VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
} /* End of 'VecAddVec' function */

/* Vector sub vector function.*/
__inline VEC VecSubVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
} /* End of 'VecSubVec' function */

/* Vector multiplicate by number function.*/
__inline VEC VecMulNum( VEC V1, DBL N )
{
  return VecSet(V1.X * N, V1.Y * N, V1.Z * N);
} /* End of 'VecMulNum' function */

/* Vector divide by number function.*/
__inline VEC VecDivNum( VEC V1, DBL N )
{
  return VecSet(V1.X / N, V1.Y / N, V1.Z / N);
} /* End of 'VecDivNum' function */

/* Vector negative function.*/
__inline VEC VecNeg( VEC V )
{
  return VecSet(-V.X, -V.Y, -V.Z);
} /* End of 'VecNeg' function */

/* Vector multiply by vec in scal function.*/
__inline DBL VecDotVec( VEC V1, VEC V2 )
{
  return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
} /* End of 'VecDotVec' function */

/* Vector multiply by vec in vectors function.*/
__inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  return VecSet(V1.Y * V2.Z - V1.Z * V2.Y, V1.Z * V2.X- V1.X * V2.Z, V1.X * V2.Y - V1.Y * V2.X);
} /* End of 'VecCrossVec' function */


/* Vectors squared length function.*/
__inline DBL VecLen2( VEC V )
{
  return VecDotVec(V, V); 
} /* End of 'VecLen2' function */

/* Vectors lenght function.*/
__inline DBL VecLen( VEC V )
{
  return sqrt(VecLen2(V));
} /* End of 'VecLen' function */

/* Vector normalize function.*/
__inline VEC VecNormalize( VEC V )
{
  DBL len = VecDotVec(V, V);

  if (len == 0 || len == 1)
    return V;
  return VecDivNum(V, sqrt(len));
} /* End of 'VecNormalize' function */

/* Transformation point function.*/
__inline VEC PointTransform( VEC V, MATR M )
{
  return VecSet(M.M[0][0] * V.X + M.M[0][1] * V.Y + M.M[0][2] * V.Z + M.M[0][3], 
                M.M[1][0] * V.X + M.M[1][1] * V.Y + M.M[1][2] * V.Z + M.M[1][3],
                M.M[2][0] * V.X + M.M[2][1] * V.Y + M.M[2][2] * V.Z + M.M[2][3]);
} /* End of 'PointTransform' function */

/* Transformation vector function.*/
__inline VEC VectorTransform( VEC V, MATR M )
{
  return VecSet(M.M[0][0] * V.X + M.M[0][1] * V.Y + M.M[0][2] * V.Z, 
                M.M[1][0] * V.X + M.M[1][1] * V.Y + M.M[1][2] * V.Z,
                M.M[2][0] * V.X + M.M[2][1] * V.Y + M.M[2][2] * V.Z);
} /* End of 'VectorTransform' function */


__inline MATR MatrIdentity( VOID )
{
  return UnitMatrix;
} /* End of 'MatrIdentity' function */

/* Translating matrix function.*/
__inline MATR MatrTranslate( VEC T )
{
  MATR m = UnitMatrix;

  m.M[3][0] = T.X;
  m.M[3][1] = T.Y;
  m.M[3][2] = T.Z;
  return m;
} /* End of 'MatrTranslate' function */

/* Scaling matr*/
__inline MATR MatrScale( VEC S )
{
  MATR m = UnitMatrix;

  m.M[0][0] = S.X;
  m.M[1][1] = S.Y;
  m.M[2][2] = S.Z;
  return m;
} /* End of 'MatrScale' function */

/* Matr rotateZ function.*/
__inline MATR MatrRotateZ( DBL AngleInDegree )
{
  DBL A = D2R(AngleInDegree), si = sin(A), co = cos(A);

  MATR M =
  {
    {
      {co, si, 0, 0},
      {-si, co, 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1}
    }
  };

  return M;
} /* End of 'MatrRotateZ' function */

/* Matr rotateX function.*/
__inline MATR MatrRotateX( DBL AngleInDegree )
{
  DBL A = D2R(AngleInDegree), si = sin(A), co = cos(A);

  MATR M =
  {
    {
      {1, 0, 0, 0},
      {0, co, si, 0},
      {0, -si, co, 0},
      {0, 0, 0, 1}
    }
  };

  return M;
} /* End of 'MatrRotateX' function */

/* Matr rotateY function.*/
__inline MATR MatrRotateY( DBL AngleInDegree )
{
  DBL A = D2R(AngleInDegree), si = sin(A), co = cos(A);

  MATR M =
  {
    {
      {co, 0, -si, 0},
      {0, 1, 0, 0},
      {si, 0, co, 0},
      {0, 0, 0, 1}
    }
  };

  return M;
} /* End of 'MatrRotateY' function */

/* Matr rotate function.*/
__inline MATR MatrRotate( DBL AngleInDegree, VEC R )
{
  DBL A = D2R(AngleInDegree), si = sin(A), co = cos(A);
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
} /* End of 'MatrRotate' function */

/* Matr multiply matr function.*/
__inline MATR MatrMulMatr( MATR M1, MATR M2 )
{
  MATR r;
  INT i, j, k;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (r.M[i][j] = 0, k = 0; k < 4; k++)
        r.M[i][j] += M1.M[i][k] * M2.M[k][j];
  return r;
} /* End of 'MatrMulMatr' function */

/* Matr transposing function.*/
__inline MATR MatrTranspose( MATR M )
{
  INT i, j;
  MATR M1;

  for(i = 0; i < 4; i++)
    for(j = 0; j < 4;j++)
      M1.M[j][i] = M.M[i][j];
  return M1;
} /* End of 'MatrTranspose' function */

/* Matr3x3 determinanl finding function.*/
__inline DBL MatrDeterm3x3( DBL M11, DBL M12, DBL M13,
                   DBL M21, DBL M22, DBL M23,
                   DBL M31, DBL M32, DBL M33 )
{
  return M11 * M22 * M33 - M11 * M23 * M32 - M12 * M21 * M33 + 
         M12 * M23 * M31 + M13 * M21 * M32 - M13 * M22 * M31;
} /* End of 'MatrDeterm3x3' function */

/* Matr determinanl finding function.*/
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
} /* End of 'MatrDeterm' function */

/* Matr inverse function.*/
__inline MATR MatrInverse( MATR M )
{
  MATR r;
  DBL det = MatrDeterm(M);
  
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
} /* End of 'MatrInverse' function */

/* Matr inversing function.*/
__inline MATR MatrInverse1( MATR M )
{
  MATR r;
  DBL det = MatrDeterm(M);

  INT p[4][3] = {{1, 2, 3}, {0, 2, 3}, {0, 1, 3}, {0, 1, 2}}, i, j, sign = 1;

  if (det == 0)
    return UnitMatrix;
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++, sign = -sign)
      r.M[j][i] = sign *
        MatrDeterm3x3(
          M.M[p[i][0]][p[j][0]], M.M[p[i][0]][p[j][1]], M.M[p[i][0]][p[j][2]],
          M.M[p[i][1]][p[j][0]], M.M[p[i][1]][p[j][1]], M.M[p[i][1]][p[j][2]],
          M.M[p[i][2]][p[j][0]], M.M[p[i][2]][p[j][1]], M.M[p[i][2]][p[j][2]]);
        det;
  return r;
} /* End of 'MatrInverse1' function */

__inline MATR MatrViewFrustum( DBL Right, DBL Left, DBL Top, DBL Bottom, DBL Far, DBL Near )
{
  MATR m =
  {
    {
      {2 * Near / (Right - Left), 0, 0, 0},
      {0, 2 * Near / (Top - Bottom), 0, 0},
      {(Right + Left) / (Right - Left), (Top + Bottom) / (Top - Bottom), -(Far + Near) / (Far - Near), -1},
      {0, 0, -2 * Near * Far / (Far - Near), 0}
    }
  };

  return m;
}


__inline VEC VecMulMatr4x4( VEC V, MATR M )
{
   DBL w = V.X * M.M[0][3] + V.Y * M.M[1][3] + V.Z * M.M[2][3] + M.M[3][3];

   return VecSet((M.M[0][0] * V.X + M.M[0][1] * V.Y + M.M[0][2] * V.Z) / w, (M.M[1][0] * V.X + M.M[1][1] * V.Y + M.M[1][2] * V.Z) / w,
         (M.M[2][0] * V.X + M.M[2][1] * V.Y + M.M[2][2] * V.Z) / w);

}
__inline MATR MatrResult( MATR M1, MATR M2, MATR M3 )
{
  return MatrMulMatr(MatrMulMatr(M1, M2), M3);
}

__inline MATR MatrView( VEC Loc, VEC At, VEC Up1 )
{
  VEC
    Dir = VecNormalize(VecSubVec(At, Loc)),
    Right = VecNormalize(VecSubVec(Dir, Up1)),
    Up = VecNormalize(VecSubVec(Right, Dir));

  MATR m =
  {
    {
      {Right.X, Up.X, -Dir.X, 0},
      {Right.Y, Up.Y, -Dir.Y, 0},
      {Right.Z, Up.Z, -Dir.Z, 0},
      {-VecDotVec(Loc, Right), -VecDotVec(Loc, Up), VecDotVec(Loc, Dir), 1}
    }
  };

  return m;
}