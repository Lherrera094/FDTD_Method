
#ifndef _FDTD_PROTO1_H
#define _FDTD_PROTO1_H

#include "fdtd.h"

/*Function Prototypes*/
void abcInit(Grid *g);
void abc(Grid *g);

void gridInit(Grid *g);

void snapshot3dInit(Grid *g);
void snapshot3d(Grid *g);

void updateE(Grid *g);
void updateH(Grid *g);

#endif
