//******************************************************************************
//
// File Name:     Passenger.h
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

#ifndef Passenger_h
#define Passenger_h

#include <iostream>
#include <string>
#include "Floor.h"

using namespace std;

//******************************************************************************
//
// Class:    Passenger
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added class
//
// Notes: None
//
//******************************************************************************
class Passenger
{
public:
      
   //***************************************************************************
   // Function    : constructor                                   
   // Description : None
   // Constraints : None
   //***************************************************************************
   Passenger();

   //***************************************************************************
   // Function    : destructor                                   
   // Description : None            
   // Constraints : None
   //***************************************************************************
   virtual ~Passenger();   

   enum Status;   // Oddly, seems to be required by Visual Studio
                  // to avoid compile errors

   // Member functions in alphabetical order   
   inline int getBoardElevatorTime() const;
      
   //***************************************************************************
   // Function    : getEndFloor                                   
   // Description : Accessor for             
   // Constraints : None
   //***************************************************************************
   inline void getEndFloor(Floor& endFloor) const;
      
   //***************************************************************************
   // Function    : getEndFloorNumber                                   
   // Description : Accessor for               
   // Constraints : None
   //***************************************************************************
   inline int getEndFloorNumber() const;
      
   //***************************************************************************
   // Function    : getExitElevatorTime                                   
   // Description : Accessor for               
   // Constraints : None
   //***************************************************************************
   inline int getExitElevatorTime() const;
      
   //***************************************************************************
   // Function    : getId                                   
   // Description : Accessor for               
   // Constraints : None
   //***************************************************************************
   inline int getId() const;
      
   //***************************************************************************
   // Function    : getStartTime                                   
   // Description : Accessor for               
   // Constraints : None
   //***************************************************************************
   inline int getStartTime() const;
      
   //***************************************************************************
   // Function    : getStartFloor                                   
   // Description : Accessor for               
   // Constraints : None
   //***************************************************************************
   inline void getStartFloor(Floor& startFloor) const;
      
   //***************************************************************************
   // Function    : getStartFloorNumber                                   
   // Description : Accessor for               
   // Constraints : None
   //***************************************************************************
   inline int getStartFloorNumber() const;
      
   //***************************************************************************
   // Function    : getStatus                                   
   // Description : Accessor for               
   // Constraints : None
   //***************************************************************************
   inline Passenger::Status getStatus() const;
      
   //***************************************************************************
   // Function    : printStatus                                   
   // Description : Prints the status in text (opposed to int)            
   // Constraints : None
   //***************************************************************************
   void printStatus() const;
      
   //***************************************************************************
   // Function    : resetBoardTime                                   
   // Description : Resets boardElevatorTime to INIT_TO_INVALID               
   // Constraints : None
   //***************************************************************************
   inline void resetBoardTime();
      
   //***************************************************************************
   // Function    : resetExitTime                                   
   // Description : Resets exitElevatorTime to INIT_TO_INVALID            
   // Constraints : None
   //***************************************************************************
   inline void resetExitTime();
      
   //***************************************************************************
   // Function    : resetStatus                                   
   // Description : Resets status to NOT_SET            
   // Constraints : None
   //***************************************************************************
   inline void resetStatus();
      
   //***************************************************************************
   // Function    : setEndFloor                                   
   // Description : Mutator for endFloor            
   // Constraints : None
   //***************************************************************************
   inline void setEndFloor(const Floor& endFloor);
      
   //***************************************************************************
   // Function    : setId                                   
   // Description : Mutator for id            
   // Constraints : None
   //***************************************************************************
   inline void setId(const int id);
      
   //***************************************************************************
   // Function    : setStartFloor                                   
   // Description : Mutator for startFloor            
   // Constraints : None
   //***************************************************************************
   inline void setStartFloor(const Floor& startFloor);
      
   //***************************************************************************
   // Function    : setStartTime                                   
   // Description : Mutator for startTime             
   // Constraints : None
   //***************************************************************************
   inline void setStartTime(const int startTime);
      
   //***************************************************************************
   // Function    : setStatus                                   
   // Description : Mutator for status      
   //                Updates passenger boardElevatorTime and exitElevatorTime 
   // Constraints : None
   //***************************************************************************
   void setStatus(const Passenger::Status status, int time);

   //***************************************************************************
   // public Class Attributes
   //***************************************************************************
   
   // Determines passenger status
   enum Status
   {
      NOT_SET = -1,
      QUEUED_WAITING_FLAGGED,
      QUEUED_WAITING_UP,
      QUEUED_WAITING_DOWN,
      RIDING,
      COMPLETED
   };

   static const int INIT_TO_INVALID = -1; // Invalid value

private:   
      
   //***************************************************************************
   // Function    : setBoardElevatorTime                                   
   // Description : Mutator for boardElevatorTime            
   // Constraints : Private, call setStatus instead
   //***************************************************************************
   inline void setBoardElevatorTime(const int boardElevatorTime);
      
   //***************************************************************************
   // Function    : setExitElevatorTime                                   
   // Description : Mutator for exitElevatorTime          
   // Constraints : Private, call setStatus instead
   //***************************************************************************
   inline void setExitElevatorTime(const int exitElevatorTime);

   int         id;                // Passenger id
   int         startTime;         // Start time in seconds
   Floor       startFloor;        // Start floor
   Floor       endFloor;          // End floor
   Status      status;            // Passenger status
   int         boardElevatorTime; // Used to calculate wait time 
                                  // until picked up by elevator
   int         exitElevatorTime;  // Used to calculate travel time on the elevator

}; // end class Passenger

//******************************************************************************
// Function : getBoardElevatorTime                                   
// Process  : Accessor for boardElevatorTime           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline int Passenger::getBoardElevatorTime() const 
{ 
   return this->boardElevatorTime; 
}

//******************************************************************************
// Function : getEndFloor                                   
// Process  : Accessor for endFloor          
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline void Passenger::getEndFloor(Floor& endFloor) const 
{ 
   endFloor = this->endFloor; 
}

//******************************************************************************
// Function : getEndFloorNumber                                   
// Process  : Accessor for endFloor's number          
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline int Passenger::getEndFloorNumber() const 
{ 
   return this->endFloor.getNumber(); 
}

//******************************************************************************
// Function : getExitElevatorTime                                   
// Process  : Accessor for exitElevatorTime          
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline int Passenger::getExitElevatorTime() const 
{ 
   return this->exitElevatorTime;
}

//******************************************************************************
// Function : getId                                   
// Process  : Accessor for id          
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline int Passenger::getId() const 
{ 
   return this->id; 
}

//******************************************************************************
// Function : getStartTime                                   
// Process  : Accessor for startTime          
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline int Passenger::getStartTime() const 
{ 
   return this->startTime; 
}

//******************************************************************************
// Function : getStartFloor                                   
// Process  : Accessor for startFloor          
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline void Passenger::getStartFloor(Floor& startFloor) const 
{ 
   startFloor = this->startFloor; 
}

//******************************************************************************
// Function : getStartFloorNumber                                   
// Process  : Accessor for startFloor's number          
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline int Passenger::getStartFloorNumber() const 
{ 
   return this->startFloor.getNumber(); 
}
   
//******************************************************************************
// Function : getStatus                                   
// Process  : Accessor for status
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline Passenger::Status Passenger::getStatus() const 
{ 
   return this->status; 
}
   
//******************************************************************************
// Function : resetBoardTime                                   
// Process  : Resets boardElevatorTime to INIT_TO_INVALID           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline void Passenger::resetBoardTime() 
{ 
   this->boardElevatorTime = Passenger::INIT_TO_INVALID; 
}

//******************************************************************************
// Function : resetExitTime                                   
// Process  : Resets exitElevatorTime to INIT_TO_INVALID        
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline void Passenger::resetExitTime() 
{ 
   this->exitElevatorTime = Passenger::INIT_TO_INVALID; 
}

//******************************************************************************
// Function : resetStatus                                   
// Process  : Resets the status to NOT_SET           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline void Passenger::resetStatus() 
{ 
   this->status = Passenger::NOT_SET; 
}

//******************************************************************************
// Function : setEndFloor                                   
// Process  : Mutator for endFloor           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline void Passenger::setEndFloor(const Floor& endFloor) 
{ 
   this->endFloor = endFloor; 
}

//******************************************************************************
// Function : setBoardElevatorTime                                   
// Process  : Mutator for boardElevatorTime            
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline void Passenger::setBoardElevatorTime(const int boardElevatorTime) 
{ 
   this->boardElevatorTime = boardElevatorTime; 
}

//******************************************************************************
// Function : setExitElevatorTime                                   
// Process  : Mutator for exitElevatorTime           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline void Passenger::setExitElevatorTime(const int exitElevatorTime) 
{ 
   this->exitElevatorTime = exitElevatorTime; 
}

//******************************************************************************
// Function : setId                                   
// Process  : Mutator for id           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline void Passenger::setId(const int id) 
{ 
   this->id = id; 
}

//******************************************************************************
// Function : setStartFloor                                   
// Process  : Mutator for start floor           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline void Passenger::setStartFloor(const Floor& startFloor) 
{ 
   this->startFloor = startFloor; 
}

//******************************************************************************
// Function : setStartTime                                   
// Process  : Mutator for start time           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline void Passenger::setStartTime(const int startTime) 
{ 
   this->startTime = startTime; 
}

#endif // Passenger_h
