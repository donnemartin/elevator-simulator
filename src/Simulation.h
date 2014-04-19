//******************************************************************************
//
// File Name:     Simulation.h
//
// File Overview: Represents a Simulation
//
//******************************************************************************
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added class
//******************************************************************************

#ifndef Simulation_h
#define Simulation_h

#include <string>
#include <vector>
#include "Elevator.h"
#include "Floor.h"
#include "Passenger.h"

using namespace std;

//******************************************************************************
//
// Class:    Simulation
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added class
//
// Notes: None
//
//******************************************************************************
class Simulation
{
public:
   
   //***************************************************************************
   // Function    : constructor                                   
   // Description : None
   // Constraints : None
   //***************************************************************************
   Simulation();

   //***************************************************************************
   // Function    : destructor                                   
   // Description : None            
   // Constraints : None
   //***************************************************************************
   virtual ~Simulation();   

   // Member functions in alphabetical order   
   
   //***************************************************************************
   // Function    : addPassenger                                   
   // Description : Adds the passenger to our list of passengers            
   // Constraints : None
   //***************************************************************************
   void addPassenger(
      const int startTime,
      const Floor& startFloor,
      const Floor& endFloor);
   
   //***************************************************************************
   // Function    : areAllPassengersCompleted                                   
   // Description : Determines if all passengers have a status of COMPLETED            
   // Constraints : None
   //***************************************************************************
   bool areAllPassengersCompleted() const;
      
   //***************************************************************************
   // Function    : calculateWaitAndTravelTimes                                   
   // Description : Calculates the wait and travel times for each passenger            
   // Constraints : None
   //***************************************************************************
   void calculateWaitAndTravelTimes();
      
   //***************************************************************************
   // Function    : atoiCheckOutOfRange                                   
   // Description : Determines if the input number is out of range from atoi            
   // Constraints : None
   //***************************************************************************
   void atoiCheckOutOfRange(const int quantity) const;
      
   //***************************************************************************
   // Function    : getTime                                   
   // Description : Accessor for time            
   // Constraints : None
   //***************************************************************************
   inline int getTime() const;
      
   //***************************************************************************
   // Function    : incrementSimulationTime                                   
   // Description : Increments the simulation time by one            
   // Constraints : None
   //***************************************************************************
   void incrementSimulationTime();
      
   //***************************************************************************
   // Function    : loadElevatorDataFromFile                                   
   // Description : Loads the data from the elevator file            
   // Constraints : None
   //***************************************************************************
   void loadElevatorDataFromFile();
      
   //***************************************************************************
   // Function    : outputWaitAndTravelTimeAnalysis                                   
   // Description : Outputs the wait and travel times to cout            
   // Constraints : None
   //***************************************************************************
   void outputWaitAndTravelTimeAnalysis() const;
      
   //***************************************************************************
   // Function    : parseLine                                   
   // Description : Parses the current line from the elevator data file            
   // Constraints : None
   //***************************************************************************
   void parseLine(
      const string& currLine,
      int& startTime, 
      Floor& startFloor, 
      Floor& endFloor) const;
      
   //***************************************************************************
   // Function    : queuePassengers                                   
   // Description : Adds passengers to the queue who have a start time
   //                equal to the current simulation time
   // Constraints : None
   //***************************************************************************
   void queuePassengers();
      
   //***************************************************************************
   // Function    : resetSimulation                                   
   // Description : Resets the simulation to allow for another run            
   // Constraints : None
   //***************************************************************************
   void resetSimulation();
      
   //***************************************************************************
   // Function    : runDefaultElevatorSimulation                                   
   // Description : Runs the default set of params for the elevator simulations            
   // Constraints : None
   //***************************************************************************
   void runDefaultElevatorSimulation();
      
   //***************************************************************************
   // Function    : runSimulation                                   
   // Description : Runs the simulation            
   // Constraints : None
   //***************************************************************************
   void runSimulation(int elevatorTimeToNextFloor);
      
   //***************************************************************************
   // Function    : setElevatorDataFile                                   
   // Description : Accessor for elevatorDataFile            
   // Constraints : None
   //***************************************************************************
   inline void setElevatorDataFile(const string& elevatorDataFile);

   //***************************************************************************
   // public Class Attributes
   //***************************************************************************

   static const int NUM_ELEVATORS    = 4;    // Number of elevators   
   static const int NUM_FLOORS       = 100;  // Number of floors

private:   
   PassengerList*  passengerListPtr;   // List of Passengers (singleton)
   SimulationTime* simulationTimePtr;  // Simulation time (singleton)

   string elevatorDataFile;            // File name containing the elevator data

   vector<Elevator> elevators;         // Vector of elevators

   vector<double> avgWaitTimes;        // Vector of avg wait times 
   vector<double> avgTravelTimes;      // Vector of avg travel times

}; // end class Simulation

//******************************************************************************
// Function : getTime                                   
// Process  : Accessor for the simulatime time           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline int Simulation::getTime() const 
{ 
   return this->simulationTimePtr->getTime(); 
}

//******************************************************************************
// Function : setElevatorDataFile                                   
// Process  : Mutator for elevatorDataFile           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline void Simulation::setElevatorDataFile(const string& elevatorDataFile) 
{ 
   this->elevatorDataFile = elevatorDataFile; 
}

#endif // Simulation_h
