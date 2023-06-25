/*
█░█ ▄▀█ █▀ █░█ ▀█▀ ▄▀█ █▄▄ █░░ █▀▀   █▀▀ █▀█ █░█ █▀█ █▀ █▀▀   ▄▀█ █▄░█ █▀▄   █▀█ █▀█ █▀▀ █▀█ █▀▀ █▀█ █▀
█▀█ █▀█ ▄█ █▀█ ░█░ █▀█ █▄█ █▄▄ ██▄   █▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄   █▀█ █░▀█ █▄▀   █▀▀ █▀▄ ██▄ █▀▄ ██▄ ▀▀█ ▄█*/

//TITLE:        Hash Table Course & Prerequisite Program
//AUTHOR:       Jaden B. Knutson

/*DESCRIPTION:  This C++ program is an Advising Assistance tool designed to aid 
                academic advisors in the Computer Science department at ABCU.
 
    THIS PROGRAM:
    -Allows efficient access to course information from a given data file 
    -Outputs usedul information such as course prerequisites to help guide students in their academic planning. 

    -Starts with a menu that offers five main options: 
        =============================
        =============================
        1. Load Data Structure. - LOADS DATA INTO HASH TABLE FROM FILE
        2. Print Course List.   - PRINT LIST OF COURSE CODES, TITLES, AND PREREQUISITES
        3. Print Course.        - INPUT COURSE CODE FROM USER TO OUTPUT COURSE INFORMATION
        4. Enter File Name.     - ALLOWS USER TO ENTER A FILE NAME TO THEN BE LOADED
        9. Exit
        =============================
        What would you like to do?
    
            -On choosing 1."Load Data Structure" - 
                    the program reads in course data from a
                    specified CSV file and organizes it into a data structure. 
    
            -Once data is loaded, users can 2."Print Course List" - 
                    Print alphanumerically sorted list of all courses

            -They can choose 3."Print Course" -  
                    Print detailed information about a specific course, including its prerequisites. 

            -They can also choose 4."Enter File Name" -
                    Changes the directory for the file that will be loaded into the data structure.
            
             L-astly 9."Exit" - ends the program. 
 */
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <iostream>         // io stream library    - input/output functions
#include <fstream>          // fstream library      - file handling functions
#include <sstream>          // sstream library      - string stream functions
#include <unordered_map>    // unordered_map library - used for hash tables
#include <vector>           // vector library       - dynamic array functions
#include <algorithm>        // algorithm library    - various algorithms (sorting)
#include <cctype>           // cctype library       - character handling functions
using namespace std;
//-------------------------------------------------------------------------------------------------
// COURSE SRUCT - store details of each course.
struct Course {
    string code; // Stores course code.
    string title; // Stores course title.
    vector<string> prerequisites; // Stores prerequisites for course.
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------










//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
█░░█ █▀▀█ █▀▀ █░░█ ▀▀█▀▀ █▀▀█ █▀▀▄ █░░ █▀▀
█▀▀█ █▄▄█ ▀▀█ █▀▀█ ░░█░░ █▄▄█ █▀▀▄ █░░ █▀▀
▀░░▀ ▀░░▀ ▀▀▀ ▀░░▀ ░░▀░░ ▀░░▀ ▀▀▀░ ▀▀▀ ▀▀▀*/
// HASHTABLE CLASS - manage course data, handle user interaction with the system/menu.
class HashTable {

     /* 
    █▀█ █▀█ █ █░█ ▄▀█ ▀█▀ █▀▀
    █▀▀ █▀▄ █ ▀▄▀ █▀█ ░█░ ██▄*/
private:
    // UNORDERED_MAP - stores course data with course code as key.
    unordered_map<string, Course> courseMap;

    //-------------------------------------------------------------------------------------------------
    // VECTOR - stores course code order.
    vector<string> courseOrder;

    //-------------------------------------------------------------------------------------------------
    // ERROR CHECKING BOOLEAN - tests if file has been loaded yet.
    bool dataLoaded = false;

    //-------------------------------------------------------------------------------------------------
    // UPPERCASE FUNCTION - Converts user input strings to uppercase.
    string toUpper(const string& str) {
        string upperString = str; // Initialize new string.
        transform(upperString.begin(), upperString.end(), upperString.begin(), ::toupper); // Convert string to uppercase.
        return upperString; // RETURN uppercase string.
    }

    //-------------------------------------------------------------------------------------------------
    // PARSE FUNCTION - splits course data from string.
    Course parseCourse(const string& line) {
        stringstream ss(line); // CREATE string stream.
        Course course; // COURSE OBJECT - object that stores parsed data.
        string prereq; // PREREQUISITE STRING - stores prerequisites.

        getline(ss, course.code, ','); // Parse course code from line.
        getline(ss, course.title, ','); // Parse course title from line.
        while (getline(ss, prereq, ',')) { // Parse prerequisites from line.
            if (!prereq.empty()) { // If prerequisite is not empty,
                course.prerequisites.push_back(prereq); // add it to prerequisites of course object.
            }
        }
        return course; // RETURN parsed Course object.
    }
//-------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
     /* 
     █▀█ █░█ █▄▄ █░░ █ █▀▀
     █▀▀ █▄█ █▄█ █▄▄ █ █▄▄*/
public:
    //-------------------------------------------------------------------------------------------------
    // MENU SELECTION #1 FUNCTION:   LOAD DATA FUNCTION - loads course data from file into hash table.
    bool loadData(const string& filename) {
        ifstream file(filename); // OPEN FILE from designated path or INPUT.

        if (!file) { // If file could not be opened,
            return false; // RETURN FALSE - the file could not be opened
        }

        string line; // LINE STRING - stores lines from file.
        while (getline(file, line)) { // While lines are left, read each line of file.
            Course course = parseCourse(line); // Parse course data from line.
            courseMap[toUpper(course.code)] = course; // Add course to hash table.
            courseOrder.push_back(toUpper(course.code)); // Add course code to course order vector.
        }
        dataLoaded = true; // DATA LOADED ERROR HANDLING - negates error handling when set to true.
        return true; // RETURN TRUE - the file was opened
    }
    //-------------------------------------------------------------------------------------------------
    // MENU SELECTION #2 FUNCTION:   OUTPUT COURSE LIST FUNCTION - prints a list of courses and prerequisites.
    void printCourseList() {
        if (!dataLoaded) { // If no data loaded by path or user INPUT:
            cout << "Error: No data has been loaded yet.\n\n"; // OUTPUT an error message and RETURN.
            return;
        }

        sort(courseOrder.begin(), courseOrder.end()); // SORT course order vector in alphanumeric order.

        for (const auto& code : courseOrder) { // For each course code in course order vector:
            const auto& course = courseMap[code]; // get course from hash table.
            cout << course.code << ", " << course.title << '\n'; // OUTPUT course code and title.
        }
        cout << "\n"; // Format line.
    }
    //-------------------------------------------------------------------------------------------------
    // MENU SELECTION #3 FUNCTION:   OUTPUT COURSE DETAILS FUNCTION - Inputs a course code from user, then prints details of the course.
    void printCourse(const string& input) {
        if (!dataLoaded) { // If data has not been loaded yet,
            cout << "Error: No data has been loaded yet.\n\n"; // OUTPUT error message and return.
            return;
        }

        //Allows user to use capitals or lowercase
        string inputToUpper = toUpper(input); // Convert string to uppercase.

        //COURSE NOT FOUND ERROR HANDLING
        if (courseMap.find(inputToUpper) == courseMap.end()) { // If course code is not found in hash table,
            cout << "Error: Course not found.\n\n"; // OUTPUT error message and return.
            return;
        }

        //OUTPUT COURSE CODE AND TITLE
        Course& course = courseMap[inputToUpper]; // Get course from hash table.
        cout << course.code << ", " << course.title << '\n'; // OUTPUT course code and title.
        cout << "Prerequisites: "; // OUTPUT prerequisites label.

        //OUTPUTS NONE IF NO PREREQUISITES PRESENT
        if (course.prerequisites.empty()) { // If course has no prerequisites,
            cout << "None"; // OUTPUT "None".
        }

        //OUTPUT PREREQUISITES
        else {
            for (auto& prereq : course.prerequisites) { // For each prerequisite of course,
                cout << prereq << ' '; // OUTPUT prerequisite.
            }
        }
        cout << "\n\n"; // Format lines.
    }
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------









/*
█▀▀ ▀▀█▀▀ █▀▀█ █▀▀█ ▀▀█▀▀ 　 █▀▄▀█ █▀▀█ ░▀░ █▀▀▄
▀▀█ ░░█░░ █▄▄█ █▄▄▀ ░░█░░ 　 █░▀░█ █▄▄█ ▀█▀ █░░█
▀▀▀ ░░▀░░ ▀░░▀ ▀░▀▀ ░░▀░░ 　 ▀░░░▀ ▀░░▀ ▀▀▀ ▀░░▀*/
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main() {
    HashTable hashTable; // HASHTABLE OBJECT - manage course data and user interactions.
    string userInput; // INPUT STRING - stores user INPUT.

    //-------------------------------------------------------------------------------------------------
    while (true) { // WHILE LOOP - continues while user INPUT is not the number 9.
    //-------------------------------------------------------------------------------------------------
        // OUTPUT USER MENU - User will choose from this list.
        cout << "=============================\n";
        cout << "=============================\n";
        cout << "1. Load Data Structure.\n";
        cout << "2. Print Course List.\n";
        cout << "3. Print Course.\n";
        cout << "4. Enter File Name.\n";
        cout << "9. Exit\n";
        cout << "=============================\n";
        cout << "What would you like to do? ";
        getline(cin, userInput); // Get user INPUT.

        //-------------------------------------------------------------------------------------------------
        //MENU CHOICE #1 - LOAD DATA FUNCTION - loads course data from file into hash table.
        if (userInput == "1") { // If user chose 1 - load data structure,
            if (!hashTable.loadData("ABCU_Advising_Program_Input.csv")) { // Try to load data into hash table.
                cout << "Error: File could not be loaded.\n"; // FAIL TO LOAD FILE - results in error message.
            }
            else {
                cout << "#1 Selected: Data loaded.\n\n"; // SUCCESSFUL FILE LOAD - results in success message. 
            }
        }

        //-------------------------------------------------------------------------------------------------
        //MENU CHOICE #2 - OUTPUT COURSE LIST FUNCTION - prints a list of courses and prerequisites.
        else if (userInput == "2") { // If user chose 2 - OUTPUT course list,
            cout << "#2 Selected: Print Course list.\n\n";
            system("pause");
            hashTable.printCourseList(); // OUTPUT course list.
        }

        //-------------------------------------------------------------------------------------------------
        //MENU CHOICE #3 - OUTPUT COURSE DETAILS FUNCTION - Inputs a course code from user, then prints details of the course.
        else if (userInput == "3") { // If user chose 3 - OUTPUT a courses information,
            cout << "#3 Selected: Print Course Information.\n\n";
            cout << "What course do you want to know about? "; // INPUT course code from user.
            getline(cin, userInput); // Get user INPUT.
            hashTable.printCourse(userInput); // OUTPUT course details.
        }

        //-------------------------------------------------------------------------------------------------
        //MENU CHOICE #4 - INPUT FILE FROM USER
        else if (userInput == "4") { // If user chose 4 - load a file from INPUT,
            cout << "#4 Selected, Enter the filename: "; // INPUT file name from user.
            getline(cin, userInput); // Get user INPUT.
            if (!hashTable.loadData(userInput)) { // Try to load data from user INPUT file into hash table.
                cout << "Error: File could not be loaded.\n\n"; // FAIL TO LOAD FILE - results in error message.
            }
            else {
                cout << "Data loaded.\n\n"; // SUCCESSFUL FILE LOAD - results in success message. 
            }
        }

        //-------------------------------------------------------------------------------------------------
        //MENU CHOICE #9 - EXIT PROGRAM
        else if (userInput == "9") { // If user chose 9 - END program,
            break; // break while loop ENDING the program.
        }

        //-------------------------------------------------------------------------------------------------
        //INVALID MENU CHOICE
        else { // If user choice is NOT valid:
            cout << userInput << " is not a valid option.\n\n"; // OUTPUT error message.
        }

//-------------------------------------------------------------------------------------------------
    }// END WHILE
//-------------------------------------------------------------------------------------------------
    cout << "Thank you for using the course planner\n"; // OUTPUT thank you message to user.
    return 0; // RETURN 0 - program ended successfully.
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/*
█▀▀ █▀▀▄ █▀▀▄ 　 █▀▄▀█ █▀▀█ ░▀░ █▀▀▄
█▀▀ █░░█ █░░█ 　 █░▀░█ █▄▄█ ▀█▀ █░░█
▀▀▀ ▀░░▀ ▀▀▀░ 　 ▀░░░▀ ▀░░▀ ▀▀▀ ▀░░▀*/