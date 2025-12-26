

#ifndef GENERICBLOCK_H_
#define GENERICBLOCK_H_

#include"ViennaBasicTypes.h"

void GenericBlocks_Clarke(ABC_TYPE *in ,ALPHA_BETA_TYPE *out);
void GenericBlocks_Sogi(SOGI_IO_TYPE *io);
void GenericBlocks_Initialize(SOGI_IO_TYPE *sogi_alpha_io, SOGI_IO_TYPE *sogi_beta_io);
void GenericBlocks_Integration(INTEGRATION_IO_TYPE *io);
void GenericBlocks_Add(ADD_IN_TYPE *x ,ADD_OUT_TYPE *y );
void GenericBlocks_PI(PI_IO_TYPE *io);
void GenericBlocks_Park(PARK_IN_TYPE *in, DQ_TYPE *dqo);
void GenericBlocks_InvClarke(ALPHA_BETA_TYPE *in ,ABC_TYPE *out);
void GenericBlocks_PR(PR_IO_TYPE *io);

#endif //end of GENERICBLOCK_H_