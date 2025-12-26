#include<stdio.h>
#include"generic/GenericBlocks.h"
#include "Vienna.h"
#include "VbusController.h"



void VbusController_initialize(VBUSCONTROLLER_STATE_TYPE *state,VBUSCONTROLLER_PARAMS_TYPE *params)
{
   
    state->pi_io->kp = *params->vbus_kp;
    state->pi_io->ki = *params->vbus_ki;
    state->pi_io->upper_lmt = *params->vbus_con_upper_lmt;
    state->pi_io->lower_lmt = *params->vbus_con_lower_lmt;
    state->pi_io->intg.out = 0.0f;
    state->pi_io->out = 0.0f;
    state->pi_io->intg.Ts = *params->Ts;

    state->vbus_ref = params->vbus_ref_init;


}


void VbusController_calc(VBUSCONTROLLER_IN_TYPE *in, VBUSCONTROLLER_STATE_TYPE *state,VBUSCONTROLLER_PARAMS_TYPE *params, VBUSCONTROLLER_OUT_TYPE *out)
{
   
    // Refrence bus voltage generation   
    *state->vbus_ref =  *state->vbus_ref + 8000.0f*(*params->Ts);

    if( *state->vbus_ref > *params->vbus_target)
    {
        *state->vbus_ref = *params->vbus_target;
    }

    state->pi_io->error = *state->vbus_ref - in->vbus_meas;
    GenericBlocks_PI(state->pi_io);
    out->vbus_con_out = state->pi_io->out;
    out->vbus_ref =  *state->vbus_ref;

    out->debug1 = in->vbus_meas;
    out->debug2 = state->pi_io->out;
   
}
