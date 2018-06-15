/* FILE NAME   : RNDSHD.C
 * PURPOSE     : WinAPI animation system.
 *               Rendering system implementation module.
 *               Shaders handle.
 * PROGRAMMER  : Vitaly A. Galinsky.
 * LAST UPDATE : 11.06.2018.
 * NOTE        : Module prefix 'VG4'.
 */

#include <stdio.h>
#include <string.h>

#include "../../anim.h"

/* Load text from file function.
 * ARGUMENTS:
 *   - file name to be load from:
 *       CHAR *FileName;
 * RETURNS:
 *   (CHAR *) load text (allocated through malloc).
 */
static CHAR * VG6_RndShdLoadTextFromFile( CHAR *FileName )
{
  FILE *F;
  CHAR *txt;
  INT flen;

  if ((F = fopen(FileName, "r")) == NULL)
    return NULL;
  fseek(F, 0, SEEK_END);
  flen = ftell(F);
  rewind(F);

  if ((txt = malloc(flen + 1)) == NULL)
  {
    fclose(F);
    return NULL;
  }
  memset(txt, 0, flen + 1);
  fread(txt, 1, flen, F);
  fclose(F);
  return txt;
} /* End of 'VG6_RndShdLoadTextFromFile' function */

/* Store log to file function.
 * ARGUMENTS:
 *   - message file prefix, shader name and text:
 *       CHAR *PartName, *Text;
 * RETURNS: None.
 */
static VOID VG6_RndShdLog( CHAR *Prefix, CHAR *Type, CHAR *Text )
{
  FILE *F;

  if ((F = fopen("BIN/SHADERS/VG4{30}SHD.LOG", "a")) == NULL)
    return;
  fprintf(F, "%s/%s.GLSL:\n%s\n", Prefix, Type, Text);
  fclose(F);
} /* End of 'VG6_RndShdLog' function */

/* Load shader program from .GLSL files function.
 * ARGUMENTS:
 *   - shader file path to load (path\***.glsl):
 *       CHAR *ShaderFileNamePrefix;
 * RETURNS:
 *   (INT) load shader program Id.
 */
INT VG6_RndShdLoad( CHAR *ShaderFileNamePrefix )
{
  struct
  {
    CHAR *Name; /* Shader file suffix name */
    INT Type;   /* Shader OpenGL type */
    INT Id;     /* Shader Id created by OpenGL */
  } shd[] =
  {
    {"VERT", GL_VERTEX_SHADER},
    {"FRAG", GL_FRAGMENT_SHADER}
  };
  INT i, prg = 0, res, Ns = sizeof(shd) / sizeof(shd[0]);
  CHAR *txt;
  BOOL is_ok = TRUE;
  static CHAR Buf[3000];

  for (i = 0; is_ok && i < Ns; i++)
  {
    /* Load shader text from file */
    sprintf(Buf, "%s/%s.GLSL", ShaderFileNamePrefix, shd[i].Name);
    if ((txt = VG6_RndShdLoadTextFromFile(Buf)) == NULL)
    {
      VG6_RndShdLog(ShaderFileNamePrefix, shd[i].Name, "Error load file");
      is_ok = FALSE;
      break;
    }
    /* Create shader */
    if ((shd[i].Id = glCreateShader(shd[i].Type)) == 0)
    {
      VG6_RndShdLog(ShaderFileNamePrefix, shd[i].Name, "Error create shader");
      free(txt);
      is_ok = FALSE;
      break;
    }
    /* Attach shader source code to shader */
    glShaderSource(shd[i].Id, 1, &txt, NULL);
    free(txt);

    /* Compile shader */
    glCompileShader(shd[i].Id);
    glGetShaderiv(shd[i].Id, GL_COMPILE_STATUS, &res);
    if (res != 1)
    {
      glGetShaderInfoLog(shd[i].Id, sizeof(Buf), &res, Buf);
      VG6_RndShdLog(ShaderFileNamePrefix, shd[i].Name, Buf);
      is_ok = FALSE;
      break;
    }
  }

  if (is_ok)
  {
    if ((prg = glCreateProgram()) == 0)
    {
      is_ok = FALSE;
      VG6_RndShdLog(ShaderFileNamePrefix, "PROG", "Error create program");
    }
    else
    {
      for(i = 0; i < Ns; i++)
        if(shd[i].Id != 0)
          glAttachShader(prg, shd[i].Id);
      glLinkProgram(prg);
      glGetProgramiv(prg, GL_LINK_STATUS, &res);
    if (res != 1)
    {
      glGetProgramInfoLog(prg, sizeof(Buf), &res, Buf);
      VG6_RndShdLog(ShaderFileNamePrefix, "PROG", Buf);
      is_ok = FALSE;
    }
    }
  }

  if (!is_ok)
  {
    /* Remove all shaders */
    for (i = 0; i < Ns; i++)
      if (shd[i].Id != 0)
      {
        glDetachShader(prg, shd[i].Id);
        glDeleteShader(shd[i].Id);
      }
    /* Remove program */
    if (prg != 0)
      glDeleteProgram(prg);
    prg = 0;
  }

  return prg;
} /* End of 'VG6_RndShdLoad' function */


/* Unload shader program from memory files function.
 * ARGUMENTS:
 *   - shader program Id:
 *       INT ProgId;
 * RETURNS: None.
 */
VOID VG6_RndShdDelete( INT ProgId )
{
  INT shdrs[5], n, i;

  if (ProgId == 0)
    return;
  glGetAttachedShaders(ProgId, 5, &n, shdrs);
  for (i = 0; i < n; i++)
  {
    glDetachShader(ProgId, shdrs[i]);
    glDeleteShader(shdrs[i]);
  }
  glDeleteProgram(ProgId);
} /* End of 'VG6_RndShdDelete' function */

/***
 * Shader storage functions
 ***/

/* Array of shaders */
vg6SHADER VG6_RndShaders[VG6_MAX_SHADERS];
/* Shadres array store size */
INT VG6_RndShadersSize;

/* Shader storage initialize function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID VG6_RndShdInit( VOID )
{
  VG6_RndShdAdd("BIN/SHADERS/DEFAULT");
} /* End of 'VG6_RndShdInit' function */

/* Shader storage deinitialize function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID VG6_RndShdClose( VOID )
{
  INT i;

  for (i = 0; i < VG6_RndShadersSize; i++)
    VG6_RndShdDelete(VG6_RndShaders[i].ProgId);
  VG6_RndShadersSize = 0;
} /* End of 'VG6_RndShdClose' function */

/* Add shader to stock from file function.
 * ARGUMENTS:
 *   - shader file path to load (path\***.glsl):
 *       CHAR *ShaderFileNamePrefix;
 * RETURNS:
 *   (INT) new shader stock number.
 */
INT VG6_RndShdAdd( CHAR *ShaderFileNamePrefix )
{
  if (VG6_RndShadersSize >= VG6_MAX_SHADERS)
    return 0;

  strncpy(VG6_RndShaders[VG6_RndShadersSize].Name,
    ShaderFileNamePrefix, VG6_STR_MAX - 1);
  VG6_RndShaders[VG6_RndShadersSize].ProgId =
    VG6_RndShdLoad(ShaderFileNamePrefix);

  return VG6_RndShadersSize++;
} /* End of 'VG6_RndShdAdd' function */

/* Update from file all load shaders function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID VG6_RndShdUpdate( VOID )
{
  INT i;

  for (i = 0; i < VG6_RndShadersSize; i++)
  {
    VG6_RndShdDelete(VG6_RndShaders[i].ProgId);
    VG6_RndShaders[i].ProgId = VG6_RndShdLoad(VG6_RndShaders[i].Name);
  }
} /* End of 'VG6_RndShdUpdate' function */

/* END OF 'RNDSHD.C' FILE */
