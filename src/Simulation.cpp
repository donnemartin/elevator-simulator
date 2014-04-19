// COPYRIGHT © 2011, Donne Martin
// All Rights Reserved.
//
//******************************************************************************
//
// File Name:     Simulation.cpp
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

#include "stdafx.h"
#include <fstream>
#include "Simulation.h"
#include <iostream>

//******************************************************************************
// Function : main                                   
// Process  : Create and run simulation
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
int _tmain(int argc, _TCHAR* argv[])
{
   try
   {
      Simulation simulation;  // Elevator simulation
      simulation.runDefaultElevatorSimulation();
   }
   catch (const bad_alloc& e)
   {
      cout << e.what() << endl;
      cout << "Caught bad_alloc" << endl;
      cout << "Terminating program" << endl;
   }
   catch (const out_of_range& e)
   {
      cout << e.what() << endl;
      cout << "Caught out_of_range" << endl;
      cout << "Terminating program" << endl;
   }
   catch (const exception& e)
   {
      cout << e.what() << endl;
      cout << "Caught exception" << endl;
      cout << "Terminating program" << endl;
   }

   cout << "End of program" << endl;
      
   char pauseBeforeTerminate = ' '; // Don't let the program terminate by itself
   cin >> pauseBeforeTerminate;
   
	return 0;
}

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
Simulation::Simulation() 
{
   this->elevatorDataFile     = "";

   this->passengerListPtr     = PassengerList::getInstance();
   this->simulationTimePtr    = SimulationTime::getInstance();

   this->elevators.resize(Simulation::NUM_ELEVATORS);
} // end Simulation::Simulation

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
Simulation::~Simulation()
{
} // end Simulation::~Simulation

//******************************************************************************
// Function : addPassenger                                   
// Process  : Update the passenger and add him to the list           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Simulation::addPassenger(
   const int startTime,
   const Floor& startFloor,
   const Floor& endFloor)
{
   // Update the passenger
   Passenger passenger; // Passenger to add to list
   passenger.setId(passengerListPtr->getPassengerListSize());
   passenger.setStartTime(startTime);
   passenger.setStartFloor(startFloor);
   passenger.setEndFloor(endFloor);
   passenger.setStatus(Passenger::NOT_SET, startTime);

   // Add the passenger to the list
   passengerListPtr->addPassenger(passenger);    
}

// 
//******************************************************************************
// Function : areAllPassengersCompleted                                   
// Process  : Loop through all of our passengers
//             If this passenger is not in the completed state
//                Set our return value to false and break
//             
// Notes    : Inefficient, consider optimizing in the next iteration by having
//             a counter incremented every time a passenger is set to complete
//             If the counter equals the number of passengers in the list,
//                Return true
//             Else
//                Return false
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
bool Simulation::areAllPassengersCompleted() const
{
   bool passengersCompleted = true; // Determines if all passengers are complete
   int  numPassengers       = 0;    // Number of passengers 
      
   numPassengers = this->passengerListPtr->getPassengerListSize();

   // Loop through all of our passengers
   for (int passIndex = 0; passIndex < numPassengers; ++passIndex)
   {
      // If this passenger is not in the completed state
      if (this->passengerListPtr->getPassengerStatusAt(passIndex) 
         != Passenger::COMPLETED)
      {
         // Set our return value to false and break
         passengersCompleted = false;
         break;
      }
   }

   return passengersCompleted;
}

//******************************************************************************
// Function : calculateWaitAndTravelTimes                                   
// Process  : Loop through all of our passengers
//             Get the start time, elevator board time, and elevator exit time
//             Calculate the wait time and travel time
//             Update our cumulative totals
//             Determine the simulation average wait and average travel time
//             Stores values to our vectors for later analysis
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Simulation::calculateWaitAndTravelTimes()
{
   double averageTravelTime      = 0;  // Average simulation travel time
   double averageWaitTime        = 0;  // Average simulation wait time
   int cumulativeTravelTime      = 0;  // Cumulative passenger travel time
   int cumulativeWaitTime        = 0;  // Cumulative passenger wait time
   int currentBoardElevatorTime  = 0;  // Curr passenger board elevator time
   int currentExitElevatorTime   = 0;  // Curr passenger exit elevator time
   int currentStartTime          = 0;  // Curr passenger start time
   int currentTravelTime         = 0;  // Curr passenger travel time
   int currentWaitTime           = 0;  // Curr passenger wait time
   int numPassengers             = 0;  // Number of passengers

   numPassengers = this->passengerListPtr->getPassengerListSize();

   // Loop through all of our passengers
   for (int passIndex = 0; passIndex < numPassengers; ++ passIndex)
   {
      // Get the start time, elevator board time, and elevator exit time
      currentStartTime 
         = this->passengerListPtr->getPassengerStartTimeAt(passIndex);

      currentBoardElevatorTime
         = this->passengerListPtr->getPassengerBoardElevatorTimeAt(passIndex);

      currentExitElevatorTime 
         = this->passengerListPtr->getPassengerExitElevatorTimeAt(passIndex);
      
      // Calculate the wait time and travel time
      currentWaitTime = currentBoardElevatorTime - currentStartTime;
      currentTravelTime = currentExitElevatorTime - currentBoardElevatorTime;

      // Update our cumulative totals
      cumulativeWaitTime += currentWaitTime;
      cumulativeTravelTime += currentTravelTime;

      // Verify this passenger is marked as complete
      // In this point in the program, all passengers should be complete
      if (this->passengerListPtr->getPassengerStatusAt(passIndex) 
          != Passenger::COMPLETED)
      {
         throw exception("Not all passengers were processed!");
      }
   }

   // Determine the simulation average wait time and average travel time
   averageWaitTime = (double)cumulativeWaitTime / (double)numPassengers;
   averageTravelTime = (double)cumulativeTravelTime / (double)numPassengers;

   // Store these values to our vectors for later analysis
   this->avgWaitTimes.push_back(averageWaitTime);
   this->avgTravelTimes.push_back(averageTravelTime);
}

//******************************************************************************
// Function : atoiCheckOutOfRange                                   
// Process  : Throw an exception if we have an out of range number from atoi           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Simulation::atoiCheckOutOfRange(const int quantity) const
{
   // Handle out of range errors from atoi
   if (INT_MAX == quantity || INT_MIN == quantity)
   {
      throw exception("atoi operation failed");
   }
}

//******************************************************************************
// Function : incrementSimulationTime                                   
// Process  : Increment simulation time
//             Queue any passengers who have a start time equal to the
//                current simulation time (logic in queuePassengers)
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Simulation::incrementSimulationTime() 
{ 
   this->simulationTimePtr->incrementTime(); 
   this->queuePassengers();
}

//******************************************************************************
// Function : loadElevatorDataFromFile                                   
// Process  : Set up ifstream with the file name           
//             If the ifstream process succeeded        
//                Skip the labels        
//                Loop while we have not reached the end of file     
//                   Get the next line     
//                   If the line is not blank  
//                      Parse the line
//                      Add passenger to the queue
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Simulation::loadElevatorDataFromFile()
{
   string   currLine   = "";   // Current line we are processing
   int      startTime  = 0;    // Start time in sec       
   
   // Set up our ifstream with the file name
   ifstream currFile(this->elevatorDataFile.c_str(), ios::in);

   // If the ifstream process succeeded
   if (currFile)
   {
      // Skip the labels
      getline(currFile, currLine);

      // Loop while we have not reached the end of file
      while (!currFile.eof())
      {
         // Get the next line
         getline(currFile, currLine);

         // If the line is not blank
         if (currLine != "")
         {
            Floor startFloor; // Start floor
            Floor endFloor;   // End floor

            // Parse the line
            this->parseLine(
               currLine, 
               startTime, 
               startFloor, 
               endFloor);

            // Add passenger to the queue
            this->addPassenger(startTime, startFloor, endFloor);  
         }
      }
   }
   // If the ifstream process failed, throw an exception
   else
   {
      throw exception("ifstream operation failed!");
   }
}

//******************************************************************************
// Function : outputWaitAndTravelTimeAnalysis                                   
// Process  : Loop through all runs and output the 
//             average wait times and average travel times       
//             Calculate the comparison % between the first and second runs
//                Calculate the average wait time % change
//                Calculate the average travel time % change
//             Output the results
//             
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Simulation::outputWaitAndTravelTimeAnalysis() const
{
   int numRuns = this->avgWaitTimes.size();  // Number of runs

   // Verify our vectors for wait and travel times are of equal size
   if (this->avgWaitTimes.size() != this->avgTravelTimes.size())
   {
      throw exception("Mismatched sizes on wait and travel times");
   }

   // Loop through all of our runs and output
   // the average wait times and average travel times
   for (int run = 0; run < numRuns; ++run)
   {
      cout << endl << "-----------------------------------------------" << endl;
      cout << "Results for run: " << run << endl;
      cout << "Average passenger wait time is: ";
      cout << this->avgWaitTimes[run] << " secs" << endl;
      cout << "Average passenger travel time is: ";
      cout << this->avgTravelTimes[run] << " secs" << endl;
   }

   static const int FIRST_RUN = 0;  // First run index
   static const int SECOND_RUN = 1; // Second run index
   
   // Calculate the comparison % between the first and second runs
   // Calculate the average wait time % change
   double compareAverageWaitTimes 
      = this->avgWaitTimes[SECOND_RUN] / this->avgWaitTimes[FIRST_RUN];

   // Calculate the comparison % between the first and second runs
   // Calculate the average travel time % change
   double compareAverageTravelTimes 
      = this->avgTravelTimes[SECOND_RUN] / this->avgTravelTimes[FIRST_RUN];

   static const int PERCENT_MULT_FACTOR = 100;  // Turns our percentages:
                                                // ie .15% to 15%
   compareAverageWaitTimes *= PERCENT_MULT_FACTOR;
   compareAverageTravelTimes *= PERCENT_MULT_FACTOR;

   // Output the results
   cout << endl << "-----------------------------------------------" << endl;
   cout << "Comparison of both runs: " << endl << endl;
   cout << "Average passenger wait time in Second Run is " << endl;
   cout << "   reduced to " << compareAverageWaitTimes;
   cout << " Percent of First Run" << endl << endl;
   cout << "Average passenger travel time in Second Run is " << endl;
   cout << "   reduced to " << compareAverageTravelTimes;
   cout << " Percent of First Run" << endl << endl;
}

//******************************************************************************
// Function : parseLine                                   
// Process  : Determine the comma positions
//             The start time string is the first text before the first comma
//                Convert start time string to int
//             Set start floor, based on string between first and second commas
//                Convert start floor string to int
//             Set end floor, based on string past the second comma
//                Convert end floor string to int
//             Handle out of range errors from atoi
//
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Simulation::parseLine(
   const string& currLine,
   int& startTime, 
   Floor& startFloor, 
   Floor& endFloor) const
{   
   static const int  NEXT_CHAR      = 1;             // 1 char after comma
   string            endFloorStr    = "";            // End floor string rep
   int               firstCommaPos  = string::npos;  // First comma pos                   
   int               secondCommaPos = string::npos;  // Second comma pos
   string            startTimeStr   = "";            // Start time string rep
   string            startFloorStr  = "";            // Start floor string rep

   // Determine the comma positions
   firstCommaPos  = currLine.find(",");
   secondCommaPos = currLine.find(",", firstCommaPos + NEXT_CHAR);

   // The start time string is the first text before the first comma
   startTimeStr = currLine.substr(0, firstCommaPos);

   // Convert start time string to int
   startTime = atoi(startTimeStr.c_str());
   
   // secondCommaPos would result in including the char one past the comma
   // secondCommaPos - 1 would result in including the comma
   // secondCommaPos - 2 results in including the char one prior the comma
   static const int  END_POS_OFFSET     = 2;
   int               secondStringEndPos = secondCommaPos - END_POS_OFFSET;

   // Set start floor, based on string between first and second commas
   startFloorStr = currLine.substr(
      firstCommaPos + NEXT_CHAR, 
      secondStringEndPos);

   // Convert start floor string to int
   startFloor.setNumber(atoi(startFloorStr.c_str()));

   // Set end floor, based on string past the second comma
   endFloorStr = currLine.substr(secondCommaPos + NEXT_CHAR);

   // Convert end floor string to int
   endFloor.setNumber(atoi(endFloorStr.c_str()));

   // Handle out of range errors from atoi
   this->atoiCheckOutOfRange(startTime);
   this->atoiCheckOutOfRange(startFloor.getNumber());
   this->atoiCheckOutOfRange(endFloor.getNumber());
}

//******************************************************************************
// Function : queuePassengers                                   
// Process  : Loop through all passengers
//             If this passenger's start time equals our simulation time,
//             We want to queue this passenger by setting his status
//                Get the passenger's start and end floors
//                If this passsenger is going up, 
//                   Set him to queued waiting up
//                If this passsenger is going down, 
//                   Set him to queued waiting down
//             
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Simulation::queuePassengers()
{
   int endFloorNumber   = -1;                // End floor number
   int numPassengers    = 0;                 // Number of passengers
   int startFloorNumber = -1;                // Start floor number
   int time             = this->getTime();   // Current simulation time

   numPassengers = this->passengerListPtr->getPassengerListSize();

   // Loop through all passengers
   for (int passIndex = 0; passIndex < numPassengers; ++ passIndex)
   {
      // If this passenger's start time equals our simulation time,
      // We want to queue this passenger by setting his status
      if (this->passengerListPtr->getPassengerStartTimeAt(passIndex) == time)
      {
         // Get the passenger's start and end floors
         startFloorNumber 
            = this->passengerListPtr->getPassengerStartFloorNumberAt(passIndex);

         endFloorNumber   
            = this->passengerListPtr->getPassengerEndFloorNumberAt(passIndex);

         // If this passsenger is going up
         if (startFloorNumber < endFloorNumber)
         {
            // Set him to queued waiting up
            this->passengerListPtr->setPassengerStatusAt(
               passIndex, 
               Passenger::QUEUED_WAITING_UP, 
               time);
         }
         // If this passsenger is going down
         else
         {
            // Set him to queued waiting down
            this->passengerListPtr->setPassengerStatusAt(
               passIndex, 
               Passenger::QUEUED_WAITING_DOWN, 
               time);
         }
      }
   }
}

//******************************************************************************
// Function : resetSimulation                                   
// Process  : Reset the simulation time
//             Loop through all the passengers 
//                Reset the passenger's:
//                   -status
//                   -elevator board time
//                   -elevator exit time
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Simulation::resetSimulation()
{
   // Number of passengers
   int numPassengers = this->passengerListPtr->getPassengerListSize();

   // Reset the simulation time
   this->simulationTimePtr->setTime(0);

   // Loop through all the passengers
   for (int passIndex = 0; passIndex < numPassengers; ++ passIndex)
   {
      // Reset the passenger's:
      // -status
      // -elevator board time
      // -elevator exit time
      this->passengerListPtr->
         resetPassengerStatusAndBoardExitTimesAt(passIndex);
   }
}

//******************************************************************************
// Function : runDefaultElevatorSimulation                                   
// Process  : Load the elevator data from the elevator file
//             Name each elevator (useful for debugging with print messages)
//             Run the first simulation
//             Reset, then run the second simulation
//             Output results
//             
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Simulation::runDefaultElevatorSimulation()
{
   static const int SEC_NEXT_FLOOR      = 10; // Time to next floor
   static const int SEC_NEXT_FLOOR_FAST = 5;  // Optimized time to next floor

   cout << "Running simulations..." << endl;

   // Load the elevator data from the elevator file
   this->setElevatorDataFile("elevators.csv");
   this->loadElevatorDataFromFile();

   static const int ELEVATOR0 = 0;  // Index of first elevator
   static const int ELEVATOR1 = 1;  // Index of second elevator
   static const int ELEVATOR2 = 2;  // Index of third elevator
   static const int ELEVATOR3 = 3;  // Index of fourth elevator

   // Name each elevator (useful for debugging with print messages)
   this->elevators[ELEVATOR0].setName("Elevator 0");
   this->elevators[ELEVATOR1].setName("Elevator 1");
   this->elevators[ELEVATOR2].setName("Elevator 2");
   this->elevators[ELEVATOR3].setName("Elevator 3");

   // Run the first simulation
   this->runSimulation(SEC_NEXT_FLOOR);

   // Reset, then run the second simulation
   this->resetSimulation();
   this->runSimulation(SEC_NEXT_FLOOR_FAST);

   // Output results
   this->outputWaitAndTravelTimeAnalysis();
}

//******************************************************************************
// Function : runSimulation                                   
// Process  : Loop through each elevator          
//               Set the elevator travel time to get to the next floor    
//             Repeat while we have not reached the end of the simulation:       
//                Loop through each elevator    
//                   Have the elevator determine its next move    
//                Increment the simulation time
//                Break when all passengers are in the completed status
//             Calculate the passenger wait and travel times
//             
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
void Simulation::runSimulation(int elevatorTimeToNextFloor)
{
   // Loop through each elevator
   for (int currElevator = 0; currElevator < NUM_ELEVATORS; ++currElevator)
   {
      // Set the elevator travel time to get to the next floor
      this->elevators[currElevator].setTimeToNextFloor(elevatorTimeToNextFloor);
   }  

   int currStartTime = 0; // Current passenger start time
   int nextStartTime = 0; // Next passenger start time
   
   // Repeat while we have not reached the end of the simulation
   while (true)
   {
      // Loop through each elevator
      for (int currElevator = 0; currElevator < NUM_ELEVATORS; ++currElevator)
      {
         // Have the elevator determine its next move
         this->elevators[currElevator].doNextMove();
      }      

      // Increment the simulation time
      this->incrementSimulationTime();

      // Break when all passengers are in the completed status
      if (this->areAllPassengersCompleted())
      {
         break;
      }
   }

   // At the end of the simulation, 
   // calculate the passenger wait and travel times
   this->calculateWaitAndTravelTimes();
}
