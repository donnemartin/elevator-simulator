// COPYRIGHT © 2011, Donne Martin
// All Rights Reserved.
//
//******************************************************************************
//
// File Name:     Passenger.cpp
//
// File Overview: Represents an elevator Passenger
//
//******************************************************************************
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added class
//******************************************************************************

#include "stdafx.h"
#include "Passenger.h"

//******************************************************************************
// File scope (static) variable definitions
//******************************************************************************

// None

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
Passenger::Passenger() 
{
   this->id          = Passenger::INIT_TO_INVALID;
   this->startTime   = Passenger::INIT_TO_INVALID;   

   this->setStatus(Passenger::NOT_SET, Passenger::INIT_TO_INVALID);

   this->setBoardElevatorTime(Passenger::INIT_TO_INVALID);
   this->setBoardElevatorTime(Passenger::INIT_TO_INVALID);
} // end Passenger::Passenger

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
Passenger::~Passenger()
{
} // end Passenger::~Passenger

//******************************************************************************
// Function : printStatus                                   
// Process  : Print the status in text (as opposed to int)           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Passenger::printStatus() const
{
   switch (this->status)
   {
      case NOT_SET:
      {
         cout << "NOT_SET";
         break;
      }
      case QUEUED_WAITING_FLAGGED:
      {
         cout << "QUEUED_WAITING_FLAGGED";
         break;
      }
      case QUEUED_WAITING_UP:
      {
         cout << "QUEUED_WAITING_UP";
         break;
      }
      case QUEUED_WAITING_DOWN:
      {
         cout << "QUEUED_WAITING_DOWN";
         break;
      }
      case RIDING:
      {
         cout << "RIDING";
         break;
      }
      case COMPLETED:
      {
         cout << "COMPLETED";
         break;
      }
      default:
      {
         throw exception("Unexpected status!");
         break;
      }
   }
}

//******************************************************************************
// Function : setStatus                                   
// Process  : Sets the status
//             Updates the passenger boardElevatorTime and exitElevatorTime
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Passenger::setStatus(const Passenger::Status status, int time) 
{ 
   this->status = status; 

   if (status != Passenger::NOT_SET)
   {
      // If the status is riding, also update the boardElevatorTime
      if (status == Passenger::RIDING)
      {
         this->boardElevatorTime = time;
      }
      // If the status is completed, also update the exitElevatorTime
      else if (status == Passenger::COMPLETED)
      {
         this->exitElevatorTime = time;
      }
   }
}
