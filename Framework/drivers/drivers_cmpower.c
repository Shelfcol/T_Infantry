/**
  ******************************************************************************
  * File Name          : drivers_cmpower.c
  * Description        : 底盘功率限制
  ******************************************************************************
  *
  * Copyright (c) 2017 Team TPP-Shanghai Jiao Tong University
  * All rights reserved.
  *
  * 底层函数
  ******************************************************************************
  */
#include "drivers_uartjudge_low.h"
#include "drivers_cmpower.h"
#include "utilities_minmax.h"
#include <math.h>
#include <stdlib.h>

extern tGameInfo mytGameInfo;
extern uint8_t JUDGE_State;

static float CM_current_max = CM_current_MAX;
static float CMFLIntensity_max = CMFLIntensity_MAX;
static float CMFRIntensity_max = CMFRIntensity_MAX;
static float CMBLIntensity_max = CMBLIntensity_MAX;
static float CMBRIntensity_max = CMBRIntensity_MAX;

void RestrictPower(int16_t *intensity1, int16_t *intensity2, int16_t *intensity3, int16_t *intensity4)
{
  dynamicUpperBound();
	
  int16_t *CMFLIntensity = intensity1;
	int16_t *CMFRIntensity = intensity2;
	int16_t *CMBLIntensity = intensity3;
	int16_t *CMBRIntensity = intensity4;
	
	float sum = (abs(*CMFLIntensity) + abs(*CMFRIntensity) + abs(*CMBLIntensity) + abs(*CMBRIntensity));
	
	MINMAX(*CMFLIntensity, -CMFLIntensity_max, CMFLIntensity_max);
	MINMAX(*CMFRIntensity, -CMFRIntensity_max, CMFRIntensity_max);
	MINMAX(*CMBLIntensity, -CMBLIntensity_max, CMBLIntensity_max);
  MINMAX(*CMBRIntensity, -CMBRIntensity_max, CMBRIntensity_max);

	if(sum > CM_current_max)
	{
		*CMFLIntensity = (CM_current_max/sum) * (*CMFLIntensity);
		*CMFRIntensity = (CM_current_max/sum) * (*CMFRIntensity);
		*CMBLIntensity = (CM_current_max/sum) * (*CMBLIntensity);
		*CMBRIntensity = (CM_current_max/sum) * (*CMBRIntensity);
	}
}	

void dynamicUpperBound()
{
	if (mytGameInfo.remainPower > 10 && mytGameInfo.remainPower < 40)
	{
		 CM_current_max = CM_current_lower;
		 CMFLIntensity_max = CMFLIntensity_lower;
		 CMFRIntensity_max = CMFRIntensity_lower;
		 CMBLIntensity_max = CMBLIntensity_lower;
		 CMBRIntensity_max = CMBRIntensity_lower;
	}

	if (mytGameInfo.remainPower < 15 )
	{
		 CM_current_max = CM_current_bottom;
		 CMFLIntensity_max = CMFLIntensity_bottom;
		 CMFRIntensity_max = CMFRIntensity_bottom;
		 CMBLIntensity_max = CMBLIntensity_bottom;
		 CMBRIntensity_max = CMBRIntensity_bottom;
	}

	if (mytGameInfo.remainPower < 7)
	{
		 CM_current_max = 0;
		 CMFLIntensity_max = 0;
		 CMFRIntensity_max = 0;
		 CMBLIntensity_max = 0;
		 CMBRIntensity_max = 0;
	}

	if (JUDGE_State == 1)
	{
		 CM_current_max = 13000;
		 CMFLIntensity_max = 4500;
		 CMFRIntensity_max = 4500;
		 CMBLIntensity_max = 4500;
		 CMBRIntensity_max = 4500;
	}
}