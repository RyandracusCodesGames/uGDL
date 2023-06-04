#include <stdlib.h>
#include <stdint.h>
#include "mathutils.h"
#include "trig_tables.h"

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : mathutils.c
	Author  : Ryandracus Chapamn
	Date 	: 6/3/2023
	Version : 1.0
	
*************************************************************************/

float uGDLMin(float a, float b){
	return a < b ? a : b;
}

float uGDLMax(float a, float b){
	return a > b ? a : b;
}

float uGDLClamp(float minVal, float targetVal, float maxVal){
	return uGDLMin(uGDLMax(minVal, targetVal), maxVal);
}

int uGDLFloor(int x)
{
	return x - (x % 1);
}

float uGDLModf(float a, float b) 
{
    int result = (int)uGDLFloor(a / b);
    return a - result * b;
}

float uGDLFixAng(float angle)
{ 
	angle = uGDLModf(angle,360);
    if (angle < 0)
        angle += 360;
    return angle;
}

float uGDLFract(float x){
	return x - uGDLFloor(x);
}

float uGDLSinf(float angle){
	return sin_lut[(int)uGDLFixAng(angle)];
}

float uGDLCosf(float angle){
	return cos_lut[(int)uGDLFixAng(angle)];
}

float uGDLTanf(float angle){
	return tan_lut[(int)uGDLFixAng(angle)];
}

float uGDLSqrt(float number)
{
	union {
        float f;
        uint32_t i;
    } conv;

    float x2;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    conv.f  = number;
    conv.i  = 0x5f3759df - ( conv.i >> 1 );
    conv.f  = conv.f * ( threehalfs - ( x2 * conv.f * conv.f ) );
    return conv.f;
}

float uGDLSmoothStep(float edge0, float edge1, float x){
	float t = uGDLClamp(0,(x - edge0) / (edge1 - edge0),1); 
	if(x <= edge0){
		return 0;
	}
	else if(x >= edge1){
		return 1;
	}
	else return t * t * (3 - 2 * t);
}

float uGDLLerp(float a, float b, float t){
	return a + t * (a - b);
}

float uGDLLerpf(float a, float b, float t){
	(1 - t) * a + t * b;
}

float uGDLInvLerp(float a, float b, float t){
	return (t - a) / (b - a);
}

int random[512] = {
	100,188,32,223,99,40,149,215,69,
	205,245,20,46,35,117,53,186,
	193,30,183,9,81,220,247,229,
	18,221,233,246,241,32,15,154,
	146,252,210,227,139,119,119,238,
	133,83,216,161,201,250,241,169,
	23,34,235,150,85,158,144,37,
	164,187,97,41,83,184,86,166,
	71,254,17,203,108,153,98,246,
	53,184,93,124,241,41,92,70,
	199,247,233,42,112,141,227,171,
	98,40,144,220,214,41,145,65,
	60,223,245,147,89,155,54,238,
	108,209,192,251,152,169,141,250,
	249,237,49,159,184,91,108,60,
	80,246,49,234,186,254,249,103,
	6,143,121,148,19,31,6,7,
	254,72,171,43,53,3,236,50,
	178,161,128,69,223,167,197,140,
	233,225,83,153,16,204,219,28,
	43,233,61,168,208,21,137,180,
	12,60,15,222,117,235,117,47,
	199,212,48,3,155,80,93,117,
	184,88,59,174,229,138,39,84,
	249,223,215,250,89,48,239,146,
	192,117,214,4,117,208,52,46,
	43,25,39,241,32,28,11,174,
	213,41,130,21,45,104,129,131,
	227,188,0,127,138,235,220,13,
	48,173,255,192,255,21,146,113,
	0,193,216,224,61,62,13,128,
	209,155,224,153,235,157,93,67,
	235,231,21,175,170,164,6,73,
	244,147,191,229,62,145,222,172,
	254,155,226,83,149,48,232,1,
	141,108,45,45,17,170,160,165,
	155,180,104,224,36,94,251,200,
	225,239,10,45,107,193,161,84,
	155,244,189,102,118,109,178,74,
	135,62,31,71,166,159,67,154,
	14,185,238,219,25,139,135,88,
	123,108,24,209,6,48,52,72,
	141,97,254,46,200,120,58,51,
	4,227,53,204,160,205,122,4,
	126,49,185,33,84,122,71,186,
	140,147,91,237,250,163,23,103,
	17,218,176,2,161,203,156,17,
	186,32,87,9,1,126,228,230,
	229,228,207,93,21,220,217,142,
	107,108,112,53,73,113,154,122,
	129,148,69,57,237,19,179,234,
	85,76,177,69,173,29,60,50,
	43,29,208,138,63,223,52,3,
	112,64,122,119,183,159,59,8,
	182,42,146,215,188,73,248,189,
	119,99,60,93,130,90,20,188,
	93,32,248,76,95,99,166,194,
	22,20,126,118,230,44,82,133,
	187,140,113,175,168,40,62,54,
	156,246,131,242,39,195,17,206,
	119,181,236,245,17,203,248,155,
	69,63,48,145,123,28,133,104,
	70,57,100,110,213,117,216,117,
	111,142,22,171,28,97,41,
};

int r_index = 0;

int uGDLRandInt(){
	 r_index = (r_index+1)&0x1ff;
    return random[r_index];
}
