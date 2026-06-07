/*
 * File: SVPWM.h
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

#ifndef RTW_HEADER_SVPWM_h_
#define RTW_HEADER_SVPWM_h_
#ifndef SVPWM_COMMON_INCLUDES_
#define SVPWM_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* SVPWM_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T UnitDelay_DSTATE;             /* '<S2>/Unit Delay' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T Ud;                           /* '<Root>/Ud' */
  real_T Uq;                           /* '<Root>/Uq' */
  real_T Freq;                         /* '<Root>/Freq' */
  real_T Ts;                           /* '<Root>/Ts' */
  real32_T Udc;                        /* '<Root>/Udc' */
  real_T ARR;                          /* '<Root>/ARR' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Tabc[3];                      /* '<Root>/Tabc' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* Model entry point functions */
extern void SVPWM_initialize(void);
extern void SVPWM_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/N' : Unused code path elimination
 * Block '<S1>/Scope1' : Unused code path elimination
 * Block '<S1>/Scope2' : Unused code path elimination
 * Block '<S1>/Scope3' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('VF/SVPWM')    - opens subsystem VF/SVPWM
 * hilite_system('VF/SVPWM/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'VF'
 * '<S1>'   : 'VF/SVPWM'
 * '<S2>'   : 'VF/SVPWM/FreqGnerator'
 * '<S3>'   : 'VF/SVPWM/InvPark'
 * '<S4>'   : 'VF/SVPWM/Sector Caculate'
 * '<S5>'   : 'VF/SVPWM/T1T1 Caculate'
 * '<S6>'   : 'VF/SVPWM/Tcm Caculate'
 * '<S7>'   : 'VF/SVPWM/XYZ Caculate'
 * '<S8>'   : 'VF/SVPWM/FreqGnerator/RangeLimit'
 */
#endif                                 /* RTW_HEADER_SVPWM_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
