#include <iostream>
#include <string>
using namespace std;

// Base class for all other person classes
class Person {
    protected:
    string firstName;
    string lastName;
    int age;

    public:
    Person(string f = "John", string l = "Doe", int a = 21) {
        this->firstName = f;
        this->lastName = l;
        this->age = a;
    }
    void printPerson() {
        cout << "This person is " << firstName << " " << lastName << ". They are " << age << " Years old." << endl;
    }

};

// Inherits from person and adds methods for job and salary
class Faculty : public Person {
    protected:
    string job = "Unknown";
    int salary = 0;

    public: 
    Faculty(string f = "John", string l = "Doe", int a = 21) : Person(f, l, a) {}
    void assignJob(string j, int s) { job = j; salary = s; }
    void printFaculty() {
        printPerson();
        cout << firstName << " is Faculty for USF. Their job is " << job << " and their salary is $" << salary << "." << endl;
    }
};

// Inherits from faculty and adds info about what class the instructor is teaching
class Instructor : public Faculty {
    protected:
    string course;
    int numStudents = 0;

    public:
    Instructor(string f = "John", string l = "Doe", int a = 21, int s = 90000) : Faculty(f, l, a) {
        this->assignJob("Instructor", s);
        this->assignCourse("None");
    }
    void assignCourse(string c) { course = c; }
    void addStudents(int n) { numStudents += n; }
    void printInstructor() {
        printFaculty();
        cout << firstName << " teaches " << course << " to " << numStudents << " students." << endl;
    }
};

// Inherits from Instructor and adds info about research the professor takes part in
class Professor : public Instructor {
    protected:
    string research;

    public:
    Professor(string f = "John", string l = "Doe", int a = 21, int s = 160000) : Instructor(f, l, a) {
        this->assignJob("Professor", s);
        this->assignResearch("None");
    }
    void assignResearch(string r) { research = r; }
    void printProfessor() {
        printInstructor();
        cout << firstName << " does researh about " << research << "." << endl;
    }
};

// Inherits from Person and adds info about students' classes and gpa
class Student : public Person {
    protected:
    string gradeLevel;
    int currentClasses = 0;
    int classesTaken = 0;
    float gpa;

    public:
    Student(string f = "John", string l = "Doe", int a = 21, float gpa = 0) : Person(f, l, a) {
        this->gpa = gpa;
        this->gradeLevel = "High School";
    }
    void updateGradeLevel(string g) { gradeLevel = g; }
    void addClasses(int n) { currentClasses += n; }
    void completeClass() { currentClasses--; }
    void updateGpa(float gpa) { this->gpa = gpa; }
    void printStudent() {
        printPerson();
        cout << firstName << " is a " << gradeLevel << " student. They are enrolled in " << currentClasses << " classes and their GPA is " << gpa << "." << endl;
    }
};

// Inherits from Student and adds methods for students' major and minor
class UndergraduateStudent : public Student {
    protected:
    string major;
    string minor;
    bool doubleMajor;

    public: 
    UndergraduateStudent(string f = "John", string l = "Doe", int a = 21, float gpa = 0, string major = "Unknown") : Student(f, l, a, gpa) {
        this->updateGradeLevel("Undergraduate");
        this->major = major;
        this->minor = "None";
        this->doubleMajor = false;
    }
    void declareMinor(string m) { minor = m; }
    void declareMajor(string m) { major = m; }
    void declareDoubleMajor(string m) { minor = m; doubleMajor = true; }
    void printUndergraduate() {
        printStudent();
        if (doubleMajor) {
            cout << firstName << " is double majoring in " << major << " and " << minor << "." << endl;
        } else {
            cout << firstName << " is majoring in " << major << " and has declared a minor in " << minor << "." << endl;
        }
         
    } 
};

// Inherits from Student and adds methods about students' research and degree.
class GraduateStudent : public Student {
    protected:
    string research;
    string degree;

    public: 
    GraduateStudent(string f = "John", string l = "Doe", int a = 21, float gpa = 0, string degree = "Unknown") : Student(f, l, a, gpa) {
        this->updateGradeLevel("Graduate");
        this->degree = degree;
        this->research = "None";
    }
    void updateDegree(string d) { degree = d; }
    void assignResearch(string r) { research = r; }
    void printGraduate() {
        printStudent();
        cout << firstName << " is pursuing a " << degree << " and is doing research in " << research << "." << endl;
    } 
};

int main() {
    Person* person = new Person();
    Faculty* faculty = new Faculty("Jimmy", "F", 30);
    Instructor* instructor = new Instructor("Johnny", "I", 32, 100000);
    Professor* professor = new Professor("Peter", "P", 35);
    UndergraduateStudent* ugstudent = new UndergraduateStudent("Daniel", "U", 19, 3.8, "BioMed");
    GraduateStudent* gstudent = new GraduateStudent("Ryan", "G", 20, 3.5, "Masters Degree");

    person->printPerson();

    faculty->assignJob("Janitor", 60000);
    faculty->printFaculty();

    instructor->assignJob("Teacher Assistant", 750000);
    instructor->assignCourse("Data Structures");
    instructor->addStudents(37);
    instructor->printInstructor();

    professor->assignCourse("Circuits");
    professor->addStudents(247);
    professor->assignResearch("Medical Robotics");
    professor->printProfessor();

    ugstudent->addClasses(5);
    ugstudent->declareMajor("Finance");
    ugstudent->declareDoubleMajor("Chemistry");
    ugstudent->printUndergraduate();

    gstudent->assignResearch("Quantum Computing");
    gstudent->updateGpa(3.86);
    gstudent->printGraduate();
    
    return 0;
}