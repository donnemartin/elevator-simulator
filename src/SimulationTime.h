//******************************************************************************
//
// File Name:     SimulationTime.h
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

#ifndef SimulationTime_h
#define SimulationTime_h

//******************************************************************************
//
// Class:    SimulationTime
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added class
//
// Notes: None
//
//******************************************************************************
class SimulationTime
{
public:

   //***************************************************************************
   // Function    : destructor                                   
   // Description : None            
   // Constraints : None
   //***************************************************************************
   virtual ~SimulationTime();   

   // Member functions in alphabetical order   

   //***************************************************************************
   // Function    : getInstance                                   
   // Description : Retrieves the single instance of the class            
   // Constraints : None
   //***************************************************************************
   inline static SimulationTime* getInstance();

   //***************************************************************************
   // Function    : getTime                                   
   // Description : Accessor for time            
   // Constraints : None
   //***************************************************************************
   inline int getTime() const;

   //***************************************************************************
   // Function    : incrementTime                                   
   // Description : Increments the time by one            
   // Constraints : None
   //***************************************************************************
   inline void incrementTime();

   //***************************************************************************
   // Function    : setTime                                   
   // Description : Mutator for time            
   // Constraints : None
   //***************************************************************************
   inline void setTime(const int time);

   //***************************************************************************
   // public Class Attributes
   //***************************************************************************

private:   
   
   //***************************************************************************
   // Function    : constructor                                   
   // Description : None
   // Constraints : None
   //***************************************************************************
   SimulationTime();
   
   static SimulationTime*  instancePtr; // Pointer to itself (singleton)
   int                     time;        // Simulation time
}; // end class SimulationTime

//******************************************************************************
// Function : getInstance                                   
// Process  : Retrieve the single instance of the class if it exist           
//             Else, create it, then return
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline SimulationTime* SimulationTime::getInstance()
{
   if (!instancePtr)
   {
      instancePtr = new SimulationTime;
   }

   return instancePtr;
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
inline int SimulationTime::getTime() const 
{ 
   return time; 
}

//******************************************************************************
// Function : incrementTime                                   
// Process  : Increment the time by one           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline void SimulationTime::incrementTime() 
{ 
   this->time++; 
}

//******************************************************************************
// Function : setTime                                   
// Process  : Mutator for time           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline void SimulationTime::setTime(const int time) 
{ 
   this->time = time; 
}

#endif // SimulationTime_h
