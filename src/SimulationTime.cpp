// COPYRIGHT © 2011, Donne Martin
// All Rights Reserved.
//
//******************************************************************************
//
// File Name:     SimulationTime.cpp
//
// File Overview: Represents a SimulationTime (singleton)
//
//******************************************************************************
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added class
//******************************************************************************

#include "stdafx.h"
#include "SimulationTime.h"

//******************************************************************************
// File scope (static) variable definitions
//******************************************************************************

SimulationTime *SimulationTime::instancePtr = 0;

//******************************************************************************
// Function : constructor                                   
// Process  : None
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************                    
SimulationTime::SimulationTime() 
{
   this->time = 0;   // Start at time 0
} // end SimulationTime::SimulationTime

//******************************************************************************
// Function : destructor                                   
// Process  : None           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
SimulationTime::~SimulationTime()
{
} // end SimulationTime::~SimulationTime
