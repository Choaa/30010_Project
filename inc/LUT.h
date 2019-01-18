// =====================================================================
//
//	Exported by Cearn's excellut v1.0
//	(comments, kudos, flames to daytshen@hotmail.com)
//
// =====================================================================
#include <stdio.h>
#ifndef LUT_H
#define LUT_H

// === LUT SIZES ===
#define SIN_SIZE 512

// === LUT DECLARATIONS ===
extern const signed short SIN[24];
int32_t calcsin(int angle);
int32_t calccos(int angle);
int32_t rotatevector(int x, int y, int angle);

#endif	// LUT_H
