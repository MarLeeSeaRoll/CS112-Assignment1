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
void optionSystem(Student students[], int count, double marks, string id, int upperlimit, int lowerlimit);
string determineGrade(double totalScore);
void printStudentData(Student students[], int size);
void lookUpStudentID(string &id, Student students[], int count, char choice);
void markValidation(double &Mark);
void updateCourseWork(double &newCourseMark);
void updateFinalExamMark(double &newFinalExamMark);
void updateMarkChoice(string &id, Student students[], int studentNum);
void highestMarksDetails(Student students[], int count);
void calculateAverageStudentMark(Student students[], int count);
void calculatePassRate(Student students[], int count);

int main()
{
    Student students[maxStudents];
    string id;
    char choice;
    int studentNum = 0;
    double Mark;
    const int disPlayStudentDetails = 1;
    const int updateMark = 2;
    const int calCulateAverageMark = 3;
    const int calculatePassRate = 4;
    const int highestMarkDetails = 5;
    const int exitProgram = 6;
    const int optionUpperLimit = 6;
    const int optionLowerLimit = 1;

    readDataFromFile(students, "studentData.txt", studentNum);
    optionSystem(students, studentNum, Mark, id, optionUpperLimit, optionLowerLimit);

    return 0;
}
void displayMenu()
{
    cout << "\nMenu Options:\n"
         << "1. Display all students data.\n"
         << "2. Update a student's marks.\n"
         << "3. Calculate average mark.\n"
         << "4. Calculate pass rate.\n"
         << "5. Display highest mark details\n"
         << "6. Exit this program\n"
         << "Please enter your choice(1-6)" << endl;
}
void optionSystem(Student students[], int count, double marks, string id, int upperlimit, int lowerlimit)
{

    int input;
    do
    {
        displayMenu();
        cin >> input;
        while (cin.fail() ||(input > upperlimit || input < lowerlimit))
        {
            cin.clear();
            string dummy;
            getline(cin,dummy);
            cout << "Invalid input, please try again" << endl;
            cin >> input;
        }

        switch (input)
        {
        case 1:
            printStudentData(students, count);
            break;
        case 2:
            updateMarkChoice(id, students, count);
            break;
        case 3:
            calculateAverageStudentMark(students, count);
            break;
        case 4:
            calculatePassRate(students, count);
            break;
        case 5:
            highestMarksDetails(students, count);
            break;
        case 6:
            cout << "Exiting Program." << endl;
        }
    } while (input != 6);
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
            else if(choice=='b'||choice=='B')
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

void calculateAverageStudentMark(Student students[], int count)
{
    double totalMark = 0;
    for (int i = 0; i < count; i++)
    {
        totalMark += students[i].courseworkScore + students[i].finalExamScore;
    }
    cout <<"The average total mark is "<< fixed << setprecision(2) << totalMark / count << endl;
}

void calculatePassRate(Student students[], int count)
{
    double passCount = 0;
    double totalScore = 0;
    double convertToPercentage = 100;
    for (int i = 0; i < count; i++)
    {
        totalScore = students[i].courseworkScore + students[i].finalExamScore;
        string grade = determineGrade(totalScore);
        if (grade != "D")
        {
            passCount++;
        }
    }
    cout << "The pass rate of this course is: " << fixed << setprecision(2) << passCount / count*convertToPercentage<<"%"<< endl;
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
    cout << "\nHighest Mark Student Details:\n";
    cout << "Student ID: " << students[highestMarkIndex].studentID << "\n";
    cout << "Coursework Score: " << students[highestMarkIndex].courseworkScore << "\n";
    cout << "Final Exam Score: " << students[highestMarkIndex].finalExamScore << "\n";
    cout << "Total Score: " << HighestTotalMark << "\n";
    cout << "Grade: " << determineGrade(HighestTotalMark) << "\n";
}
void updateMarkChoice(string &id, Student students[], int studentNum)
{
    char choice;
    cout << "Enter 'E' to update course work\nEnter 'F'to update final exam mark\nEnter 'B' to update both\nAny other key to return to previous menu: " << endl;
    cin >> choice;

    while (choice == 'e' || choice == 'E' || choice == 'F' || choice == 'f'||choice=='b'||choice=='B')
    {
        lookUpStudentID(id, students, studentNum, choice);
        cout << "Do you want to update another student?\nEnter 'E' to update course work\nEnter 'F'to update final exam mark\nEnter'B' to update both\nAny other key to return previous menu." << endl;
        cin >> choice;
    }
}
