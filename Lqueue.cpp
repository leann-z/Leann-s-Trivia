#ifndef LQUEUE_CPP
#define LQUEUE_CPP
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//Templated node class used in templated linked list
template <class T>
class Node {
   public:
  Node( const T& data ); //Constructor
  T& GetData(); //Gets data from node
  void SetData( const T& data ); //Sets data in node
  Node<T>* GetNext(); //Gets next pointer
  void SetNext( Node<T>* next ); //Sets next pointer
private:
  T m_data;
  Node<T>* m_next;
};

//Overloaded constructor for Node
template <class T>
Node<T>::Node( const T& data ) {
   m_data = data;
   m_next = NULL;
}

//Returns the data from a Node
template <class T>
T& Node<T>::GetData() {
   return m_data;
}

//Sets the data in a Node
template <class T>
void Node<T>::SetData( const T& data ) {
   m_data = data;
}

//Gets the pointer to the next Node
template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

//Sets the next Node
template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

template <class T>
class Lqueue {
 public:
  // Name: Lqueue() (Linked List Queue) - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Preconditions: None
  // Postconditions: Creates a new lqueue where m_head and m_tail point to nullptr
  // Required
  Lqueue();
  // Name: ~Lqueue() - Destructor
  // Desc: Used to destruct a Lqueue
  // Preconditions: There is an existing lqueue with at least one node
  // Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
  // Required
 ~Lqueue();
  // Name: Lqueue (Copy Constructor)
  // Preconditions: Creates a copy of existing LQueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  // Required
  Lqueue(const Lqueue&);
  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: Copies an Lqueue into an existing Lqueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  // Required
  Lqueue<T>& operator= (Lqueue&);
  // Name: Push
  // Preconditions: Takes in data. Creates new node. 
  //                Requires a Lqueue
  // Postconditions: Adds a new node to the end of the lqueue.
  // Required
  void Push(const T&);
  // Name: Pop
  // Preconditions: Lqueue with at least one node. 
  // Postconditions: Removes first node in the lqueue, returns data from first node.
  // Required
  T Pop();
  // Name: Display
  // Preconditions: Outputs the lqueue.
  // Postconditions: Displays the data in each node of lqueue
  // Required (used only for testing)
  void Display();
  // Name: Front
  // Preconditions: Requires a populated lqueue
  // Postconditions: Returns whatever data is in front
  // Required
  T Front();
  // Name: IsEmpty
  // Preconditions: Requires a lqueue
  // Postconditions: Returns if the lqueue is empty.
  // Required
  bool IsEmpty();
  // Name: GetSize
  // Preconditions: Requires a lqueue
  // Postconditions: Returns m_size
  // Required
  int GetSize();
  // Name: Find()
  // Preconditions: Requires a lqueue
  // Postconditions: Iterates and if it finds the thing, returns index, else -1
  // Required
  int Find(T&);
  // Name: Swap(int)
  // Preconditions: Requires a lqueue
  // Postconditions: Swaps the nodes at the index with the node prior to it.
  // Required
  void Swap(int);
  // Name: Clear
  // Preconditions: Requires a lqueue
  // Postconditions: Removes all nodes in a lqueue
  // Required
  void Clear();
  // Name: At
  // Precondition: Existing Lqueue
  // Postcondition: Returns object from Lqueue at a specific location
  // Desc: Iterates to node x and returns data from Lqueue
  // Required
  T At (int x);
private:
  Node <T> *m_head; //Node pointer for the head
  Node <T> *m_tail; //Node pointer for the tail
  int m_size; //Number of nodes in queue
};

// Preconditions: None
// Postconditions: Creates a new lqueue where m_head and m_tail point to nullptr
template <typename T>
Lqueue<T>::Lqueue() {
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0; // sets all variables to null/0
}


// Preconditions: There is an existing lqueue with at least one node
// Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
//                 to have no memory leaks!
template <typename T>
Lqueue<T>::~Lqueue<T>() {
    Clear(); // calls clear here to deallocate
}

// Preconditions: Creates a copy of existing LQueue
//                Requires a Lqueue
// Postconditions: Copy of existing Lqueue
template <typename T>
Lqueue<T>::Lqueue(const Lqueue<T> & q) {
    m_size = 0;
    Node<T> *newNode = q.m_head; // creates new node
    while (newNode != nullptr) {
        Push(newNode->GetData()); // use push function with new node's data
        newNode = newNode->GetNext();
    }


}

// Preconditions: Copies an Lqueue into an existing Lqueue
//                Requires a Lqueue
// Postconditions: Copy of existing Lqueue
template <typename T>
Lqueue<T> &Lqueue<T>::operator=(Lqueue<T> & q) {
    Node<T> *newNode = q.m_head; // creates new node
    while (newNode != nullptr) {
        Push(newNode->GetData()); // pushes new node data
        newNode = newNode->GetNext();
    }
    return *this;
}


// Preconditions: Takes in data. Creates new node.
//                Requires a Lqueue
// Postconditions: Adds a new node to the end of the lqueue.
template <typename T>
void Lqueue<T>::Push(const T& n) {
    Node <T> *newNode = new Node<T>(n); // points to a new node
    // A new node is created

    //if the list is empty set head to point to new node
    if (m_head == nullptr) {

        m_head = newNode;
        m_tail = newNode;
    }
    else {

        m_tail->SetNext(newNode); // if head is not null then tail should too
        m_tail = newNode;
    }
    m_size++;


}


// Preconditions: Lqueue with at least one node.
// Postconditions: Removes first node in the lqueue, returns data from first node.
template <typename T>
T Lqueue<T>::Pop() {
    if (m_head == nullptr) {
        return NULL;
    }

    // Move the head pointer to the next node
    Node<T>* temp = m_head;
    T prev = temp->GetData();
    m_head = m_head->GetNext();

    delete temp; // deallocates

    m_size--; // decrement size

    return prev;

    // have to return data
}


// Preconditions: Outputs the lqueue.
// Postconditions: Displays the data in each node of lqueue
template <typename T>
void Lqueue<T>::Display() {

    Node<T>* temp = m_head;
    while(temp != NULL){
        cout<<temp->GetData()<< endl; // couts data in each node
        temp = temp->GetNext();
    }
}


// Preconditions: Requires a populated lqueue
// Postconditions: Returns whatever data is in front
template <typename T>
T Lqueue<T>::Front() {
 if (m_head == nullptr) {
     return NULL; // if the linked list is empty
 } else {
     return m_head->GetData(); // return data
 }
}


// Preconditions: Requires a lqueue
// Postconditions: Returns if the lqueue is empty.
template <typename T>
bool Lqueue<T>::IsEmpty() {
    if(m_head == NULL){ // if the list is empty
        return true;
    } else {
        return false;
    }
}


// Preconditions: Requires a lqueue
// Postconditions: Returns m_size
template <typename T>
int Lqueue<T>::GetSize() {
    return m_size;
}


// Preconditions: Requires a lqueue
// Postconditions: Iterates and if it finds the thing, returns index, else -1
template <typename T>
int Lqueue<T>::Find(T & data) {
    Node<T>* current = m_head; // initialize current
    int i = 0;
    while (current != NULL) // while we are not at the end of the list
    {
        if (current->GetData() == data)
            return i; // return index
        current = current->GetNext();
        i++;
    }
    return -1;
}


// Preconditions: Requires a lqueue
// Postconditions: Swaps the nodes at the index with the node prior to it.
template <typename T>
void Lqueue<T>::Swap(int key1){

    // if they already equal each other
    Node<T> *previous = NULL, *current = m_head;
    int i = 0;
    while (current != nullptr && i != key1) { // while we arent at the end of the list and havent found key
        previous = current;
        current = current->GetNext();
        i++;
    }


    // if either current or present is null, nothing to do
    if (current == nullptr || previous == nullptr)
        return;


    Node<T>* temp = previous;
    temp->SetNext(current->GetNext());
    current->SetNext(temp);



    if (i == 1)
        m_head = current; // set beginning of the list to current
    else if (i == m_size - 1)
        m_tail = temp;

}


// Preconditions: Requires a lqueue
// Postconditions: Removes all nodes in a lqueue
template <typename T>
void Lqueue<T>::Clear() {

    // get the real head by dereferencing
    Node<T>* curr = m_head;
    Node<T>* next = nullptr;

    while (curr != nullptr) // while we arent at the end of the list
    {
        next = curr->GetNext();
        delete curr;
        curr = next;
    }
    // dereference head again
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}


// Precondition: Existing Lqueue
// Postcondition: Returns object from Lqueue at a specific location
// Desc: Iterates to node x and returns data from Lqueue
template <typename T>
T Lqueue<T>::At(int x) {
    Node<T>* current = m_head;

    // the index
    int count = 0;
    while (current != NULL) {
        if (count == x)
            return (current->GetData());
        count++;
        current = current->GetNext();
    }

    // if not found, fail
    return NULL;
}




#endif
