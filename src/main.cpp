#include <iostream>
#include <string>
using namespace std;

// =====================
// STRUCTURES
// =====================
struct Teacher {
    int id;
    string name;
    string subject;
    string availability;
    Teacher* next;
};

struct ClassRoom {
    string className;
    string subject;
    ClassRoom* next;
};

struct Schedule {
    string teacherName;
    string className;
    string subject;
    Schedule* next;
};

// =====================
// GLOBAL HEAD POINTERS
// =====================
Teacher* headTeacher = NULL;
ClassRoom* headClass = NULL;
Schedule* headSchedule = NULL;

// =====================
// TEACHER MANAGEMENT
// =====================
void addTeacher() {
    Teacher* newT = new Teacher;
    cout << "\nEnter Teacher ID: ";
    cin >> newT->id;
    cout << "Enter Name: ";
    cin >> newT->name;
    cout << "Enter Subject: ";
    cin >> newT->subject;
    cout << "Enter Availability: ";
    cin >> newT->availability;
    newT->next = NULL;

    if (headTeacher == NULL)
        headTeacher = newT;
    else {
        Teacher* temp = headTeacher;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newT;
    }
    cout << "? Teacher added successfully.\n";
}

void viewTeachers() {
    if (headTeacher == NULL) {
        cout << "? No teachers found.\n";
        return;
    }

    cout << "\n?? Teacher List:\n";
    Teacher* temp = headTeacher;
    while (temp != NULL) {
        cout << "ID: " << temp->id
             << " | Name: " << temp->name
             << " | Subject: " << temp->subject
             << " | Availability: " << temp->availability << endl;
        temp = temp->next;
    }
}

void updateTeacher() {
    int id;
    cout << "\nEnter Teacher ID to update: ";
    cin >> id;

    Teacher* temp = headTeacher;
    while (temp != NULL && temp->id != id)
        temp = temp->next;

    if (temp == NULL) {
        cout << "? Teacher not found.\n";
        return;
    }

    cout << "Enter new Name: ";
    cin >> temp->name;
    cout << "Enter new Subject: ";
    cin >> temp->subject;
    cout << "Enter new Availability: ";
    cin >> temp->availability;

    cout << "? Teacher updated successfully.\n";
}

// =====================
// CLASS MANAGEMENT
// =====================
void addClass() {
    ClassRoom* newC = new ClassRoom;
    cout << "\nEnter Class Name: ";
    cin >> newC->className;
    cout << "Enter Subject: ";
    cin >> newC->subject;

    newC->next = NULL;

    if (headClass == NULL) {
        headClass = newC;
    } else {
        ClassRoom* temp = headClass;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newC;
    }

    cout << "? Class added successfully.\n";
}

void viewClasses() {
    if (headClass == NULL) {
        cout << "? No classes found.\n";
        return;
    }

    cout << "\n?? Classes List:\n";
    ClassRoom* temp = headClass;
    while (temp != NULL) {
        cout << "Class: " << temp->className
             << " | Subject: " << temp->subject << endl;
        temp = temp->next;
    }
}

// =====================
// CONFLICT CHECKER
// =====================
bool checkConflict(string teacherName, string subject) {
    Schedule* temp = headSchedule;
    while (temp != NULL) {
        if (temp->teacherName == teacherName && temp->subject == subject)
            return true;
        temp = temp->next;
    }
    return false;
}

// =====================
// SCHEDULE GENERATOR
// =====================
void generateSchedule() {
    if (headTeacher == NULL || headClass == NULL) {
        cout << "? Need at least one teacher and one class.\n";
        return;
    }

    Teacher* tempTeacher = headTeacher;
    ClassRoom* tempClass = headClass;

    cout << "\n?? Generating Schedule...\n";

    while (tempClass != NULL) {
        if (checkConflict(tempTeacher->name, tempClass->subject)) {
            cout << "? Conflict: " << tempTeacher->name
                 << " already assigned for " << tempClass->subject << endl;
        } else {
            Schedule* newS = new Schedule;
            newS->teacherName = tempTeacher->name;
            newS->className = tempClass->className;
            newS->subject = tempClass->subject;
            newS->next = headSchedule;
            headSchedule = newS;  // insert at head

            cout << "? " << newS->teacherName << " assigned to "
                 << newS->className << " (" << newS->subject << ")\n";
        }

        // Move class pointer
        tempClass = tempClass->next;

        // Move teacher pointer (looping)
        tempTeacher = tempTeacher->next;
        if (tempTeacher == NULL)
            tempTeacher = headTeacher;
    }

    cout << "\n? Schedule generated successfully!\n";
}

// =====================
// VIEW TIMETABLE
// =====================
void viewTimetable() {
    if (headSchedule == NULL) {
        cout << "? Timetable empty.\n";
        return;
    }

    cout << "\n?? Timetable:\n";
    Schedule* temp = headSchedule;
    while (temp != NULL) {
        cout << "Teacher: " << temp->teacherName
             << " | Class: " << temp->className
             << " | Subject: " << temp->subject << endl;
        temp = temp->next;
    }
}

// =====================
// MENUS
// =====================
void teacherMenu() {
    int choice;
    do {
        cout << "\n===== Teacher Menu =====";
        cout << "\n1. Add Teacher";
        cout << "\n2. View Teachers";
        cout << "\n3. Update Teacher";
        cout << "\n0. Back";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addTeacher(); break;
            case 2: viewTeachers(); break;
            case 3: updateTeacher(); break;
        }
    } while (choice != 0);
}

void classMenu() {
    int choice;
    do {
        cout << "\n===== Class Menu =====";
        cout << "\n1. Add Class";
        cout << "\n2. View Classes";
        cout << "\n0. Back";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addClass(); break;
            case 2: viewClasses(); break;
        }
    } while (choice != 0);
}

void scheduleMenu() {
    int choice;
    do {
        cout << "\n===== Schedule Menu =====";
        cout << "\n1. Generate Schedule";
        cout << "\n2. View Timetable";
        cout << "\n0. Back";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: generateSchedule(); break;
            case 2: viewTimetable(); break;
        }
    } while (choice != 0);
}

// =====================
// MAIN MENU
// =====================
int main() {
    int choice;
    do {
        cout << "\n===============================";
        cout << "\n  SCHOOL TIMETABLE SYSTEM";
        cout << "\n===============================";
        cout << "\n1. Teacher Management";
        cout << "\n2. Class Management";
        cout << "\n3. Schedule Generator";
        cout << "\n4. View Timetable";
        cout << "\n0. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: teacherMenu(); break;
            case 2: classMenu(); break;
            case 3: scheduleMenu(); break;
            case 4: viewTimetable(); break;
            case 0: cout << "? Exiting...\n"; break;
            default: cout << "? Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
