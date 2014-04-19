// COPYRIGHT © 2011, Donne Martin
// All Rights Reserved.
//
//******************************************************************************
//
// File Name:     Elevator.cpp
//
// File Overview: Represents a Elevator
//
//******************************************************************************
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added class
//******************************************************************************

#include "stdafx.h"
#include <iostream>
#include "Elevator.h"

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
Elevator::Elevator() 
{
   this->setMoveState(Elevator::STOPPED_NO_PASSENGERS);
   this->passengerListPtr     = PassengerList::getInstance();
   this->simulationTimePtr    = SimulationTime::getInstance();
   this->name                 = "";   
   this->timeToNextFloor      = Elevator::INVALID_VALUE;
   this->moveFloorTimer       = Elevator::INVALID_VALUE;
   this->stopTimer            = Elevator::INVALID_VALUE;
   this->setDestPassengerIndex(Elevator::INVALID_VALUE);
} // end Elevator::Elevator

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
Elevator::~Elevator()
{
} // end Elevator::~Elevator

//******************************************************************************
// Function : addPassengerAtIndex                                   
// Process  : Print that we picked up this passenger
//             Add this passenger to our list of passengers
//             Set this passenger's status to riding
//             If we have no destination passenger (this is our first passenger)  
//                Set this as our new destination passenger
//             Print the elevator's passengers
//                 
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Elevator::addPassengerAtIndex(const int index)
{
   // Print that we picked up this passenger
   this->printPassengerAction(" picked up  ", index);
   
   // Add this passenger to our list of passengers
   this->passengerIds.push_back(index);

   // Set this passenger's status to riding
   this->passengerListPtr->setPassengerStatusAt(
      index, 
      Passenger::RIDING, 
      this->getTime());
   
   // If we have no destination passenger (this is our first passenger)  
   if (this->destPassengerIndex == Elevator::INVALID_VALUE)
   {
      // Set this as our new destination passenger
      this->setDestPassengerIndex(index);

      // Sanity check
      if (passengerIds.size() != 1)
      {
         throw exception("Expected this to be our first passenger");
      }
   }

   // Print the elevator's passengers
   this->printPassengerIds();

   // Sanity check
   if (this->passengerIds.size() > Elevator::MAX_PASSENGERS)
   {
      throw exception("Picked up too many passengers");
   }

   // Sanity check
   if (this->passengerIds.size() == Elevator::MAX_PASSENGERS && 
      !this->isDestPassengerOnBoard())
   {
      throw exception("Elevator full, but dest passenger is not on board");
   }
}

//******************************************************************************
// Function : checkDropOffPassengers                                   
// Process  : If we have passengers on the elevator
//             Loop through all of our passengers
//                Get the end floor and passenger Id
//                If the end floor equals the elevator's current floor
//                   Add this passenger to our list to be dropped off
//             Begin stopping the elevator if our list is not empty
//                      
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Elevator::checkDropOffPassengers(const bool movedUp)
{
   int currEndFloorNumber  = Elevator::INVALID_VALUE; // Curr end floor number
   int currId              = Elevator::INVALID_VALUE; // Curr passenger Id

   list<int>::const_iterator iter;  // Const iterator to our list of passengers

   // If we have passengers on the elevator
   if (this->passengerIds.size() > 0)
   {      
      // Loop through all of our passengers
      for (iter = passengerIds.begin() ; iter != passengerIds.end(); iter++)
      {
         // Get the end floor and passenger Id
         currEndFloorNumber 
            = this->passengerListPtr->getPassengerEndFloorNumberAt(*iter);

         currId = this->passengerListPtr->getPassengerIdAt(*iter);

         // If the end floor equals the elevator's current floor,
         // Add this passenger to our list to be dropped off
         if (this->currFloor.getNumber() == currEndFloorNumber)
         {
            this->dropOffList.push_back(currId);
         }
      }
   }

   // Begin stopping the elevator if our list is not empty
   if (!this->dropOffList.empty())
   {
      this->setMoveStateToStopping(movedUp);
   }
}

//******************************************************************************
// Function : checkForNewDestinationPassenger                                   
// Process  : If we have a passenger matching our criteria...
//             If we don't have a dest passenger, flag next passenger as taken
//                Set as our next destination passenger
//                        
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Elevator::checkForNewDestinationPassenger()
{   
   bool  flagPassenger      = false; // Prevents mult elevators from setting 
                                     // this as our destination passenger

   int   nextPassengerIndex = Elevator::INVALID_VALUE; // Next passenger
   Passenger::Status status = Passenger::NOT_SET;      // Passenger status

   // If we don't have a destination passenger, flag the next passenger as taken
   // This will be our destination passenger
   if (this->destPassengerIndex == Elevator::INVALID_VALUE)
   {
      flagPassenger = true;
   }

   // Get passenger status based on our move state
   status = this->getMatchingPassengerStatus();

   // If we have a passenger matching our criteria...
   if (this->passengerListPtr->getNextDestinationPassengerIndex(this->getTime(), 
      this->currFloor, 
      this->destFloor, 
      status, 
      nextPassengerIndex))
   {
      // Flag this passenger as taken
      if (flagPassenger && nextPassengerIndex != Elevator::INVALID_VALUE)
      {
         // Set as our next destination passenger
         this->setDestPassengerIndex(nextPassengerIndex);
         this->passengerListPtr->setPassengerStatusAt(
            nextPassengerIndex, 
            Passenger::QUEUED_WAITING_FLAGGED, 
            this->getTime());
      }
   }
}

//******************************************************************************
// Function : checkPickupPassengers                                   
// Process  : If we moved up, check to pick up passengers QUEUED_WAITING_UP
//            If we moved down, check to pick up passengers QUEUED_WAITING_DOWN
//             Get our list of queued passengers who we can pick up at this floor
//             Begin stopping the elevator if our list is not empty
//                              
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Elevator::checkPickupPassengers(const bool movedUp)
{
   Passenger::Status status = Passenger::NOT_SET;  // Passenger status
   
   // If we moved up, check to pick up passengers who are QUEUED_WAITING_UP
   if (movedUp)
   {
      status = Passenger::QUEUED_WAITING_UP;
   }
   // If we moved down, check to pick up passengers who are QUEUED_WAITING_DOWN
   else
   {
      status = Passenger::QUEUED_WAITING_DOWN;
   }

   // Get our list of queued passengers who we can pick up at this floor
   this->passengerListPtr->getQueuedPassengersAtFloor(
      this->getTime(), 
      this->currFloor, 
      status, 
      this->destPassengerIndex, 
      this->pickUpList);
   
   // Begin stopping the elevator if our list is not empty
   if (!this->pickUpList.empty())
   {
      this->setMoveStateToStopping(movedUp);
   }
}

//******************************************************************************
// Function : determineNextDestinationPassenger                                   
// Process  : Determine if we are moving up or down
//
//             If we are moving up, check if we have any passengers that have 
//             end floors higher than our current floor and find the max
//             If there is such a passenger, continue moving up       
//                Loop through our list of passengers
//                   If there is a passenger with an end floor higher 
//                   than our current floor, continue moving up
//                If we are still moving up
//                   Find the passenger with the max end floor
//                Else
//                   All passengers on the elevator have end floors 
//                   below the current floor, find the passenger with the
//                   min end floor
//
//             If we are moving down, check if we have any passengers that have 
//             end floors lower than our current floor and find the min
//             If there is such a passenger, continue moving down
//                Loop through our list of passengers
//                   If there is a passenger with an end floor lower 
//                   than our current floor, continue moving down
//                If we are still moving down
//                   Find the passenger with the min end floor
//                Else
//                   All passengers on the elevator have end floors 
//                   above the current floor, find the passengerw ith the
//                   max end floor
//                      
// Notes    : This function is a little large, see if we can break this up
//             and maybe factor out some similar functionality in the 
//             next iteration
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Elevator::determineNextDestinationPassenger()
{
   list<int>::const_iterator iter;  // Const iterator of paseenger list
   bool movingUp = false;           // Determines if we are moving up or down

   // Determine if we are moving up or down
   switch (this->moveState)
   {
      case STOPPED_GOING_UP:
      case STOPPING_GOING_UP:
      case MOVING_UP:
      {
         movingUp = true;
         break;
      }
      case STOPPED_GOING_DOWN:
      case STOPPING_GOING_DOWN:
      case MOVING_DOWN:
      {
         movingUp = false;
         break;
      }
      default:
      {
         throw exception("Unexpected moveState!");
         break;
      }
   }
   
   // If we are moving up, check if we have any passengers that have 
   // end floors higher than our current floor and find the max
   // If there is such a passenger, continue moving up
   if (movingUp)
   {
      bool continueMovingUp = false; // Determines if we should continue up

      // Loop through our list of passengers
      for (iter = passengerIds.begin(); iter != passengerIds.end(); iter++)
      {
         // If there is a passenger with an end floor higher 
         // than our current floor, continue moving up
         if (this->passengerListPtr->
            getPassengerEndFloorNumberAt(*iter) > this->currFloor.getNumber())
         {
            continueMovingUp = true;
            break;
         }
      }

      // Find the passenger with the max end floor
      if (continueMovingUp)
      {
         this->setDestPassengerIndex(determinePassengerIdWithMaxEndFloor());
      }
      // All passengers on the elevator have end floors 
      // below the current floor, find the passenger with the min end floor
      else
      {
         this->setDestPassengerIndex(determinePassengerIdWithMinEndFloor());
      }
   }   

   // If we are moving down, check if we have any passengers that have 
   // end floors lower than our current floor and find the min
   // If there is such a passenger, continue moving down
   else
   {
      bool continueMovingDown = false; // Determines if we should continue down

      // Loop through our list of passengers
      for (iter = passengerIds.begin(); iter != passengerIds.end(); iter++)
      {
         // If there is a passenger with an end floor lower 
         // than our current floor, continue moving down
         if (this->passengerListPtr->
            getPassengerEndFloorNumberAt(*iter) < this->currFloor.getNumber())
         {
            continueMovingDown = true;
            break;
         }
      }

      // Find the passenger with the min end floor
      if (continueMovingDown)
      {
         this->setDestPassengerIndex(determinePassengerIdWithMinEndFloor());
      }
      // All passengers on the elevator have end floors 
      // above the current floor, find the passenger with the max end floor
      else
      {
         this->setDestPassengerIndex(determinePassengerIdWithMaxEndFloor());
      }
   }
}

//******************************************************************************
// Function : determinePassengerIdWithMaxEndFloor                                   
// Process  : Loop through all of our passengers
//             If this passenger's end floor is greater than our max floor
//             or this is our first pass          
//                Update the max floor to this passenger's end floor
//                Set the return value to this passenger who currently
//                has the highest floor
//                   
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
int Elevator::determinePassengerIdWithMaxEndFloor() const
{
   list<int>::const_iterator iter;              // Const iter of passenger Ids
   bool firstPass    = true;                    // First pass through loop
   int currMaxFloor = Elevator::INVALID_VALUE;  // Curr maximum floor
   int passengerId  = Elevator::INVALID_VALUE;  // Curr passenger Id

   // Loop through all of our passengers
   for (iter = passengerIds.begin(); iter != passengerIds.end(); iter++)
   {
      // If this passenger's end floor is greater than our max floor
      // or this is our first pass
      if (this->passengerListPtr->
         getPassengerEndFloorNumberAt(*iter) > currMaxFloor || firstPass)
      {
         // Update the max floor to this passenger's end floor
         currMaxFloor = this->passengerListPtr->
            getPassengerEndFloorNumberAt(*iter);

         // Set the return value to this passenger who currently
         // has the highest floor
         passengerId = this->passengerListPtr->getPassengerIdAt(*iter);

         firstPass = false;
      }
   }

   return passengerId;
}

//******************************************************************************
// Function : determinePassengerIdWithMinEndFloor                                   
// Process  : Loop through all of our passengers
//             If this passenger's end floor is less than our min floor
//             or this is our first pass        
//                Update the min floor to this passenger's end floor
//                Set the return value to this passenger who currently
//                has the lowest floor
//                          
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
int Elevator::determinePassengerIdWithMinEndFloor() const
{
   list<int>::const_iterator iter;               // Const iter of passenger Ids
   bool firstPass    = true;                     // First pass through loop
   int  currMinFloor = Elevator::INVALID_VALUE;  // Curr minimum floor
   int  passengerId  = Elevator::INVALID_VALUE;  // Curr passenger Id
   
   // Loop through all of our passengers
   for (iter = passengerIds.begin(); iter != passengerIds.end(); iter++)
   {
      // If this passenger's end floor is less than our min floor
      // or this is our first pass
      if (this->passengerListPtr->
         getPassengerEndFloorNumberAt(*iter) < currMinFloor || firstPass)
      {
         // Update the min floor to this passenger's end floor
         currMinFloor = this->passengerListPtr->
            getPassengerEndFloorNumberAt(*iter);

         // Set the return value to this passenger who currently
         // has the lowest floor
         passengerId = this->passengerListPtr->getPassengerIdAt(*iter);

         firstPass = false;
      }
   }

   return passengerId;
}

//******************************************************************************
// Function : doNextMove                                   
// Process  : Determine the next move for the elevator based on state
//             This function calls other functions to determine action
//             The only case that might need explanation: STOPPED_NO_PASSENGERS
//                Check if there are any passengers in the passenger list
//                If there is a passenger, get the one who got there soonest, 
//                flag him as taken by the elevator
//                               
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Elevator::doNextMove()
{
   switch (this->moveState)
   {
   case STOPPED_NO_PASSENGERS:
      {
         // Check if there are any passengers in the passenger list
         // If there is a passenger, get the one who got there the soonest, 
         // flag him as taken by the elevator
         this->checkForNewDestinationPassenger();
         this->moveTowardsDestinationPassengerFloor();
         break;
      }
      case STOPPED_GOING_UP:
      case STOPPED_GOING_DOWN:
      {
         this->handleStopped();
         break;
      }
      case STOPPING_GOING_UP:
      case STOPPING_GOING_DOWN:
      {
         this->handleStopping();
         break;
      }
      case MOVING_UP:
      {
         bool handleMovingUp = true;
         this->handleElevatorMove(handleMovingUp);
         break;
      }
      case MOVING_DOWN:
      {
         bool handleMovingUp = false;
         this->handleElevatorMove(handleMovingUp);
         break;
      }
      case INVALID_MOVE_STATE:
      default:
      {
         throw exception ("Invalid elevator MoveState!");
         break;
      }
   }
}

//******************************************************************************
// Function : dropOffPassengers                                   
// Process  : Loop through the list of passengers to drop off
//               Remove this passenger
//            Clear the list for next use         
//                      
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Elevator::dropOffPassengers()
{
   int numPassengers = this->dropOffList.size();   // Number of passengers
                                                   // to drop off

   // Loop through the list of passengers to drop off
   for (int currPassenger = 0; currPassenger < numPassengers; ++currPassenger)
   {
      // Remove this passenger
      this->removePassengerAtIndex(this->dropOffList[currPassenger]);
   }

   // Clear the list for next use
   this->dropOffList.clear();
}

//******************************************************************************
// Function : getMatchingPassengerStatus                                   
// Process  : If the elevator is stopped with no passengers
//                we will take any passenger
//             If the elevator is stopped or stopping...
//                If the destination passenger is on board, 
//                check the end floor vs the current floor to determine 
//                if the elevator's next move is going up or going down.
//                   If going up, our next passenger should be QUEUED_WAITING_UP
//                   Else, our next passenger should be QUEUED_WAITING_DOWN
//                Else, check the elevator's start floor vs the current floor
//                   If going up, our next passenger should be QUEUED_WAITING_UP
//                   Else, our next passenger should be QUEUED_WAITING_DOWN
//             If the elevator is moving up, 
//             our next passenger should be QUEUED_WAITING_UP
//             If the elevator is moving down, 
//             our next passenger should be QUEUED_WAITING_DOWN           
//                     
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
Passenger::Status Elevator::getMatchingPassengerStatus()
{
   Passenger::Status status = Passenger::NOT_SET;      // Passenger status

   switch (this->moveState)
   {
      // If the elevator is stopped with no passengers
      // we will take any passenger
      case STOPPED_NO_PASSENGERS:
      {
         status = Passenger::NOT_SET;
         break;
      }
      // If the elevator is stopped or stopping...
      case STOPPED_GOING_UP:
      case STOPPED_GOING_DOWN:
      case STOPPING_GOING_UP:
      case STOPPING_GOING_DOWN:
      {
         // Look at destination passenger
         if (this->destPassengerIndex == Elevator::INVALID_VALUE)
         {
            throw exception("Elevator moving without dest passenger set");
         }
         else
         {
            // If the destination passenger is on board, 
            // check the end floor vs the current floor to determine 
            // if the elevator's next move is going up or going down.
            if (this->isDestPassengerOnBoard())
            {
               // If going up, our next passenger should be QUEUED_WAITING_UP
               if (this->currFloor.getNumber() < this->passengerListPtr->
                  getPassengerEndFloorNumberAt(this->destPassengerIndex))
               {
                  status = Passenger::QUEUED_WAITING_UP;
               }
               // Else, our next passenger should be QUEUED_WAITING_DOWN
               else if (this->currFloor.getNumber() > this->passengerListPtr->
                  getPassengerEndFloorNumberAt(this->destPassengerIndex))
               {
                  status = Passenger::QUEUED_WAITING_DOWN;
               }
               else 
               {
                  throw exception("Unexpected start and end floor states");
               }
            }
            // Else, check the elevator's start floor vs the current floor
            else
            {
               // If going up, our next passenger should be QUEUED_WAITING_UP
               if (this->currFloor.getNumber() < this->passengerListPtr->
                  getPassengerStartFloorNumberAt(this->destPassengerIndex))
               {
                  status = Passenger::QUEUED_WAITING_UP;
               }
               // Else, our next passenger should be QUEUED_WAITING_DOWN
               else if (this->currFloor.getNumber() > this->passengerListPtr->
                  getPassengerStartFloorNumberAt(this->destPassengerIndex))
               {
                  status = Passenger::QUEUED_WAITING_DOWN;
               }
               else 
               {
                  throw exception("Unexpected start and end floor states");
               }
            }
         }

         break;
      }
      // If the elevator is moving up, 
      // our next passenger should be QUEUED_WAITING_UP
      case MOVING_UP:
      {
         status = Passenger::QUEUED_WAITING_UP;
         break;
      }
      // If the elevator is moving down, 
      // our next passenger should be QUEUED_WAITING_DOWN
      case MOVING_DOWN:
      {
         status = Passenger::QUEUED_WAITING_DOWN;
         break;
      }
      default:
      {
         throw exception("Invalid moveState!");
         break;
      }
   }

   return status;
}

//******************************************************************************
// Function : handleElevatorMove                                   
// Process  : If the elevator has reached its destination floor
//                If we are at a complete stop
//                   If we were moving up, 
//                      Set move state to STOPPED_GOING_UP
//                   If we were moving down, 
//                      Set move state to STOPPED_GOING_DOWN
//                Otherwise, decrement our stop tmer
//             Else, we have not yet reached destination floor
//                Decrement our move floor timer
//                If we are on a floor (not in between floors)
//                   If we are moving up, increment current floor by one
//                   If we are moving down, decrement current floor by one
//                   Check if there is anyone we can drop off
//                   Check if there is anyone we can pick up
//
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Elevator::handleElevatorMove(const bool movedUp)
{
   // If the elevator has reached its destination floor
   if (0 == this->moveFloorTimer)
   {
      // If we are at a complete stop
      if (0 == this->stopTimer)
      {
         // If we were moving up, update our move state to STOPPED_GOING_UP
         if (movedUp)
         {
            this->setMoveState(Elevator::STOPPED_GOING_UP);
         }
         // If we were moving down, update our move state to STOPPED_GOING_DOWN
         else
         {
            this->setMoveState(Elevator::STOPPED_GOING_DOWN);
         }
      }
      // Otherwise, decrement our stop tmer
      else
      {
         this->stopTimer--;
      }
   }
   // We have not yet reached destination floor
   else
   {
      // Decrement our move floor timer
      this->moveFloorTimer--;

      // If we are on a floor (not in between floors)
      if (0 == this->moveFloorTimer % this->timeToNextFloor)
      {
         // If we are moving up, increment current floor by one
         if (movedUp)
         {
            this->currFloor.incrementFloorNumber();
         }
         // If we are moving down, decrement current floor by one
         else {
            this->currFloor.decrementFloorNumber();
         }
         
         // Check if there is anyone we can drop off
         this->checkDropOffPassengers(movedUp);

         // Check if there is another passenger we can pick up
         this->checkPickupPassengers(movedUp);
      }
   }
}

//******************************************************************************
// Function : handleStopped                                   
// Process  : Pick up and drop off passengers
//             Begin moving towards the destination passenger's floor
//             
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Elevator::handleStopped()
{
   // Pick up and drop off passengers
   this->pickUpPassengers();
   this->dropOffPassengers();

   // Begin moving towards the destination passenger's floor
   this->moveTowardsDestinationPassengerFloor();
}

//******************************************************************************
// Function : handleStopping                                   
// Process  : Decrement our stopping timer
//             If we are stopped
//                Update our move state to STOPPED taking into account
//                the elevator's future direction (up/down)           
//                
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Elevator::handleStopping()
{
   // Decrement our stopping timer
   this->stopTimer--;

   // If we are stopped
   if (0 == this->stopTimer)
   {
      // Update our move state to STOPPED taking into account
      // the elevator's future direction (up/down)
      if (this->moveState == Elevator::STOPPING_GOING_UP)
      {
         this->setMoveState(Elevator::STOPPED_GOING_UP);
      }
      else if (this->moveState == Elevator::STOPPING_GOING_DOWN)
      {
         this->setMoveState(Elevator::STOPPED_GOING_DOWN);
      }
      else 
      {
         throw exception("Expected elevator to be stopping");
      }
   }
}

//******************************************************************************
// Function : isDestPassengerOnBoard                                   
// Process  : Loop through all the passengers
//             If this passenger is our destination passenger,
//                update the return value and break           
//                        
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
bool Elevator::isDestPassengerOnBoard() const
{
   list<int>::const_iterator iter;  // Const iterator to our list of passengers
   bool isOnBoard = false;          // Determines if the destination
                                    // passenger is on board
   
   // Loop through all the passengers
   for (iter = passengerIds.begin() ; iter != passengerIds.end(); iter++)
   {
      // If this passenger is our destination passenger,
      // update the return value and break
      if (this->passengerListPtr->
         getPassengerIdAt(*iter) == this->destPassengerIndex)
      {
         isOnBoard = true;
         break;
      }
   }

   return isOnBoard;
}

//******************************************************************************
// Function : moveDown                                   
// Process  : Update the move state
//             Update the floor timer to reflect the total move time
//             to our destination floor          
//             Set the stop timer
//                          
// Notes    : This seems very similar to moveUp, see if we can refactor
//             in the next revision
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Elevator::moveDown(const int numFloors)
{
   // Update the move state
   this->setMoveState(Elevator::MOVING_DOWN);
   
   // Update the floor timer to reflect the total move time
   // to our destination floor
   this->moveFloorTimer 
      = numFloors * this->timeToNextFloor + this->timeToNextFloor;

   // Set the stop timer
   this->stopTimer = Elevator::SEC_STOP;
}

//******************************************************************************
// Function : moveUp                                   
// Process  : Update the move state
//             Update the floor timer to reflect the total move time
//             to our destination floor   
//             Set the stop time
//                     
// Notes    : This seems very similar to moveDown, see if we can refactor
//             in the next revision
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Elevator::moveUp(const int numFloors)
{
   // Update the move state
   this->setMoveState(Elevator::MOVING_UP);

   // Update the floor timer to reflect the total move time
   // to our destination floor
   this->moveFloorTimer 
      = numFloors * this->timeToNextFloor + this->timeToNextFloor;
   
   // Set the stop timer
   this->stopTimer = Elevator::SEC_STOP;
}

//******************************************************************************
// Function : moveTowardsDestinationPassengerFloor                                   
// Process  : If we have a destination passenger set
//             If the destination passenger is on the elevator, 
//                Move to his end floor so we can drop him off            
//             Else
//                Move towards his start floor so we can pick him up
//             If the destination floor is less than our current floor
//                We need to move up      
//             Else
//                We need to move down
//                       
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Elevator::moveTowardsDestinationPassengerFloor()
{
   // If we have a destination passenger set
   if (this->destPassengerIndex != Elevator::INVALID_VALUE)
   {
      int destFloorNumber = Elevator::INVALID_VALUE;    // Dest floor number
      
      // If the destination passenger is on the elevator, move to his end floor
      // so we can drop him off
      if (this->isDestPassengerOnBoard())
      {
         destFloorNumber = this->passengerListPtr->
            getPassengerEndFloorNumberAt(this->destPassengerIndex);
      }
      // Otherwise, move towards his start floor so we can pick him up
      else
      {
         destFloorNumber = this->passengerListPtr->
            getPassengerStartFloorNumberAt(this->destPassengerIndex);
      }

      // If the destination floor is less than our current floor
      // we need to move up
      if (this->currFloor.getNumber() < destFloorNumber)
      {
         this->moveUp(destFloorNumber - this->currFloor.getNumber());

      }
      // Otherwise, we need to move down
      else
      {
         this->moveDown(this->currFloor.getNumber() - destFloorNumber);
      }
   }
}

//******************************************************************************
// Function : pickUpPassengers                                   
// Process  : Loop through the list of passengers to drop off
//             If we have one minus the maximum number of passengers,
//                only allow the destination passenger to board          
//                   If this is our destination passenger
//                      Add this passenger
//             Otherwise, allow any passenger to board, up to elevator capacity
//                       
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Elevator::pickUpPassengers()
{
   int numPassengers = this->pickUpList.size();    // Number of passengers
                                                   // to pick up

   // Loop through the list of passengers to drop off
   for (int currPassenger = 0; currPassenger < numPassengers; ++currPassenger)
   {
      // If we have one minus the maximum number of passengers,
      // only allow the destination passenger to board
      if (this->passengerIds.size() == Elevator::MAX_PASSENGERS - 1 && 
         !this->isDestPassengerOnBoard())
      {
         // If this is our destination passenger
         if (this->pickUpList[currPassenger] == this->destPassengerIndex)
         {
            // Add this passenger
            this->addPassengerAtIndex(this->pickUpList[currPassenger]);
         }
      }
      // Otherwise, allow any passenger to board, up to elevator capacity
      else if (this->passengerIds.size() < Elevator::MAX_PASSENGERS)
      {
         this->addPassengerAtIndex(this->pickUpList[currPassenger]);
      }
   }

   // Sanity check
   if (this->passengerIds.size() > Elevator::MAX_PASSENGERS)
   {
      throw exception("Picked up too many passengers");
   }
   
   // Clear the list for next use
   this->pickUpList.clear();
}

//******************************************************************************
// Function : printMoveState                                   
// Process  : Print a text version of the move state to cout
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Elevator::printMoveState() const
{
   switch (this->moveState)
   {
      case INVALID_MOVE_STATE:
      {
         cout << "INVALID_MOVE_STATE";
         break;
      }
      case STOPPED_NO_PASSENGERS:
      {
         cout << "STOPPED_NO_PASSENGERS";
         break;
      }
      case STOPPED_GOING_UP:
      {
         cout << "STOPPED_GOING_UP";
         break;
      }
      case STOPPED_GOING_DOWN:
      {
         cout << "STOPPED_GOING_DOWN";
         break;
      }
      case STOPPING_GOING_UP:
      {
         cout << "STOPPING_GOING_UP";
         break;
      }
      case STOPPING_GOING_DOWN:
      {
         cout << "STOPPING_GOING_DOWN";
         break;
      }
      case MOVING_UP:
      {
         cout << "MOVING_UP";
         break;
      }
      case MOVING_DOWN:
      {
         cout << "MOVING_DOWN";
         break;
      }
      default:
      {
         throw exception("Unexpected moveState!");
         break;
      }
   }
}

//******************************************************************************
// Function : printPassengerAction                                   
// Process  : Prints the specified passenger action to cout
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Elevator::printPassengerAction(const string& action, const int index) const
{
   cout << this->name;
   cout << action;
   cout << " Passenger: " << index;
   cout << " Floor: " << this->currFloor.getNumber();
   cout << " Time: " << this->getTime() << " sec";
   cout << endl;
}

//******************************************************************************
// Function : printPassengerIds                                   
// Process  : Loop through all passengers
//             Output the current passenger's Id
//             If this is our destination passenger, add an asterisk
//                    
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Elevator::printPassengerIds() const
{
   cout << "   " << this->name << " Passengers: [ ";

   list<int>::const_iterator iter;  // Const iterator of passenger Ids

   // Loop through all passengers
   for (iter = this->passengerIds.begin(); 
       iter != this->passengerIds.end(); 
       iter++)
   {
      // Output the current passenger's Id
      cout << *iter;

      // If this is our destination passenger, add an asterisk
      if (*iter == this->destPassengerIndex)
      {
         cout << "*";
      }

      cout << " ";
   }

   cout << "]" << endl;   
}

//******************************************************************************
// Function : removePassengerAtIndex                                   
// Process  : Print that we picked up this passenger
//             Remove this passenger from out list of passengers
//             Set this passenger's status to completed
//             If we just unloaded our destination passenger, 
//                Check our passengers for the next destination passenger
//             Print the elevator's passengers
//             If we have no more passengers
//                Update our state to stopped with no passengers         
//                      
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Elevator::removePassengerAtIndex(const int index)
{
   // Print that we picked up this passenger
   this->printPassengerAction(" dropped off", index);

   // Remove this passenger from out list of passengers
   this->passengerIds.remove(index);

   // Set this passenger's status to completed
   this->passengerListPtr->setPassengerStatusAt(
      index, 
      Passenger::COMPLETED, 
      this->getTime());
   
   // If we just unloaded our destination passenger, 
   // check our passengers for the next destination passenger
   if (index == this->destPassengerIndex)
   {
      this->setDestPassengerIndex(Elevator::INVALID_VALUE);
      this->determineNextDestinationPassenger();
   }

   // Print the elevator's passengers
   this->printPassengerIds();
      
   // If we have no more passengers, update our state
   // to stopped with no passengers
   if (this->passengerIds.empty())
   {
      this->setMoveState(Elevator::STOPPED_NO_PASSENGERS);
   }
}

//******************************************************************************
// Function : setMoveStateToStopping                                   
// Process  : If we moved up, set our move state to STOPPING_GOING_UP
//            If we moved down, set our move state to STOPPING_GOING_DOWN                    
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Elevator::setMoveStateToStopping(const bool movedUp)
{
   // If we moved up, set our move state to STOPPING_GOING_UP
   if (movedUp)
   {
      this->setMoveState(Elevator::STOPPING_GOING_UP);
   }
   // If we moved down, set our move state to STOPPING_GOING_DOWN
   else 
   {
      this->setMoveState(Elevator::STOPPING_GOING_DOWN);
   }
}
