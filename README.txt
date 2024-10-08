Student Academic record Management System

Introduction

This C++ program is designed to manage student academic record for a course. It allows students to view and update student academic performance data.

Features

-Display student ID, coursework mark and final exam mark
-Update student marks based on student ID (coursework and/or final exam)
-Calculate and display average marks
-Calculate and display pass rate
-Display details of student with highest mark

Functionality

    Read data from file and store
    -This program reads data from file "studentData.txt" and stores in a 'Student' struct, which includes student ID, coursework score and final exam score
    -The first line of the file(headline) will be discarded
    -Automatically if the data file is not found

    Grades calculation
    -This program will not use a array to store letter grades.
    -Each student's letter grade is determined besed on total mark (course + final exam)
    -Grade conformation logic based on USP grading system (USP Hankbook 2024: https://www.usp.ac.fj/handbookandcalendar2024/)

    Menu Options
    Including six options
    1. Display all students data: Displays a formatted table of all student academic record
    2. Update a student's marks: Allows updating coursework, final exam, or both marks for a specific student
    3. Average marks: Calculates and displays average coursework, final exam, and total marks
    4. Pass rate: Calculates and displays the percentage of students who passed (grade C or above)
    5. Highest mark details: Displays information about the student with the highest total score
    6. Exiting from program

    Input validation
    -This program includes mark input validation to make sure the mark input is between 0-50
    -It also includes choice input validation to make sure the choice input is bwtween 1-6

    Mark update
    -This program allows user to update coursework mark and final exam mark individually or both of them

    Overall statistic
    -This program will calculate the average mark of coursework mark, final exam mark and overall mark

    Highest mark details
    -This program will find and display the information of student with highest score

Important notes to getting start
-A stduent data file is required, the default file name is "studentData.txt", you can change it by modifying the parameter inside the readDataFromFile function that is called in the main function
-Ensure that the data in your file is arranged as: student ID, coursework mark, final exam mark
-The maximum number of student that can be handled is 100, it can be changed by modifying the constant in the nith line of the code
-If the data file is not found or error exist, the program will stop

How to run
-This program requires a C++ compiler or IDE, you can compile this program in DevC++
