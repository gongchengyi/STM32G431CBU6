/*
 * File: Park_test.c
 *
 * Code generated for Simulink model 'Park_test'.
 *
 * Model version                  : 1.5
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Tue May 19 16:34:54 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "Park_test.h"
#include <math.h>
#include "mw_cmsis.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <float.h>
#define NumBitsPerChar                 8U

/* Exported block signals */
real32_T id;                           /* '<S1>/Park' */
real32_T iq;                           /* '<S1>/Park' */
real32_T ia;                           /* '<S7>/Sin' */
real32_T ib;                           /* '<S7>/Sin1' */
real32_T ic;                           /* '<S7>/Sin2' */
real32_T ialpha;                       /* '<S2>/Clark' */
real32_T ibeta;                        /* '<S2>/Clark' */

/* Block signals and states (default storage) */
DW rtDW;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
extern real_T rt_modd_snf(real_T u0, real_T u1);
extern real32_T rt_modf_snf(real32_T u0, real32_T u1);
static real_T rtGetNaN(void);
static real32_T rtGetNaNF(void);

#define NOT_USING_NONFINITE_LITERALS   1

extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;
static void rt_InitInfAndNaN(size_t realSize);
static boolean_T rtIsInf(real_T value);
static boolean_T rtIsInfF(real32_T value);
static boolean_T rtIsNaN(real_T value);
static boolean_T rtIsNaNF(real32_T value);
typedef struct {
  struct {
    uint32_T wordH;
    uint32_T wordL;
  } words;
} BigEndianIEEEDouble;

typedef struct {
  struct {
    uint32_T wordL;
    uint32_T wordH;
  } words;
} LittleEndianIEEEDouble;

typedef struct {
  union {
    real32_T wordLreal;
    uint32_T wordLuint;
  } wordL;
} IEEESingle;

real_T rtInf;
real_T rtMinusInf;
real_T rtNaN;
real32_T rtInfF;
real32_T rtMinusInfF;
real32_T rtNaNF;
static real_T rtGetInf(void);
static real32_T rtGetInfF(void);
static real_T rtGetMinusInf(void);
static real32_T rtGetMinusInfF(void);

/*
 * Initialize rtNaN needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetNaN(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T nan = 0.0;
  if (bitsPerReal == 32U) {
    nan = rtGetNaNF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF80000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    nan = tmpVal.fltVal;
  }

  return nan;
}

/*
 * Initialize rtNaNF needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetNaNF(void)
{
  IEEESingle nanF = { { 0.0F } };

  nanF.wordL.wordLuint = 0xFFC00000U;
  return nanF.wordL.wordLreal;
}

/*
 * Initialize the rtInf, rtMinusInf, and rtNaN needed by the
 * generated code. NaN is initialized as non-signaling. Assumes IEEE.
 */
static void rt_InitInfAndNaN(size_t realSize)
{
  (void) (realSize);
  rtNaN = rtGetNaN();
  rtNaNF = rtGetNaNF();
  rtInf = rtGetInf();
  rtInfF = rtGetInfF();
  rtMinusInf = rtGetMinusInf();
  rtMinusInfF = rtGetMinusInfF();
}

/* Test if value is infinite */
static boolean_T rtIsInf(real_T value)
{
  return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);
}

/* Test if single-precision value is infinite */
static boolean_T rtIsInfF(real32_T value)
{
  return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
}

/* Test if value is not a number */
static boolean_T rtIsNaN(real_T value)
{
  boolean_T result = (boolean_T) 0;
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  if (bitsPerReal == 32U) {
    result = rtIsNaNF((real32_T)value);
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.fltVal = value;
    result = (boolean_T)((tmpVal.bitVal.words.wordH & 0x7FF00000) == 0x7FF00000 &&
                         ( (tmpVal.bitVal.words.wordH & 0x000FFFFF) != 0 ||
                          (tmpVal.bitVal.words.wordL != 0) ));
  }

  return result;
}

/* Test if single-precision value is not a number */
static boolean_T rtIsNaNF(real32_T value)
{
  IEEESingle tmp;
  tmp.wordL.wordLreal = value;
  return (boolean_T)( (tmp.wordL.wordLuint & 0x7F800000) == 0x7F800000 &&
                     (tmp.wordL.wordLuint & 0x007FFFFF) != 0 );
}

/*
 * Initialize rtInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T inf = 0.0;
  if (bitsPerReal == 32U) {
    inf = rtGetInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0x7FF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    inf = tmpVal.fltVal;
  }

  return inf;
}

/*
 * Initialize rtInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetInfF(void)
{
  IEEESingle infF;
  infF.wordL.wordLuint = 0x7F800000U;
  return infF.wordL.wordLreal;
}

/*
 * Initialize rtMinusInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetMinusInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T minf = 0.0;
  if (bitsPerReal == 32U) {
    minf = rtGetMinusInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    minf = tmpVal.fltVal;
  }

  return minf;
}

/*
 * Initialize rtMinusInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetMinusInfF(void)
{
  IEEESingle minfF;
  minfF.wordL.wordLuint = 0xFF800000U;
  return minfF.wordL.wordLreal;
}

real_T rt_modd_snf(real_T u0, real_T u1)
{
  real_T y;
  y = u0;
  if (u1 == 0.0) {
    if (u0 == 0.0) {
      y = u1;
    }
  } else if (rtIsNaN(u0) || rtIsNaN(u1) || rtIsInf(u0)) {
    y = (rtNaN);
  } else if (u0 == 0.0) {
    y = 0.0 / u1;
  } else if (rtIsInf(u1)) {
    if ((u1 < 0.0) != (u0 < 0.0)) {
      y = u1;
    }
  } else {
    boolean_T yEq;
    y = fmod(u0, u1);
    yEq = (y == 0.0);
    if ((!yEq) && (u1 > floor(u1))) {
      real_T q;
      q = fabs(u0 / u1);
      yEq = !(fabs(q - floor(q + 0.5)) > DBL_EPSILON * q);
    }

    if (yEq) {
      y = u1 * 0.0;
    } else if ((u0 < 0.0) != (u1 < 0.0)) {
      y += u1;
    }
  }

  return y;
}

real32_T rt_modf_snf(real32_T u0, real32_T u1)
{
  real32_T y;
  y = u0;
  if (u1 == 0.0F) {
    if (u0 == 0.0F) {
      y = u1;
    }
  } else if (rtIsNaNF(u0) || rtIsNaNF(u1) || rtIsInfF(u0)) {
    y = (rtNaNF);
  } else if (u0 == 0.0F) {
    y = 0.0F / u1;
  } else if (rtIsInfF(u1)) {
    if ((u1 < 0.0F) != (u0 < 0.0F)) {
      y = u1;
    }
  } else {
    boolean_T yEq;
    y = fmodf(u0, u1);
    yEq = (y == 0.0F);
    if ((!yEq) && (u1 > floorf(u1))) {
      real32_T q;
      q = fabsf(u0 / u1);
      yEq = !(fabsf(q - floorf(q + 0.5F)) > FLT_EPSILON * q);
    }

    if (yEq) {
      y = u1 * 0.0F;
    } else if ((u0 < 0.0F) != (u1 < 0.0F)) {
      y += u1;
    }
  }

  return y;
}

/* Model step function */
void Park_test_step(void)
{
  real_T rtb_Mod;
  real_T rtb_Mod_e;
  real32_T rtb_Cos;
  real32_T rtb_Sin;

  /* Outputs for Atomic SubSystem: '<Root>/Park_test' */
  /* Math: '<S10>/Mod' incorporates:
   *  Constant: '<S10>/Constant'
   *  Sum: '<S3>/Sum'
   *  UnitDelay: '<S3>/Unit Delay'
   */
  rtb_Mod = rt_modd_snf(rtDW.UnitDelay_DSTATE + 0.00062831853071795862,
                        6.2831853071795862);

  /* Trigonometry: '<S1>/Sin' incorporates:
   *  DataTypeConversion: '<S1>/Cast To Single'
   */
  rtb_Sin = sinf((real32_T)rtb_Mod);

  /* Outputs for Atomic SubSystem: '<S1>/Clark_test' */
  /* Math: '<S9>/Mod' incorporates:
   *  Constant: '<S9>/Constant'
   *  Sum: '<S8>/Sum'
   *  UnitDelay: '<S8>/Unit Delay'
   */
  rtb_Mod_e = rt_modd_snf(rtDW.UnitDelay_DSTATE_a + 0.00062831853071795862,
    6.2831853071795862);

  /* Trigonometry: '<S7>/Sin' incorporates:
   *  Constant: '<S7>/Constant'
   *  Constant: '<S7>/Constant3'
   *  DataTypeConversion: '<S7>/Cast To Single'
   *  Gain: '<S7>/Gain'
   *  Math: '<S7>/Mod'
   *  Sum: '<S7>/Add'
   */
  ia = arm_sin_f32(-rt_modf_snf((real32_T)(rtb_Mod_e + 2.0943951023931953),
    6.28318548F));

  /* Trigonometry: '<S7>/Sin1' incorporates:
   *  Constant: '<S7>/Constant4'
   *  DataTypeConversion: '<S7>/Cast To Single1'
   *  Gain: '<S7>/Gain1'
   *  Math: '<S7>/Mod1'
   *  Sum: '<S7>/Add1'
   */
  ib = arm_sin_f32(-rt_modf_snf((real32_T)rtb_Mod_e, 6.28318548F));

  /* Trigonometry: '<S7>/Sin2' incorporates:
   *  Constant: '<S7>/Constant5'
   *  DataTypeConversion: '<S7>/Cast To Single2'
   *  Gain: '<S7>/Gain2'
   *  Math: '<S7>/Mod2'
   *  Sum: '<S7>/Add2'
   */
  ic = arm_sin_f32(-rt_modf_snf((real32_T)(rtb_Mod_e - 2.0943951023931953),
    6.28318548F));

  /* MATLAB Function: '<S2>/Clark' */
  ialpha = ((2.0F * ia - ib) - ic) / 3.0F;
  ibeta = (ib - ic) * 1.73205078F / 3.0F;

  /* Update for UnitDelay: '<S8>/Unit Delay' */
  rtDW.UnitDelay_DSTATE_a = rtb_Mod_e;

  /* End of Outputs for SubSystem: '<S1>/Clark_test' */

  /* Trigonometry: '<S1>/Cos' incorporates:
   *  DataTypeConversion: '<S1>/Cast To Single1'
   */
  rtb_Cos = cosf((real32_T)rtb_Mod);

  /* MATLAB Function: '<S1>/Park' */
  id = ialpha * rtb_Cos + ibeta * rtb_Sin;
  iq = -ialpha * rtb_Sin + ibeta * rtb_Cos;

  /* Update for UnitDelay: '<S3>/Unit Delay' */
  rtDW.UnitDelay_DSTATE = rtb_Mod;

  /* End of Outputs for SubSystem: '<Root>/Park_test' */
}

/* Model initialize function */
void Park_test_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
