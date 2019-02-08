// ====================================================================
// // Homework 2 for CS163
// // Bradley Fallon
// // bfallon@pdx.edu
// // 1/31/2019
// // ====================================================================
//
//
// This program defines an abstract data structure that is intended to be used to store text messages.
// There is a message object, which will contain a messages text body and metadata. There are two levels
// of message storage. The first level is a stack, where only the newest message  of the stack can be accessed. The
// second level is a queue, where only the newest message of the queue can be accessed.
//
// When a new message is added to the message storage system, it will be put to the top of the stack. This message
// can be read, deleted, or moved to the queue. Messages that are unwanted can be deleted. Messages that are to be
// kept until further action, are sent to the back of the queue. The front of the queue can be read or deleted.
//
// The new message stack will have a stack class with methods to push, pop, peek, and display.
// The stack will be implemented as a linear link list (LLL) of arrays. The LLL nodes
// will be implemented with structs that point to the next node and the child array. The array
// will be made up of message data objects.
//
// The action item message queue will have methods to enqueue, dequeue, peek, and display.
// The queue will be implemented as a circular link list (CLL) of messages. The CLL nodes
// will be implemented with structs that point to the next node and the message data. The list object
// will have one pointer, rear, which is the most recently added item.
// The next pointer of rear points to the oldest item. When a new item is added,
// it is put at the next pointer of rear, and the new reference of the oldest item gets
// stored at the new item's next pointer.
//
// There will be a top level class for the client to use. This will have methods for create a new message, 
// read the newest message, delete the newest message, move newest message to action queue, read the oldest
// queue message, and delete the oldest queue message.
//
// There will be a class for the message data object, because I like to have methods for setting and getting the values,
// displaying, initializing, and deleting the message data.
//
// All methods of the list will return 1 for success and 0 for failure. It is up to the appliction developer
// to determine what to do in case of these errors and how to communicate with the user if necessary.
//
//
// TEST PLAN
//
// Function                 Case          Expected
//
// stack::push            empty           add the thing and return 1
// stack::pop             empty           return 0
// stack::pop             normal          return 1, remove top
// stack::peek            empty           return 0
// stack::peek            normal          return 1, ref var copies top
// stack::display         normal          return 1, displays top
// stack::display         empty           return 0
//
// queue::enqueue         normal          return 1, rear->next is new
// queue::dequeue         normal          return 1, rear->next is rear->next->next
// queue::dequeue         empty           return 0
// stack::peek            empty           return 0
// stack::peek            normal          return 1, ref var copies top
// stack::display         normal          return 1, displays top
// stack::display         empty           return 0
//
//

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int SIZE_STACK_ARRAY=5;

class Message{
	public:
		Message(void);
		~Message(void);

		int clone(Message &); // Makes this message copy a reference

		int set_author(const char text[]);
		int set_subject(const char text[]);
		int set_date(const char text[]);
		int set_body(const char text[]);

		void display();

	private:
		char * author;
		char * subject;
		char * date;
		char * body;
};

struct StackNode{
	StackNode * next; // Points to the next node
	Message * messages; // Points to the start of an array of messages
};

struct MsgNode{
	MsgNode * next;
	Message msg;
};

class Stack{
	public:
		Stack(void);
		~Stack(void);

		int push(Message & );
		int peek(Message & );
		int pop(Message &); 
		bool is_empty();

	private:
		StackNode * head;
		int top;

};

class Queue{
	public:
		Queue(void);
		~Queue(void);

		int enqueue(Message & );
		int peek(Message & );
		int dequeue(Message &); 
		bool is_empty();

	private:
		MsgNode * rear;
		int top;                                                                                        
};
