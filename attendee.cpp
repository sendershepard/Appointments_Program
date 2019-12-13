//Sender Shepard
//attendee.h
//This file includes the attendee classes as well as the binary search tree
//classes. This file creates functions in which the participant will be 
//able to hold appointments in a Circular Linked List. These apointments 
//will be found on an dayLLL object wich is passed down from main. This 
//gives the opportunity to sign up an appt. The BST will be able to hold 
//attendees. The BST will be able to display it's contents with the 
//participants contents as well. 

#include "attendee.h"

//Default constructor; setting private members to instances of NULL and 0.
attendee::attendee()
{
    rear = NULL; //Setting hand to be empty.
    last_name = NULL; //Setting the score to be 0.
}



//Default deconstructor.
attendee::~attendee(void)
{
    if(rear)
    {
    event_node * head = rear -> go_next(); //Head to be in the beginning.
    rear -> go_next() = NULL; //Disjoining the CLL.
   
    event_node * temp = head; 

        while(temp) //Traverse while there are nodes.
        {
            head = head -> go_next();
            //delete temp -> return_event();
            delete temp;
            temp = head;
        }
    }   
    if(last_name)
        delete [] last_name; 
}



//Copy constructor.
attendee::attendee(const attendee & to_copy)
{
    last_name = new char[ strlen(to_copy.last_name) + 1 ];
    strcpy(last_name, to_copy.last_name); //Deep copy of data members. 
    
    event_node * current = to_copy.rear -> go_next(); //Setting current to end
    to_copy.rear -> go_next() = NULL; //Disjoining the list.

    if(current) //If head exists, copy it. 
    {
        rear = new event_node( *to_copy.rear ); //New node copies w/ copy'ct.
        current = current -> go_next(); //Advancing head. 

    }
    
    event_node * current2 = rear; //Pointer set to new head. 

    while(current)
    {
        event_node * temp = new event_node( *current ); //Copy constructor use.
        current2 -> go_next() = temp; //Setting pointer to temp.
        current2 = temp; //Setting current with the value of temp. 

        current = current -> go_next(); //Advancing pointers.
    }
    
    current2 -> go_next() = rear; //Setting current pointer to rear: CLL.
    rear = current2; //Updating rear to the end of the list. 
}



//This function does a deep copy of the attendee's member variables. 
int attendee::create_attendee(char * last)
{
    if(last_name)
        delete [] last_name;
    
    last_name = new char[strlen(last) + 1 ];
    strcpy(last_name, last);
}



//This function creates an obj of attendee type and performs a deep copy.  
int attendee::copy_attendee(const attendee & person)
{
    if(last_name)
        delete [] last_name;
    
    last_name = new char[strlen(person.last_name) + 1 ];
    strcpy(last_name, person.last_name);
}



//Function that compares the last name. If it is an exact match,
//return 1, and thus true. 
int attendee::compare_attendee(char * last)
{
    if( strcmp (last, last_name) == 0 )
        return 1;
    else 
        return 0; 
}



//This function compares the string and if it is smaller will return
//-1, if it is equal 0 and if it is greater 1. 
int attendee::compare_attendee(const attendee & last)
{
    return strcmp(last.last_name, last_name); 
}



//Adding an appointment using a Circular Linked List (CLL)
//The card is added at the end of the list. 
int attendee::insert_event(event & adding)
{
    event_node * temp = new event_node; //Creating a new node.
    temp -> return_event() = new event; //Creating an event. 
    temp -> return_event() -> copy_event(adding); //Copying the data.
    temp -> go_next() = NULL; //Setting next poinger to NULL.
    
    if( !rear ) //Special case 1. No nodes present. 
    {
        rear = temp; 
        temp -> go_next() = rear; //Connecting the only node to itself.
    }
    else if( rear -> go_next() == rear ) //Special case 2. Only one node.
    {
        rear -> go_next() = temp; //Connecting the hand to temp. 
        temp -> go_next() = rear; //Using temp pointer to connect hand.
        rear = temp;              //Updating hand.
    }
    else //ALL other cases.
    {
        temp -> go_next() = rear -> go_next(); //Setting temp to head of list.
        rear -> go_next() = temp; //Setting the hand's next pointer to temp.
        rear = rear -> go_next(); //Updating the hand to be at the end.
    }   
}



//This function prompts user to chose a day in which to sign up for a day.
//It also prompts the user to sign up for a time. 
int attendee::retrieve(dayLLL & found, event & an_event)
{
    char day[INPUT] = {'\0'}; //Variable to hold user input. 
    int time = 0; //Variable to hold user input. 

    cout << "\nPlease enter weekday you wish to sign up for: " << endl;
    cin.get(day, INPUT, '\n');
    cin.ignore(100, '\n');

    if( found.retrieve_day(day) ) //if user input is a match:
    {
        cout << "\nPlease enter time you want to sign up for: " << endl;
        cin >> time;
        cin.ignore(100, '\n');

        if( found.retrieve_time(time, day, an_event) )
        {
            insert_event(an_event);
        }
    }
}



//Function in which an attendee pointer is used to display all of the 
//appointments that this person has. 
int attendee::display_all(void) const
{
    if( !rear ) //If the hand is empty, exit the function.
        return 0;
    
    event_node * current = rear; //Setting a temp pointer to the end of CLL.
    int i = 0; //Integer counter to close CLL loop.  

    cout << "\n-----------These are your apptointments--------------" << endl; 
    while( current && !i )//While there are nodes and it's not end of list.
    {
        current -> return_event() -> display();
        current = current -> go_next(); //Traverse.

        if ( current == rear )
            ++i;//We have reached the end of list. Flag it. 
    }
    return 1; //Exit successfully.
}



//Function to display the data members of the attendee class. 
int attendee::display(void) const
{
    cout << "\n---Last name is: " << last_name << endl; 
}



//Default constructor. 
tree_node::tree_node(void)
{
    left = NULL;
    right = NULL;
    person = NULL;
}



//Default constructor. 
BST::BST(void)
{
    root = NULL;
}



//Default deconstructor.
BST::~BST(void)
{
    remove_all(root); //Recursive call to delete the tree.
}



//Recursive function that calls itself until it has put the tree on 
//the stack and upon it's return deletes all nodes. 
int BST::remove_all(tree_node *& root)
{
    if(!root)
        return 0;
    
    remove_all(root -> go_left());
    remove_all(root -> go_right());
    delete root -> return_person();
    delete root;
    root = NULL; 
}



//Function that calls the private member function to insert an attendee.
int BST::insert(const attendee & to_add)
{
    return insert(root, to_add);
}



//This is is a recursive function which calls itself in order to traverse
//the tree and upon it's return it inserts an attendee. 
int BST::insert(tree_node *& root, const attendee & to_add)
{
    if(!root) //Add a node at the leave or root of the tree. 
    {
        root = new tree_node; //Creating a new tree node. 
        root -> return_person() = new attendee(to_add); //Copy constructor. 
        root -> go_left() = root -> go_right() = NULL; //Setting p to null. 
    }
    else if(root -> return_person() -> compare_attendee(to_add) < 0)
        insert(root -> go_left(), to_add);
    else
        insert(root -> go_right(), to_add); 
}



//Function to create appointments by inserting them into the BST. 
void BST::create_appointment(attendee & to_add)
{
    char name[INPUT] = {'\0'}; //Loca variable to hold user input. 
    
    cout << "\nPlease enter the last name of the participant here: " << endl;
    cin.get(name, INPUT, '\n');
    cin.ignore(100, '\n');

    to_add.create_attendee(name); //Creating an attendee for the BST.  
}



//This function is the ostream operator overloaded function. This function
//will allow the user to output the contents of the list through main 
//with the simple use of the << operator. 
ostream& operator<<(ostream& out, const BST & name)
{
    name.display_all(); //Calling the display all function. 
    
    return out; //Returning the stream of output to the main program.
}



//This function will call the private member function to display the tree. 
int BST::display_all(void) const
{
    if(root)
        display_all(root); //Recursive call. 
}



//This is a recursive function that traverses the tree and upon it's return
//it will display the tree. 
int BST::display_all(tree_node * root) const
{
    if(!root) //If the root is empty, exit. 
        return 0;
    
    display_all(root -> go_left() ); //In order traversal. 
    root -> return_person() -> display(); //Display contents of root. 
    if( root -> return_person() ) //If the attendee has appointments display.
    {
        cout << "\nThis are the appointments that you are signed up for:\n";
        root -> return_person() ->  display_all();
    }
    display_all(root -> go_right() ); //In order traversal. 
}

