
#ifndef _FDTD_PROTO1_H
#define _FDTD_PROTO1_H

#include "fdtd.h"

/*Function Prototypes*/
/*void abcInit(Grid *g);
void abc(Grid *g);*/

void gridInit(Grid *g);

void snapshotInit2d(Grid *g);
void snapshot2d(Grid *g);

/*void tfsfInit(Grid *g);
void tfsfUpdate(Grid *g);
*/

void updateE2d(Grid *g);
void updateH2d(Grid *g);

#endif
