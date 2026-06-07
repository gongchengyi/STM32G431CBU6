/*
 * File: doubleloop.c
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

#include "doubleloop.h"
#include "rtwtypes.h"
#include <math.h>

/* Named constants for Chart: '<S2>/Chart' */
#define IN_AlignStage                  ((uint8_T)1U)
#define IN_IDLE                        ((uint8_T)2U)
#define IN_RunStage                    ((uint8_T)3U)

/* Exported block signals */
real32_T SpeedFd;                      /* '<S118>/Gain1' */
real32_T Motor_state;                  /* '<S2>/Chart' */

/* Exported data definition */

/* Definition for custom storage class: Struct */
currkpki_type currkpki = {
  /* curr_ki */
  2.3F,

  /* curr_kp */
  0.0008F
};

spdkpki_type spdkpki = {
  /* spd_ki */
  0.021F,

  /* spd_kp */
  0.013F
};

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
static void rate_scheduler(void);

/*
 *         This function updates active task flag for each subrate.
 *         The function is called at model base rate, hence the
 *         generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (rtM->Timing.TaskCounters.TID[1])++;
  if ((rtM->Timing.TaskCounters.TID[1]) > 9) {/* Sample time: [0.001s, 0.0s] */
    rtM->Timing.TaskCounters.TID[1] = 0;
  }
}

/* Model step function */
void doubleloop_step(void)
{
  int32_T rtb_N;
  real32_T Integrator;
  real32_T UnitDelay;
  real32_T rtb_DeadZone;
  real32_T rtb_IntegralGain;
  real32_T rtb_Saturation;
  real32_T rtb_Sum;
  real32_T rtb_Sum_e;
  real32_T rtb_u_alpha;
  uint32_T SpeedLoop_ELAPS_T;
  int8_T tmp;
  int8_T tmp_0;

  /* Outputs for Atomic SubSystem: '<Root>/doubleloop' */
  /* Chart: '<S2>/Chart' incorporates:
   *  Inport: '<Root>/Motor_OnOff'
   */
  if (rtDW.temporalCounter_i1 < 2047U) {
    rtDW.temporalCounter_i1++;
  }

  if (rtDW.is_active_c3_doubleloop == 0U) {
    rtDW.is_active_c3_doubleloop = 1U;
    rtDW.is_c3_doubleloop = IN_IDLE;
  } else {
    switch (rtDW.is_c3_doubleloop) {
     case IN_AlignStage:
      rtDW.SpeedReset = 0.0F;
      if (rtDW.temporalCounter_i1 >= 2000) {
        rtDW.is_c3_doubleloop = IN_RunStage;
        rtDW.SpeedReset = 1.0F;
      } else if (rtU.Motor_OnOff == 0.0F) {
        rtDW.is_c3_doubleloop = IN_IDLE;
      } else {
        Motor_state = 2.0F;
      }
      break;

     case IN_IDLE:
      if (rtU.Motor_OnOff == 1.0F) {
        rtDW.temporalCounter_i1 = 0U;
        rtDW.is_c3_doubleloop = IN_AlignStage;
        rtDW.SpeedReset = 0.0F;
      } else {
        Motor_state = 1.0F;
      }
      break;

     default:
      /* case IN_RunStage: */
      rtDW.SpeedReset = 1.0F;
      if (rtU.Motor_OnOff == 0.0F) {
        rtDW.is_c3_doubleloop = IN_IDLE;
      } else {
        Motor_state = 3.0F;
      }
      break;
    }
  }

  /* End of Chart: '<S2>/Chart' */

  /* UnitDelay: '<S1>/Unit Delay' */
  UnitDelay = rtDW.UnitDelay_DSTATE;
  if (rtM->Timing.TaskCounters.TID[1] == 0) {
    /* S-Function (fcgen): '<S1>/Function-Call Generator' incorporates:
     *  SubSystem: '<S1>/SpeedLoop'
     */
    if (rtDW.SpeedLoop_RESET_ELAPS_T) {
      SpeedLoop_ELAPS_T = 0U;
    } else {
      SpeedLoop_ELAPS_T = rtM->Timing.clockTick1 - rtDW.SpeedLoop_PREV_T;
    }

    rtDW.SpeedLoop_PREV_T = rtM->Timing.clockTick1;
    rtDW.SpeedLoop_RESET_ELAPS_T = false;

    /* Sum: '<S118>/Sum' incorporates:
     *  Inport: '<Root>/Encoder_Theta'
     *  UnitDelay: '<S118>/Unit Delay'
     */
    rtb_Sum_e = rtU.Encoder_Theta - rtDW.UnitDelay_DSTATE_a;

    /* If: '<S169>/If' incorporates:
     *  Constant: '<S170>/Constant'
     *  Constant: '<S171>/Constant'
     *  Gain: '<S118>/Gain'
     *  Gain: '<S118>/Gain1'
     *  Gain: '<S170>/Gain'
     *  Gain: '<S171>/Gain'
     *  Gain: '<S172>/Gain'
     *  Sum: '<S170>/Subtract'
     *  Sum: '<S171>/Subtract'
     */
    if (rtb_Sum_e > 4.2F) {
      /* Outputs for IfAction SubSystem: '<S169>/If Action Subsystem' incorporates:
       *  ActionPort: '<S170>/Action Port'
       */
      rtb_Sum_e = (rtb_Sum_e - 6.28318548F) * 1000.0F;

      /* End of Outputs for SubSystem: '<S169>/If Action Subsystem' */
    } else if (rtb_Sum_e < -4.2F) {
      /* Outputs for IfAction SubSystem: '<S169>/If Action Subsystem1' incorporates:
       *  ActionPort: '<S171>/Action Port'
       */
      rtb_Sum_e = (rtb_Sum_e + 6.28318548F) * 1000.0F;

      /* End of Outputs for SubSystem: '<S169>/If Action Subsystem1' */
    } else {
      /* Outputs for IfAction SubSystem: '<S169>/If Action Subsystem2' incorporates:
       *  ActionPort: '<S172>/Action Port'
       */
      rtb_Sum_e *= 1000.0F;

      /* End of Outputs for SubSystem: '<S169>/If Action Subsystem2' */
    }

    SpeedFd = 9.54929638F * rtb_Sum_e * 0.25F;

    /* End of If: '<S169>/If' */

    /* Sum: '<S3>/Sum' incorporates:
     *  Inport: '<Root>/SpeedRef'
     */
    rtb_Sum_e = rtU.SpeedRef - SpeedFd;

    /* Gain: '<S149>/Integral Gain' */
    rtb_IntegralGain = spdkpki.spd_ki * rtb_Sum_e;

    /* DiscreteIntegrator: '<S152>/Integrator' */
    if (rtDW.Integrator_SYSTEM_ENABLE != 0) {
      /* DiscreteIntegrator: '<S152>/Integrator' */
      Integrator = rtDW.Integrator_DSTATE_e;
    } else if ((UnitDelay > 0.0F) && (rtDW.Integrator_PrevResetState <= 0)) {
      /* DiscreteIntegrator: '<S152>/Integrator' */
      Integrator = 0.0F;
    } else {
      /* DiscreteIntegrator: '<S152>/Integrator' */
      Integrator = 0.001F * (real32_T)SpeedLoop_ELAPS_T * rtDW.Integrator_PREV_U
        + rtDW.Integrator_DSTATE_e;
    }

    /* End of DiscreteIntegrator: '<S152>/Integrator' */

    /* Sum: '<S161>/Sum' incorporates:
     *  Gain: '<S157>/Proportional Gain'
     */
    rtb_Sum_e = spdkpki.spd_kp * rtb_Sum_e + Integrator;

    /* DeadZone: '<S145>/DeadZone' incorporates:
     *  Saturate: '<S159>/Saturation'
     */
    if (rtb_Sum_e > 20.0F) {
      rtb_DeadZone = rtb_Sum_e - 20.0F;

      /* Saturate: '<S159>/Saturation' */
      rtDW.Saturation = 20.0F;
    } else {
      if (rtb_Sum_e >= -20.0F) {
        rtb_DeadZone = 0.0F;
      } else {
        rtb_DeadZone = rtb_Sum_e - -20.0F;
      }

      if (rtb_Sum_e < -20.0F) {
        /* Saturate: '<S159>/Saturation' */
        rtDW.Saturation = -20.0F;
      } else {
        /* Saturate: '<S159>/Saturation' */
        rtDW.Saturation = rtb_Sum_e;
      }
    }

    /* End of DeadZone: '<S145>/DeadZone' */

    /* Update for UnitDelay: '<S118>/Unit Delay' incorporates:
     *  Inport: '<Root>/Encoder_Theta'
     */
    rtDW.UnitDelay_DSTATE_a = rtU.Encoder_Theta;

    /* Update for DiscreteIntegrator: '<S152>/Integrator' */
    rtDW.Integrator_SYSTEM_ENABLE = 0U;
    rtDW.Integrator_DSTATE_e = Integrator;
    if (UnitDelay > 0.0F) {
      rtDW.Integrator_PrevResetState = 1;
    } else if (UnitDelay < 0.0F) {
      rtDW.Integrator_PrevResetState = -1;
    } else if (UnitDelay == 0.0F) {
      rtDW.Integrator_PrevResetState = 0;
    } else {
      rtDW.Integrator_PrevResetState = 2;
    }

    /* Switch: '<S143>/Switch1' incorporates:
     *  Constant: '<S143>/Clamping_zero'
     *  Constant: '<S143>/Constant'
     *  Constant: '<S143>/Constant2'
     *  RelationalOperator: '<S143>/fix for DT propagation issue'
     */
    if (rtb_DeadZone > 0.0F) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    /* Switch: '<S143>/Switch2' incorporates:
     *  Constant: '<S143>/Clamping_zero'
     *  Constant: '<S143>/Constant3'
     *  Constant: '<S143>/Constant4'
     *  RelationalOperator: '<S143>/fix for DT propagation issue1'
     */
    if (rtb_IntegralGain > 0.0F) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    /* Switch: '<S143>/Switch' incorporates:
     *  Constant: '<S143>/Clamping_zero'
     *  Logic: '<S143>/AND3'
     *  RelationalOperator: '<S143>/Equal1'
     *  RelationalOperator: '<S143>/Relational Operator'
     *  Switch: '<S143>/Switch1'
     *  Switch: '<S143>/Switch2'
     */
    if ((rtb_DeadZone != 0.0F) && (tmp == tmp_0)) {
      /* Update for DiscreteIntegrator: '<S152>/Integrator' incorporates:
       *  Constant: '<S143>/Constant1'
       */
      rtDW.Integrator_PREV_U = 0.0F;
    } else {
      /* Update for DiscreteIntegrator: '<S152>/Integrator' */
      rtDW.Integrator_PREV_U = rtb_IntegralGain;
    }

    /* End of Switch: '<S143>/Switch' */
    /* End of Outputs for S-Function (fcgen): '<S1>/Function-Call Generator' */
  }

  /* SwitchCase: '<S2>/Switch Case' */
  switch ((int32_T)Motor_state) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S2>/Switch Case Action Subsystem' incorporates:
     *  ActionPort: '<S10>/Action Port'
     */
    /* Merge: '<S2>/Merge' incorporates:
     *  Constant: '<S10>/Constant'
     *  SignalConversion generated from: '<S10>/theta_fd'
     */
    rtDW.Merge = 0.0F;

    /* Merge: '<S2>/Merge1' incorporates:
     *  Constant: '<S10>/Constant1'
     *  SignalConversion generated from: '<S10>/id_ref'
     */
    rtDW.Merge1 = 0.0F;

    /* Merge: '<S2>/Merge2' incorporates:
     *  Constant: '<S10>/Constant2'
     *  SignalConversion generated from: '<S10>/iq_ref'
     */
    rtDW.Merge2 = 0.0F;

    /* End of Outputs for SubSystem: '<S2>/Switch Case Action Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S2>/Switch Case Action Subsystem1' incorporates:
     *  ActionPort: '<S11>/Action Port'
     */
    /* Merge: '<S2>/Merge' incorporates:
     *  Constant: '<S11>/Constant'
     *  SignalConversion generated from: '<S11>/theta_fd'
     */
    rtDW.Merge = 0.0F;

    /* Merge: '<S2>/Merge1' incorporates:
     *  Constant: '<S11>/Constant1'
     *  SignalConversion generated from: '<S11>/id_ref'
     */
    rtDW.Merge1 = 2.0F;

    /* Merge: '<S2>/Merge2' incorporates:
     *  Constant: '<S11>/Constant2'
     *  SignalConversion generated from: '<S11>/iq_ref'
     */
    rtDW.Merge2 = 0.0F;

    /* End of Outputs for SubSystem: '<S2>/Switch Case Action Subsystem1' */
    break;

   case 3:
    /* Outputs for IfAction SubSystem: '<S2>/Switch Case Action Subsystem2' incorporates:
     *  ActionPort: '<S12>/Action Port'
     */
    /* Merge: '<S2>/Merge1' incorporates:
     *  Constant: '<S12>/Constant1'
     *  SignalConversion generated from: '<S12>/id_ref'
     */
    rtDW.Merge1 = 0.0F;

    /* Merge: '<S2>/Merge' incorporates:
     *  Inport: '<Root>/Encoder_Theta'
     *  SignalConversion generated from: '<S12>/Encoder_theta'
     */
    rtDW.Merge = rtU.Encoder_Theta;

    /* Merge: '<S2>/Merge2' incorporates:
     *  SignalConversion generated from: '<S12>/iq'
     */
    rtDW.Merge2 = rtDW.Saturation;

    /* End of Outputs for SubSystem: '<S2>/Switch Case Action Subsystem2' */
    break;
  }

  /* End of SwitchCase: '<S2>/Switch Case' */

  /* Trigonometry: '<S2>/Cos' */
  Integrator = cosf(rtDW.Merge);

  /* Trigonometry: '<S2>/Cos1' */
  rtb_DeadZone = sinf(rtDW.Merge);

  /* MATLAB Function: '<S2>/Clark' incorporates:
   *  Inport: '<Root>/ia'
   *  Inport: '<Root>/ib'
   *  Inport: '<Root>/ic'
   */
  rtb_Sum_e = ((2.0F * rtU.ia - rtU.ib) - rtU.ic) / 3.0F;
  rtb_IntegralGain = (rtU.ib - rtU.ic) * 1.73205078F / 3.0F;

  /* Sum: '<S7>/Sum' incorporates:
   *  MATLAB Function: '<S2>/Park'
   */
  UnitDelay = rtDW.Merge1 - (rtb_Sum_e * Integrator + rtb_IntegralGain *
    rtb_DeadZone);

  /* Sum: '<S55>/Sum' incorporates:
   *  Constant: '<S7>/Constant2'
   *  DiscreteIntegrator: '<S46>/Integrator'
   *  Product: '<S51>/PProd Out'
   */
  rtb_Sum = UnitDelay * currkpki.curr_kp + rtDW.Integrator_DSTATE;

  /* Sum: '<S7>/Sum1' incorporates:
   *  MATLAB Function: '<S2>/Park'
   */
  rtb_Sum_e = rtDW.Merge2 - (-rtb_Sum_e * rtb_DeadZone + rtb_IntegralGain *
    Integrator);

  /* Sum: '<S105>/Sum' incorporates:
   *  Constant: '<S7>/Constant1'
   *  DiscreteIntegrator: '<S96>/Integrator'
   *  Product: '<S101>/PProd Out'
   */
  rtb_IntegralGain = rtb_Sum_e * currkpki.curr_kp + rtDW.Integrator_DSTATE_p;

  /* Saturate: '<S103>/Saturation' */
  if (rtb_IntegralGain > 12.4707661F) {
    rtb_Saturation = 12.4707661F;
  } else if (rtb_IntegralGain < -12.4707661F) {
    rtb_Saturation = -12.4707661F;
  } else {
    rtb_Saturation = rtb_IntegralGain;
  }

  /* End of Saturate: '<S103>/Saturation' */

  /* MATLAB Function: '<S2>/MATLAB Function' */
  rtb_u_alpha = rtb_Sum * Integrator - rtb_Saturation * rtb_DeadZone;
  rtb_Saturation = rtb_Sum * rtb_DeadZone + rtb_Saturation * Integrator;

  /* Outputs for Atomic SubSystem: '<S2>/SVPWM' */
  /* Fcn: '<S113>/N' incorporates:
   *  Fcn: '<S113>/B0'
   *  Fcn: '<S113>/B1'
   *  Fcn: '<S113>/B2'
   *  Switch: '<S113>/Switch'
   *  Switch: '<S113>/Switch1'
   *  Switch: '<S113>/Switch2'
   */
  rtb_N = ((-rtb_u_alpha * 0.866025388F - rtb_Saturation * 0.5F >= 0.0F) *
           (int32_T)4.0 + (rtb_u_alpha * 0.866025388F - 0.5F * rtb_Saturation >=
            0.0F) * (int32_T)2.0) + (rtb_Saturation >= 0.0F);

  /* Gain: '<S116>/Gain2' */
  rtb_Sum = 0.866025388F * rtb_Saturation;

  /* Gain: '<S116>/Gain' */
  Integrator = 1.5F * rtb_u_alpha;

  /* Product: '<S116>/Product' incorporates:
   *  Constant: '<S2>/Constant1'
   *  Inport: '<Root>/Udc'
   *  Math: '<S116>/Math Function'
   *
   * About '<S116>/Math Function':
   *  Operator: reciprocal
   */
  rtb_DeadZone = 1.0F / rtU.Udc * 0.0001F;

  /* MultiPortSwitch: '<S114>/Multiport Switch' incorporates:
   *  Gain: '<S114>/Gain'
   *  Gain: '<S114>/Gain1'
   *  Gain: '<S114>/Gain2'
   *  Gain: '<S116>/Gain1'
   *  Product: '<S116>/Product1'
   *  Product: '<S116>/Product2'
   *  Product: '<S116>/Product3'
   *  Sum: '<S116>/Add'
   *  Sum: '<S116>/Add1'
   */
  switch (rtb_N) {
   case 1:
    rtb_u_alpha = (rtb_Sum - Integrator) * rtb_DeadZone;

    /* MultiPortSwitch: '<S114>/Multiport Switch1' incorporates:
     *  Product: '<S116>/Product2'
     *  Product: '<S116>/Product3'
     *  Sum: '<S116>/Add'
     *  Sum: '<S116>/Add1'
     */
    rtb_Sum = (rtb_Sum + Integrator) * rtb_DeadZone;
    break;

   case 2:
    rtb_u_alpha = (rtb_Sum + Integrator) * rtb_DeadZone;

    /* MultiPortSwitch: '<S114>/Multiport Switch1' incorporates:
     *  Gain: '<S114>/Gain'
     *  Gain: '<S116>/Gain1'
     *  Product: '<S116>/Product1'
     *  Product: '<S116>/Product3'
     *  Sum: '<S116>/Add'
     */
    rtb_Sum = -(1.73205078F * rtb_Saturation * rtb_DeadZone);
    break;

   case 3:
    rtb_u_alpha = -((rtb_Sum - Integrator) * rtb_DeadZone);

    /* MultiPortSwitch: '<S114>/Multiport Switch1' incorporates:
     *  Gain: '<S114>/Gain2'
     *  Gain: '<S116>/Gain1'
     *  Product: '<S116>/Product1'
     *  Product: '<S116>/Product2'
     *  Sum: '<S116>/Add1'
     */
    rtb_Sum = 1.73205078F * rtb_Saturation * rtb_DeadZone;
    break;

   case 4:
    rtb_u_alpha = -(1.73205078F * rtb_Saturation * rtb_DeadZone);

    /* MultiPortSwitch: '<S114>/Multiport Switch1' incorporates:
     *  Gain: '<S114>/Gain'
     *  Gain: '<S116>/Gain1'
     *  Product: '<S116>/Product1'
     *  Product: '<S116>/Product2'
     *  Sum: '<S116>/Add1'
     */
    rtb_Sum = (rtb_Sum - Integrator) * rtb_DeadZone;
    break;

   case 5:
    rtb_u_alpha = 1.73205078F * rtb_Saturation * rtb_DeadZone;

    /* MultiPortSwitch: '<S114>/Multiport Switch1' incorporates:
     *  Gain: '<S114>/Gain1'
     *  Gain: '<S116>/Gain1'
     *  Product: '<S116>/Product1'
     *  Product: '<S116>/Product3'
     *  Sum: '<S116>/Add'
     */
    rtb_Sum = -((rtb_Sum + Integrator) * rtb_DeadZone);
    break;

   default:
    rtb_u_alpha = -((rtb_Sum + Integrator) * rtb_DeadZone);

    /* MultiPortSwitch: '<S114>/Multiport Switch1' incorporates:
     *  Gain: '<S114>/Gain1'
     *  Gain: '<S114>/Gain2'
     *  Product: '<S116>/Product2'
     *  Product: '<S116>/Product3'
     *  Sum: '<S116>/Add'
     *  Sum: '<S116>/Add1'
     */
    rtb_Sum = -((rtb_Sum - Integrator) * rtb_DeadZone);
    break;
  }

  /* End of MultiPortSwitch: '<S114>/Multiport Switch' */

  /* Fcn: '<S114>/Fcn' incorporates:
   *  Constant: '<S2>/Constant1'
   */
  rtb_DeadZone = (0.0001F - rtb_Sum) - rtb_u_alpha;

  /* Switch: '<S114>/Switch' incorporates:
   *  Constant: '<S2>/Constant1'
   *  Fcn: '<S114>/Fcn1'
   */
  if (rtb_DeadZone >= 0.0F) {
    Integrator = rtb_u_alpha;
  } else {
    Integrator = rtb_u_alpha * 0.0001F / (rtb_u_alpha + rtb_Sum);
  }

  /* End of Switch: '<S114>/Switch' */

  /* Switch: '<S114>/Switch1' incorporates:
   *  Constant: '<S2>/Constant1'
   *  Fcn: '<S114>/Fcn2'
   */
  if (rtb_DeadZone > 0.0F) {
    rtb_DeadZone = rtb_Sum;
  } else {
    rtb_DeadZone = rtb_Sum * 0.0001F / (rtb_u_alpha + rtb_Sum);
  }

  /* End of Switch: '<S114>/Switch1' */

  /* Fcn: '<S115>/Fcn1' incorporates:
   *  Constant: '<S2>/Constant1'
   */
  rtb_Saturation = ((Integrator + 0.0001F) - rtb_DeadZone) / 4.0F;

  /* Fcn: '<S115>/Fcn' incorporates:
   *  Constant: '<S2>/Constant1'
   */
  rtb_Sum = ((0.0001F - Integrator) - rtb_DeadZone) / 4.0F;

  /* Fcn: '<S115>/Fcn2' incorporates:
   *  Constant: '<S2>/Constant1'
   */
  rtb_u_alpha = ((rtb_DeadZone + 0.0001F) + Integrator) / 4.0F;

  /* MultiPortSwitch: '<S115>/Multiport Switch' incorporates:
   *  Constant: '<S2>/Constant1'
   *  Fcn: '<S115>/Fcn1'
   *  Fcn: '<S115>/Fcn2'
   */
  switch (rtb_N) {
   case 1:
    rtb_DeadZone = ((Integrator + 0.0001F) - rtb_DeadZone) / 4.0F;

    /* MultiPortSwitch: '<S115>/Multiport Switch1' incorporates:
     *  Constant: '<S2>/Constant1'
     *  Fcn: '<S115>/Fcn'
     *  Fcn: '<S115>/Fcn1'
     */
    Integrator = rtb_Sum;

    /* MultiPortSwitch: '<S115>/Multiport Switch2' incorporates:
     *  Fcn: '<S115>/Fcn2'
     */
    rtb_Sum = rtb_u_alpha;
    break;

   case 2:
    rtb_DeadZone = rtb_Sum;

    /* MultiPortSwitch: '<S115>/Multiport Switch1' incorporates:
     *  Fcn: '<S115>/Fcn2'
     */
    Integrator = rtb_u_alpha;

    /* MultiPortSwitch: '<S115>/Multiport Switch2' incorporates:
     *  Fcn: '<S115>/Fcn1'
     */
    rtb_Sum = rtb_Saturation;
    break;

   case 3:
    rtb_DeadZone = rtb_Sum;

    /* MultiPortSwitch: '<S115>/Multiport Switch1' incorporates:
     *  Fcn: '<S115>/Fcn1'
     */
    Integrator = rtb_Saturation;

    /* MultiPortSwitch: '<S115>/Multiport Switch2' incorporates:
     *  Fcn: '<S115>/Fcn2'
     */
    rtb_Sum = rtb_u_alpha;
    break;

   case 4:
    rtb_DeadZone = ((rtb_DeadZone + 0.0001F) + Integrator) / 4.0F;

    /* MultiPortSwitch: '<S115>/Multiport Switch1' incorporates:
     *  Constant: '<S2>/Constant1'
     *  Fcn: '<S115>/Fcn1'
     *  Fcn: '<S115>/Fcn2'
     */
    Integrator = rtb_Saturation;
    break;

   case 5:
    rtb_DeadZone = ((rtb_DeadZone + 0.0001F) + Integrator) / 4.0F;

    /* MultiPortSwitch: '<S115>/Multiport Switch1' incorporates:
     *  Constant: '<S2>/Constant1'
     *  Fcn: '<S115>/Fcn'
     *  Fcn: '<S115>/Fcn2'
     */
    Integrator = rtb_Sum;

    /* MultiPortSwitch: '<S115>/Multiport Switch2' incorporates:
     *  Fcn: '<S115>/Fcn1'
     */
    rtb_Sum = rtb_Saturation;
    break;

   default:
    rtb_DeadZone = ((Integrator + 0.0001F) - rtb_DeadZone) / 4.0F;

    /* MultiPortSwitch: '<S115>/Multiport Switch1' incorporates:
     *  Constant: '<S2>/Constant1'
     *  Fcn: '<S115>/Fcn1'
     *  Fcn: '<S115>/Fcn2'
     */
    Integrator = rtb_u_alpha;
    break;
  }

  /* End of MultiPortSwitch: '<S115>/Multiport Switch' */
  /* End of Outputs for SubSystem: '<S2>/SVPWM' */

  /* DeadZone: '<S89>/DeadZone' */
  if (rtb_IntegralGain > 12.4707661F) {
    rtb_IntegralGain -= 12.4707661F;
  } else if (rtb_IntegralGain >= -12.4707661F) {
    rtb_IntegralGain = 0.0F;
  } else {
    rtb_IntegralGain -= -12.4707661F;
  }

  /* End of DeadZone: '<S89>/DeadZone' */

  /* Product: '<S93>/IProd Out' incorporates:
   *  Constant: '<S7>/Constant4'
   */
  rtb_Sum_e *= currkpki.curr_ki;

  /* Update for UnitDelay: '<S1>/Unit Delay' */
  rtDW.UnitDelay_DSTATE = rtDW.SpeedReset;

  /* Update for DiscreteIntegrator: '<S46>/Integrator' incorporates:
   *  Constant: '<S7>/Constant3'
   *  Product: '<S43>/IProd Out'
   */
  rtDW.Integrator_DSTATE += UnitDelay * currkpki.curr_ki * 0.0001F;

  /* Switch: '<S87>/Switch1' incorporates:
   *  Constant: '<S87>/Clamping_zero'
   *  Constant: '<S87>/Constant'
   *  Constant: '<S87>/Constant2'
   *  RelationalOperator: '<S87>/fix for DT propagation issue'
   */
  if (rtb_IntegralGain > 0.0F) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  /* Switch: '<S87>/Switch2' incorporates:
   *  Constant: '<S87>/Clamping_zero'
   *  Constant: '<S87>/Constant3'
   *  Constant: '<S87>/Constant4'
   *  RelationalOperator: '<S87>/fix for DT propagation issue1'
   */
  if (rtb_Sum_e > 0.0F) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  /* Switch: '<S87>/Switch' incorporates:
   *  Constant: '<S87>/Clamping_zero'
   *  Constant: '<S87>/Constant1'
   *  Logic: '<S87>/AND3'
   *  RelationalOperator: '<S87>/Equal1'
   *  RelationalOperator: '<S87>/Relational Operator'
   *  Switch: '<S87>/Switch1'
   *  Switch: '<S87>/Switch2'
   */
  if ((rtb_IntegralGain != 0.0F) && (tmp == tmp_0)) {
    rtb_Sum_e = 0.0F;
  }

  /* Update for DiscreteIntegrator: '<S96>/Integrator' incorporates:
   *  Switch: '<S87>/Switch'
   */
  rtDW.Integrator_DSTATE_p += 0.0001F * rtb_Sum_e;

  /* Outputs for Atomic SubSystem: '<S2>/SVPWM' */
  /* Outport: '<Root>/Tabc' incorporates:
   *  Constant: '<S2>/Constant'
   *  Constant: '<S2>/Constant1'
   *  Gain: '<S9>/Gain'
   *  Product: '<S9>/Divide'
   *  Product: '<S9>/Divide1'
   *  Product: '<S9>/Divide2'
   */
  rtY.Tabc[0] = 2.0F * rtb_DeadZone / 0.0001F * 8500.0F;
  rtY.Tabc[1] = 2.0F * Integrator / 0.0001F * 8500.0F;
  rtY.Tabc[2] = 2.0F * rtb_Sum / 0.0001F * 8500.0F;

  /* End of Outputs for SubSystem: '<S2>/SVPWM' */
  /* End of Outputs for SubSystem: '<Root>/doubleloop' */
  if (rtM->Timing.TaskCounters.TID[1] == 0) {
    /* Update absolute timer for sample time: [0.001s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.001, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    rtM->Timing.clockTick1++;
  }

  rate_scheduler();
}

/* Model initialize function */
void doubleloop_initialize(void)
{
  /* SystemInitialize for Atomic SubSystem: '<Root>/doubleloop' */
  /* SystemInitialize for S-Function (fcgen): '<S1>/Function-Call Generator' incorporates:
   *  SubSystem: '<S1>/SpeedLoop'
   */
  /* InitializeConditions for DiscreteIntegrator: '<S152>/Integrator' */
  rtDW.Integrator_PrevResetState = 2;

  /* End of SystemInitialize for S-Function (fcgen): '<S1>/Function-Call Generator' */
  /* End of SystemInitialize for SubSystem: '<Root>/doubleloop' */

  /* Enable for Atomic SubSystem: '<Root>/doubleloop' */
  /* Enable for S-Function (fcgen): '<S1>/Function-Call Generator' incorporates:
   *  SubSystem: '<S1>/SpeedLoop'
   */
  rtDW.SpeedLoop_RESET_ELAPS_T = true;

  /* Enable for DiscreteIntegrator: '<S152>/Integrator' */
  rtDW.Integrator_SYSTEM_ENABLE = 1U;

  /* End of Enable for S-Function (fcgen): '<S1>/Function-Call Generator' */
  /* End of Enable for SubSystem: '<Root>/doubleloop' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
