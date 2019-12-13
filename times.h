//Sender Shepard
//times.h 
//This file will contain the classes which will creat a Linear Linked List 
//of events, each one of these Linear Linked Lists will then be palced in a 
//day node which will hold a day. The days will be arranged in Linear Linked 
//Lists as well so that a calendar can be created in order for participants 
//to schedule their appoinments. This file will load the days and events
//from an external data file. 

using namespace std;
#include <iostream>
#include <cctype>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <fstream>


#ifndef TIMES //If this file has not been previously defined by a .cpp file.,
#define TIMES //Then define without overriding previous definition. 

//Creates an array of constant size MAX.
const int INPUT = 50;


//A class that will be able to create an event; this class will have functions
//that will create, copy, and display events.
class event
{
    public:
        event(void);//Default constructor.
        ~event(void);//Default deconstructor.
        event(const event & to_copy){}; //Copy constructor.
        int create_event(char * dayz, char * des, int t); //Fills an even obj. 
        int copy_event(const event & entry); //Takes object as arg to copy
        int compare_time(int time); //This function compares times of events.
        int display(void) const; //Displays all.
        //Operator overloading functions. 
        event & operator=(const event & add);
        friend ostream& operator<<(ostream& ,const event &);

    protected:
        char * eventz; //Protected data members. 
        char * description; 
        int time; //Time of event. 
};



//This class serves as a node class in order to assist in the formulation of a 
//data structure, in this case it will be a Linear Linked List and thus there 
//will be a next pointer. It will also have a pointer to events.
class event_node
{
      public:
        event_node(void);//Default constructor.
        ~event_node(void);//Default deconstructor. 
        event_node(const event_node & );//Copy constructor.
        event_node *& go_next(void)   {return next;};//Getter for next pointer.
        event *& return_event(void) {return a_event;};

    protected:
        event_node * next;//Pointers to a event_node.
        event * a_event; 
};



//This class will be used to create a Linear Linked List of days. It will 
//derive from the node class in order to create a "has a" relationship.
class eventLLL: public event_node
{
      public:
        eventLLL(); //Default constructor. 
        ~eventLLL(); //Default deconstructor. 
        eventLLL(const eventLLL & to_copy); //Copy constructor. 
        void create_events(event & to_add); //Creates events. 
        int insert_event(const event & adding);//Inserts event into a LLL
        int compare_time(int time, event & an_event); //Compares member vars.
        int display_all() const; //Display the LLL. 
        //Operator overloading functions go here:         
        eventLLL & operator=(const eventLLL & add); 
        friend ostream& operator<<(ostream& ,const eventLLL &);

      protected:   
        int eventLLL_id; //Protected data members. 
        event_node * head; //Head pointer to an even node to form a LLL. 
};



//A class that will be able to create a day; this class will have functions
//that will create, copy, and display days.
class day
{
    public:
        day(void);//Default constructor.
        ~day(void);//Default deconstructor.
        day(const day & to_copy); //Copy constructor.
        int create_day(char * day, char * des, int t);
        int copy_day(const day & entry);
        int compare_day(char * day); //Returns true if there is a match. 
        int display(void) const; //Displays all.
        //Operator overloading functions go here. 
        day & operator=(const day & add);
        friend ostream& operator<<(ostream& ,const day &);

    protected:
        char * weekday;
        char * description; 
        int time;        
};



//This class serves as a node class in order to assist in the formulation of a 
//data structure, in this case it will be a Linear Linked List and thus there 
//will be a next pointer. It will also have a pointer to events.
class day_node   
{
    public:
        day_node(void);//Default constructor.
        ~day_node(void);//Default deconstructor. 
        day_node(const day_node & );//Copy constructor.
        day_node *& go_next(void)   {return next;};//Getter for next pointer.
        day *& return_day(void) {return a_day;};
        eventLLL *& return_events() {return events;}; 

    protected:
        day_node * next; //Pointers to a node.
        day * a_day; //Pointer to a day. 
        eventLLL * events; //This pointer will be able to access events LLL.  
};



//This class will be used to create a Linear Linked List of days. It will 
//derive from the node class in order to create a "has a" relationship. 
class dayLLL: public day_node
{
    public:
        dayLLL();             
        ~dayLLL();
        dayLLL(char * day, char * desc, int t, int n){};
        dayLLL(const dayLLL & new_day);
        void create_day(day & dayz);
        int insert_day(const day & adding);
        int retrieve_day(char * day); 
        int retrieve_time(int time, char * day, event & an_event);
        int admit_event(const event & a_event);
        int admit_eventLLL(const eventLLL & );
        int display_all() const;       
        //Operator overloading functions go here. 
        friend dayLLL operator+(const dayLLL & L1, const dayLLL & L2);
        friend ostream& operator<<(ostream& ,const dayLLL &);
        dayLLL & operator=(const dayLLL & add); 
       
    protected:   
        int dayLLL_id;
        day_node * head; //Node pointer to a head. 
};

#endif 

