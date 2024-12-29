/*
 * StudentSYS.h
 *
 *  Created on: Jul 21, 2024
 *      Author: Mohamed Hamdy
 */

#ifndef STUDENTSYS_H_
#define STUDENTSYS_H_

#include "Queue.h"

#define ElementType SStudentInfo_t
#define namelength 20
#define numberofcourses 5
#define numberofstudent 50
#define DPRINTF(...) 	{fflush(stdout);\
		fflush(stdin);\
		printf(__VA_ARGS__);\
		fflush(stdout);\
		fflush(stdin);}


typedef struct {
	uint32_t rollnumber;
	char firstname[namelength];
	char secondname[namelength];
	float GPA;
	uint32_t courses[numberofcourses];
}SStudentInfo_t;
typedef union {
	uint32_t rollnumber;
	char firstname[namelength];
	uint32_t courseID;
}UFindContent_t;
typedef enum {
	RollNumber,
	FirstName,
	CourseID
}EFindChoice_t;


void StudentSYSIntialization();


void add_student_manually();
void add_students_from_file();
void find_student(EFindChoice_t searchtype);
void delete_student_by_roll();
void edit_student_by_roll();
void view_all_students();
void delete_all_students();
void Save_in_text_file();


ElementType* TakeStudentInfoFromConsole();
void ShowStudentInfo(ElementType* ptrStudentStruct);


#endif /* STUDENTSYS_H_ */
