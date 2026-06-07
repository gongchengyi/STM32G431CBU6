/*
 * File: Park_test.h
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

#ifndef RTW_HEADER_Park_test_h_
#define RTW_HEADER_Park_test_h_
#ifndef Park_test_COMMON_INCLUDES_
#define Park_test_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Park_test_COMMON_INCLUDES_ */

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
  real_T UnitDelay_DSTATE;             /* '<S3>/Unit Delay' */
  real_T UnitDelay_DSTATE_a;           /* '<S8>/Unit Delay' */
} DW;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block signals and states (default storage) */
extern DW rtDW;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real32_T id;                    /* '<S1>/Park' */
extern real32_T iq;                    /* '<S1>/Park' */
extern real32_T ia;                    /* '<S7>/Sin' */
extern real32_T ib;                    /* '<S7>/Sin1' */
extern real32_T ic;                    /* '<S7>/Sin2' */
extern real32_T ialpha;                /* '<S2>/Clark' */
extern real32_T ibeta;                 /* '<S2>/Clark' */

/* Model entry point functions */
extern void Park_test_initialize(void);
extern void Park_test_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Scope' : Unused code path elimination
 * Block '<S2>/Scope1' : Unused code path elimination
 * Block '<S7>/Scope' : Unused code path elimination
 * Block '<S1>/Scope' : Unused code path elimination
 * Block '<S1>/Scope1' : Unused code path elimination
 * Block '<S1>/Scope2' : Unused code path elimination
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
 * hilite_system('untitled/Park_test')    - opens subsystem untitled/Park_test
 * hilite_system('untitled/Park_test/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'untitled'
 * '<S1>'   : 'untitled/Park_test'
 * '<S2>'   : 'untitled/Park_test/Clark_test'
 * '<S3>'   : 'untitled/Park_test/FreqGnerator'
 * '<S4>'   : 'untitled/Park_test/InvPark'
 * '<S5>'   : 'untitled/Park_test/Park'
 * '<S6>'   : 'untitled/Park_test/Clark_test/Clark'
 * '<S7>'   : 'untitled/Park_test/Clark_test/ThreeCurrGenerator'
 * '<S8>'   : 'untitled/Park_test/Clark_test/ThreeCurrGenerator/FreqGnerator'
 * '<S9>'   : 'untitled/Park_test/Clark_test/ThreeCurrGenerator/FreqGnerator/RangeLimit'
 * '<S10>'  : 'untitled/Park_test/FreqGnerator/RangeLimit'
 */
#endif                                 /* RTW_HEADER_Park_test_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
