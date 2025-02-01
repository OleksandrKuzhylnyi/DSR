#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

const int MAX_NAME_SIZE = 16;
const int MAX_SUBJECT_NAME_SIZE = 16;
const int MAX_STATE_NAME_SIZE = 10;
const int MAX_NUMBER_OF_STUDENTS = 30;

struct Name
{
    char first[MAX_NAME_SIZE];
    char middle[MAX_NAME_SIZE];
    char last[MAX_NAME_SIZE];
};

struct Subject
{
    char name[MAX_SUBJECT_NAME_SIZE];
    int grade;
};

struct Student
{
    char faculty_number[9];
    char EGN[11];
    Name name;
    char sex;
    int age;
    char state[MAX_STATE_NAME_SIZE];
    Subject subjects[5];
    float average_grade;
};

bool is_digit(char text[]);
bool is_digit_or_point(char text[]);
bool are_characters_valid(char text[]);
bool check_zero(int added_students);

int get_valid_integer(int lower_bound, int upper_bound);
float get_valid_float(float lower_bound, float upper_bound);
void get_grade(Student &student, int index);

void add_faculty_number(Student students[], int added_students);
void add_EGN(Student students[], int added_students);
void add_name(Student &student, int added_students, const char type[]);
void add_sex(Student &student, int added_students);
void add_age(Student &student, int added_students);
void add_state(Student &student, int added_students);
void add_subjects(Student &student, int added_students);

bool is_faculty_number_valid(Student students[], int &added_students, char faculty_number[]);
bool is_EGN_valid(Student students[], int &added_students, char EGN[]);
bool is_name_valid(char name[]);
bool are_subjects_valid(Student student);
bool is_student_valid(Student students[], int added_students);

void calculate_average_grade(Student &student);
void swap_students(Student &student_1, Student &student_2);

void add_students(Student students[], int &added_students);
int display_students(Student students[], int added_students);
int search_by_grade_in_BP(Student students[], int added_students);
int search_for_weak(Student students[], int added_students);
int sort_by_name(Student students[], int added_students);
int save_to_file(Student students[], int added_students);
int load_from_file(Student students[], int &added_students);
int search_by_state_and_sort_by_faculty_number(Student students[], int added_students);
int search_by_average_grade_and_sort_by_EGN(Student students[], int added_students);
int update_grades(Student students[], int added_students);
int update_state(Student students[], int added_students);

void info();

int main()
{
    Student students[MAX_NUMBER_OF_STUDENTS];
    int added_students = 0;
    int choice;

    load_from_file(students, added_students);

    while (true)
    {
        info();
        choice = get_valid_integer(1, 12);

        switch (choice)
        {
        case 1:
            add_students(students, added_students);
            break;
        case 2:
            display_students(students, added_students);
            break;
        case 3:
            search_by_grade_in_BP(students, added_students);
            break;
        case 4:
            search_for_weak(students, added_students);
            break;
        case 5:
            sort_by_name(students, added_students);
            break;
        case 6:
            save_to_file(students, added_students);
            break;
        case 7:
            load_from_file(students, added_students);
            break;
        case 8:
            search_by_state_and_sort_by_faculty_number(students, added_students);
            break;
        case 9:
            search_by_average_grade_and_sort_by_EGN(students, added_students);
            break;
        case 10:
            update_grades(students, added_students);
            break;
        case 11:
            update_state(students, added_students);
            break;
        case 12:
            save_to_file(students, added_students);
            exit(0);
        }
    }
    return 0;
}

bool is_digit(char text[])
{
    for (int i = 0; i < strlen(text); i++)
    {
        if (!isdigit(text[i]))
            return false;
    }
    return true;
}

bool is_digit_or_point(char text[])
{
    for (int i = 0; i < strlen(text); i++)
    {
        if (!isdigit(text[i]) && text[i] != '.')
            return false;
    }
    return true;
}

bool are_characters_valid(char text[])
{
    for (int i = 0; i < strlen(text); i++)
    {
        if (!isalpha(text[i]) && text[i] != ' ' && text[i] != '-')
            return false;
    }
    return true;
}

bool check_zero(int added_students)
{
    if (added_students == 0)
    {
        cout << "There are no students.\n";
        return true;
    }

    return false;
}

int get_valid_integer(int lower_bound, int upper_bound)
{
    char input[1000];
    int integer;

    while (true)
    {
        cin.getline(input, sizeof(input));

        if (strlen(input) == 0 || strlen(input) > 2 || !is_digit(input))
        {
            cout << "Invalid input. Try again\n";
            continue;
        }

        integer = atoi(input);

        if (integer < lower_bound || integer > upper_bound)
        {
            cout << "Invalid input. Try again\n";
            continue;
        }

        break;
    }

    return integer;
}

float get_valid_float(float lower_bound, float upper_bound)
{
    char input[1000];
    float number;

    while (true)
    {
        cin.getline(input, sizeof(input));

        if (strlen(input) == 0 || strlen(input) > 7 || !is_digit_or_point(input))
        {
            cout << "Invalid input. Try again\n";
            continue;
        }

        number = atof(input);

        if (number < lower_bound || number > upper_bound)
        {
            cout << "Invalid input. Try again\n";
            continue;
        }

        break;
    }

    return number;
}

void get_grade(Student &student, int index)
{
    char input[1000];

    while (true)
    {
        cout << "Enter grade (0, 2-6) in " << student.subjects[index].name << endl;
        cin.getline(input, sizeof(input));

        if (strlen(input) != 1 || (input[0] != '0' && input[0] != '2' && input[0] != '3' &&
            input[0] != '4' && input[0] != '5' && input[0] != '6'))
        {
            cout << "Invalid input.\n";
            continue;
        }

        student.subjects[index].grade = atoi(input);
        break;
    }
}

void add_faculty_number(Student students[], int added_students)
{
    char faculty_number[1000];

    while (true)
    {
        cout << "Enter faculty number of the student number " << added_students + 1 << endl;
        cin.getline(faculty_number, sizeof(faculty_number));

        if (strlen(faculty_number) != 8 || !is_digit(faculty_number))
        {
            cout << "Invalid input.\n";
            continue;
        }

        bool unique = true;

        for (int i = 0; i < added_students; i++)
        {
            if (strcmp(students[i].faculty_number, faculty_number) == 0)
            {
                unique = false;
                cout << "Student with this faculty number already exists.\n";
                break;
            }
        }

        if (!unique)
            continue;

        strcpy(students[added_students].faculty_number, faculty_number);
        break;
    }
}

void add_EGN(Student students[], int added_students)
{
    char EGN[1000];

    while (true)
    {
        cout << "Enter EGN of the student number " << added_students + 1 << endl;
        cin.getline(EGN, sizeof(EGN));

        if (strlen(EGN) != 10 || !is_digit(EGN))
        {
            cout << "Invalid input.\n";
            continue;
        }

        bool unique = true;

        for (int i = 0; i < added_students; i++)
        {
            if (strcmp(students[i].EGN, EGN) == 0)
            {
                unique = false;
                cout << "Student with this EGN already exists.\n";
                break;
            }
        }

        if (!unique)
            continue;

        strcpy(students[added_students].EGN, EGN);
        break;
    }
}

void add_name(Student &student, int added_students, const char type[])
{
    char tmp[1000];

    while (true)
    {
        cout << "Enter " << type << " name of the student number " << added_students + 1 << endl;
        cin.getline(tmp, sizeof(tmp));

        if (strlen(tmp) >= MAX_NAME_SIZE)
        {
            cout << "Name is too long.\n";
            continue;
        }

        if (!are_characters_valid(tmp))
        {
            cout << "Name contains invalid characters.\n";
            continue;
        }

        if (strcmp(type, "first") == 0)
            strcpy(student.name.first, tmp);
        else if (strcmp(type, "middle") == 0)
            strcpy(student.name.middle, tmp);
        else if (strcmp(type, "last") == 0)
            strcpy(student.name.last, tmp);
        else
            cout << "Wrong parameters.\n";

        break;
    }
}

void add_sex(Student &student, int added_students)
{
    int choice;

    cout << "Choose sex of the student number " << added_students + 1 << ":\n"
         << "1 for 'Male'\n"
         << "2 for 'Female'\n";
    choice = get_valid_integer(1, 2);

    if (choice == 1)
        student.sex = 'M';
    else
        student.sex = 'F';
}

void add_age(Student &student, int added_students)
{
    cout << "Enter age (10-99) of the student number " << added_students + 1 << '\n';
    student.age = get_valid_integer(10, 99);
}

void add_state(Student &student, int added_students)
{
    int choice;

    cout << "Choose state of the student number " << added_students + 1 << ":\n"
         << "1 for 'Active'\n"
         << "2 for 'On leave'\n"
         << "3 for 'Graduated'\n";
    choice = get_valid_integer(1, 3);

    if (choice == 1)
        strcpy(student.state, "Active");
    else if (choice == 2)
        strcpy(student.state, "On leave");
    else
        strcpy(student.state, "Graduated");
}

void add_subjects(Student &student, int added_students)
{
    char subject_name[1000];
    char input[1000];

    cout << "Enter subjects of the student number " << added_students + 1 << '\n' << "Subject 1 is BP.\n";
    strcpy(student.subjects[0].name, "BP");

    for (int i = 0; i < 5; i++)
    {
        while (true)
        {
            if (i == 0)
                break;

            cout << "Enter name of the subject number " << i + 1 << endl;
            cin.getline(subject_name, sizeof(subject_name));

            if (strlen(subject_name) >= MAX_SUBJECT_NAME_SIZE)
            {
                cout << "Subject name is too long.\n";
                continue;
            }

            strcpy(student.subjects[i].name, subject_name);

            break;
        }

        get_grade(student, i);
    }
}

bool is_faculty_number_valid(Student students[], int &added_students, char faculty_number[])
{
    if (strlen(faculty_number) != 8 || !is_digit(faculty_number))
        return false;

    for (int i = 0; i < added_students; i++)
    {
        if (strcmp(students[i].faculty_number, faculty_number) == 0)
            return false;
    }

    return true;
}

bool is_EGN_valid(Student students[], int &added_students, char EGN[])
{
    if (strlen(EGN) != 10 || !is_digit(EGN))
        return false;

    for (int i = 0; i < added_students; i++)
    {
        if (strcmp(students[i].EGN, EGN) == 0)
            return false;
    }

    return true;
}

bool is_name_valid(char name[])
{
    return (strlen(name) != 0 && strlen(name) < MAX_NAME_SIZE && are_characters_valid(name));
}

bool are_subjects_valid(Student student)
{
    for (int i = 0; i < 5; i++)
    {
        if (student.subjects[i].grade != 0 && (student.subjects[i].grade < 2 || student.subjects[i].grade > 6) ||
            strlen(student.subjects[i].name) == 0 || strlen(student.subjects[i].name) >= MAX_SUBJECT_NAME_SIZE)
            return false;
    }

    if (strcmp(student.subjects[0].name, "BP") != 0)
        return false;

    return true;
}

bool is_student_valid(Student students[], int added_students)
{
    return (is_faculty_number_valid(students, added_students, students[added_students].faculty_number) &&
            is_EGN_valid(students, added_students, students[added_students].EGN) &&
            is_name_valid(students[added_students].name.first) && 
            is_name_valid(students[added_students].name.middle) &&
            is_name_valid(students[added_students].name.last) && 
            (strcmp(students[added_students].state, "Active") == 0 ||
            strcmp(students[added_students].state, "On leave") == 0 ||
            strcmp(students[added_students].state, "Graduated") == 0) &&
            students[added_students].age > 10 && students[added_students].age < 99 &&
            (students[added_students].sex == 'M' || students[added_students].sex == 'F') &&
            are_subjects_valid(students[added_students]));
}

void calculate_average_grade(Student &student)
{
    int sum = 0;

    for (int i = 0; i < 5; i++)
    {
        sum += student.subjects[i].grade;
    }

    student.average_grade = sum / 5.0;
}

void swap_students(Student &student_1, Student &student_2)
{
    Student tmp;

    tmp = student_1;
    student_1 = student_2;
    student_2 = tmp;
}

void add_students(Student students[], int &added_students)
{
    int new_students;

    cout << "How many students do you want to add? (from 0 to " << (MAX_NUMBER_OF_STUDENTS - added_students) << ")\n";
    new_students = get_valid_integer(0, MAX_NUMBER_OF_STUDENTS - added_students);

    for (int i = 0; i < new_students; i++)
    {
        add_faculty_number(students, added_students);
        add_EGN(students, added_students);
        add_name(students[added_students], added_students, "first");
        add_name(students[added_students], added_students, "middle");
        add_name(students[added_students], added_students, "last");
        add_sex(students[added_students], added_students);
        add_age(students[added_students], added_students);
        add_state(students[added_students], added_students);
        add_subjects(students[added_students], added_students);
        calculate_average_grade(students[added_students]);
        added_students++;
    }
}

int display_students(Student students[], int added_students)
{
    if (check_zero(added_students))
        return 1;

    int table_width = 3 * MAX_NAME_SIZE + 5 * MAX_SUBJECT_NAME_SIZE + MAX_STATE_NAME_SIZE + 54;

    for (int i = 0; i < table_width; i++)
        cout << "-";

    cout << endl
         << "|" << setw(10) << "Faculty No"
         << "|" << setw(10) << left << "EGN"
         << "|" << setw(MAX_NAME_SIZE - 1) << left << "First name"
         << "|" << setw(MAX_NAME_SIZE - 1) << left << "Middle name"
         << "|" << setw(MAX_NAME_SIZE - 1) << left << "Last name"
         << "|" << setw(3) << left << "Sex"
         << "|" << setw(3) << left << "Age"
         << "|" << setw(MAX_STATE_NAME_SIZE - 1) << left << "State"
         << "|" << setw(MAX_SUBJECT_NAME_SIZE + 2) << left << "Grade 1"
         << "|" << setw(MAX_SUBJECT_NAME_SIZE + 2) << left << "Grade 2"
         << "|" << setw(MAX_SUBJECT_NAME_SIZE + 2) << left << "Grade 3"
         << "|" << setw(MAX_SUBJECT_NAME_SIZE + 2) << left << "Grade 4"
         << "|" << setw(MAX_SUBJECT_NAME_SIZE + 2) << left << "Grade 5"
         << "|" << setw(7) << left << "Average"
         << "|" << endl;

    for (int i = 0; i < added_students; i++)
    {
        cout << "|" << setw(10) << students[i].faculty_number << "|" << setw(10) << left << students[i].EGN << "|"
             << setw(MAX_NAME_SIZE - 1) << left << students[i].name.first << "|" << setw(MAX_NAME_SIZE - 1) << left
             << students[i].name.middle << "|" << setw(MAX_NAME_SIZE - 1) << left << students[i].name.last << "|"
             << setw(3) << left << (students[i].sex) << "|" << setw(3) << left << students[i].age << "|"
             << setw(MAX_STATE_NAME_SIZE - 1) << left << students[i].state << "|";
        for (int j = 0; j < 5; j++)
        {
            cout << setw(strlen(students[i].subjects[j].name)) << left << students[i].subjects[j].name << ": "
                 << students[i].subjects[j].grade << setw(MAX_SUBJECT_NAME_SIZE - strlen(students[i].subjects[j].name))
                 << right << "|";
        }
        cout << setw(7) << left << students[i].average_grade << "|" << endl;
    }

    for (int i = 0; i < table_width; i++)
        cout << "-";

    cout << endl;

    return 0;
}

int search_by_grade_in_BP(Student students[], int added_students)
{
    if (check_zero(added_students))
        return 1;

    Student right_students[MAX_NUMBER_OF_STUDENTS];
    int number_of_right_students = 0;
    int min, max;

    cout << "Enter minimal grade (integer from 0 to 6, inclusive).\n";
    min = get_valid_integer(0, 6);
    cout << "Enter maximal grade (integer from 0 to 6, inclusive).\n";
    max = get_valid_integer(0, 6);

    for (int i = 0; i < added_students; i++)
    {
        if (students[i].subjects[0].grade >= min && students[i].subjects[0].grade <= max)
        {
            right_students[number_of_right_students] = students[i];
            number_of_right_students++;
        }
    }
    if (number_of_right_students == 0)
        cout << "There are no students that have grades in the given interval.\n";
    else
        display_students(right_students, number_of_right_students);

    return 0;
}

int search_for_weak(Student students[], int added_students)
{
    if (check_zero(added_students))
        return 1;

    Student weak_students[MAX_NUMBER_OF_STUDENTS];
    int number_of_weak_students = 0;

    for (int i = 0; i < added_students; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (students[i].subjects[j].grade == 2)
            {
                weak_students[number_of_weak_students] = students[i];
                number_of_weak_students++;
                break;
            }
        }
    }

    if (number_of_weak_students == 0)
        cout << "There are no weak students.\n";
    else
        display_students(weak_students, number_of_weak_students);

    return 0;
}

int sort_by_name(Student students[], int added_students)
{
    if (check_zero(added_students))
        return 1;

    for (int i = 0; i < added_students - 1; i++)
    {
        for (int j = 0; j < added_students - i - 1; j++)
        {
            if (strcmp(students[j].name.first, students[j + 1].name.first) > 0)
                swap_students(students[j], students[j + 1]);
        }
    }

    display_students(students, added_students);

    return 0;
}

int save_to_file(Student students[], int added_students)
{
    if (check_zero(added_students))
        return 1;

    ofstream fp;

    fp.open("students.txt");

    if (fp.fail())
    {
        cout << endl << "Output file opening failed.\n";
        return 1;
    }

    for (int i = 0; i < added_students; i++)
    {
        fp << students[i].faculty_number << endl;
        fp << students[i].EGN << endl;
        fp << students[i].name.first << endl;
        fp << students[i].name.middle << endl;
        fp << students[i].name.last << endl;
        fp << students[i].state << endl;
        for (int j = 0; j < 5; j++)
        {
            fp << students[i].subjects[j].name << endl;
            fp << students[i].subjects[j].grade << endl;
        }
        fp << students[i].sex << endl;
        fp << students[i].age;
        if (i < added_students - 1)
            fp << endl;
    }

    fp.close();

    cout << added_students << " students are saved to file.\n";
    return 0;
}

int load_from_file(Student students[], int &added_students)
{
    int students_before_loading = added_students;

    ifstream fp;

    fp.open("students.txt");

    if (fp.fail())
    {
        cout << endl << "Input file opening failed.\n";
        return 1;
    }

    while ((!fp.eof()) && (added_students < MAX_NUMBER_OF_STUDENTS))
    {
        fp.getline(students[added_students].faculty_number, sizeof(students[added_students].faculty_number), '\n');
        fp.getline(students[added_students].EGN, sizeof(students[added_students].EGN), '\n');
        fp.getline(students[added_students].name.first, sizeof(students[added_students].name.first), '\n');
        fp.getline(students[added_students].name.middle, sizeof(students[added_students].name.middle), '\n');
        fp.getline(students[added_students].name.last, sizeof(students[added_students].name.last), '\n');
        fp.getline(students[added_students].state, sizeof(students[added_students].state), '\n');
        for (int i = 0; i < 5; i++)
        {
            fp.getline(students[added_students].subjects[i].name, sizeof(students[added_students].subjects[i].name),
                       '\n');
            fp >> students[added_students].subjects[i].grade;
            fp.ignore();
        }
        fp >> students[added_students].sex;
        fp >> students[added_students].age;
        fp.ignore();

        if (!is_student_valid(students, added_students))
        {
            cout << "Data in the file isn't valid.\n";
            return 1;
        }

        calculate_average_grade(students[added_students]);
        added_students++;

        if (added_students >= MAX_NUMBER_OF_STUDENTS)
        {
            cout << "The maximum of students in the group is reached. "
                 << "Next students from the file won't be loaded.\n";
            break;
        }
    }

    fp.close();

    if (added_students - students_before_loading != 1)
        cout << added_students - students_before_loading << " students are loaded from file.\n";
    else
        cout << "1 student is loaded from file.\n";

    return 0;
}

int search_by_state_and_sort_by_faculty_number(Student students[], int added_students)
{
    if (check_zero(added_students))
        return 1;

    Student right_students[MAX_NUMBER_OF_STUDENTS];
    int number_of_right_students = 0;
    char state[MAX_STATE_NAME_SIZE];
    int choice;

    cout << "Choose students of what state do you want to see:\n"
         << "1 for 'Active'\n"
         << "2 for 'On leave'\n"
         << "3 for 'Graduated'\n";
    ;
    choice = get_valid_integer(1, 3);

    if (choice == 1)
        strcpy(state, "Active");
    else if (choice == 2)
        strcpy(state, "On leave");
    else
        strcpy(state, "Graduated");

    for (int i = 0; i < added_students; i++)
    {
        if (strcmp(students[i].state, state) == 0)
        {
            right_students[number_of_right_students] = students[i];
            number_of_right_students++;
        }
    }

    for (int i = 0; i < number_of_right_students - 1; i++)
    {
        for (int j = 0; j < number_of_right_students - i - 1; j++)
        {
            if (strcmp(right_students[j].faculty_number, right_students[j + 1].faculty_number) > 0)
                swap_students(right_students[j], right_students[j + 1]);
        }
    }

    if (number_of_right_students == 0)
        cout << "There are no students of the given state.\n";
    else
        display_students(right_students, number_of_right_students);

    return 0;
}

int search_by_average_grade_and_sort_by_EGN(Student students[], int added_students)
{
    if (check_zero(added_students))
        return 1;

    Student right_students[30];
    int number_of_right_students = 0;
    float min, max;

    cout << "Enter minimal average grade (0-6, inclusive, up to 5 decimal places).\n";
    min = get_valid_float(0, 6);
    cout << "Enter maximal average grade (0-6, inclusive, up to 5 decimal places).\n";
    max = get_valid_float(0, 6);

    for (int i = 0; i < added_students; i++)
    {
        if (students[i].average_grade >= min && students[i].average_grade <= max)
        {
            right_students[number_of_right_students] = students[i];
            number_of_right_students++;
        }
    }

    for (int i = 0; i < number_of_right_students - 1; i++)
    {
        for (int j = 0; j < number_of_right_students - i - 1; j++)
        {
            if (strcmp(right_students[j].EGN, right_students[j + 1].EGN) > 0)
                swap_students(right_students[j], right_students[j + 1]);
        }
    }

    if (number_of_right_students == 0)
        cout << "There are no students with average grade in the given interval.\n";
    else
        display_students(right_students, number_of_right_students);

    return 0;
}

int update_grades(Student students[], int added_students)
{
    if (check_zero(added_students))
        return 1;

    char faculty_number[1000];
    char grade[1000];
    int choice;
    int index = -1;

    cout << "Enter faculty number of the student you want to change.\n";
    cin.getline(faculty_number, sizeof(faculty_number));

    for (int i = 0; i < added_students; i++)
    {
        if (strcmp(students[i].faculty_number, faculty_number) == 0)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "There is no student with that faculty number.\n";
        return 1;
    }

    if (strcmp(students[index].state, "Active") != 0)
    {
        cout << "It is impossible to update grades of inactive student.\n";
        return 1;
    }

    cout << "Student has the following marks:\n";
    for (int i = 0; i < 5; i++)
    {
        cout << students[index].subjects[i].name << ": " << students[index].subjects[i].grade << endl;
    }

    for (int i = 0; i < 5; i++)
    {
        if (students[index].subjects[i].grade == 0)
            get_grade(students[index], i);
        else
        {
            cout << "Do you want to change the grade in " << students[index].subjects[i].name << " ?\n"
                 << "1 for yes\n"
                 << "2 for no\n";
            choice = get_valid_integer(1, 2);
            if (choice == 1)
                get_grade(students[index], i);
        }
    }

    calculate_average_grade(students[index]);

    return 0;
}

int update_state(Student students[], int added_students)
{
    if (check_zero(added_students))
        return 1;

    char faculty_number[1000];
    int choice;
    int index = -1;

    cout << "Enter faculty number of the student you want to change.\n";
    cin.getline(faculty_number, sizeof(faculty_number));

    for (int i = 0; i < added_students; i++)
    {
        if (strcmp(students[i].faculty_number, faculty_number) == 0)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "There is no student with that faculty number.\n";
        return 1;
    }

    if (strcmp(students[index].state, "Graduated") == 0)
    {
        cout << "It is impossible to update state of graduated student.\n";
        return 1;
    }

    cout << "Current state of the student is '" << students[index].state << "'.\n";

    if (strcmp(students[index].state, "Active") == 0)
        cout << "Student's state can be changed to 'On leave'.\n";
    else
        cout << "Student's state can be changed to 'Active'.\n";

    cout << "Do you want to change the state of the student?\n"
         << "1 for yes\n"
         << "2 for no\n";
    choice = get_valid_integer(1, 2);

    if (choice == 1)
    {
        if (strcmp(students[index].state, "Active") == 0)
            strcpy(students[index].state, "On leave");
        else
            strcpy(students[index].state, "Active");
    }

    cout << "New state of the student is '" << students[index].state << "'.\n";
    return 0;
}

void info()
{
    cout << "Choose 1 to add students to the group.\n"
         << "Choose 2 to display all the students on the screen.\n"
         << "Choose 3 to display students with grades in interval in BP on the screen.\n"
         << "Choose 4 to display students with at least one grade '2' on the screen.\n"
         << "Choose 5 to sort students by first name and display students on the screen.\n"
         << "Choose 6 to save students to file.\n"
         << "Choose 7 to load students from file.\n"
         << "Choose 8 to choose students by state and sort by faculty number.\n"
         << "Choose 9 to choose students by average grade in interval and sort by EGN.\n"
         << "Choose 10 to update grades of the student.\n"
         << "Choose 11 to update state of the student.\n"
         << "Choose 12 to exit this program.\n"
         << "Enter your choice.\n";
}