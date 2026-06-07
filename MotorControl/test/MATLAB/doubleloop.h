/*
 * File: doubleloop.h
 *
 * Code generated for Simulink model 'doubleloop'.
 *
 * Model version                  : 1.4
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Sat Jun  6 11:09:47 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_doubleloop_h_
#define RTW_HEADER_doubleloop_h_
#ifndef doubleloop_COMMON_INCLUDES_
#define doubleloop_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* doubleloop_COMMON_INCLUDES_ */

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
  real32_T Merge;                      /* '<S2>/Merge' */
  real32_T Merge1;                     /* '<S2>/Merge1' */
  real32_T Merge2;                     /* '<S2>/Merge2' */
  real32_T Saturation;                 /* '<S159>/Saturation' */
  real32_T SpeedReset;                 /* '<S2>/Chart' */
  real32_T UnitDelay_DSTATE;           /* '<S1>/Unit Delay' */
  real32_T Integrator_DSTATE;          /* '<S46>/Integrator' */
  real32_T Integrator_DSTATE_p;        /* '<S96>/Integrator' */
  real32_T UnitDelay_DSTATE_a;         /* '<S118>/Unit Delay' */
  real32_T Integrator_DSTATE_e;        /* '<S152>/Integrator' */
  real32_T Integrator_PREV_U;          /* '<S152>/Integrator' */
  uint32_T SpeedLoop_PREV_T;           /* '<S1>/SpeedLoop' */
  uint16_T temporalCounter_i1;         /* '<S2>/Chart' */
  int8_T Integrator_PrevResetState;    /* '<S152>/Integrator' */
  uint8_T Integrator_SYSTEM_ENABLE;    /* '<S152>/Integrator' */
  uint8_T is_active_c3_doubleloop;     /* '<S2>/Chart' */
  uint8_T is_c3_doubleloop;            /* '<S2>/Chart' */
  boolean_T SpeedLoop_RESET_ELAPS_T;   /* '<S1>/SpeedLoop' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T ia;                         /* '<Root>/ia' */
  real32_T ib;                         /* '<Root>/ib' */
  real32_T ic;                         /* '<Root>/ic' */
  real32_T Encoder_Theta;              /* '<Root>/Encoder_Theta' */
  real32_T SpeedRef;                   /* '<Root>/SpeedRef' */
  real32_T Udc;                        /* '<Root>/Udc' */
  real32_T Motor_OnOff;                /* '<Root>/Motor_OnOff' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T Tabc[3];                    /* '<Root>/Tabc' */
} ExtY;

/* Type definition for custom storage class: Struct */
typedef struct currkpki_tag {
  real32_T curr_ki;                    /* Referenced by:
                                        * '<S7>/Constant3'
                                        * '<S7>/Constant4'
                                        */
  real32_T curr_kp;                    /* Referenced by:
                                        * '<S7>/Constant1'
                                        * '<S7>/Constant2'
                                        */
} currkpki_type;

typedef struct spdkpki_tag {
  real32_T spd_ki;                   /* Referenced by: '<S149>/Integral Gain' */
  real32_T spd_kp;               /* Referenced by: '<S157>/Proportional Gain' */
} spdkpki_type;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick1;
    struct {
      uint8_T TID[2];
    } TaskCounters;
  } Timing;
};

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

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
extern real32_T SpeedFd;               /* '<S118>/Gain1' */
extern real32_T Motor_state;           /* '<S2>/Chart' */

/* Model entry point functions */
extern void doubleloop_initialize(void);
extern void doubleloop_step(void);

/* Exported data declaration */

/* Declaration for custom storage class: Struct */
extern currkpki_type currkpki;
extern spdkpki_type spdkpki;

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S9>/N' : Unused code path elimination
 * Block '<S9>/Scope1' : Unused code path elimination
 * Block '<S9>/Scope2' : Unused code path elimination
 * Block '<S9>/Scope3' : Unused code path elimination
 * Block '<S2>/Cast To Single' : Eliminate redundant data type conversion
 * Block '<S2>/Cast To Single1' : Eliminate redundant data type conversion
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
 * hilite_system('SpeedLoop/doubleloop')    - opens subsystem SpeedLoop/doubleloop
 * hilite_system('SpeedLoop/doubleloop/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'SpeedLoop'
 * '<S1>'   : 'SpeedLoop/doubleloop'
 * '<S2>'   : 'SpeedLoop/doubleloop/CurrentLoop'
 * '<S3>'   : 'SpeedLoop/doubleloop/SpeedLoop'
 * '<S4>'   : 'SpeedLoop/doubleloop/CurrentLoop/Chart'
 * '<S5>'   : 'SpeedLoop/doubleloop/CurrentLoop/Clark'
 * '<S6>'   : 'SpeedLoop/doubleloop/CurrentLoop/MATLAB Function'
 * '<S7>'   : 'SpeedLoop/doubleloop/CurrentLoop/PID controller'
 * '<S8>'   : 'SpeedLoop/doubleloop/CurrentLoop/Park'
 * '<S9>'   : 'SpeedLoop/doubleloop/CurrentLoop/SVPWM'
 * '<S10>'  : 'SpeedLoop/doubleloop/CurrentLoop/Switch Case Action Subsystem'
 * '<S11>'  : 'SpeedLoop/doubleloop/CurrentLoop/Switch Case Action Subsystem1'
 * '<S12>'  : 'SpeedLoop/doubleloop/CurrentLoop/Switch Case Action Subsystem2'
 * '<S13>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller'
 * '<S14>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1'
 * '<S15>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Anti-windup'
 * '<S16>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/D Gain'
 * '<S17>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Filter'
 * '<S18>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Filter ICs'
 * '<S19>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/I Gain'
 * '<S20>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Ideal P Gain'
 * '<S21>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Ideal P Gain Fdbk'
 * '<S22>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Integrator'
 * '<S23>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Integrator ICs'
 * '<S24>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/N Copy'
 * '<S25>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/N Gain'
 * '<S26>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/P Copy'
 * '<S27>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Parallel P Gain'
 * '<S28>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Reset Signal'
 * '<S29>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Saturation'
 * '<S30>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Saturation Fdbk'
 * '<S31>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Sum'
 * '<S32>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Sum Fdbk'
 * '<S33>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Tracking Mode'
 * '<S34>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Tracking Mode Sum'
 * '<S35>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Tsamp - Integral'
 * '<S36>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Tsamp - Ngain'
 * '<S37>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/postSat Signal'
 * '<S38>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/preSat Signal'
 * '<S39>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Anti-windup/Passthrough'
 * '<S40>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/D Gain/Disabled'
 * '<S41>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Filter/Disabled'
 * '<S42>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Filter ICs/Disabled'
 * '<S43>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/I Gain/External Parameters'
 * '<S44>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Ideal P Gain/Passthrough'
 * '<S45>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S46>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Integrator/Discrete'
 * '<S47>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Integrator ICs/Internal IC'
 * '<S48>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/N Copy/Disabled wSignal Specification'
 * '<S49>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/N Gain/Disabled'
 * '<S50>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/P Copy/Disabled'
 * '<S51>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Parallel P Gain/External Parameters'
 * '<S52>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Reset Signal/Disabled'
 * '<S53>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Saturation/Passthrough'
 * '<S54>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Saturation Fdbk/Disabled'
 * '<S55>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Sum/Sum_PI'
 * '<S56>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Sum Fdbk/Disabled'
 * '<S57>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Tracking Mode/Disabled'
 * '<S58>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Tracking Mode Sum/Passthrough'
 * '<S59>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S60>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/Tsamp - Ngain/Passthrough'
 * '<S61>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/postSat Signal/Forward_Path'
 * '<S62>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller/preSat Signal/Forward_Path'
 * '<S63>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Anti-windup'
 * '<S64>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/D Gain'
 * '<S65>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Filter'
 * '<S66>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Filter ICs'
 * '<S67>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/I Gain'
 * '<S68>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Ideal P Gain'
 * '<S69>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Ideal P Gain Fdbk'
 * '<S70>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Integrator'
 * '<S71>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Integrator ICs'
 * '<S72>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/N Copy'
 * '<S73>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/N Gain'
 * '<S74>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/P Copy'
 * '<S75>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Parallel P Gain'
 * '<S76>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Reset Signal'
 * '<S77>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Saturation'
 * '<S78>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Saturation Fdbk'
 * '<S79>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Sum'
 * '<S80>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Sum Fdbk'
 * '<S81>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Tracking Mode'
 * '<S82>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Tracking Mode Sum'
 * '<S83>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Tsamp - Integral'
 * '<S84>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Tsamp - Ngain'
 * '<S85>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/postSat Signal'
 * '<S86>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/preSat Signal'
 * '<S87>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Anti-windup/Disc. Clamping Parallel'
 * '<S88>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S89>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S90>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/D Gain/Disabled'
 * '<S91>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Filter/Disabled'
 * '<S92>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Filter ICs/Disabled'
 * '<S93>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/I Gain/External Parameters'
 * '<S94>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Ideal P Gain/Passthrough'
 * '<S95>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S96>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Integrator/Discrete'
 * '<S97>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Integrator ICs/Internal IC'
 * '<S98>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/N Copy/Disabled wSignal Specification'
 * '<S99>'  : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/N Gain/Disabled'
 * '<S100>' : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/P Copy/Disabled'
 * '<S101>' : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Parallel P Gain/External Parameters'
 * '<S102>' : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Reset Signal/Disabled'
 * '<S103>' : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Saturation/Enabled'
 * '<S104>' : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Saturation Fdbk/Disabled'
 * '<S105>' : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Sum/Sum_PI'
 * '<S106>' : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Sum Fdbk/Disabled'
 * '<S107>' : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Tracking Mode/Disabled'
 * '<S108>' : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S109>' : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Tsamp - Integral/TsSignalSpecification'
 * '<S110>' : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/Tsamp - Ngain/Passthrough'
 * '<S111>' : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/postSat Signal/Forward_Path'
 * '<S112>' : 'SpeedLoop/doubleloop/CurrentLoop/PID controller/Discrete PID Controller1/preSat Signal/Forward_Path'
 * '<S113>' : 'SpeedLoop/doubleloop/CurrentLoop/SVPWM/Sector Caculate'
 * '<S114>' : 'SpeedLoop/doubleloop/CurrentLoop/SVPWM/T1T1 Caculate'
 * '<S115>' : 'SpeedLoop/doubleloop/CurrentLoop/SVPWM/Tcm Caculate'
 * '<S116>' : 'SpeedLoop/doubleloop/CurrentLoop/SVPWM/XYZ Caculate'
 * '<S117>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller'
 * '<S118>' : 'SpeedLoop/doubleloop/SpeedLoop/thetatospeed'
 * '<S119>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Anti-windup'
 * '<S120>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/D Gain'
 * '<S121>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Filter'
 * '<S122>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Filter ICs'
 * '<S123>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/I Gain'
 * '<S124>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Ideal P Gain'
 * '<S125>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Ideal P Gain Fdbk'
 * '<S126>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Integrator'
 * '<S127>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Integrator ICs'
 * '<S128>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/N Copy'
 * '<S129>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/N Gain'
 * '<S130>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/P Copy'
 * '<S131>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Parallel P Gain'
 * '<S132>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Reset Signal'
 * '<S133>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Saturation'
 * '<S134>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Saturation Fdbk'
 * '<S135>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Sum'
 * '<S136>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Sum Fdbk'
 * '<S137>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Tracking Mode'
 * '<S138>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Tracking Mode Sum'
 * '<S139>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Tsamp - Integral'
 * '<S140>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Tsamp - Ngain'
 * '<S141>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/postSat Signal'
 * '<S142>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/preSat Signal'
 * '<S143>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Anti-windup/Disc. Clamping Parallel'
 * '<S144>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S145>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S146>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/D Gain/Disabled'
 * '<S147>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Filter/Disabled'
 * '<S148>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Filter ICs/Disabled'
 * '<S149>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/I Gain/Internal Parameters'
 * '<S150>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Ideal P Gain/Passthrough'
 * '<S151>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S152>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Integrator/Discrete'
 * '<S153>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Integrator ICs/Internal IC'
 * '<S154>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/N Copy/Disabled wSignal Specification'
 * '<S155>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/N Gain/Disabled'
 * '<S156>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/P Copy/Disabled'
 * '<S157>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Parallel P Gain/Internal Parameters'
 * '<S158>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Reset Signal/External Reset'
 * '<S159>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Saturation/Enabled'
 * '<S160>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Saturation Fdbk/Disabled'
 * '<S161>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Sum/Sum_PI'
 * '<S162>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Sum Fdbk/Disabled'
 * '<S163>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Tracking Mode/Disabled'
 * '<S164>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Tracking Mode Sum/Passthrough'
 * '<S165>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S166>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/Tsamp - Ngain/Passthrough'
 * '<S167>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/postSat Signal/Forward_Path'
 * '<S168>' : 'SpeedLoop/doubleloop/SpeedLoop/Discrete PID Controller/preSat Signal/Forward_Path'
 * '<S169>' : 'SpeedLoop/doubleloop/SpeedLoop/thetatospeed/AngleLimit'
 * '<S170>' : 'SpeedLoop/doubleloop/SpeedLoop/thetatospeed/AngleLimit/If Action Subsystem'
 * '<S171>' : 'SpeedLoop/doubleloop/SpeedLoop/thetatospeed/AngleLimit/If Action Subsystem1'
 * '<S172>' : 'SpeedLoop/doubleloop/SpeedLoop/thetatospeed/AngleLimit/If Action Subsystem2'
 */
#endif                                 /* RTW_HEADER_doubleloop_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
