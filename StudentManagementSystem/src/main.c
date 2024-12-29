/*
 ============================================================================
 Name        : main.c
 Author      : Mohamed Hamdy
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#include "StudentSYS.h"

int main(void)
{
	StudentSYSIntialization();

	uint32_t option;
	while(1)
	{
		DPRINTF("\n**********Choose on of the following Options**********");
		DPRINTF("\n\t1: Add Student Manually");
		DPRINTF("\n\t2: Add Student From Text File");
		DPRINTF("\n\t3: Search Student By Roll Number");
		DPRINTF("\n\t4: Search Student By First Name");
		DPRINTF("\n\t5: Search Student By Course ID");
		DPRINTF("\n\t6: Delete Student By Roll Number");
		DPRINTF("\n\t7: Edit Student By Roll Number");
		DPRINTF("\n\t8: View All Students");
		DPRINTF("\n\t9: Delete All Students");
		DPRINTF("\n\t10: Save In Text File");
		DPRINTF("\n\t11: Exit");

		DPRINTF("\nEnter Option Number: ");
		scanf("%u",&option);
		DPRINTF("******************************\n");
		switch (option)
		{
		case 1:add_student_manually();break;
		case 2:add_students_from_file();break;
		case 3:find_student(RollNumber);break;
		case 4:find_student(FirstName);break;
		case 5:find_student(CourseID);break;
		case 6:delete_student_by_roll();break;
		case 7:edit_student_by_roll();break;
		case 8:view_all_students();break;
		case 9:delete_all_students();break;
		case 10:Save_in_text_file();break;
		case 11:exit(1);break;
		default:DPRINTF("**********Wrong Option**********\n");break;
		}
	}
	return EXIT_SUCCESS;
}
