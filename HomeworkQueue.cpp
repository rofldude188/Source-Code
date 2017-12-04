//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

//////////////////////////////////////////////////////////////
//
// local #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <stddef.h>
#include <cstddef>
#include <iostream>
using namespace std;
#endif

//////////////////////////////////////////////////////////////
//
// struct definitions 
//
#ifndef MARMOSET_TESTING
enum COURSE {CHE102, MATH115, MATH117, ECE105, ECE150, ECE190, Null};

struct Assignment 
{
	COURSE course; // CHE102, MATH117, etc.
	int assnNum; // Assignment Number
	int dueMonth; // Month due (1-12)
	int dueDay; // Day due (1-31)
	char* description; // Assignment description
};

struct HomeworkQueue
{
	Assignment* assn;
	HomeworkQueue* nextInQueue;
};

#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
//

bool enqueue(HomeworkQueue*& queue, const Assignment& assignment);
const Assignment* dequeue(HomeworkQueue*& queue);
int daysTillDue(const HomeworkQueue* q, const COURSE course);
const Assignment* dueIn(const HomeworkQueue* q, const int numDays);

//////////////////////////////////////////////////////////////
//
// Function definitions. PLEASE USE HELPER FUNCTIONS
//
bool isEmpty(HomeworkQueue *head){
	if(head == 0)
		return true;
	else
		return false;
}
void insertAsFirstElement(HomeworkQueue *&head, HomeworkQueue *&last, Assignment *assn){
	HomeworkQueue *temp = new HomeworkQueue;
	temp->assn = assn;
	temp->nextInQueue = 0;
	head = temp;
	last = temp;
}
void addNodeAtPos(HomeworkQueue *& head, Assignment *assn, int pos)
{
  HomeworkQueue* prev = new HomeworkQueue();
  HomeworkQueue* curr = new HomeworkQueue();
  HomeworkQueue* newNode = new HomeworkQueue();
  newNode->assn = assn;

  int tempPos = 0;   // Traverses through the list

  curr = head;      // Initialize current to head;
  if(head != 0)
  {
    while(curr->nextInQueue != 0 && tempPos != pos)
    {
        prev = curr;
        curr = curr->nextInQueue;
        tempPos++;
    }
    if(pos==0)
    {
       cout << "Adding at Head! " << endl;
       // Call function to addNode from head;
    }
    else if(curr->nextInQueue == 0 && pos == tempPos+1)
    {
      cout << "Adding at Tail! " << endl;
       //Call function to addNode at tail;
    }
    else if(pos > tempPos+1){
      cout << " Position is out of bounds " << endl;
     //Position not valid
	}
    else{
        prev->nextInQueue = newNode;
        newNode->nextInQueue = curr;
        cout << "Node added at position: " << pos << endl;
    }
 }
 else
 {
    head = newNode;
    newNode->nextInQueue=0;
    cout << "Added at head as list is empty! " << endl;
 }
}
void insert(HomeworkQueue *&head, HomeworkQueue *&last, Assignment *assn){
	int index = 0;
	if(isEmpty(head))
		insertAsFirstElement(head, last, assn);
	else{
		cout << "is it even reaching this" << endl;
		HomeworkQueue *temp2;
		for(temp2 = head;temp2->nextInQueue != NULL; temp2 = temp2->nextInQueue){
			if(assn->dueMonth < temp2->assn->dueMonth){
				addNodeAtPos(head, assn, index);
			}
			else if(temp2->nextInQueue == NULL){
				addNodeAtPos(head, assn, index+1);
			}
			else{
				index++;
			}
		}
				
	//determine what position to insert this assignment

	//This code just adds to the end of list
	//HomeworkQueue *temp = new HomeworkQueue;
	//temp->assn = assn;
	
	
	/*HomeworkQueue *temp2;
	for(temp2 = head;temp2->nextInQueue != NULL; temp2 = temp2->nextInQueue){
		if(temp2->assn->dueMonth > temp->assn->dueMonth){
			temp->nextInQueue = temp2;	
		}
		else{
			temp->nextInQueue = NULL;
		}
	}	*/
	
	//temp->nextInQueue = 0;
	//last->nextInQueue = temp;
	//last = temp;
	}
}
void showList(HomeworkQueue *& head){
	if(isEmpty(head)){
		cout << "The list is empty\n";
	}
	else{
		HomeworkQueue *iter = head;
		cout << "The list contains: \n";
		while(iter != 0){
			cout << iter->assn->course << endl;
			cout << iter->assn->assnNum << endl;
			cout << iter->assn->dueMonth << endl;
			cout << iter->assn->dueDay << endl;
			cout << iter->assn->description << endl;
			iter = iter->nextInQueue;
		}
	}
}
bool enqueue(HomeworkQueue*& queue, const Assignment& assignment)
{
		HomeworkQueue *head = 0;
	HomeworkQueue *last = 0;
	Assignment *a = new Assignment;
	a->course = assignment.course;
	a->assnNum = assignment.assnNum;
	a->dueMonth = assignment.dueMonth;
	a->dueDay = assignment.dueDay;
	a->description = assignment.description;

	insert(head, last, a);
	showList(head);
	return true;
}
const Assignment* dequeue(HomeworkQueue*& queue)
{
	return 0;
}
int daysTillDue(const HomeworkQueue* q, const COURSE course)
{
	return -1;
}
const Assignment* dueIn(const HomeworkQueue* q, const int numDays)
{
	return 0;
}

//////////////////////////////////////////////////////////////
//
// Test Driver
//
// Do not remove the #ifndef and its associated #endif
//

#ifndef MARMOSET_TESTING

int main(const int argc, const char* const argv[]) {
  		// Some test driver code here ....
	std::cout << std::endl << "Implement some more appropriate tests in main()" << std::endl << std::endl;
	HomeworkQueue *head = NULL;
	HomeworkQueue *last = NULL;
	
	HomeworkQueue* p_queue = new HomeworkQueue;
	p_queue->nextInQueue = NULL;
	p_queue->assn = NULL;

	char sampleDescription[] = "Sequential Execution";
	Assignment assn1 = 
	{
		.course = ECE150,
		.assnNum = 1,
		.dueMonth = 9,
		.dueDay = 15,
		.description = sampleDescription
	};
	Assignment assn2 = 
	{
		.course = ECE105,
		.assnNum = 2,
		.dueMonth = 6,
		.dueDay = 12,
		.description = sampleDescription
	};
	Assignment assn3 = 
	{
		.course = ECE105,
		.assnNum = 3,
		.dueMonth = 3,
		.dueDay = 10,
		.description = sampleDescription
	};
	//Assignment *assn = new Assignment;
	//assn->course = ECE150;
	//assn->assnNum = 0;
	//assn->dueMonth = 9;
	//assn->dueDay = 15;
	//assn->description = sampleDescription;
	//insert(head, last, assn1);
	//showList(head);
	bool enqueueSuccess = enqueue(p_queue, assn1);
	bool s = enqueue(p_queue, assn2);
	bool t = enqueue(p_queue, assn3);
	showList(head);  
	if(enqueueSuccess)
	{
		std::cout << "assn1 enqueued successfully" << std::endl << std::endl;

	}
	else
	{
		std::cout << "enqueue() failed" << std::endl << std::endl; 
	}

	const Assignment* p_firstAssignmentInQueue = dequeue(p_queue);
	
	if (p_firstAssignmentInQueue)
	{
		std::cout << "Dequeue successful..." << std::endl;
		std::cout << "Course: " << p_firstAssignmentInQueue->course << std::endl;
		std::cout << "Assignment #: " << p_firstAssignmentInQueue->assnNum << std::endl;
		std::cout << "Day due: " << p_firstAssignmentInQueue->dueDay << std::endl;
		std::cout << "Month due: " << p_firstAssignmentInQueue->dueMonth << std::endl;
		std::cout << "Description: " << p_firstAssignmentInQueue->description << std::endl;
	}
	else
	{
		std::cout << "dequeue() failed" << std::endl;
	}

	delete p_queue;

	return 0;
}

#endif
