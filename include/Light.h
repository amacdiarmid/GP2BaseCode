#ifndef _LIGHT_H
#define _LIGHT_H

#include "Common.h"

struct LightData
{
	vec3 direction;
	vec4 ambientColour;
	vec4 diffuseColour;
	vec4 specularColour;
};

#endif