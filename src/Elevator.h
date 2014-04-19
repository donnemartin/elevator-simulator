//******************************************************************************
//
// File Name:     Elevator.h
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

#ifndef Elevator_h
#define Elevator_h

#include <list>
#include "Passenger.h"
#include "PassengerList.h"
#include "SimulationTime.h"

using namespace std;

//******************************************************************************
//
// Class:    Elevator
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added class
//
// Notes: None
//
//******************************************************************************
class Elevator
{
public:
   
   //***************************************************************************
   // Function    : constructor                                   
   // Description : None
   // Constraints : None
   //***************************************************************************
   Elevator();

   //***************************************************************************
   // Function    : destructor                                   
   // Description : None            
   // Constraints : None
   //***************************************************************************
   virtual ~Elevator();   

   // Member functions in alphabetical order   
   
   enum MoveState;   // Oddly, seems to be required by Visual Studio
                     // to avoid compile errors
      
   //***************************************************************************
   // Function    : addPassengerAtIndex                                   
   // Description : Adds the specified passenger to our list            
   // Constraints : None
   //***************************************************************************
   void addPassengerAtIndex(const int index);
      
   //***************************************************************************
   // Function    : checkDropOffPassengers                                   
   // Description : Checks if there are any passengers to drop off            
   // Constraints : None
   //***************************************************************************
   void checkDropOffPassengers(const bool movedUp);
      
   //***************************************************************************
   // Function    : checkForNewDestinationPassenger                                   
   // Description : Checks for our new destination passenger            
   // Constraints : None
   //***************************************************************************
   void checkForNewDestinationPassenger();
      
   //***************************************************************************
   // Function    : checkPickupPassengers                                   
   // Description : Checks if there are any passengers to pick up            
   // Constraints : None
   //***************************************************************************
   void checkPickupPassengers(const bool movedUp);
      
   //***************************************************************************
   // Function    : determineNextDestinationPassenger                                   
   // Description : Determines which passenger should be our dest passenger
   //                Called after our dest passenger has been unloaded
   // Constraints : None
   //***************************************************************************
   void determineNextDestinationPassenger();
      
   //***************************************************************************
   // Function    : determinePassengerIdWithMaxEndFloor                                   
   // Description : Looks at our list of passengers to determine the next
   //                destination passenger based on the one who has the
   //                highest end floor since the elevator is going up
   // Constraints : Relies on determinePassengerIdWithMaxEndFloor
   //               Relies on determinePassengerIdWithMinEndFloor
   //***************************************************************************
   int determinePassengerIdWithMaxEndFloor() const;
      
   //***************************************************************************
   // Function    : determinePassengerIdWithMinEndFloor                                   
   // Description : Looks at our list of passengers to determine the next
   //                destination passenger based on the one who has the
   //                lowest end floor since the elevator is going down         
   // Constraints : None
   //***************************************************************************
   int determinePassengerIdWithMinEndFloor() const;
      
   //***************************************************************************
   // Function    : dropOffPassengers                                   
   // Description : Drops off passengers in dropOffList at the current floor            
   // Constraints : None
   //***************************************************************************
   void dropOffPassengers();
      
   //***************************************************************************
   // Function    : doNextMove                                   
   // Description : Performs the elevator's next move            
   // Constraints : None
   //***************************************************************************
   void doNextMove();
      
   //***************************************************************************
   // Function    : getMatchingPassengerStatus                                   
   // Description : Retrieves the matching passenger status based on
   //                the elevator's current move state
   // Constraints : None
   //***************************************************************************
   Passenger::Status getMatchingPassengerStatus();
      
   //***************************************************************************
   // Function    : getName                                   
   // Description : Access for name            
   // Constraints : None
   //***************************************************************************
   inline void getName(string& name) const;
      
   //***************************************************************************
   // Function    : getTime                                   
   // Description : Accessor for time            
   // Constraints : None
   //***************************************************************************
   inline int getTime() const;
      
   //***************************************************************************
   // Function    : handleElevatorMove                                   
   // Description : Handles the elevator movement up or down            
   // Constraints : None
   //***************************************************************************
   void handleElevatorMove(const bool movedUp);
      
   //***************************************************************************
   // Function    : handleStopped                                   
   // Description : Handles the stopped elevator            
   // Constraints : None
   //***************************************************************************
   void handleStopped();
      
   //***************************************************************************
   // Function    : handleStopping                                   
   // Description : Handles the elevator that is going to stop            
   // Constraints : None
   //***************************************************************************
   void handleStopping();
      
   //***************************************************************************
   // Function    : isDestPassengerOnBoard                                   
   // Description : Determines if the destination passenger is on board            
   // Constraints : None
   //***************************************************************************
   bool isDestPassengerOnBoard() const;
      
   //***************************************************************************
   // Function    : moveDown                                   
   // Description : Handles the elevator moving down            
   // Constraints : None
   //***************************************************************************
   void moveDown(const int numFloors);
      
   //***************************************************************************
   // Function    : moveTowardsDestinationPassengerFloor                                   
   // Description : Moves towards the destination passenger's floor            
   // Constraints : None
   //***************************************************************************
   void moveTowardsDestinationPassengerFloor();
      
   //***************************************************************************
   // Function    : moveUp                                   
   // Description : Handles the elevator moving up            
   // Constraints : None
   //***************************************************************************
   void moveUp(const int numFloors);
      
   //***************************************************************************
   // Function    : pickUpPassengers                                   
   // Description : Picks up passengers in pickUpList at the current floor             
   // Constraints : None
   //***************************************************************************
   void pickUpPassengers();
      
   //***************************************************************************
   // Function    : printMoveState                                   
   // Description : Prints the move state (string as opposed to int) to cout            
   // Constraints : None
   //***************************************************************************
   void printMoveState() const;
      
   //***************************************************************************
   // Function    : printPassengerAction                                   
   // Description : Prints the passengeer action to cout            
   // Constraints : None
   //***************************************************************************
   void printPassengerAction(const string& action, const int index) const;
      
   //***************************************************************************
   // Function    : printPassengerIds                                   
   // Description : Prints the list of passenger ids to cout            
   // Constraints : None
   //***************************************************************************
   void printPassengerIds() const;
      
   //***************************************************************************
   // Function    : removePassengerAtIndex                                   
   // Description : Removes the specified passenger from the elevator            
   // Constraints : None
   //***************************************************************************
   void removePassengerAtIndex(const int index);
      
   //***************************************************************************
   // Function    : setDestPassengerIndex                                   
   // Description : Mutator for destPassengerIndex          
   // Constraints : None
   //***************************************************************************
   inline void setDestPassengerIndex(const int index);
      
   //***************************************************************************
   // Function    : setMoveState                                   
   // Description : Mutator for destPassengerIndex             
   // Constraints : None
   //***************************************************************************
   inline void setMoveState(const Elevator::MoveState moveState);
      
   //***************************************************************************
   // Function    : setMoveStateToStopping                                   
   // Description : Sets the elevator move state to STOPPING_GOING_UP or _DOWN          
   // Constraints : None
   //***************************************************************************
   void setMoveStateToStopping(const bool movedUp);
      
   //***************************************************************************
   // Function    : setName                                   
   // Description : Mutator for name             
   // Constraints : None
   //***************************************************************************
   inline void setName(const string& name);
      
   //***************************************************************************
   // Function    : setTimeToNextFloor                                   
   // Description : Mutator for timeToNextFloor             
   // Constraints : None
   //***************************************************************************
   inline void setTimeToNextFloor(const int timeToNextFloor);

   //***************************************************************************
   // public Class Attributes
   //***************************************************************************

   // Elevator movement state
   enum MoveState
   {
      INVALID_MOVE_STATE = -1,
      STOPPED_NO_PASSENGERS,
      STOPPED_GOING_UP,
      STOPPED_GOING_DOWN,
      STOPPING_GOING_UP,
      STOPPING_GOING_DOWN,
      MOVING_UP,
      MOVING_DOWN
   };
   
   static const int INVALID_VALUE      = -1;  // Invalid value
   static const int MAX_PASSENGERS      = 8;  // Number of passengers/elevator
   static const int SEC_STOP            = 2;  // Time from STOPPING TO STOPPED
                                    
private:   
   Floor             currFloor;           // Current floor the elevator was on
   Floor             destFloor;           // Destination floor
   int               destPassengerIndex;  // Destination passenger index
   vector<int>       dropOffList;         // Vector of passengers to drop off
   int               moveFloorTimer;      // Timer to move between destination
   MoveState         moveState;           // Elevator move state
   string            name;                // Elevator name
   list<int>         passengerIds;        // List of Passengers ids on the elevator
   PassengerList*    passengerListPtr;    // List of Passengers (singleton)
   vector<int>       pickUpList;          // Vector of passengers to pick up
   SimulationTime*   simulationTimePtr;   // Simulation time (singleton)
   int               stopTimer;           // Current timer to stop
   int               timeToNextFloor;     // Time in seconds to move between floors

}; // end class Elevator

//******************************************************************************
// Function : getName                                   
// Process  : Accessor for name           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline void Elevator::getName(string& name) const 
{ 
   name = this->name; 
}

//******************************************************************************
// Function : getTime                                   
// Process  : Accessor for time           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline int Elevator::getTime() const 
{ 
   return this->simulationTimePtr->getTime(); 
}

//******************************************************************************
// Function : setDestPassengerIndex                                   
// Process  : Mutator for destPassengerIndex           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline void Elevator::setDestPassengerIndex(const int index) 
{ 
   this->destPassengerIndex = index; 
}

//******************************************************************************
// Function : setMoveState                                   
// Process  : Mutator for moveState            
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline void Elevator::setMoveState(const Elevator::MoveState moveState)
{
   this->moveState = moveState;
}

//******************************************************************************
// Function : setName                                   
// Process  : Mutator for name            
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline void Elevator::setName(const string& name) 
{ 
   this->name = name; 
}

//******************************************************************************
// Function : setTimeToNextFloor                                   
// Process  : Mutator for timeToNextFloor            
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline void Elevator::setTimeToNextFloor(const int timeToNextFloor) 
{ 
   this->timeToNextFloor = timeToNextFloor; 
}

#endif // Elevator_h
