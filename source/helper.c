#include <stdio.h>
#include <nds.h>

#include "helper.h"

double clamp(float d, float min, float max) {
	const float t = d < min ? min : d;
	return t > max ? max : t;
}