elevatorsimulator
============

Simulates four elevators available to take passengers up and down the floors of a 100 floor building, written in C++.

Simulation mechanics:
-There are 4 elevators available to take passengers up and down the floors of a 100 floor building.
-Each Elevator can be stopped, stopping, moving up, or moving down.
-It takes an elevator 2 seconds of stopping to be stopped.
-It takes each elevator 10 seconds of moving to move between each floor.
-There is a maximum of 8 passengers allowed in a single elevator.
-The elevator data file determines when passengers ask for an elevator, their starting floor, and their destination floor.
--A passenger arrives at the start floor at the start fime, waits for the elevator to arrive and stays on the elevator until arriving at the end floor.
-When a elevator arrives at a floor, it picks up all of the passengers waiting at the floor, up to the maximum capacity of 8, and then starts moving to the End Floors.
-Passengers are queued waiting, if necessary, for elevators.
-The simulation performs one loop each simulated second.
-During each loop, each object decides what to do.
-If stopped and current time is equal to or greater than the next start time, the elevator either begins moving up or moving down depending on the direction needed to pick up the passenger.
-If moving up or moving down and there are one or more passengers waiting at a floor along the way, or if there are current passengers with end floor being the current floor, it begins stopping.
-When stopped at a floor, if there are any passengers in the elevator with that end Floor as a destination, it discharges the passengers. Then, if there are any passengers with that floor as their start Floor it picks up passengers up to the capacity of the elevator.
-Only one elevator can pick up a passenger.
-There is no central controller of elevators as each elevator is making its own decisions as to which passengers to pick up and discharge, therefore there are no conflicts.

The simulation implements an elevator solution then determines the average wait time and the average travel time it takes for
passengers.  The simulation is run twice, one for each elevator taking 10 seconds to move between each floor, and the other for each elevator taking 5 seconds instead.  For the second run, the simulation determines the % reduction of average wait time and the % reduction of average travel time for passengers.

Elevator data:

![alt tag](https://raw.githubusercontent.com/donnemartin/elevatorsimulator/master/res/elevatordata.png)

Simulation run snippet:

![alt tag](https://raw.githubusercontent.com/donnemartin/elevatorsimulator/master/res/simulation.png)

Simulation results:

![alt tag](https://raw.githubusercontent.com/donnemartin/elevatorsimulator/master/res/results.png)