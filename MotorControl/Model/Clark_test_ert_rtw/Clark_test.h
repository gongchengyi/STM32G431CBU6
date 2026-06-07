/*
 * File: Clark_test.h
 *
 * Code generated for Simulink model 'Clark_test'.
 *
 * Model version                  : 1.3
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Fri May 15 17:11:27 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Clark_test_h_
#define RTW_HEADER_Clark_test_h_
#ifndef Clark_test_COMMON_INCLUDES_
#define Clark_test_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Clark_test_COMMON_INCLUDES_ */

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
  real_T UnitDelay_DSTATE;             /* '<S4>/Unit Delay' */
} DW;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T ialpha;                     /* '<Root>/ialpha' */
  real32_T ibeta;                      /* '<Root>/ibeta' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block signals and states (default storage) */
extern DW rtDW;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real32_T ia;                    /* '<S3>/Sin' */
extern real32_T ib;                    /* '<S3>/Sin1' */
extern real32_T ic;                    /* '<S3>/Sin2' */

/* Model entry point functions */
extern void Clark_test_initialize(void);
extern void Clark_test_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Scope' : Unused code path elimination
 * Block '<S1>/Scope1' : Unused code path elimination
 * Block '<S3>/Scope' : Unused code path elimination
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
 * hilite_system('untitled/Clark_test')    - opens subsystem untitled/Clark_test
 * hilite_system('untitled/Clark_test/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'untitled'
 * '<S1>'   : 'untitled/Clark_test'
 * '<S2>'   : 'untitled/Clark_test/Clark'
 * '<S3>'   : 'untitled/Clark_test/ThreeCurrGenerator'
 * '<S4>'   : 'untitled/Clark_test/ThreeCurrGenerator/FreqGnerator'
 * '<S5>'   : 'untitled/Clark_test/ThreeCurrGenerator/FreqGnerator/RangeLimit'
 */
#endif                                 /* RTW_HEADER_Clark_test_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
