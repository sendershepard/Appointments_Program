//Sender Shepard
//times.ccp
//Times Functions
//This file contains all of the body of the functions for the times.h file.
//This fill will expand on the concept of Object Oriented designs and will 
//also include some of the descritptions of what the classes are doing.
//This file will create a Linear Linked Listt of Linear Linked Lists which
//will be called dayLLL. That is the each node of the dayLLL will hold a 
//Linear Linked list of events. The events and days are loaded from a file
//so that the available times and schedules can be chosen for the participants
//to sign up. 
//
#include "times.h"

//Default constructor. Initializing pointers to NULL. 
event::event(void)
{
    eventz = description = NULL;
    time = 0; 
}



//Defaul Deconstructor. Deletes pointer to chars if they exist. 
event::~event(void)
{
    if(eventz)
        delete [] eventz;
    if (description)
        delete [] description;
}



//This function creates an event by setting the data members
//to the pertinent arguments being passed. 
int event::create_event(char * events, char * des, int t)
{
    if(eventz) //Delete the char pointer if it exists. 
        delete [] eventz;

    eventz = new char[ strlen(events) + 1 ]; //Dyanmic memory for char *
    strcpy(eventz, events); //String copy the dynamic char arrays. 
    
    if(description) //Delete the char pointer if it exists. 
        delete [] description; 

    description = new char[ strlen(des) + 1 ]; //Allocating memory dynamically.
    strcpy(description, des);
    
    time = t; //Setting time to the argument passed down. 
}



//This function takes an argument and copies it.
int event::copy_event(const event & copy_from)
{
    if(eventz)
        delete [] eventz;
    
    eventz = new char[ strlen(copy_from.eventz) + 1 ];
    strcpy(eventz, copy_from.eventz);
    
    if(description)
        delete [] description; 

    description = new char[ strlen(copy_from.description) + 1 ];
    strcpy(description, copy_from.description);
    
    time = copy_from.time;
}



//This is a function that compares the time of event the user
//typed in with the event in the LLL.
int event::compare_time(int match)
{
    if( match == time)
        return 1; //Return 1 if succesful match!
    else 
        return 0; //Rerturn false otherwise.
}



//Function that displays a event. 
int event::display() const 
{
    cout << " *** Event: " << eventz  << "\n**Description: "  << description;
    cout << "\nTime: " << time << " pm" << endl; 
}



//This function is the operator overloaded function for the assignment op.
//This function basically performs a deep copy of the event data members
//and returns it as a *this pointer. 
event &event::operator=(const event & copy_from)
{
    if(this == &copy_from)
        return *this;
    
    if(eventz) //If there is already an eventz, delete it. 
        delete [] eventz;
    
    eventz = new char[strlen(copy_from.eventz) + 1];
    strcpy(eventz, copy_from.eventz);

    if(description) //If there is already a description, delete it. 
        delete [] description; 

    description = new char[ strlen(copy_from.description) + 1 ];
    strcpy(description, copy_from.description);
    
    time = copy_from.time;

    return *this; //Exit and return the reference of the event object. 
}



//This is the overloaded function for the ostream output class. 
ostream& operator<<(ostream& out, const event & eve)
{
    eve.display(); //Calling the display function of events. 

    return out; //Returning the flow of the ostream. 
}



//Default constructor. Initializes pointer values to NULL.
event_node::event_node(void)
{
    next = NULL;
    a_event = NULL;  
}



//Default deconstructor. 
event_node::~event_node(void)
{
    if(a_event)
        delete a_event; //Deletes pointer to events. 
}



//This is the event_node copy's contructor. 
event_node::event_node(const event_node & to_copy)
{
    //Deep copying the data of the event pointer. 
    a_event = new event;
    a_event -> copy_event( *to_copy.a_event );
    next = NULL; 
}



//Default constructor
eventLLL::eventLLL(void)
{
    head = NULL;    //Pointer to head is set to NULL.
    eventLLL_id = 0;   
}



//Default deconstructor
eventLLL::~eventLLL(void)
{
    if(head) //If there is a list. 
    {
        event_node * temp = head; //Setting temp to head. 

        while(temp) //While there is a list.
        {
            temp = head -> go_next();
            delete head; //Delete the node of the list. 
            head =  temp; //Updating the head pointer. 
        }
    }
}



//Copy constructor.
//Copying the whole list.
eventLLL::eventLLL(const eventLLL & to_copy)
{
    event_node * current = to_copy.head; //Setting current to head.
    
    if(current) //If head exists, copy it. 
    {
        head = new event_node( *to_copy.head ); //New node copies w/ copy'ct.
        current = current -> go_next(); //Advancing head. 

    }
    
    event_node * current2 = head; //Pointer set to new head. 

    while(current)
    {
        event_node * temp = new event_node( *current ); //Copy constructor use.
        current2 -> go_next() = temp; //Setting pointer to temp.
        current2 = temp; //Setting current with the value of temp. 

        current = current -> go_next(); //Advancing pointers.
    }
}



//This function compares the time of the events in the LLL and if a match is
//found, then the function returns 1 as a success. 
int eventLLL::compare_time(int time, event & an_event)
{
    event_node * current = head; //Setting current to point to head. 
    
    while(current) //While there are nodes in the LLL. 
    {
        if( current -> return_event() -> compare_time(time)) //Comparing here.
        {
            //Deep copying event info here.        
            an_event = *current -> return_event(); //Assignment op for eventobj

            cout << "\nCool! You signed up for: " << time << " pm" << endl;
            current -> return_event() -> display();
            return 1; //Return 1 for success. 
        }
        
        current = current -> go_next(); //Traversing here. 
    }
}



//This function will create a day with information in it and 
//subsequently insert it into a Linear Linked List. 
void eventLLL::create_events(event & to_add)
{
    char eventz[INPUT], desc[INPUT]; //Local variables to hold data members.
    int time; //Time of day. 
    
    ifstream fileIn; //FileIn variable associated to read from file. 
    fileIn.open("eventz.txt"); //File with days. 

    if (fileIn) //Verify we have access to the file. 
    {
        fileIn.get(eventz, INPUT, '!'); //We check for contents. 
        while( !fileIn.eof() ) //We read until the end of the file.
        {
            fileIn.ignore(100, '!');

            fileIn.get(desc, INPUT, '!');
            fileIn.ignore(100, '!');
            
            fileIn >> time;
            fileIn.ignore(100, '\n');
            
            to_add.create_event(eventz, desc, time);
            insert_event(to_add);  
            
            fileIn.get(eventz, INPUT, '!'); //Loop ends if file empty. 
        }
    } //End of access to file. 
    fileIn.close();
}



//This function will take the reference of the argument being passed 
//to insert into a Linear Linked List. 
int eventLLL::insert_event(const event & adding)
{
    event_node * temp = new event_node; //Creating a new pointer to event_node.
    temp -> return_event() = new event; //Creating a new event. 
    temp -> return_event() -> copy_event(adding);  //Copying the data into day.
    
    if(!head) //If the list is empty.
    {
        temp -> go_next() = NULL; //Set next to Null. 
        head = temp; //Set the value of temp into head. 
    }
    else
    {
        event_node * current = head;  //Creating a head pointer. 

        while( current -> go_next() ) //Reaching the end of the list. 
        {
            current = current -> go_next();
        }
        current -> go_next() = temp; //Advancing pointers. 
        current = temp; 
    }

}



//This is the overloaded function for the assingment operator.
//In this function a Linear Linked List is copied as well as deep
//copying the members and pointers within this LLL; that is, within
//each LLL node, there is another LLL that is being copied. 
eventLLL & eventLLL::operator=(const eventLLL & add)
{ 
    event_node * current = add.head; //Setting a pointer to the original head.
    
    if (current)
    {
        head = new event_node( *add.head ); //Copy constructor. 
        current = current -> go_next(); //Traversing here. 
    }
    
    event_node * current2 = head; //Setting a new pointer to a new head. 
    
    while(current) //While the list is full. 
    {
        event_node * temp = new event_node( *current ); //Copy constructor.
        current2 -> go_next() = temp;
        current2 = temp; //Setting the new head to temp. 

        current = current -> go_next(); //Treaversing here. 
    }

    return *this; //Returning the this pointer. 
}



//This function is the ostream operator overloaded function. This function
//will allow the user to output the contents of the list through main 
//with the simple use of the << operator. 
ostream& operator<<(ostream& out, const eventLLL & event)
{
    event.display_all(); //Calling the display all function. 
    
    return out; //Returning the stream of output to the main program.
}



//Display all of the events Linear Linked List. 
int eventLLL::display_all(void) const
{
    if(!head) //If list is empty, exit. 
        return 0;

    event_node * current = head; //Setting a current pointer to head. 

    while(current) //While the there are items in the list: 
    {
        current -> return_event() -> display(); //Display items.
        current = current -> go_next(); //Traversing here. 
    }
}


//---------------------  Day classes  ----------------------------------
//Default constructor, initializing values to NULL. 
day::day(void)
{
    weekday = description = NULL;
    time = 0; 
}



//Default deconstructor. If there are pointers to char, delete them. 
day::~day(void)
{
    if(weekday)
      delete [] weekday;
    if(description)
        delete [] description;
}



//This function creates a bone by setting the integers 
//to the pertinent sides of the bone. 
int day::create_day(char * dayz, char * des, int t)
{
    if(weekday)
        delete [] weekday;
    
    weekday = new char[ strlen(dayz) + 1 ];
    strcpy(weekday, dayz);
    
    if(description)
        delete [] description; 

    description = new char[ strlen(des) + 1 ];
    strcpy(description, des);
    
    time = t;
}



//This function takes an argument and copies it.
int day::copy_day(const day & copy_from)
{ 
    if(weekday)
        delete [] weekday;
    
    weekday = new char[ strlen(copy_from.weekday) + 1 ];
    strcpy(weekday, copy_from.weekday);
     
    if(description)
        delete [] description; 

    description = new char[ strlen(copy_from.description) + 1 ];
    strcpy(description, copy_from.description);
    
    time = copy_from.time;
}



//This is a function that compares the day the user
//typed in with the day in the LLL.
int day::compare_day(char * day)
{
    if( strcmp(day, weekday) == 0)
        return 1; //Return 1 if succesful match!
    else 
        return 0; //Rerturn false otherwise.
}



//Function that displays a day. 
int day::display() const 
{
    cout << "Weekday: " << weekday  << "\nDescription: " << description; 
    cout << "\nStart time: " << time << " pm" << endl; 
}



//This function is the operator overloaded function for the assignment op.
//This function basically performs a deep copy of the event day members
//and returns it as a *this pointer. 
day &day::operator=(const day & copy_from)
{
    if(this == &copy_from) //If the argument has the same address as this.
        return *this; 
    
    if(weekday) //If there is already a weekday, delete it.
        delete [] weekday; //Avoiding memory leaks. 
    
    weekday = new char[strlen(copy_from.weekday) + 1];
    strcpy(weekday, copy_from.weekday);

    if(description) //If there is already a description, delete it.
        delete [] description; 

    description = new char[ strlen(copy_from.description) + 1 ];
    strcpy(description, copy_from.description);
    
    time = copy_from.time; //Copying an integer. 

    return *this; //Exit and return the reference of the day object. 
}



//This function is the ostream operator overloaded function. This function
//will allow the user to output the contents of the list through main 
//with the simple use of the << operator. 
ostream& operator<<(ostream& out, const day & dayz)
{
    dayz.display(); //Calling the day display function. 
    
    return out; //Returning the stream of output to the main program.
}



//Default constructor. Initializes pointer values to NULL.
day_node::day_node(void)
{
    next = NULL;
    a_day = NULL;
    events = NULL; 
}



//Default deconstructor. 
day_node::~day_node(void)
{ 
    if(a_day)
        delete a_day; //Deletes pointer of days. 
    if(events)
        delete events; //Deletes pointer of events. 
}



//This is the node copy's contructor. 
day_node::day_node(const day_node & to_copy)
{
    //Deep copying the data of the day pointer. 
    a_day = new day;
    a_day -> copy_day( *to_copy.a_day );
    
    //Deep copying events.
    if(to_copy.events)
        events = new eventLLL( *to_copy.events );
    next = NULL;
}



//Default constructor
dayLLL::dayLLL(void)
{
    head = NULL; //Pointer to head is set to NULL.
    dayLLL_id = 0;   
}



//Copy constructor.
//Copying the whole list.
dayLLL::dayLLL(const dayLLL & to_copy)
{
    day_node * current = to_copy.head; //Setting current to head. 
    
    if (current) //If head exists, copy it. 
    {
        head = new day_node( *to_copy.head ); //New nodde copies w/ copy'ct.
        current = current -> go_next(); //Advancing head. 
    }
    
    day_node * current2 = head; //Pointer set to new head. 
    
    while(current)
    {
        day_node * temp = new day_node( *current ); //Copy Constructor use. 
        current2 -> go_next() = temp; //Setting pointer to temp. 
        current2 = temp; //Setting current with value of temp. 

        current = current -> go_next(); //Avancing next pointers. 
    }
}



//Default deconstructor
dayLLL::~dayLLL()
{
    if(head) //If there is a list. 
    {
        day_node * temp = head; //Setting temp to head. 

        while(temp) //While there is a list.
        {
            temp = head -> go_next();
            delete head; //Delete the node of the list. 
            head =  temp;  //Updating the head pointer. 
        }
    }
}



//This function will create a day with information in it and 
//subsequently insert it into a Linear Linked List. 
void dayLLL::create_day(day & to_add)
{
    char dayz[INPUT], desc[INPUT]; //Local variables to hold data members.
    int time; //Time of day. 
    
    ifstream fileIn; //FileIn variable associated to read from file. 
    fileIn.open("dayz.txt"); //File with days. 

    if (fileIn) //Verify we have access to the file. 
    {
        fileIn.get(dayz, INPUT, '!'); //We check for contents. 
        while( !fileIn.eof() ) //We read until the end of the file.
        {
            fileIn.ignore(100, '!');

            fileIn.get(desc, INPUT, '!');
            fileIn.ignore(100, '!');
            
            fileIn >> time;
            fileIn.ignore(100, '\n');
            
            to_add.create_day(dayz, desc, time);
            insert_day(to_add);  
            
            fileIn.get(dayz, INPUT, '!'); //Loop ends if file empty. 
        }
    } //End of access to file. 
    fileIn.close();
}



//This function will take the reference of the argument being passed 
//to insert into a Linear Linked List. 
int dayLLL::insert_day(const day & adding)
{
    day_node * temp = new day_node; //Creating a new pointer to day_node.
    temp -> return_day() = new day; //Creating a new day. 
    temp -> return_day() -> copy_day(adding); //Copying the data into day.
    
    if(!head) //If the list is empty. 
    {
        temp -> go_next() = NULL; //Set next to Null. 
        head = temp; //Set the value of temp into head. 
    }
    else
    {
        day_node * current = head; //Creating a head pointer. 

        while( current -> go_next() ) //Reaching the end of the list. 
        {
            current = current -> go_next();
        }
        current -> go_next() = temp; //Advancing pointers. 
        current = temp; 
    }
}



//This function takes in as an argument a day entered by the user to verify
//if there is a match in the LLL. It will also display the events connected to
//this day. 
int dayLLL::retrieve_day(char * day)
{
    if(!head) //If the list is empty exit. 
        return 0;
    
    day_node * current = head; //Setting current pointer to head. 
    
    while( current ) //Reaching the end of the list. 
        {
            if( current -> return_day() -> compare_day(day) ) //Compare funct.
            {
                cout << "\nCool! You chose to sign up for " << day << endl; 
                
                if ( current -> return_events() ) //If there are events.
                {   
                    cout << "\nConnected events to this day: " << endl;
                    current -> return_events() -> display_all();
                }
                return 1; //Return true if match found!
            }
            
            current = current -> go_next(); //Traversing here. 
        }
}



//This function takes in as an argument a time and day entered by the user.
//If there is a match in the LLL return true. 
int dayLLL::retrieve_time(int time, char * day, event & an_event)
{
    if(!head) //If the list is empty return 0. 
        return 0;
    
    day_node * current = head; //Setting current pointer to head. 
    
    while( current ) //Reaching the end of the list. 
    {
        if( current -> return_day() -> compare_day(day) ) //Compare funct.
        {
            if ( current -> return_events() -> compare_time(time,an_event) ) 
                return 1; //Return true if match found!
        }
        current = current -> go_next(); //Traversing here. 
    }
}



//This function will admit a LLL of events and add this list to the day. 
//This function will add the LLL of events that were load from file.
int dayLLL::admit_eventLLL(const eventLLL & admitted)
{
    day_node * current = head; //Setting current to head. 

    while(current) //While there are days available add events. 
    {
        current -> return_events() = new eventLLL(admitted); //Copy constr'.
        current = current -> go_next(); //Traversing our list. 
    }
}



//This function will admit one event and add it into the LLL of events.
int dayLLL::admit_event(const event & admitted) 
{    
    day_node * current = head;
    current -> return_events() = new eventLLL; //Creating a new LLL node. 
    current -> return_events() -> insert_event(admitted); //Copying data. 
}



//This function concatenates both of the arguments together. Therefore, for 
//every piece of information that is found on list2, it will be appended to
//list 1. 
dayLLL operator+(const dayLLL & list1, const dayLLL & list2) 
{    
    dayLLL temp(list1); //Creating a temporary object to return to main. 
    
    if(!temp.head) //If the list is empty return it as is. 
        temp = list2;
 
    else
    {
        day_node * dest = temp.head; //Setting destination head. 
        
        while( dest -> go_next() ) //Reaching the end of the list. 
            dest = dest -> go_next(); 
        
        day_node * source = list2.head; //Setting source to head of list2. 
        
        while(source) //While there are items on the source list. 
        {
            dest -> go_next() = new day_node( *source ); //Appending at end.
            dest = dest -> go_next();  //Advancing the destination pointer.
            source = source -> go_next(); //Advancing the source pointer.
        }
        dest -> go_next() = NULL;
    }
    return temp; //Return the object. 
}



//This is the overloaded function for the assingment operator.
//In this function a Linear Linked List is copied as well as deep
//copying the members and pointers within this LLL; that is, within
//each LLL node, there is another LLL that is being copied. 
dayLLL & dayLLL::operator=(const dayLLL & add)
{ 
    day_node * current = add.head; //Setting current to head of argument.
    
    if (current) //If head exists, set it.
    {
        head = new day_node( *add.head ); //Copies contents of head node. 
        current = current -> go_next();
    }
    
    day_node * current2 = head; //Setting current2 to the head of the new list.
    
    while(current)
    {
        day_node * temp = new day_node( *current ); //Copying the contents 
        current2 -> go_next() = temp; //Setting next to temp.
        current2 = temp; //Setting the values of temp into current2. 

        current = current -> go_next();
    }

    return *this; //Return the pointer of the current object. 
}



//This function is the ostream operator overloaded function. This function
//will allow the user to output the contents of the list through main 
//with the simple use of the << operator. 
ostream& operator<<(ostream& out, const dayLLL & day)
{
    day.display_all(); //Calling the display all function. 
    
    return out; //Returning the stream of output to the main program.
}



//Display all of the days of the Liner Linked List as well as all of 
//the Linear Linked List of events that are connected to each day node. 
int dayLLL::display_all(void) const
{
    if(!head)
        return 0; //If the head is empty exit the function with 0. 

    day_node * current = head; //Setting current to head. 

    while(current) //While there is a list to travers. 
    {
        cout << "\n-Scheduled day: " << endl;
        current -> return_day() -> display(); //Display each day in the LLL.
        
        if ( current -> return_events() ) //If ther are events in the day.
        {   
            cout << "\nConnected events to this day: " << endl;
            current -> return_events() -> display_all(); //Dispay the events. 
        }
        
        current = current -> go_next(); //Advancing the next pointers. 
    }
}

