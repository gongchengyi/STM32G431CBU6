/*
 * File: SVPWM.c
 *
 * Code generated for Simulink model 'SVPWM'.
 *
 * Model version                  : 1.9
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Wed May 27 17:57:29 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "SVPWM.h"
#include <math.h>
#include "rtwtypes.h"
#include <stddef.h>
#include <float.h>
#define NumBitsPerChar                 8U

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
extern real_T rt_modd_snf(real_T u0, real_T u1);
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

/* Model step function */
void SVPWM_step(void)
{
  real_T rtb_Fcn2_tmp_tmp;
  real_T rtb_Mod;
  real_T rtb_MultiportSwitch;
  real_T rtb_MultiportSwitch1;
  real_T rtb_MultiportSwitch1_c;
  real_T rtb_MultiportSwitch_c;
  int32_T rtb_N;
  real32_T rtb_Cos;
  real32_T rtb_Sin;
  real32_T rtb_v_alpha;

  /* Outputs for Atomic SubSystem: '<Root>/SVPWM' */
  /* Math: '<S8>/Mod' incorporates:
   *  Constant: '<S8>/Constant'
   *  Gain: '<S2>/Gain'
   *  Inport: '<Root>/Freq'
   *  Sum: '<S2>/Sum'
   *  UnitDelay: '<S2>/Unit Delay'
   */
  rtb_Mod = rt_modd_snf(0.00062831853071795862 * rtU.Freq +
                        rtDW.UnitDelay_DSTATE, 6.2831853071795862);

  /* Trigonometry: '<S1>/Cos' incorporates:
   *  DataTypeConversion: '<S1>/Cast To Single1'
   */
  rtb_Cos = cosf((real32_T)rtb_Mod);

  /* Trigonometry: '<S1>/Sin' incorporates:
   *  DataTypeConversion: '<S1>/Cast To Single'
   */
  rtb_Sin = sinf((real32_T)rtb_Mod);

  /* MATLAB Function: '<S1>/InvPark' incorporates:
   *  Inport: '<Root>/Ud'
   *  Inport: '<Root>/Uq'
   */
  rtb_v_alpha = (real32_T)rtU.Ud * rtb_Cos - (real32_T)rtU.Uq * rtb_Sin;
  rtb_Cos = (real32_T)rtU.Ud * rtb_Sin + (real32_T)rtU.Uq * rtb_Cos;

  /* Fcn: '<S4>/N' incorporates:
   *  Fcn: '<S4>/B0'
   *  Fcn: '<S4>/B1'
   *  Fcn: '<S4>/B2'
   *  Switch: '<S4>/Switch'
   *  Switch: '<S4>/Switch1'
   *  Switch: '<S4>/Switch2'
   */
  rtb_N = ((-rtb_v_alpha * 0.866025388F - rtb_Cos * 0.5F >= 0.0F) * (int32_T)4.0
           + (rtb_v_alpha * 0.866025388F - 0.5F * rtb_Cos >= 0.0F) * (int32_T)
           2.0) + (rtb_Cos >= 0.0F);

  /* Gain: '<S7>/Gain2' */
  rtb_Sin = 0.866025388F * rtb_Cos;

  /* Gain: '<S7>/Gain' */
  rtb_v_alpha *= 1.5F;

  /* Product: '<S7>/Product' incorporates:
   *  Inport: '<Root>/Ts'
   *  Inport: '<Root>/Udc'
   *  Math: '<S7>/Math Function'
   *
   * About '<S7>/Math Function':
   *  Operator: reciprocal
   */
  rtb_MultiportSwitch_c = 1.0F / rtU.Udc * rtU.Ts;

  /* MultiPortSwitch: '<S5>/Multiport Switch' incorporates:
   *  Gain: '<S5>/Gain'
   *  Gain: '<S5>/Gain1'
   *  Gain: '<S5>/Gain2'
   *  Gain: '<S7>/Gain1'
   *  Product: '<S7>/Product1'
   *  Product: '<S7>/Product2'
   *  Product: '<S7>/Product3'
   *  Sum: '<S7>/Add'
   *  Sum: '<S7>/Add1'
   */
  switch (rtb_N) {
   case 1:
    rtb_MultiportSwitch = (rtb_Sin - rtb_v_alpha) * rtb_MultiportSwitch_c;

    /* MultiPortSwitch: '<S5>/Multiport Switch1' incorporates:
     *  Product: '<S7>/Product2'
     *  Product: '<S7>/Product3'
     *  Sum: '<S7>/Add'
     *  Sum: '<S7>/Add1'
     */
    rtb_MultiportSwitch1 = (rtb_Sin + rtb_v_alpha) * rtb_MultiportSwitch_c;
    break;

   case 2:
    rtb_MultiportSwitch = (rtb_Sin + rtb_v_alpha) * rtb_MultiportSwitch_c;

    /* MultiPortSwitch: '<S5>/Multiport Switch1' incorporates:
     *  Gain: '<S5>/Gain'
     *  Gain: '<S7>/Gain1'
     *  Product: '<S7>/Product1'
     *  Product: '<S7>/Product3'
     *  Sum: '<S7>/Add'
     */
    rtb_MultiportSwitch1 = -(1.73205078F * rtb_Cos * rtb_MultiportSwitch_c);
    break;

   case 3:
    rtb_MultiportSwitch = -((rtb_Sin - rtb_v_alpha) * rtb_MultiportSwitch_c);

    /* MultiPortSwitch: '<S5>/Multiport Switch1' incorporates:
     *  Gain: '<S5>/Gain2'
     *  Gain: '<S7>/Gain1'
     *  Product: '<S7>/Product1'
     *  Product: '<S7>/Product2'
     *  Sum: '<S7>/Add1'
     */
    rtb_MultiportSwitch1 = 1.73205078F * rtb_Cos * rtb_MultiportSwitch_c;
    break;

   case 4:
    rtb_MultiportSwitch = -(1.73205078F * rtb_Cos * rtb_MultiportSwitch_c);

    /* MultiPortSwitch: '<S5>/Multiport Switch1' incorporates:
     *  Gain: '<S5>/Gain'
     *  Gain: '<S7>/Gain1'
     *  Product: '<S7>/Product1'
     *  Product: '<S7>/Product2'
     *  Sum: '<S7>/Add1'
     */
    rtb_MultiportSwitch1 = (rtb_Sin - rtb_v_alpha) * rtb_MultiportSwitch_c;
    break;

   case 5:
    rtb_MultiportSwitch = 1.73205078F * rtb_Cos * rtb_MultiportSwitch_c;

    /* MultiPortSwitch: '<S5>/Multiport Switch1' incorporates:
     *  Gain: '<S5>/Gain1'
     *  Gain: '<S7>/Gain1'
     *  Product: '<S7>/Product1'
     *  Product: '<S7>/Product3'
     *  Sum: '<S7>/Add'
     */
    rtb_MultiportSwitch1 = -((rtb_Sin + rtb_v_alpha) * rtb_MultiportSwitch_c);
    break;

   default:
    rtb_MultiportSwitch = -((rtb_Sin + rtb_v_alpha) * rtb_MultiportSwitch_c);

    /* MultiPortSwitch: '<S5>/Multiport Switch1' incorporates:
     *  Gain: '<S5>/Gain1'
     *  Gain: '<S5>/Gain2'
     *  Product: '<S7>/Product2'
     *  Product: '<S7>/Product3'
     *  Sum: '<S7>/Add'
     *  Sum: '<S7>/Add1'
     */
    rtb_MultiportSwitch1 = -((rtb_Sin - rtb_v_alpha) * rtb_MultiportSwitch_c);
    break;
  }

  /* End of MultiPortSwitch: '<S5>/Multiport Switch' */

  /* Fcn: '<S5>/Fcn' incorporates:
   *  Inport: '<Root>/Ts'
   */
  rtb_MultiportSwitch_c = (rtU.Ts - rtb_MultiportSwitch1) - rtb_MultiportSwitch;

  /* Switch: '<S5>/Switch' incorporates:
   *  Fcn: '<S5>/Fcn1'
   *  Inport: '<Root>/Ts'
   */
  if (rtb_MultiportSwitch_c >= 0.0) {
    rtb_MultiportSwitch1_c = rtb_MultiportSwitch;
  } else {
    rtb_MultiportSwitch1_c = rtb_MultiportSwitch * rtU.Ts / (rtb_MultiportSwitch
      + rtb_MultiportSwitch1);
  }

  /* End of Switch: '<S5>/Switch' */

  /* Switch: '<S5>/Switch1' incorporates:
   *  Fcn: '<S5>/Fcn2'
   *  Inport: '<Root>/Ts'
   */
  if (rtb_MultiportSwitch_c > 0.0) {
    rtb_MultiportSwitch_c = rtb_MultiportSwitch1;
  } else {
    rtb_MultiportSwitch_c = rtb_MultiportSwitch1 * rtU.Ts / (rtb_MultiportSwitch
      + rtb_MultiportSwitch1);
  }

  /* End of Switch: '<S5>/Switch1' */

  /* Fcn: '<S6>/Fcn1' incorporates:
   *  Inport: '<Root>/Ts'
   */
  rtb_MultiportSwitch = ((rtU.Ts + rtb_MultiportSwitch1_c) -
    rtb_MultiportSwitch_c) / 4.0;

  /* Fcn: '<S6>/Fcn' incorporates:
   *  Inport: '<Root>/Ts'
   */
  rtb_MultiportSwitch1 = ((rtU.Ts - rtb_MultiportSwitch1_c) -
    rtb_MultiportSwitch_c) / 4.0;

  /* Fcn: '<S6>/Fcn2' incorporates:
   *  Inport: '<Root>/Ts'
   */
  rtb_Fcn2_tmp_tmp = ((rtU.Ts + rtb_MultiportSwitch_c) + rtb_MultiportSwitch1_c)
    / 4.0;

  /* MultiPortSwitch: '<S6>/Multiport Switch' incorporates:
   *  Fcn: '<S6>/Fcn1'
   *  Fcn: '<S6>/Fcn2'
   *  Inport: '<Root>/Ts'
   */
  switch (rtb_N) {
   case 1:
    rtb_MultiportSwitch_c = ((rtU.Ts + rtb_MultiportSwitch1_c) -
      rtb_MultiportSwitch_c) / 4.0;

    /* MultiPortSwitch: '<S6>/Multiport Switch1' incorporates:
     *  Fcn: '<S6>/Fcn'
     *  Fcn: '<S6>/Fcn1'
     *  Inport: '<Root>/Ts'
     */
    rtb_MultiportSwitch1_c = rtb_MultiportSwitch1;

    /* MultiPortSwitch: '<S6>/Multiport Switch2' incorporates:
     *  Fcn: '<S6>/Fcn2'
     */
    rtb_MultiportSwitch1 = rtb_Fcn2_tmp_tmp;
    break;

   case 2:
    rtb_MultiportSwitch_c = rtb_MultiportSwitch1;

    /* MultiPortSwitch: '<S6>/Multiport Switch1' incorporates:
     *  Fcn: '<S6>/Fcn2'
     */
    rtb_MultiportSwitch1_c = rtb_Fcn2_tmp_tmp;

    /* MultiPortSwitch: '<S6>/Multiport Switch2' incorporates:
     *  Fcn: '<S6>/Fcn1'
     */
    rtb_MultiportSwitch1 = rtb_MultiportSwitch;
    break;

   case 3:
    rtb_MultiportSwitch_c = rtb_MultiportSwitch1;

    /* MultiPortSwitch: '<S6>/Multiport Switch1' incorporates:
     *  Fcn: '<S6>/Fcn1'
     */
    rtb_MultiportSwitch1_c = rtb_MultiportSwitch;

    /* MultiPortSwitch: '<S6>/Multiport Switch2' incorporates:
     *  Fcn: '<S6>/Fcn2'
     */
    rtb_MultiportSwitch1 = rtb_Fcn2_tmp_tmp;
    break;

   case 4:
    rtb_MultiportSwitch_c = ((rtU.Ts + rtb_MultiportSwitch_c) +
      rtb_MultiportSwitch1_c) / 4.0;

    /* MultiPortSwitch: '<S6>/Multiport Switch1' incorporates:
     *  Fcn: '<S6>/Fcn1'
     *  Fcn: '<S6>/Fcn2'
     *  Inport: '<Root>/Ts'
     */
    rtb_MultiportSwitch1_c = rtb_MultiportSwitch;
    break;

   case 5:
    rtb_MultiportSwitch_c = ((rtU.Ts + rtb_MultiportSwitch_c) +
      rtb_MultiportSwitch1_c) / 4.0;

    /* MultiPortSwitch: '<S6>/Multiport Switch1' incorporates:
     *  Fcn: '<S6>/Fcn'
     *  Fcn: '<S6>/Fcn2'
     *  Inport: '<Root>/Ts'
     */
    rtb_MultiportSwitch1_c = rtb_MultiportSwitch1;

    /* MultiPortSwitch: '<S6>/Multiport Switch2' incorporates:
     *  Fcn: '<S6>/Fcn1'
     */
    rtb_MultiportSwitch1 = rtb_MultiportSwitch;
    break;

   default:
    rtb_MultiportSwitch_c = ((rtU.Ts + rtb_MultiportSwitch1_c) -
      rtb_MultiportSwitch_c) / 4.0;

    /* MultiPortSwitch: '<S6>/Multiport Switch1' incorporates:
     *  Fcn: '<S6>/Fcn1'
     *  Fcn: '<S6>/Fcn2'
     *  Inport: '<Root>/Ts'
     */
    rtb_MultiportSwitch1_c = rtb_Fcn2_tmp_tmp;
    break;
  }

  /* End of MultiPortSwitch: '<S6>/Multiport Switch' */

  /* Update for UnitDelay: '<S2>/Unit Delay' */
  rtDW.UnitDelay_DSTATE = rtb_Mod;

  /* Outport: '<Root>/Tabc' incorporates:
   *  Gain: '<S1>/Gain'
   *  Inport: '<Root>/ARR'
   *  Inport: '<Root>/Ts'
   *  Product: '<S1>/Divide'
   *  Product: '<S1>/Divide1'
   *  Product: '<S1>/Divide2'
   */
  rtY.Tabc[0] = 2.0 * rtb_MultiportSwitch_c / rtU.Ts * rtU.ARR;
  rtY.Tabc[1] = 2.0 * rtb_MultiportSwitch1_c / rtU.Ts * rtU.ARR;
  rtY.Tabc[2] = 2.0 * rtb_MultiportSwitch1 / rtU.Ts * rtU.ARR;

  /* End of Outputs for SubSystem: '<Root>/SVPWM' */
}

/* Model initialize function */
void SVPWM_initialize(void)
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
