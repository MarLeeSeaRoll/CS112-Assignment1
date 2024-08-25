#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <iomanip>

using namespace std;

const int maxStudents = 100;

struct Student
{
    string studentID;
    double courseworkScore;
    double finalExamScore;
};

void discard_line(ifstream &in);
void readDataFromFile(Student students[], string filename, int &count);
void welcomeScreen(char choice);
void mainMenu(char choice);
string determineGrade(double totalScore);
void printStudentData(Student students[], int size);
void lookUpStudentID(string &id, Student students[], int count, char choice);
void markValidation(double &Mark);
void updateCourseWork(double &newCourseMark);
void updateFinalExamMark(double &newFinalExamMark);
void optionSystem(string &id, Student students[], int studentNum, char choice);
void highestMarksDetails(Student students[], int count);
double calculateAverageStudentMark(Student students[], int count);
double calculatePassRate(Student students[], int count);

int main()
{
    Student students[maxStudents];
    string id;
    char choice;
    int studentNum = 0;
    int index = 0;
    double newCourseMark;
    double newFinalExamMark;
    welcomeScreen(choice);
    optionSystem(id, students, studentNum, choice);
    readDataFromFile(students, "studentData.txt", studentNum);
    printStudentData(students, studentNum);

    cout << "Exiting Program." << endl;

    return 0;
}
void welcomeScreen(char choice)
{
    cout << "Welcome to Student Grade System\n"
         << "Enter S to star or any other key to quit:" << endl;
    cin >> choice;
}
void mainMenu(char choice)
{
    cout << "------------------Menu------------------\n"
         << "1. Update student marks"
         << "2. Print student detail with grade\n"
         << "3. Print average marks\n"
         << "4. Print the pass rate of this course\n"
         << "5. Print the highest scores full details\n"
         << "Press any other key to exit the program."
         << endl;
    cin >> choice;
}
void discard_line(ifstream &in)
{
    char c;

    do
        in.get(c);
    while (c != '\n');
}

void readDataFromFile(Student students[], string filename, int &count)
{
    ifstream in_file(filename.c_str());

    if (!in_file)
    {
        cout << "\nError! File failed to load";
        exit(1);
    }

    discard_line(in_file);

    while (in_file >> students[count].studentID >> students[count].courseworkScore >> students[count].finalExamScore)
    {
        count++;
        if (count >= maxStudents)
            break;
    }

    in_file.close();
}

string determineGrade(double totalScore)
{
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
    else
        return "D";
}

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
    highestMarksDetails(students, count);
    cout << "The average mark is " << fixed << setprecision(2) << calculateAverageStudentMark(students, count) << endl;
    cout << "The pass rate of this course is " << fixed << setprecision(2) << calculatePassRate(students, count) << endl;
}

void lookUpStudentID(string &id, Student students[], int count, char choice)
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
            lookUpStudentID(id, students, count, choice);
        }
        else
        {
            cout << "Returning to previous menu." << endl;
            return;
        }
    }
}

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

void updateCourseWork(double &newCourseMark)
{
    cout << "Please enter new course work mark (Between 0-50):" << endl;
    cin >> newCourseMark;
    markValidation(newCourseMark);
}

void updateFinalExamMark(double &newFinalExamMark)
{
    cout << "Please enter new final exam mark (Between 0-50):" << endl;
    cin >> newFinalExamMark;
    markValidation(newFinalExamMark);
}

double calculateAverageStudentMark(Student students[], int count)
{
    double totalMark = 0;
    for (int i = 0; i < count; i++)
    {
        totalMark += students[i].courseworkScore + students[i].finalExamScore;
    }
    return totalMark / count;
}

double calculatePassRate(Student students[], int count)
{
    double passCount = 0;
    double totalScore = 0;
    for (int i = 0; i < count; i++)
    {
        totalScore = students[i].courseworkScore + students[i].finalExamScore;
        string grade = determineGrade(totalScore);
        if (grade != "D")
        {
            passCount++;
        }
    }
    double passRate = passCount / count;
    return passRate;
}
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
    cout << "Highest Mark Student Details:\n";
    cout << "Student ID: " << students[highestMarkIndex].studentID << "\n";
    cout << "Coursework Score: " << students[highestMarkIndex].courseworkScore << "\n";
    cout << "Final Exam Score: " << students[highestMarkIndex].finalExamScore << "\n";
    cout << "Total Score: " << HighestTotalMark << "\n";
    cout << "Grade: " << determineGrade(HighestTotalMark) << "\n";
}
void optionSystem(string &id, Student students[], int studentNum, char choice)
{
    while (choice == 'S' || choice == 's')
    {
        mainMenu(choice);
        lookUpStudentID(id, students, studentNum, choice);
        cout << "Do you want to update another student? Enter 'E' to update course work, enter 'F'to update final exam mark or any other key to exit." << endl;
        cin >> choice;
    }
}
