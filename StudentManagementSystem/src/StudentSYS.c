/*
 * StudentSYS.c
 *
 *  Created on: Jul 21, 2024
 *      Author: Mohamed Hamdy
 */

#include "Queue.h"
#include "StudentSYS.h"

Queue_t Students_FIFO;
ElementType Students_Arr[numberofstudent];
FILE *students_file, *students_update_file;


void StudentSYSIntialization()
{
	Queue_init(&Students_FIFO, Students_Arr, numberofstudent);
}


void add_student_manually()
{
	ElementType* Item = TakeStudentInfoFromConsole();
	if (!Item)
	{
		printf("[Error] The roll number is already taken. The roll number must be unique.\n");
		return;
	}

	Queue_enqueue(&Students_FIFO, Item);
}
void add_students_from_file()
{
	ElementType Item;

	// Opening a student.txt file with option read
	students_file = fopen("students.txt", "r");

	// Check if the file exist and there is data or not
	if(students_file == NULL)
	{
		printf("\n [ERROR] student.txt file not found.\n");
		return NULL;
	}

	// Reading students until end of file this using of feof == Check end of file
	while(!feof(students_file))
	{
		//ElementType* Item = TakeStudentInfoFromFile();
		fscanf(students_file, "%u", &Item.rollnumber);

		if(Queue_search(&Students_FIFO, Item.rollnumber)) //If roll number Found, return NULL
		{
			//The roll number is already taken.
			printf("[Error] The roll number %u is already taken. The roll number must be unique.\n", Item.rollnumber);
			// Ignore the rest of the line
			fscanf(students_file, "%*[^\n]");
			continue;
		}

		fscanf(students_file, "%s", Item.firstname);
		fscanf(students_file, "%s", Item.secondname);
		fscanf(students_file, "%f", &Item.GPA);

		for (int i = 0; i < numberofcourses; i++)
		{
			fscanf(students_file, "%u", &Item.courses[i]);
		}

		Queue_enqueue(&Students_FIFO, &Item);
	}
	// Closing the file
	fclose(students_file);
}
void find_student(EFindChoice_t searchtype)
{
	UFindContent_t data;
	switch(searchtype)
	{
	case RollNumber:
		DPRINTF("\tEnter roll number: ");
		scanf("%u", &data.rollnumber);
		Queue_find(&Students_FIFO, RollNumber, data);
		break;
	case FirstName:
		DPRINTF("\tEnter first name: ");
		scanf("%s", data.firstname);
		Queue_find(&Students_FIFO, FirstName, data);
		break;
	case CourseID:
		DPRINTF("\tEnter Course ID: ");
		scanf("%u", &data.courseID);
		Queue_find(&Students_FIFO, CourseID, data);
		break;
	}
}
void delete_student_by_roll()
{
	uint32_t rollnumber;
	DPRINTF("\tEnter roll number: ");
	scanf("%u", &rollnumber);

	ElementType* ptr_temp = Queue_search(&Students_FIFO, rollnumber);
	if (!ptr_temp)
	{
		printf("[Error] The roll number is not exist.\n");
		return;
	}

	Queue_delete_item(&Students_FIFO, ptr_temp);
}
void edit_student_by_roll()
{
	uint32_t rollnumber;
	uint32_t rollnumbernew;
	DPRINTF("\tEnter roll number: ");
	scanf("%u", &rollnumber);

	ElementType* ptr_temp = Queue_search(&Students_FIFO, rollnumber);
	if (!ptr_temp)
	{
		printf("[Error] The roll number is not exist.\n");
		return;
	}

	//show student info before editing
	ShowStudentInfo(ptr_temp);

	uint32_t option;
	DPRINTF("\n----------Choose on of the following Options----------");
	DPRINTF("\n\t1: Edit Roll Number");
	DPRINTF("\n\t2: Edit First Name");
	DPRINTF("\n\t3: Edit Second Name");
	DPRINTF("\n\t4: Edit GPA");
	DPRINTF("\n\t5: Edit Courses");
	DPRINTF("\nEnter Option Number: ");
	scanf("%u",&option);
	DPRINTF("--------------------\n");

	switch (option)
	{
	case 1:
		DPRINTF("\tEnter new roll number: ");
		scanf("%u", &rollnumbernew);

		if(Queue_search(&Students_FIFO, rollnumbernew)) //If new roll number Found, return NULL
		{
			//The roll number is already taken.
			printf("[Error] The roll number %u is already taken. The roll number must be unique.\n", rollnumbernew);
			break;
		}

		ptr_temp->rollnumber = rollnumbernew;
		DPRINTF("\n----------Edited successfully----------");
		break;
	case 2:
		DPRINTF("\tEnter new first name:  ");
		scanf("%s", ptr_temp->firstname);
		DPRINTF("\n----------Edited successfully----------");
		break;
	case 3:
		DPRINTF("\tEnter new second name:  ");
		scanf("%s", ptr_temp->secondname);
		DPRINTF("\n----------Edited successfully----------");
		break;
	case 4:
		DPRINTF("\tEnter new GPA:  ");
		scanf("%f", &ptr_temp->GPA);
		DPRINTF("\n----------Edited successfully----------");
		break;
	case 5:
		DPRINTF("\t1: Edit Course no.1");
		DPRINTF("\n\t2: Edit Course no.2");
		DPRINTF("\n\t3: Edit Course no.3");
		DPRINTF("\n\t4: Edit Course no.4");
		DPRINTF("\n\t5: Edit Course no.5");
		DPRINTF("\nEnter Option Number: ");
		scanf("%u",&option);
		DPRINTF("\tEnter new course ID: ");
		scanf("%u", &ptr_temp->courses[option-1]);
		DPRINTF("----------Edited successfully----------");
		break;
	default:
		DPRINTF("=====Wrong Option=====\n");
		break;
	}
	ShowStudentInfo(ptr_temp);
}
void view_all_students()
{
	Queue_print(&Students_FIFO);
}
void delete_all_students()
{
	Queue_delete_all_items(&Students_FIFO);
}
void Save_in_text_file()
{

	if (IsQueueNotExist(&Students_FIFO)){
		printf("----------Queue is NULL (Not Exist)----------\n");
		return;
	}

	if (IsQueueEmpty(&Students_FIFO)){
		printf("----------Queue is Empty----------\n");
		return;
	}

	// Opening a student.txt file with option read
	students_update_file = fopen("students_update.txt", "w");

	// Check if the file exist and there is data or not
	if(students_update_file == NULL)
	{
		printf("\n [ERROR] students_update.txt file not found. \n");
		return NULL;
	}

	ElementType* ptr_temp = Students_FIFO.tail;
	do
	{
		if (IsQueuePointerGoToEnd(&Students_FIFO, ptr_temp))
			ptr_temp = PointerResetToBase(&Students_FIFO, ptr_temp);

		fprintf(students_update_file, "%u ", ptr_temp->rollnumber);
		fprintf(students_update_file, "%s ", ptr_temp->firstname);
		fprintf(students_update_file, "%s ", ptr_temp->secondname);
		fprintf(students_update_file, "%0.2f ", ptr_temp->GPA);

		for (int i = 0; i < numberofcourses; i++)
		{
			fprintf(students_update_file, "%u ", ptr_temp->courses[i]);
		}
		// New line after every Item
		fprintf(students_update_file, "\n");
		ptr_temp++;
	}
	while(ptr_temp != Students_FIFO.head);

	printf("\n----------Update Students Info are saved in students_update.txt file successfully----------\n");

	// Closing the file
	fclose(students_file);
}


ElementType* TakeStudentInfoFromConsole()
{
	static ElementType NewStudent;

	DPRINTF("\tEnter roll number: ");
	scanf("%u", &NewStudent.rollnumber);

	if(Queue_search(&Students_FIFO, NewStudent.rollnumber)) //If roll number Found, return NULL
	{
		//The roll number is already taken.
		return NULL;
	}

	DPRINTF("\tEnter first name: ");
	scanf("%s", NewStudent.firstname);

	DPRINTF("\tEnter second name: ");
	scanf("%s", NewStudent.secondname);

	DPRINTF("\tEnter GPA: ");
	scanf("%f", &NewStudent.GPA);

	DPRINTF("\tEnter Courses IDs\n");
	for (int i = 0; i < numberofcourses; i++)
	{
		DPRINTF("\t\tEnter Courses no.%d: ",i+1);
		scanf("%u", &NewStudent.courses[i]);
	}
	return &NewStudent;
}
void ShowStudentInfo(ElementType* ptrStudentStruct)
{
	printf("\n\tRoll number: %u\n", ptrStudentStruct->rollnumber);
	printf("\tFirst name: %s\n", ptrStudentStruct->firstname);
	printf("\tSecond name: %s\n", ptrStudentStruct->secondname);
	printf("\tGPA: %0.2f\n", ptrStudentStruct->GPA);
	printf("\tCourses: \n");
	for (int i = 0; i < numberofcourses; i++)
	{
		printf("\t%u ",ptrStudentStruct->courses[i]);
	}
	printf("\n");
}
