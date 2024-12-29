# Students Management System

The Students Management System is a C-based application designed to manage student records efficiently using a queue data structure. It serves as a practical implementation of key concepts in C programming, data structures, and algorithms. The system provides functionality to add, search, edit, and delete student data while maintaining the records in memory and supporting file operations for data persistence.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
  - [Menu Options](#menu-options)
- [APIs and Functions](#apis-and-functions)
  - [Queue Functions](#queue-functions)
  - [Student Management Functions](#student-management-functions)
- [Dependencies](#dependencies)
- [Configuration](#configuration)
- [Examples](#examples)
  - [Adding a Student Manually](#adding-a-student-manually)
  - [Loading Students from a File](#loading-students-from-a-file)
  - [Saving Data to a File](#saving-data-to-a-file)
- [Troubleshooting](#troubleshooting)
- [Contributors](#contributors)
- [License](#license)

## Features

- Add student details manually or from a file.
- Search for students by roll number, first name, or course ID.
- Edit student information, including roll number, name, GPA, and enrolled courses.
- Delete individual or all student records.
- View all students in the queue.
- Save student data to a file for future use.
- Queue-based memory management ensures efficient handling of student records.

## Installation

1. Clone the repository or download the source code files.
2. Ensure you have a C compiler (e.g., GCC) installed on your system.
3. Compile the code using the provided files:

   ```bash
   gcc main.c Queue.c StudentSYS.c -o StudentsManagementSystem
   ```

4. Run the executable:

   ```bash
   ./StudentsManagementSystem
   ```

## Usage

The system provides an interactive menu for managing student records:

1. Run the compiled executable.
2. Choose from the menu options:
   - Add, search, edit, delete, view, or save student records.
3. Exit the application when done.

### Menu Options

1. Add Student Manually
2. Add Student From Text File
3. Search Student By Roll Number
4. Search Student By First Name
5. Search Student By Course ID
6. Delete Student By Roll Number
7. Edit Student By Roll Number
8. View All Students
9. Delete All Students
10. Save In Text File
11. Exit

## APIs and Functions

### Queue Functions

- `Queue_init`: Initializes the queue with a specified size.
- `Queue_enqueue`: Adds a student record to the queue.
- `Queue_dequeue`: Removes a student record from the queue (not used in this project).
- `Queue_delete_item`: Deletes a specific student record.
- `Queue_delete_all_items`: Clears the entire queue.
- `Queue_print`: Displays all student records.
- `Queue_find`: Searches for a student based on a specified criterion.

### Student Management Functions

- `add_student_manually`: Adds a student through user input.
- `add_students_from_file`: Reads student records from a text file and adds them to the queue.
- `find_student`: Searches for students by roll number, name, or course ID.
- `delete_student_by_roll`: Deletes a specific student by roll number.
- `edit_student_by_roll`: Edits the details of a student by roll number.
- `view_all_students`: Displays all students in the system.
- `delete_all_students`: Clears all student records from the system.
- `Save_in_text_file`: Saves all current student data to a text file.

## Dependencies

- **C Standard Library**:
  - `stdio.h`, `stdlib.h`, `stdint.h`, `string.h`
- **Files**:
  - `Queue.c`, `Queue.h`: Queue implementation.
  - `StudentSYS.c`: Student management logic.
  - `main.c`: Application entry point.

## Configuration

- **Queue Size**: Adjust the number of students by modifying `numberofstudent` in `StudentSYS.c`.
- **File Paths**: Ensure `students.txt` (input) and `students_update.txt` (output) exist and are accessible in the working directory.

## Examples

### Adding a Student Manually

1. Choose option 1 from the menu.
2. Enter the student's roll number, name, GPA, and courses.
3. The student is added to the system.

### Loading Students from a File

1. Create a `students.txt` file with the following format:

   ```
   RollNumber FirstName LastName GPA Course1 Course2 Course3 ...
   ```

2. Choose option 2 to load the students.

### Saving Data to a File

1. Choose option 10 from the menu.
2. The student data is saved to `students_update.txt`.

## Troubleshooting

- **File Not Found**: Ensure `students.txt` exists in the working directory for file-based input.
- **Queue Overflow**: Increase the size of `numberofstudent` if the queue exceeds its capacity.
- **Duplicate Roll Number**: Use unique roll numbers for each student.

## Contributors

- **Mohamed Hamdy**: Author and developer.

## License

This project is licensed under the [MIT License](LICENSE). You are free to use, modify, and distribute it as per the license terms.
