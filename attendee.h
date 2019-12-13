//Sender Shepard
//attendee.h
//This file contains the classes in which a the attendee will be able to create
//appointments with the available events that come from the dayLLL. The client 
//program holds the available events through the objects created by the 
//event and day classes. The attendee will hold the events in a CLLL and 
//the BST will hold an attendee with all of their appointments. 

#include "times.h" 

#ifndef ATTENDEE //If this file has not been previously defined by a .cpp file.
#define ATTENDEE //Then define without overriding previous definition. 

//A class that will be able to create an attendee; this class will have 
//functions that will create, copy, and display attendees. Furthermore it will
//have a pointer to event nodes in order to create a CLLL data structure
//of events for each attende. 
class attendee
{
    public:
        attendee(void);//Default constructor.
        ~attendee(void);//Default deconstructor. 
        attendee(const attendee &);//Copy constructr.
        int create_attendee(char * last); 
        int copy_attendee(const attendee & to_add);
        int compare_attendee(char * last);
        int compare_attendee(const attendee & last);
        int insert_event(event & add);
        int retrieve(dayLLL & found, event & an_event); 
        int display(void) const; //Displays Last name.
        int display_all(void) const; //Displays all appointments in attendee.

    protected:
        event_node * rear; //Pointer for CLL.
        char * last_name;//Array of characters for last name. 
};



//This class serves as a node class in order to assist in the formulation of a 
//data structure, in this case it will be a tree structure and thus there 
//will be left and right pointers. It will also have a pointer to an attendee.
class tree_node: public attendee
{
      public:
             tree_node(); //Default constructor. 
             tree_node * & go_left()     {return left;}; //In line functions.
             tree_node * & go_right()    {return right;};
             attendee * & return_person() {return person;};
      
      protected:
             tree_node * left; //Varibles for left and right pointers. 
             tree_node * right;
             attendee * person; //Pointer for the attendee class. 
};



//A "node" IS A "attendee", so through the root pointer you can 
//call all of the public functions within the attendee class and hierarchy
class BST: public tree_node 
{
      public:
             BST(); //Default constructor. 
             ~BST(); //Default deconstructor. 
	     BST(const BST & ); //Copy constructor. 
             int insert(const attendee & to_add); //Wrapper function to insert.
             void create_appointment(attendee & to_add); //Cretes appts. 
             int display_all(void) const; //Displays all items in the tree. 
             //Operator overloaded functions go here. 
             friend ostream& operator<<(ostream& ,const BST &);

      protected:
             //Here are the recursive functions that the public functions call
             int remove_all(tree_node * & root); //Deletes the data strucutre.
             int insert(tree_node * & root, const attendee & to_add);
             int display_all(tree_node * root) const;  //Display all items. 
  
             tree_node * root;//a tree of appts
};

#endif
