//******************************************************************************
//
// File Name:     Floor.h
//
// File Overview: Represents a Floor
//
//******************************************************************************
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added class
//******************************************************************************

#ifndef Floor_h
#define Floor_h

using namespace std;

//******************************************************************************
//
// Class:    Floor
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added class
//
// Notes: None
//
//******************************************************************************
class Floor
{
public:
   
   //***************************************************************************
   // Function    : constructor                                   
   // Description : None
   // Constraints : None
   //***************************************************************************
   Floor();

   //***************************************************************************
   // Function    : destructor                                   
   // Description : None            
   // Constraints : None
   //***************************************************************************
   virtual ~Floor();   

   // Member functions in alphabetical order      

   //***************************************************************************
   // Function    : decrementFloorNumber                                   
   // Description : Decrements the floor number by one            
   // Constraints : None
   //***************************************************************************
   inline void decrementFloorNumber();
      
   //***************************************************************************
   // Function    : getNumber                                   
   // Description : Accessor for number            
   // Constraints : None
   //***************************************************************************
   inline int getNumber() const;
      
   //***************************************************************************
   // Function    : incrementFloorNumber                                   
   // Description : Increments the floor number by one          
   // Constraints : None
   //***************************************************************************
   inline void incrementFloorNumber();
      
   //***************************************************************************
   // Function    : operator<                                   
   // Description : Overrides operator< to work with floor's number             
   // Constraints : None
   //***************************************************************************
   inline bool operator<(const Floor& floor);
      
   //***************************************************************************
   // Function    : setNumber                                   
   // Description : Mutator for number            
   // Constraints : None
   //***************************************************************************
   inline void setNumber(const int number);
   
   //***************************************************************************
   // public Class Attributes
   //***************************************************************************
   static const int START_FLOOR = 1;   // Start at the first floor

private:   
   int number;    // Floor number

}; // end class Floor

//******************************************************************************
// Function : decrementFloorNumber                                   
// Process  : Decrement the floor number by one           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline void Floor::decrementFloorNumber() 
{ 
   this->number--; }

//******************************************************************************
// Function : getNumber                                   
// Process  : Accessor for number           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline int Floor::getNumber() const 
{ 
   return this->number; }

//******************************************************************************
// Function : incrementFloorNumber                                   
// Process  : Increment the floor number by one           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline void Floor::incrementFloorNumber() 
{ 
   this->number++; }

//******************************************************************************
// Function : operator<                                   
// Process  : Override operator< to work with floor's number           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline bool Floor::operator<(const Floor& floor) 
{
   return floor.getNumber() < this->getNumber();
}

//******************************************************************************
// Function : setNumber                                   
// Process  : Mutator for number           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 7.23.11        Donne Martin         Added function
//******************************************************************************
inline void Floor::setNumber(const int number) 
{ 
   this->number = number; }

#endif // Floor_h
