/*
 * Queue.h
 *
 *  Created on: Jul 21, 2024
 *      Author: Mohamed Hamdy
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdint.h>
#include <stdint.h>
#include <string.h>
#include "StudentSYS.h"


#define ElementType SStudentInfo_t

typedef struct {
	uint32_t length;
	ElementType* base;
	ElementType* head;
	ElementType* tail;
	uint32_t count;
}Queue_t;

typedef enum {
	Queue_No_Error,
	Queue_Full,
	Queue_Empty,
	Queue_Null,
}QueueStatus_t;

QueueStatus_t Queue_init(Queue_t* FIFOStruct, ElementType* DataBuffer, uint32_t DataBufferLength);//called in StudentSYSIntialization()
QueueStatus_t Queue_enqueue(Queue_t* FIFOStruct, ElementType* Item);//called in add_student_manually() & add_students_from_file()
QueueStatus_t Queue_dequeue(Queue_t* FIFOStruct);//never called
QueueStatus_t Queue_delete_item(Queue_t* FIFOStruct, ElementType* ptrItemToBeDeleted);//called in delete_student_by_roll()
QueueStatus_t Queue_delete_all_items(Queue_t* FIFOStruct);//called in delete_all_students()
ElementType* Queue_search(Queue_t* FIFOStruct, uint32_t data);
QueueStatus_t Queue_print(Queue_t* FIFOStruct);//called in view_all_students()

//This function strongly depend on application layer "StudentSYS" and its Structure Data.
QueueStatus_t Queue_find(Queue_t* FIFOStruct, EFindChoice_t searchtype, UFindContent_t data);

uint8_t IsQueuePointerGoToEnd(Queue_t* FIFOStruct, ElementType* Pointer);
ElementType* PointerResetToBase(Queue_t* FIFOStruct, ElementType* ptr);
uint8_t IsQueueFull(Queue_t* FIFOStruct);
uint8_t IsQueueEmpty(Queue_t* FIFOStruct);
uint8_t IsQueueNotExist(Queue_t* FIFOStruct);

#endif /* QUEUE_H_ */
