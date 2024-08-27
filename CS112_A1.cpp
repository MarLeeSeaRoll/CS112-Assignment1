#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <iomanip>

using namespace std;
// Maximum number of students that can be stored
const int maxStudents = 100;
// Sturcture to store student information
struct Student
{
    string studentID;
    double courseworkScore;
    double finalExamScore;
};
// Function prototypes
// Skip the headline of the file
void discard_line(ifstream &in);
// Read and store student data from file
void readDataFromFile(Student students[], string filename, int &count);
// Display main menu and process user input
void displayMenuAndInputProcess(Student students[], int count, string id);
// Calculate students grades base on total mark
string determineGrade(double totalScore);
// Display all student data in a formatted table
void printStudentData(Student students[], int size);
// Look up a student ID, update marks based user's choice and display the modified all student data
void lookUpStudentIDandUpdateMarks(string &id, Student students[], int count, char choice);
// Validate input marks, used in updateCourseWork and updateFinalExamWork
void markValidation(double &Mark);
// Update student's coursework mark
void updateCourseWork(double &newCourseMark);
// Update student's final exam mark
void updateFinalExamMark(double &newFinalExamMark);
// Prompt student which mark they want to update
void updateMarkChoice(string &id, Student students[], int count);
// Print the detail information of the student who get highest mark
void highestMarksDetails(Student students[], int count);
// Calculate and display the average student mark
void calculateAverageStudentMark(Student students[], int count);
// Calculate and display the pass rate in percentage
void calculatePassRate(Student students[], int count);

int main()
{
    // Array to store all student data
    Student students[maxStudents];
    // Variable to store student ID input by the user
    string id;
    // Count of students read from the file
    int studentCount = 0;
    // Read data from file and populate the student array
    readDataFromFile(students, "studentData.txt", studentCount);
    // Display the menu and process user input
    displayMenuAndInputProcess(students, studentCount, id);

    return 0;
}

// Function to display the main menu
void displayMenu()
{
    cout << "\nMenu Options:\n"
         << "1. Display all students data.\n"
         << "2. Update a student's marks.\n"
         << "3. The average marks of this course.\n"
         << "4. The pass rate of this course.\n"
         << "5. Display highest mark details\n"
         << "6. Exit this program\n"
         << "Please enter your choice(1-6)" << endl;
}

// Manages the menu display and handles the user input for menu options
void displayMenuAndInputProcess(Student students[], int count, string id)
{
    // Limitation of menu options
    const int OptionUpperLimit = 6;
    const int OptionLowerLimit = 1;

    // Constant for each menu option
    const int DisplayStudentDetails = 1;
    const int UpdateMark = 2;
    const int CalCulateAverageMark = 3;
    const int CalculatePassRate = 4;
    const int HighestMarkDetails = 5;
    const int ExitProgram = 6;

    int choice;
    do
    {
        displayMenu(); // Display option menu
        cin >> choice; // Options input
        // Input validation for options
        while (cin.fail() || (choice > OptionUpperLimit || choice < OptionLowerLimit))
        {
            cin.clear();
            string dummy;
            getline(cin, dummy);
            cout << "Invalid input, please try again" << endl;
            cin >> choice;
        }

        // Execute different actions based on the user's choice
        switch (choice)
        {
        case DisplayStudentDetails:
            printStudentData(students, count); // Display all student data
            break;
        case UpdateMark:
            updateMarkChoice(id, students, count); // Update marks
            break;
        case CalCulateAverageMark:
            calculateAverageStudentMark(students, count); // Calculate and print average total mark
            break;
        case CalculatePassRate:
            calculatePassRate(students, count); // Calculate and print pass rate
            break;
        case HighestMarkDetails: // Display detail information of highest mark student
            highestMarksDetails(students, count);
            break;
        case 6:
            cout << "Exiting Program." << endl;
        }
    } while (choice != 6);
}
// Function to discard headline of file
void discard_line(ifstream &in)
{
    char c;

    do
        in.get(c);
    while (c != '\n');
}
// Function to read student data from file and populate the students array
void readDataFromFile(Student students[], string filename, int &count)
{
    ifstream in_file(filename.c_str());
    // Check if file opening failed
    if (!in_file)
    {
        cout << "\nError! File failed to load";
        exit(1);
    }

    discard_line(in_file); // Discard headline
    // Read student data from the file until the end of file or maxStudents is reached
    while (in_file >> students[count].studentID >> students[count].courseworkScore >> students[count].finalExamScore)
    {
        count++;
        if (count >= maxStudents)
            break;
    }

    in_file.close();
}
// Function to determine student grade based on total mark
string determineGrade(double totalScore)
{
    // Grade determination logic
    if (totalScore >= 85)
        return "A+";
    else if (totalScore >= 78)
        return "A";
    else if (totalScore >= 71)
        return "B+";
    else if (totalScore >= 64)
        return "B";
    else if (totalScore >= 57)
        return "C+";
    else if (totalScore >= 50)
        return "C";
    else if (totalScore >= 40)
        return "D";
    else
        return "E";
}
// Function to display all student information
void printStudentData(Student students[], int count)
{
    cout << "The file that you chose to open is displayed below.\n";
    cout << "Student Data:\n";
    cout << "---------------------------------------------------\n";
    cout << "Student ID\tCoursework\tFinal Exam\tGrade\n";
    cout << "---------------------------------------------------\n";

    for (int i = 0; i < count; ++i)
    {
        double totalScore = students[i].courseworkScore + students[i].finalExamScore;
        string grade = determineGrade(totalScore);
        cout << students[i].studentID << "\t\t" << students[i].courseworkScore << "\t\t" << students[i].finalExamScore << "\t\t" << grade << endl;
    }
    cout << "\n\n";
}
// Function to look up a student ID
// Update marks based on user's choice and display the modified all student data
// Nested in markUpdateChoice
void lookUpStudentIDandUpdateMarks(string &id, Student students[], int count, char choice)
{
    cout << "Please provide the student ID" << endl;
    cin >> id;

    bool found = false;

    for (int i = 0; i < count; ++i)
    {
        if (students[i].studentID == id)
        {
            found = true;
            if (choice == 'e' || choice == 'E')
            {
                updateCourseWork(students[i].courseworkScore);
            }
            else if (choice == 'f' || choice == 'F')
            {
                updateFinalExamMark(students[i].finalExamScore);
            }
            else if (choice == 'b' || choice == 'B')
            {
                updateCourseWork(students[i].courseworkScore);
                updateFinalExamMark(students[i].finalExamScore);
            }
            printStudentData(students, count);
            return;
        }
    }

    if (!found)
    {
        char retryChoice;
        cout << "Student ID not found, Please enter 'Y' if you want to try again or any keys to return to previous menu:" << endl;
        cin >> retryChoice;
        if (retryChoice == 'y' || retryChoice == 'Y')
        {
            lookUpStudentIDandUpdateMarks(id, students, count, choice);
        }
        else
        {
            cout << "Returning to previous menu." << endl;
            return;
        }
    }
}
// Function to validate input of marks
void markValidation(double &Mark)
{
    const double upperLimit = 50.0;
    const double lowerLimit = 0.0;
    while (cin.fail() || Mark < lowerLimit || Mark > upperLimit)
    {
        cin.clear();
        string dummy;
        getline(cin, dummy);
        cout << "Invalid input, please enter correct mark;" << endl;
        cin >> Mark;
    }
}
// Function to update coursework mark
// Nested in lookUpStudentIDandUpdateMarks
void updateCourseWork(double &newCourseMark)
{
    cout << "Please enter new course work mark (Between 0-50):" << endl;
    cin >> newCourseMark;
    markValidation(newCourseMark); // Get and validate new coursework mark
}
// Function to update final exam marks
// Nested in lookUpStudentIDandUpdateMarks
void updateFinalExamMark(double &newFinalExamMark)
{
    cout << "Please enter new final exam mark (Between 0-50):" << endl;
    cin >> newFinalExamMark;
    markValidation(newFinalExamMark); // Get and validate new final exam mark
}
// Function to calculate and display average marks
void calculateAverageStudentMark(Student students[], int count)
{
    double totalMark = 0;
    double totalCourseWork = 0;
    double totalFinalExamMark = 0;
    for (int i = 0; i < count; i++)
    {
        totalCourseWork += students[i].courseworkScore;
        totalFinalExamMark += students[i].finalExamScore;
        totalMark += students[i].courseworkScore + students[i].finalExamScore;
    }
    cout << "\nThe average course work mark is " << fixed << setprecision(2) << totalCourseWork / count << endl;
    cout << "The average total final mark is " << fixed << setprecision(2) << totalFinalExamMark / count << endl;
    cout << "The average total mark is " << fixed << setprecision(2) << totalMark / count << endl;
}
// Function to calculate and display pass rate
void calculatePassRate(Student students[], int count)
{
    double passCount = 0;
    double totalScore = 0;
    double convertToPercentage = 100;
    for (int i = 0; i < count; i++)
    {
        totalScore = students[i].courseworkScore + students[i].finalExamScore;
        string grade = determineGrade(totalScore);
        if (grade != "D" && grade != "E")
        {
            passCount++;
        }
    }
    cout << "The pass rate of this course is: " << fixed << setprecision(2) << passCount / count * convertToPercentage << "%" << endl;
}
// Function tofind and  display highest marks details
void highestMarksDetails(Student students[], int count)
{
    double HighestTotalMark = students[0].courseworkScore + students[0].finalExamScore;
    int highestMarkIndex = 0;
    double totalMark = 0;
    for (int i = 0; i < count; i++)
    {
        totalMark = students[i].courseworkScore + students[i].finalExamScore;
        if (totalMark > HighestTotalMark)
        {
            HighestTotalMark = totalMark;
            highestMarkIndex = i;
        }
    }
    cout << "\nHighest Mark Student Details:\n";
    cout << "Student ID: " << students[highestMarkIndex].studentID << "\n";
    cout << "Coursework Score: " << students[highestMarkIndex].courseworkScore << "\n";
    cout << "Final Exam Score: " << students[highestMarkIndex].finalExamScore << "\n";
    cout << "Total Score: " << HighestTotalMark << "\n";
    cout << "Grade: " << determineGrade(HighestTotalMark) << "\n";
}
// Function to process user's choice for updating marks
void updateMarkChoice(string &id, Student students[], int count)
{
    char choice;
    cout << "Enter 'E' to update course work\nEnter 'F'to update final exam mark\nEnter 'B' to update both\nAny other key to return to previous menu: " << endl;
    cin >> choice;

    while (choice == 'e' || choice == 'E' || choice == 'F' || choice == 'f' || choice == 'b' || choice == 'B')
    {
        lookUpStudentIDandUpdateMarks(id, students, count, choice);
        cout << "Do you want to update another student?\nEnter 'E' to update course work\nEnter 'F'to update final exam mark\nEnter 'B' to update both\nAny other key to return previous menu." << endl;
        cin >> choice;
    }
}
