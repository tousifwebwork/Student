#include <iostream>
#include <fstream>
#include <vector>
#include "json.hpp"  // Include the JSON library

using namespace std;
using json = nlohmann::json;

struct Student {
    int rollNo;
    string name;
    int marks;
    string grade;
};

// Function to add a student
void addStudent() {
    Student student;
    cout << "Enter Roll No: ";
    cin >> student.rollNo;

    // Consume the newline character left by 'cin'
    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, student.name);  // Read the name into a string

    cout << "Enter Marks: ";
    cin >> student.marks;

    // Determine grade based on marks
    if (student.marks >= 90) student.grade = "A";
    else if (student.marks >= 75) student.grade = "B";
    else if (student.marks >= 50) student.grade = "C";
    else student.grade = "F";

    // Read the current student data from file
    vector<Student> students;
    ifstream inputFile("students.json");
    if (inputFile) {
        json j;
        inputFile >> j;
        for (auto& el : j) {
            Student s;
            s.rollNo = el["rollNo"];
            s.name = el["name"];
            s.marks = el["marks"];
            s.grade = el["grade"];
            students.push_back(s);
        }
    }

    // Add the new student to the list
    students.push_back(student);

    // Write updated list back to the JSON file
    json j;
    for (auto& s : students) {
        j.push_back({
            {"rollNo", s.rollNo},
            {"name", s.name},
            {"marks", s.marks},
            {"grade", s.grade}
        });
    }
    
    ofstream outputFile("students.json");
    outputFile << j.dump(4);  // Pretty print with indentation
    outputFile.close();

    cout << "Student added successfully!\n";
}

// Function to display all students
void displayStudents() {
    ifstream inputFile("students.json");
    if (inputFile) {
        json j;
        inputFile >> j;

        cout << "Student Records:\n";
        for (auto& student : j) {
            cout << "Roll No: " << student["rollNo"] << "\n";
            cout << "Name: " << student["name"] << "\n";
            cout << "Marks: " << student["marks"] << "\n";
            cout << "Grade: " << student["grade"] << "\n";
            cout << "---------------------\n";
        }
    } else {
        cout << "No student records found!\n";
    }
}

// Function to search for a student by Roll No
void searchStudent() {
    int rollNo;
    cout << "Enter Roll No to search: ";
    cin >> rollNo;

    ifstream inputFile("students.json");
    bool found = false;
    if (inputFile) {
        json j;
        inputFile >> j;

        for (auto& student : j) {
            if (student["rollNo"] == rollNo) {
                cout << "Student Found!\n";
                cout << "Roll No: " << student["rollNo"] << "\n";
                cout << "Name: " << student["name"] << "\n";
                cout << "Marks: " << student["marks"] << "\n";
                cout << "Grade: " << student["grade"] << "\n";
                found = true;
                break;
            }
        }
    }

    if (!found) {
        cout << "Student with Roll No " << rollNo << " not found.\n";
    }
}

// Main menu function
void menu() {
    int choice;
    do {
        // Display the menu options
        cout << "\nMenu:\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student by Roll No\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Consume the newline character after choice
        cin.ignore();

        switch (choice) {
            case 1:
                addStudent();  // Add a student
                break;
            case 2:
                displayStudents();  // Display all students
                break;
            case 3:
                searchStudent();  // Search for a student by Roll No
                break;
            case 4:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);  // Continue until the user chooses to exit
}

int main() {
    menu();
    return 0;
}
