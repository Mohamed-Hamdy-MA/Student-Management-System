/*
 * Queue.c
 *
 *  Created on: Jul 21, 2024
 *      Author: Mohamed Hamdy
 */

#include "Queue.h"
#include "StudentSYS.h"


QueueStatus_t Queue_init(Queue_t* FIFOStruct, ElementType* DataBuffer, uint32_t DataBufferLength)
{
	FIFOStruct->length = DataBufferLength;
	FIFOStruct->base = DataBuffer;
	FIFOStruct->head = FIFOStruct->base;
	FIFOStruct->tail = FIFOStruct->base;
	FIFOStruct->count = 0;

	if (IsQueueNotExist(FIFOStruct)){
		printf("==========Queue is NULL (Not Exist)==========\n");
		return Queue_Null;
	}

	printf("==========Queue initialization Done successfully==========\n");
	return Queue_No_Error;
}
QueueStatus_t Queue_enqueue(Queue_t* FIFOStruct, ElementType* ItemSource)
{
	if (IsQueueNotExist(FIFOStruct)){
		printf("==========Queue is NULL (Not Exist)==========\n");
		return Queue_Null;
	}

	if (IsQueueFull(FIFOStruct)){
		printf("Queue is Full");
		printf("==========Item with roll number %u failed to EnQueued==========\n", ItemSource->rollnumber);
		return Queue_Full;
	}

	if (IsQueueEmpty(FIFOStruct)){
		FIFOStruct->head = FIFOStruct->base;
		FIFOStruct->tail = FIFOStruct->base;
	}

	*(FIFOStruct->head) = *ItemSource;
	printf("==========Item with roll number %u is EnQueued to index %u successfully==========\n",
			ItemSource->rollnumber, FIFOStruct->head - FIFOStruct->base);
	FIFOStruct->head++;
	FIFOStruct->count++;
	if (IsQueuePointerGoToEnd(FIFOStruct, FIFOStruct->head))
		FIFOStruct->head = PointerResetToBase(FIFOStruct, FIFOStruct->head);
	return Queue_No_Error;
}
QueueStatus_t Queue_dequeue(Queue_t* FIFOStruct)
{
	if (IsQueueNotExist(FIFOStruct)){
		printf("==========Queue is NULL (Not Exist)==========\n");
		return Queue_Null;
	}
	if (IsQueueEmpty(FIFOStruct)){
		printf("==========Queue is Empty==========\n");
		return Queue_Empty;
	}

	/*
	 *ItemDestination = *(FIFOStruct->tail);
	printf("==========Item %X is DeQueued from index %u successfully==========\n",
	 *ItemDestination, FIFOStruct->tail - FIFOStruct->base);
	 */

	FIFOStruct->tail++;
	FIFOStruct->count--;
	if (IsQueuePointerGoToEnd(FIFOStruct, FIFOStruct->tail))
		FIFOStruct->tail = PointerResetToBase(FIFOStruct, FIFOStruct->tail);
	return Queue_No_Error;
}
QueueStatus_t Queue_delete_item(Queue_t* FIFOStruct, ElementType* ptrItemToBeDeleted)
{
	uint32_t rollnumberStoreVariable = ptrItemToBeDeleted->rollnumber;

	if (IsQueueNotExist(FIFOStruct)){
		printf("==========Queue is NULL (Not Exist)==========\n");
		return Queue_Null;
	}
	if (IsQueueEmpty(FIFOStruct)){
		printf("==========Queue is Empty==========\n");
		return Queue_Empty;
	}

	//check if item is top element (only one element or top from multiple elements)
	//just minus 1 from head and count
	if (ptrItemToBeDeleted == FIFOStruct->head - 1){
		FIFOStruct->head--;
		FIFOStruct->count--;
		printf("==========Item with roll number %u Deleted successfully==========\n", rollnumberStoreVariable);
		return Queue_No_Error;
	}

	ElementType* ptr_temp_1 = ptrItemToBeDeleted;
	ElementType* ptr_temp_2 = ptr_temp_1 + 1;

	while(ptr_temp_2 != FIFOStruct->head)
	{
		*ptr_temp_1 = *ptr_temp_2;
		ptr_temp_1++;
		ptr_temp_2++;

		if (IsQueuePointerGoToEnd(FIFOStruct, ptr_temp_1))
			FIFOStruct->head = PointerResetToBase(FIFOStruct, ptr_temp_1);

		if (IsQueuePointerGoToEnd(FIFOStruct, ptr_temp_2))
			FIFOStruct->head = PointerResetToBase(FIFOStruct, ptr_temp_2);
	}

	FIFOStruct->head--;
	FIFOStruct->count--;
	printf("==========Item with roll number %u Deleted successfully==========\n", rollnumberStoreVariable);
	return Queue_No_Error;
}
QueueStatus_t Queue_delete_all_items(Queue_t* FIFOStruct)
{
	if (IsQueueNotExist(FIFOStruct)){
		printf("==========Queue is NULL (Not Exist)==========\n");
		return Queue_Null;
	}
	if (IsQueueEmpty(FIFOStruct)){
		printf("==========Queue is Empty==========\n");
		return Queue_Empty;
	}

	PointerResetToBase(FIFOStruct,FIFOStruct->head);
	PointerResetToBase(FIFOStruct,FIFOStruct->tail);
	FIFOStruct->count = 0;
	printf("\n==========All Items in Queue are Deleted successfully, Queue is Empty Now.==========\n");
	return Queue_Empty;
}
QueueStatus_t Queue_print(Queue_t* FIFOStruct)
{
	if (IsQueueNotExist(FIFOStruct)){
		printf("==========Queue is NULL (Not Exist)==========\n");
		return Queue_Null;
	}
	if (IsQueueEmpty(FIFOStruct)){
		printf("==========Queue is Empty==========\n");
		return Queue_Empty;}

	printf("\n==========Printing Queue==========\n");
	ElementType* ptr_temp = FIFOStruct->tail;
	for (uint32_t i = 0; i < FIFOStruct->count; i++)
	{
		if (IsQueuePointerGoToEnd(FIFOStruct, ptr_temp))
			ptr_temp = PointerResetToBase(FIFOStruct, ptr_temp);
		printf("==========>> Index %u in Queue.", ptr_temp - FIFOStruct->base);

		/*///////////////////////////////////////////////*/
		ShowStudentInfo(ptr_temp); //Define your data display based on data type
		/*///////////////////////////////////////////////*/

		ptr_temp++;
	}
	printf("==========Done==========\n");
	return Queue_No_Error;
}
ElementType* Queue_search(Queue_t* FIFOStruct, uint32_t data)
{
	if (IsQueueNotExist(FIFOStruct)){
		printf("==========Queue is NULL (Not Exist)==========\n");
		return NULL;
	}

	if (IsQueueEmpty(FIFOStruct)){
		printf("==========Queue is Empty==========\n");
		return NULL;
	}

	ElementType* ptr_temp = FIFOStruct->tail;
	for (uint32_t i = 0; i < FIFOStruct->count; i++)
	{
		if (IsQueuePointerGoToEnd(FIFOStruct, ptr_temp))
			ptr_temp = PointerResetToBase(FIFOStruct, ptr_temp);

		/*//////////////////////////////////////*/ //Define your condition based on your data type
		if (data == ptr_temp->rollnumber) // in my case roll number inside ElementType of structure
		{
			printf("==========Found==========\n");
			return ptr_temp;
		}
		/*//////////////////////////////////////*/

		ptr_temp++;
	}
	//No match
	printf("==========No Match==========\n");
	return NULL;
}

//This function strongly depend on application layer "StudentSYS" and its Structure Data.
QueueStatus_t Queue_find(Queue_t* FIFOStruct, EFindChoice_t searchtype, UFindContent_t data)
{
	if (IsQueueNotExist(FIFOStruct)){
		printf("==========Queue is NULL (Not Exist)==========\n");
		return Queue_Null;
	}

	if (IsQueueEmpty(FIFOStruct)){
		printf("==========Queue is Empty==========\n");
		return Queue_Empty;
	}

	ElementType* ptr_temp = FIFOStruct->tail;
	uint32_t frequency = 0;

	for (uint32_t i = 0; i < FIFOStruct->count; i++)
	{
		if (IsQueuePointerGoToEnd(FIFOStruct, ptr_temp))
			ptr_temp = PointerResetToBase(FIFOStruct, ptr_temp);

		/*//////////////////////////////////////*/
		switch(searchtype)
		{
		case RollNumber:
			if (data.rollnumber == ptr_temp->rollnumber)
			{
				frequency++;
				ShowStudentInfo(ptr_temp);
				printf("\n========== Frequency = %u ==========\n", frequency);
				return Queue_No_Error;
			}
			break; //break switch

		case FirstName:
			if (*data.firstname == *ptr_temp->firstname)
			{
				frequency++;
				ShowStudentInfo(ptr_temp);
			}
			break; //break switch

		case CourseID:

			for (int j = 0; j < numberofcourses; j++)
			{
				if (data.courseID == ptr_temp->courses[j])
				{
					frequency++;
					ShowStudentInfo(ptr_temp);
					break; //break for j
				}
			}
			break; //break switch
		}
		/*//////////////////////////////////////*/
		 ptr_temp++;
	}
	if (frequency == 0)printf("==========No Match==========\n");
	else printf("\n========== Frequency = %u ==========\n", frequency);
	return Queue_No_Error;
}

uint8_t IsQueuePointerGoToEnd(Queue_t* FIFOStruct, ElementType* Pointer)
{
	if (Pointer == FIFOStruct->base + (FIFOStruct->length * sizeof(ElementType)))
		return 1;
	return 0;
}
ElementType* PointerResetToBase(Queue_t* FIFOStruct, ElementType* Pointer)
{
	Pointer = FIFOStruct->base;
	return Pointer;
}
uint8_t IsQueueFull(Queue_t* FIFOStruct)
{
	if (FIFOStruct->count == FIFOStruct->length) {
		return 1;
	}
	return 0;
}
uint8_t IsQueueEmpty(Queue_t* FIFOStruct)
{
	if (FIFOStruct->count == 0) {
		return 1;
	}
	return 0;
}
uint8_t IsQueueNotExist(Queue_t* FIFOStruct)
{
	if (!FIFOStruct->base || !FIFOStruct->head || !FIFOStruct->tail) {
		return 1;
	}
	return 0;
}
