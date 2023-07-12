# Assignment Management Software System

This is a project developed in C language for managing student assignments and submissions. The system allows students to form groups, each containing 2 students, and the teacher can assign different assignments to different groups. The teacher can evaluate the assignments offline and conduct viva for each group. The system maintains two databases: one for student records and another for assignment records.

## Student Database

The student database contains the following fields for each student record:
- Student ID
- Name
- Group Partner
- Group ID
- Assignment Name/ID
- Deadline
- Status of Assignment (Submitted/Not Submitted/Evaluated)
- Offline Evaluation Marks
- Viva Marks

## Assignment Database

The assignment database contains the following fields for each assignment record:
- Assignment ID
- Topic Name
- Status (Declared/Due Date Over/Evaluated)

Each assignment record can have a separate database inside, which contains the following fields for each record:
- Student Group ID
- Status (Declared/Submitted/Not Submitted/Evaluated)
- Marks Given

## Operations

The following operations are defined in the system:

1. Insert a student record: This operation allows the insertion of a new student record into the student database. After insertion, appropriate changes/insertions are made in the assignment database as well.

2. Insert assignment record: This operation allows the insertion of a new assignment record into the assignment database. The insertion function can take a list of students and allocate the assignment to multiple student groups, resulting in insertions in the student database as well.

3. Change status of assignment and student database: This operation allows changing the status of the assignment and student databases based on different events, such as a student group submitting the assignment or an assignment being evaluated for a specific student group. Once an assignment is evaluated for all student groups, the status of the assignment itself changes to "evaluated".

4. Print details of declared but not evaluated assignments: This operation prints the details of assignments that have been declared but not yet evaluated.

5. Print details of student groups who have not submitted assignments: This operation prints the details of student groups who have not submitted assignments even if the due date is over.

6. Print details of student groups with pending evaluation: This operation prints the details of student groups for whom the assignment is yet to be evaluated, even though they have been submitted. If a viva is remaining to be taken, it is explicitly mentioned.

7. Print details of student groups for a given assignment ID: This operation prints the details of student groups for a given assignment ID in decreasing order of the marks they have received in the assignment.

8. Print student groups receiving top marks in each assignment: This operation prints the student groups receiving top marks in each assignment given.

9. Range search: This operation allows searching and printing the details of assignments with assignment IDs between assignment-id-1 and assignment-id-2.

## Usage

To use this system, you can create a menu-driven program where students and the teacher can log in (password not mandatory) and perform all the above operations. The program should provide options for each operation and guide the user through the necessary steps to complete the desired task.

Please note that creating a menu-driven program is not compulsory, but extra credits may be given for implementing it.

## Conclusion

The Assignment Management Software System is designed to simplify the process of managing student assignments and submissions. It provides a user-friendly interface for students and teachers to perform various operations related to assignments and evaluations.
