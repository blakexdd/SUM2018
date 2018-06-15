/* FILE NAME: RND.H
 * PROGRAMMER: VG6
 * DATE: 08.06.2018
 * PURPOSE: Prototipes
 */
#ifndef __RND_H_
#define __RND_H_

#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")
#pragma comment(lib, "glew32s")
#include "../def.h"
#define GLEW_STATIC
#include <glew.h>
#include <gl/gl.h>
#include <gl/glu.h>

extern HWND VG6_hWndRn;
extern HDC VG6_hDCRndFrame;
extern HBITMAP VG6_hBmRndFrame;
extern INT VG6_RndFrameW, VG6_RndFrameH;
extern FLT VG6_RndProjSize;
extern FLT VG6_RndProjDist;
extern FLT VG6_RndProjFarClip;
extern MATR VG6_RndMatrView;
extern MATR VG6_RndMatrProj;
extern MATR VG6_RndMatrVP;
extern INT VG6_MouseWheel;

#define VG6_STR_MAX 300

/*** Shaders handle ***/

/* Shader program store type */
typedef struct tagvg6SHADER
{
  CHAR Name[VG6_STR_MAX]; /* Shader filename prefix */
  INT ProgId;             /* Shader program Id */
} vg6SHADER;

/* Shaders stock maximum size */
#define VG6_MAX_SHADERS 30
/* Array of shaders */
extern vg6SHADER VG6_RndShaders[VG6_MAX_SHADERS];
/* Shadres array store size */
extern INT VG6_RndShadersSize;

/* Shader storage initialize function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID VG6_RndShdInit( VOID );

/* Shader storage deinitialize function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID VG6_RndShdClose( VOID );

/* Add shader to stock from file function.
 * ARGUMENTS:
 *   - shader file path to load (path\***.glsl):
 *       CHAR *ShaderFileNamePrefix;
 * RETURNS:
 *   (INT) new shader stock number.
 */
INT VG6_RndShdAdd( CHAR *ShaderFileNamePrefix );

/* Update from file all load shaders function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID VG6_RndShdUpdate( VOID );

/* Load shader program from .GLSL files function.
 * ARGUMENTS:
 *   - shader file path to load (path\***.glsl):
 *       CHAR *ShaderFileNamePrefix;
 * RETURNS:
 *   (INT) load shader program Id.
 */
INT VG6_RndShdLoad( CHAR *ShaderFileNamePrefix );

/* Unload shader program from memory files function.
 * ARGUMENTS:
 *   - shader program Id:
 *       INT ProgId;
 * RETURNS: None.
 */
VOID VG6_RndShdDelete( INT ProgId );

/*** Materials handle ***/

/* Material store type */
typedef struct tagvg6MATERIAL
{
  CHAR Name[VG6_STR_MAX]; /* Material name */
  INT ShdNo;              /* Shader number in shader array */

  /* to be continue */
} vg6MATERIAL;

/* Material stock maximum size */
#define VG6_MAX_MATERIALS 30
/* Array of materials */
extern vg6MATERIAL VG6_RndMaterials[VG6_MAX_MATERIALS];
/* Materials array store size */
extern INT VG6_RndMaterialsSize;

/* Material storage initialize function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID VG6_RndMtlInit( VOID );

/* Add material to stock function.
 * ARGUMENTS:
 *   - pointer to material data:
 *       vg4MATERIAL *Mtl;
 * RETURNS:
 *   (INT) new material stock number.
 */
INT VG6_RndMtlAdd( vg6MATERIAL *Mtl );

/* Apply material before rendering function.
 * ARGUMENTS:
 *   - material number in materials storage array:
 *       INT MtlNo;
 * RETURNS:
 *   (INT) applyed material shader program Id.
 */
INT VG6_RndMtlApply( INT MtlNo );

/* Space vertex representation type */
typedef struct tagvg6VERTEX
{
  VEC P;  /* Vertex position */
  VEC2 T; /* Vertex texture coordinates */
  VEC N;  /* Vertex normal */
  VEC4 C; /* Vertex color */
} vg6VERTEX;

/* Primitive type */
typedef enum tagvg6PRIM_TYPE
{
  VG6_RND_PRIM_TRIMESH, VG6_RND_PRIM_FRID
} vg6PRIM_TYPE;

/* Primitive representation type */
typedef struct tagvg6PRIM
{
  vg6PRIM_TYPE Type; /* Primitive type */
  INT
    VA,          /* Vertex array Id */
    VBuf,        /* Vertex buffer Id */
    IBuf;        /* Index buffer Id (if 0 - use only vertex buffer) */
  INT NumOfI;   /* Number of indices */
  INT MtlNo;

  MATR Trans;   /* Additional transformation matrix */
} vg6PRIM;


VOID VG6_RndInit( HWND hWnd );
VOID VG6_RndClose( VOID );
VOID VG6_RndResize( INT W, INT H );
VOID VG6_RndStart( VOID );
VOID VG6_RndEnd( VOID );
VOID VG6_RndCopyFrame( HDC hDC );
VOID VG6_RndProjSet( VOID );
VOID VG6_RndCamSet( VEC Loc, VEC At, VEC Up1 );
BOOL VG6_RndPrimCreate( vg6PRIM *Pr, vg6PRIM_TYPE Type, vg6VERTEX *V, INT NoofV, INT *I, INT NoofI );
VOID VG6_RndPrimFree( vg6PRIM *Pr );
VOID VG6_RndPrimDraw( vg6PRIM *Pr, MATR World );
BOOL VG6_RndPrimLoad( vg6PRIM *Pr, CHAR *FileName );

#endif