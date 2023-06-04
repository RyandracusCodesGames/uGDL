#ifndef MATH_UTILS_H
#define MATH_UTILS_H

/*************************************************************************
	Copyright (c) 2023-present Ryandracus Chapman (@RyandracusCodesGames)
	
	(The Ultimate Graphics Display Library)
	
	Library : uGDL
	File    : mathutils.h
	Author  : Ryandracus Chapamn
	Date 	: 6/3/2023
	Version : 1.0
	
*************************************************************************/

/*GENERAL MATH MACROS AND FUNCTIONS*/
#define uGDLPI 3.1415965

#define uGDLAbs(a) ((a) < 0 ? -(a) ? (a))
#define uGDLMinU(a, b) ((a) < (b) ? (a) : (b))
#define uGDLMaxU(a, b) ((a) > (b) ? (a) : (b))

#define uGDLDegToRad(deg) (deg * (uGDLPI/180.00f))
#define uGDLRadToDeg(rad) (rad * (180.00f/uGDLPI))

typedef int uGDLBool;

#define TRUE 1
#define FALSE 0

float uGDLMin(float a, float b);
float uGDLMax(float a, float b);
float uGDLClamp(float minVal, float targetVal, float maxVal);
float uGDLFract(float x);
int uGDLFloor(int x);
float uGDLModf(float a, float b);
float uGDLFixAng(float angle); 
float uGDLSinf(float angle);
float uGDLCosf(float angle);
float uGDLTanf(float angle);
float uGDLSqrt(float number);
float uGDLSmoothStep(float edge0, float edge1, float x);
float uGDLLerp(float a, float b, float t);
float uGDLLerpf(float a, float b, float t);
float uGDLInvLerp(float a, float b, float t);
int uGDLRandInt();

#endif
