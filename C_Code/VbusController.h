
#ifndef VBUSCONTROLLER_H_
#define VBUSCONTROLLER_H_

#include"generic/ViennaBasicTypes.h"


typedef struct
{

    float32 vbus_meas;
   

} VBUSCONTROLLER_IN_TYPE; 

typedef struct
{
    float32 *vbus_ref;
    PI_IO_TYPE *pi_io;
                                                             
} VBUSCONTROLLER_STATE_TYPE;

typedef struct
{
    float32 *vbus_target;
    float32 *vbus_ref_init;
    float32 *Ts;

    float32	*vbus_kp;
    float32	*vbus_ki;
    float32	*vbus_con_upper_lmt ;
    float32	*vbus_con_lower_lmt ;
                                                             
} VBUSCONTROLLER_PARAMS_TYPE;

typedef struct
{

    float32 vbus_ref;
    float32 vbus_con_out;

    float32 debug1;
    float32 debug2;
                                                             
} VBUSCONTROLLER_OUT_TYPE;

void VbusController_initialize(VBUSCONTROLLER_STATE_TYPE *state,VBUSCONTROLLER_PARAMS_TYPE *pll_params);
void VbusController_calc(VBUSCONTROLLER_IN_TYPE *in, VBUSCONTROLLER_STATE_TYPE *state,VBUSCONTROLLER_PARAMS_TYPE *params, VBUSCONTROLLER_OUT_TYPE *out);


#endif //end of VBUSCONTROLLER_H_