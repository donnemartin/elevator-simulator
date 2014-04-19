//******************************************************************************
//
// File Name:     PassengerList.h
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

#ifndef PassengerList_h
#define PassengerList_h

#include <vector>
#include <list>
#include "Passenger.h"

using namespace std;

//******************************************************************************
//
// Class:    PassengerList
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added class
//
// Notes: None
//
//******************************************************************************
class PassengerList
{
public:

   //***************************************************************************
   // Function    : destructor                                   
   // Description : None            
   // Constraints : None
   //***************************************************************************
   virtual ~PassengerList();   

   // Member functions in alphabetical order   

   //***************************************************************************
   // Function    : addPassenger                                   
   // Description : Adds the passenger to the list            
   // Constraints : None
   //***************************************************************************
   inline void addPassenger(const Passenger& passenger);
   
   //***************************************************************************
   // Function    : getInstance                                   
   // Description : Retrieves the single instance of the class            
   // Constraints : None
   //***************************************************************************
   inline static PassengerList* getInstance();
   
   //***************************************************************************
   // Function    : getNextDestinationPassengerIndex                                   
   // Description : Retrieves the next destination passenger matching
   //                the input criteria
   // Constraints : None
   //***************************************************************************
   bool getNextDestinationPassengerIndex(
      const int time, 
      const Floor& currentFloor, 
      const Floor& endFloor, 
      const Passenger::Status status,
      int& passengerIndex);
   
   //***************************************************************************
   // Function    : getPassengerBoardElevatorTimeAt                                   
   // Description : Retrieves the board elevator time of the specified passenger            
   // Constraints : None
   //***************************************************************************
   inline int getPassengerBoardElevatorTimeAt(const int index) const;

   //***************************************************************************
   // Function    : getPassengerEndFloorNumberAt                                   
   // Description : Retrieves the end floor number of the specified passenger              
   // Constraints : None
   //***************************************************************************
   inline int getPassengerEndFloorNumberAt(const int index) const;

   //***************************************************************************
   // Function    : getPassengerExitElevatorTimeAt                                   
   // Description : Retrieves the exit elevator time of the specified passenger              
   // Constraints : None
   //***************************************************************************
   inline int getPassengerExitElevatorTimeAt(const int index) const;

   //***************************************************************************
   // Function    : getPassengerIdAt                                   
   // Description : Retrieves the id of the specified passenger              
   // Constraints : None
   //***************************************************************************
   inline int getPassengerIdAt(const int index) const;

   //***************************************************************************
   // Function    : getPassengerListSize                                   
   // Description : Retrieves the passenger list size              
   // Constraints : None
   //***************************************************************************
   inline int getPassengerListSize() const;   

   //***************************************************************************
   // Function    : getPassengerStartFloorNumberAt                                   
   // Description : Retrieves the start floor number of the specified passenger              
   // Constraints : None
   //***************************************************************************
   inline int getPassengerStartFloorNumberAt(const int index) const;

   //***************************************************************************
   // Function    : getPassengerStartTimeAt                                   
   // Description : Retrieves the start time of the specified passenger              
   // Constraints : None
   //***************************************************************************
   inline int getPassengerStartTimeAt(const int index) const;

   //***************************************************************************
   // Function    : getPassengerStatusAt                                   
   // Description : Retrieves the status of the specified passenger            
   // Constraints : None
   //***************************************************************************
   inline Passenger::Status getPassengerStatusAt(const int index) const;
   
   //***************************************************************************
   // Function    : getQueuedPassengersAtFloor                                   
   // Description : Retrieves a list of queued passengers at a specified floor
   //                that matches the input criteria
   // Constraints : None
   //***************************************************************************
   bool getQueuedPassengersAtFloor(
      const int time, 
      const Floor& currentFloor, 
      const Passenger::Status status, 
      const int destPassengerIndex,
      vector<int>& nextPassengerIndex);

   //***************************************************************************
   // Function    : resetPassengerStatusAndBoardExitTimesAt                                   
   // Description : Resets the passenger status and elevator board/exit times            
   // Constraints : None
   //***************************************************************************
   void resetPassengerStatusAndBoardExitTimesAt(const int index);

   //***************************************************************************
   // Function    : setPassengerStatusAt                                   
   // Description : Sets the status of the specified passenger            
   // Constraints : None
   //***************************************************************************
   inline void setPassengerStatusAt(const int index, Passenger::Status status, const int time);

   //***************************************************************************
   // public Class Attributes
   //***************************************************************************

private:   
   
   //***************************************************************************
   // Function    : constructor                                   
   // Description : None
   // Constraints : None
   //***************************************************************************
   PassengerList();
   
   static PassengerList*   instancePtr;         // Pointer to itself (singleton)
                                                // we are processing
   vector<Passenger>       passengerList;       // List of queued passengers
}; // end class PassengerList

//******************************************************************************
// Function : addPassenger                                   
// Process  : Add the specified passenger to our list of passengers           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline void PassengerList::addPassenger(const Passenger& passenger) 
{ 
   this->passengerList.push_back(passenger); 
}

//******************************************************************************
// Function : getInstance                                   
// Process  : Retrieve the single instance to the class if it exists
//             Else, create it, then return
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline PassengerList* PassengerList::getInstance()
{
   if (!instancePtr)
   {
      instancePtr = new PassengerList;
   }

   return instancePtr;
}

//******************************************************************************
// Function : getPassengerBoardElevatorTimeAt                                   
// Process  : Retrieves the board elevator time of the specified passenger           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline int PassengerList::getPassengerBoardElevatorTimeAt(const int index) const 
{ 
   return this->passengerList.at(index).getBoardElevatorTime(); 
}

//******************************************************************************
// Function : getPassengerEndFloorNumberAt                                   
// Process  : Retrieves the end floor number of the specified passenger           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline int PassengerList::getPassengerEndFloorNumberAt(const int index) const 
{ 
   return this->passengerList.at(index).getEndFloorNumber(); 
}

//******************************************************************************
// Function : getPassengerExitElevatorTimeAt                                   
// Process  : Retrieves the exit elevator time of the specified passenger           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline int PassengerList::getPassengerExitElevatorTimeAt(const int index) const 
{ 
   return this->passengerList.at(index).getExitElevatorTime(); 
}

//******************************************************************************
// Function : getPassengerIdAt                                   
// Process  : Retrieves the id of the specified passenger           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline int PassengerList::getPassengerIdAt(const int index) const 
{ 
   return this->passengerList.at(index).getId(); 
}

//******************************************************************************
// Function : getPassengerListSize                                   
// Process  : Retrieves the passenger list size
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline int PassengerList::getPassengerListSize() const 
{ 
   return this->passengerList.size(); 
}
   
//******************************************************************************
// Function : getPassengerStartFloorNumberAt                                   
// Process  : Retrieves the start floor number of the specified passenger           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline int PassengerList::getPassengerStartFloorNumberAt(const int index) const 
{ 
   return this->passengerList.at(index).getStartFloorNumber(); 
}

//******************************************************************************
// Function : getPassengerStartTimeAt                                   
// Process  : Retrieves the start time of the specified passenger           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline int PassengerList::getPassengerStartTimeAt(const int index) const 
{ 
   return this->passengerList.at(index).getStartTime(); 
}

//******************************************************************************
// Function : getPassengerStatusAt                                   
// Process  : Retrieves the status of the specified passenger           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline Passenger::Status PassengerList::getPassengerStatusAt(const int index) const 
{ 
   return this->passengerList.at(index).getStatus(); 
}

//******************************************************************************
// Function : setPassengerStatusAt                                   
// Process  : Sets the status of the specified passenger           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline void PassengerList::setPassengerStatusAt(const int index, Passenger::Status status, const int time) 
{ 
   this->passengerList.at(index).setStatus(status, time); 
}

#endif // PassengerList_h
