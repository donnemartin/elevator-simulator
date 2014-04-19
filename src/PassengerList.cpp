// COPYRIGHT © 2011, Donne Martin
// All Rights Reserved.
//
//******************************************************************************
//
// File Name:     PassengerList.cpp
//
// File Overview: Represents a PassengerList (singleton)
//
//******************************************************************************
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added class
//******************************************************************************

#include "stdafx.h"
#include "PassengerList.h"

//******************************************************************************
// File scope (static) variable definitions
//******************************************************************************

PassengerList *PassengerList::instancePtr = 0;

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
PassengerList::PassengerList() 
{
} // end PassengerList::PassengerList

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
PassengerList::~PassengerList()
{
} // end PassengerList::~PassengerList

//******************************************************************************
// Function : getNextDestinationPassengerIndex                                   
// Process  : Loop through all the passengers
//             Get the current passenger
//                If passenger is invalid, flagged, riding, or done, continue
//             If the waiting status matches (going up/down)
//             or we don't care about direction (empty elevator)
//             and the curr passenger is flagged for pickup by another elevator
//                If the simulation time >= passenger start time
//                   Get the start floor
//                   If the passenger's start floor is within the input floors 
//                   or we don't care where the passenger is
//                      This is our next passenger
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
bool PassengerList::getNextDestinationPassengerIndex(
   const int time, 
   const Floor& currentFloor, 
   const Floor& endFloor, 
   const Passenger::Status status,
   int& nextPassengerIndex)
{
   bool  match          = false; // Determines if there is a match
   int   numPassengers  = 0;     // Number of passengers
   
   numPassengers = this->passengerList.size();

   // Loop through all the passengers
   for (int passIndex = 0; passIndex < numPassengers; ++passIndex)
   {
      // Get the current passenger
      Passenger currPassenger = this->passengerList.at(passIndex);

      // If this passenger is invalid, flagged, riding, or done, continue
      if (currPassenger.getStatus() == Passenger::NOT_SET                || 
          currPassenger.getStatus() == Passenger::QUEUED_WAITING_FLAGGED || 
          currPassenger.getStatus() == Passenger::RIDING                 || 
          currPassenger.getStatus() == Passenger::COMPLETED)
      {
         continue;
      }
      
      // If the waiting status matches (going up/down) 
      // or we don't care about direction (empty elevator)
      // and the current passenger is flagged for pickup by another elevator
      if ((status == currPassenger.getStatus() || 
           status == Passenger::NOT_SET)       && 
           currPassenger.getStatus() != Passenger::QUEUED_WAITING_FLAGGED)
      {
         // If the simulation time >= passenger start time
         if (time >= currPassenger.getStartTime())
         {
            // Get the start floor
            Floor currStartFloor;
            currPassenger.getStartFloor(currStartFloor);

            // If the passenger's start floor is within the input floors 
            // or we don't care where the passenger is
            if (currentFloor.getNumber() <= currStartFloor.getNumber() && 
                endFloor.getNumber() >= currStartFloor.getNumber() || 
                status == Passenger::NOT_SET)
            {
               // This is our next passenger
               nextPassengerIndex = currPassenger.getId();
               match = true;

               break;
            }
         }
      }
   }

   return match;
}

//******************************************************************************
// Function : getQueuedPassengersAtFloor                                   
// Process  : Loop through all the passengers
//             Get the current passenger
//                Don't consider passengers who have already completed riding
//             If the waiting status matches (going up/down)
//             or this is the elevator's destination passenger
//                If the simulation time >= passenger start time
//                   Get the start floor
//                   If the passenger's start floor equals the current floor
//                      Add this passenger to the list of matching passengers
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
bool PassengerList::getQueuedPassengersAtFloor(
   const int time, 
   const Floor& currentFloor, 
   const Passenger::Status status, 
   const int destPassengerIndex,
   vector<int>& nextPassengerIndex)
{
   bool  match          = false; // Determines if there is a match
   int   numPassengers  = 0;     // Number of passengers
   
   numPassengers = this->passengerList.size();

   // Loop through all the passengers
   for (int passIndex = 0; passIndex < numPassengers; ++passIndex)
   {
      // Get the current passenger
      Passenger currPassenger = this->passengerList.at(passIndex);

      // Don't consider passengers who have already completed riding
      if (currPassenger.getStatus() == Passenger::COMPLETED)
      {
         continue;
      }
            
      // If the waiting status matches (going up/down)
      // or this is the elevator's destination passenger
      if (status == currPassenger.getStatus() || 
          destPassengerIndex == passIndex)
      {
         // If the simulation time >= passenger start time
         if (time >= currPassenger.getStartTime())
         {
            // Get the start floor
            Floor currStartFloor;
            currPassenger.getStartFloor(currStartFloor);

            // If the passenger's start floor equals the current floor
            if (currentFloor.getNumber() == currStartFloor.getNumber())
            {
               // Add this passenger to the list of matching passengers
               nextPassengerIndex.push_back(currPassenger.getId());
               match = true;
            }
         }
      }
   }

   return match;
}

//******************************************************************************
// Function : resetPassengerStatusAndBoardExitTimesAt                                   
// Process  : Reset the passenger status
//             Reset the passenger board time
//             Reset the passenger exit time
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void PassengerList::resetPassengerStatusAndBoardExitTimesAt(const int index) 
{ 
   this->passengerList.at(index).resetStatus(); 
   this->passengerList.at(index).resetBoardTime(); 
   this->passengerList.at(index).resetExitTime(); 
}
