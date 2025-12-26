


#include<stdio.h>
#include<math.h>
#include"GenericBlocks.h"





// SOGI_IO_TYPE sogi_io;
// SOGI_PARAM_TYPE sogi_params;

void GenericBlocks_Initialize(SOGI_IO_TYPE *sogi_alpha_io, SOGI_IO_TYPE *sogi_beta_io)
{

    // //Initialize SOGI params
    // sogi_alpha_io->w = 50.0f*2.0f*3.1416f;
    // sogi_alpha_io->k = 0.5f;

    // sogi_alpha_io->intg1.upper_lmt = 500.0f;
    // sogi_alpha_io->intg1.lower_lmt = -500.0f;
    // sogi_alpha_io->intg1.out = 0.0f;

    // sogi_alpha_io->intg2.upper_lmt = 500.0f;
    // sogi_alpha_io->intg2.lower_lmt = -500.0f;
    // sogi_alpha_io->intg2.out = 0.0f;

    // sogi_beta_io->w = 50.0f*2.0f*3.1416f;
    // sogi_beta_io->k = 0.5f;

    // sogi_beta_io->intg1.upper_lmt = 500.0f;
    // sogi_beta_io->intg1.lower_lmt = -500.0f;
    // sogi_beta_io->intg1.out = 0.0f;

    // sogi_beta_io->intg2.upper_lmt = 500.0f;
    // sogi_beta_io->intg2.lower_lmt = -500.0f;
    // sogi_beta_io->intg2.out = 0.0f;
    // // sogi_io->Ts = 1/35000.0f;


}

void GenericBlocks_Clarke(ABC_TYPE *in ,ALPHA_BETA_TYPE *out)
{
    out->Alpha = TWO_BY_THREE*(in->A - in->B*ONE_BY_TWO - in->C*ONE_BY_TWO);
    out->Beta = TWO_BY_THREE*(0 + SQRT_3*in->B*ONE_BY_TWO - SQRT_3*in->C*ONE_BY_TWO);
    out->ZeroSequence = TWO_BY_THREE*(in->A + in->B  + in->C) *ONE_BY_TWO;
}

void GenericBlocks_InvClarke(ALPHA_BETA_TYPE *in ,ABC_TYPE *out)
{

    out->A = in->Alpha;
    out->B = -0.5f*in->Alpha + SQRT_3*0.5f*in->Beta;
    out->C = -0.5f*in->Alpha - SQRT_3*0.5f*in->Beta;
}

void GenericBlocks_Park(PARK_IN_TYPE *in, DQ_TYPE *dqo)
{
    dqo->q = cos(in->th)*in->AlBeZero.Alpha + sin(in->th)*in->AlBeZero.Beta;
    dqo->d = -(-sin(in->th)*in->AlBeZero.Alpha + cos(in->th)*in->AlBeZero.Beta);
    dqo->o = 0.0f;
}

void GenericBlocks_Integration(INTEGRATION_IO_TYPE *io)
{

    io->out =  io->out + io->Ts *io->in_old;
    io->in_old = io->in;

      // saturate 
    if ( io->out > io->upper_lmt)
    {
        io->out = io->upper_lmt;
    }
    else if (io->out < io->lower_lmt)
    {
        io->out =  io->lower_lmt;
    }
}

void GenericBlocks_Sogi(SOGI_IO_TYPE *io)
{

    float32 temp;

    temp = ((-io->out + io->in)*io->k - io->out_quadrature)*io->w;

    io->intg1.in = temp;
    GenericBlocks_Integration(&io->intg1);
    io->out = io->intg1.out;
    
    io->intg2.in = io->out;
    GenericBlocks_Integration(&io->intg2);
    temp = io->intg2.out;

    io->out_quadrature = temp *io->w;

}

void GenericBlocks_PI(PI_IO_TYPE *io)
{
    float32 temp, p_term,i_term;

    p_term = io->error * io->kp;


    io->intg.lower_lmt = io->lower_lmt;
    io->intg.upper_lmt = io->upper_lmt;
    io->intg.in = io->error*io->ki;
    GenericBlocks_Integration(&io->intg);

    i_term = io->intg.out;

    temp  = p_term + i_term;

      // saturate 
    if ( temp > io->upper_lmt)
    {
        io->out = io->upper_lmt;
       
    }
    else if (temp < io->lower_lmt)
    {
        io->out =  io->lower_lmt;
    }
    else
    {
        io->out = temp;
    }
}

// void GenericBlocks_Resonance(PR_IO_TYPE *io)
// {
    
// }

void GenericBlocks_PR(PR_IO_TYPE *io)
{
    float32 temp, p_term,res_term;

    p_term = io->error * io->kp;

    // io->intg.lower_lmt = io->lower_lmt;
    // io->intg.upper_lmt = io->upper_lmt;
    // io->intg.in = io->error*io->ki;
    // GenericBlocks_Integration(&io->intg);

    // io->res.w = 5;
    io->res.in = io->error*io->ki;
    GenericBlocks_Sogi(&io->res);

    res_term = io->res.out;

    temp  = p_term + res_term;

      // saturate 
    if ( temp > io->upper_lmt)
    {
        io->out = io->upper_lmt;
       
    }
    else if (temp < io->lower_lmt)
    {
        io->out =  io->lower_lmt;
    }
    else
    {
        io->out = temp;
    }
}