//Sender Shepard
//#main.cpp
//This is the client program file. In here we get to test some of the operator
//overloading functions as well as some data structures and their connections
//with themselves. For example, the eventLLL and DayLLL are Linear Linked Lists
//of events and days, respectively. The dayLLL however, contains an eventLLL 
//within it it. Likewise the BST tree contains participants who have a CLL
//within them to represent appointments. The client program will be able to
//sign up as many participants as needed as the data strucutre is set for 
//the BST, however, a poll class needs to be created to creat an array of 
//participants.

#include "times.h"
#include "attendee.h"

//Prototype for the again function. 
bool again(const char prompt[]);

int main ()
{
    event an_event;//Creating an event object. 
    day a_day; //Creating a day object. 
    eventLLL original_event, copy_event; //Creating two eventLLL to copy op ov.
    dayLLL original_day, copy_day; //Creating to dayLLL to copy with op overld.

    original_event.create_events(an_event); //Creating a LLL of events. 
    original_day.create_day(a_day); //Creating a LLL of days.  
    
    //Testing operator overloading in here, assignment operator. 
    copy_event = original_event; //Copying data into copy_event. 
    original_day.admit_eventLLL(copy_event); //Adding events into days. 
    
    cout << "\nDisplaying all days and all events connected to them: " << endl;
    
    copy_day = original_day; //Testing operator overloading, assignment op.
    cout << copy_day; //Overloading << operator. 
    
    //----------------- BST classes and attendees ------------------------//
    attendee an_attendee, attendee; //An object for an attendee. 
    BST testBST; //BST obj. 

    testBST.create_appointment(an_attendee); //Creating an attendee in BST. 
    //Creating appointments for one attendee. 
    do{
        
        an_attendee.retrieve(original_day, an_event); //Inserting appt.

    }while( again ("\n~~~Want to sign up for another appt? 'Y' or 'N' ") );
    
    testBST.insert(an_attendee); //Inserting an attendee into the BST. 
    
    //Prompting the user to add another attendee.
    if( again ("\n~~~Want to sign up another participant? 'Y' or 'N' ") )
    {
        testBST.create_appointment(attendee); //Creating an attendee in BST. 
    
        do{    
            
            attendee.retrieve(original_day, an_event); //Inserting appt.
        
        }while( again ("\n~~~Want to sign up for another appt? 'Y' or 'N' ") );
    
    testBST.insert(attendee); //Inserting an attendee into the BST. 
    }

    cout << "\nDisplaying BST appointments by last name: " << endl; 
    cout << testBST; //Using << operator overloaded here. 

    return 0;
}



//This function prompts the user to repeat an action. 
bool again (const char prompt[])
{
    char response; //Variable to hold response from user.

        cout << prompt; //Prompting user here. 
        cin >> response; cin.ignore(100, '\n');

    return 'Y' == toupper(response);
}
