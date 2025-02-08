from typing import List

MAX_NAME_LENGTH = 32
NUMBER_OF_SUBJECTS = 5

def get_int(prompt: str) -> int:
    while True:
        try:
            return int(input(prompt))
        except ValueError:
            print("Not an integer.")

def get_grade(subject_name: str) -> int:
    while True:
        grade = get_int(f"Enter grade in {subject_name}: ")
        if grade in [0, 2, 3, 4, 5, 6]:
            return grade
        print("Invalid grade")

class Student:
    def __init__(self, faculty_number: str = '', egn: str = '', first_name: str = '', middle_name: str = '',
                 last_name: str = '', subjects: dict = {}, sex: str = '', age: int = -1, state: str = ''):
        self._faculty_number = faculty_number
        self._egn = egn
        self._first_name = first_name
        self._middle_name = middle_name
        self._last_name = last_name
        self._subjects = subjects
        self._sex = sex
        self._age = age
        self._state = state

    @property
    def faculty_number(self):
        return self._faculty_number
    
    @faculty_number.setter
    def faculty_number (self, faculty_number):
        if len(faculty_number) == 8 and faculty_number.isdecimal():
            self._faculty_number = faculty_number
        else:
            raise ValueError("Invalid faculty number")

    @property
    def egn(self):
        return self._egn

    @egn.setter
    def egn(self, egn):
        if len(egn) == 10 and egn.isdecimal():
            self._egn = egn
        else:
            raise ValueError("Invalid EGN")

    @property
    def first_name(self):
        return self._first_name

    @first_name.setter
    def first_name(self, first_name):
        if len(first_name) <= MAX_NAME_LENGTH and first_name.isalpha():
            self._first_name = first_name
        else:
            raise ValueError("Invalid first name")

    @property
    def middle_name(self):
        return self._middle_name

    @middle_name.setter
    def middle_name(self, middle_name):
        if len(middle_name) <= MAX_NAME_LENGTH and middle_name.isalpha():
            self._middle_name = middle_name
        else:  
            raise ValueError("Invalid middle name")

    @property
    def last_name(self):
        return self._last_name

    @last_name.setter
    def last_name(self, last_name):
        if len(last_name) <= MAX_NAME_LENGTH and last_name.isalpha():
            self._last_name = last_name
        else:
            raise ValueError("Invalid last name")

    @property
    def subjects(self):
        return self._subjects

    @subjects.setter
    def subjects(self, subjects):
        if (len(subjects) == NUMBER_OF_SUBJECTS
            and all(grade in [0, 2, 3, 4, 5, 6]) for grade in subjects.values()):
            self._subjects = subjects
        else:
            raise ValueError("Invalid subjects")

    @property
    def sex(self):
        return self._sex

    @sex.setter
    def sex(self, sex):
        if sex in ["M", "F"]:
            self._sex = sex
        else:
            raise ValueError("Invalid sex")

    @property
    def age(self):
        return self._age

    @age.setter
    def age(self, age):
        if age >= 10 and age <= 100:
            self._age = age
        else:
            raise ValueError("Invalid age")

    @property
    def state(self):
        return self._state

    @state.setter
    def state(self, state):
        if state in ["Active", "On leave", "Graduated"]:
            self._state = state
        else:
            raise ValueError("Invalid state")

    def add_faculty_number(self):
        while True:
            try:
                faculty_number = input("Enter faculty number: ")
                self.faculty_number = faculty_number
                break
            except ValueError:
                print("Invalid faculty number")

    def add_egn(self):
        while True:
            try:
                egn = input("Enter egn: ")
                self.egn = egn
                break
            except ValueError:
                print("Invalid egn")

    def add_first_name(self):
        while True:
            try:
                first_name = input("Enter first name: ")
                self.first_name = first_name
                break
            except ValueError:
                print("Invalid first name")

    def add_middle_name(self):
        while True:
            try:
                middle_name = input("Enter middle name: ")
                self.middle_name = middle_name
                break
            except ValueError:
                print("Invalid middle name")

    def add_last_name(self):
        while True:
            try:
                last_name = input("Enter last name: ")
                self.last_name = last_name
                break
            except ValueError:
                print("Invalid last name")

    def add_subjects(self):
        self.subjects["BP"] = get_grade("BP")  # BP is mandatory
        for _ in range(NUMBER_OF_SUBJECTS - 1):
            self.add_subject()

    def add_subject(self):
        while True:
            subject_name = input("Enter subject name: ")
            if subject_name not in self.subjects:
                break
            print("This subject already exists")
        self.subjects[subject_name] = get_grade(subject_name)

    def add_sex(self):
        while True:
            try:
                self.sex = input("Enter sex: ")
                break
            except ValueError:
                print("Invalid sex")

    def add_age(self):
        while True:
            try:
                self.age = int(input("Enter age: "))
                break
            except ValueError:
                print("Invalid age")

    def add_state(self):
        while True:
            try:
                self.state = input("Enter state: ")
                break
            except ValueError:
                print("Invalid state")

    def add(self):
        self.add_faculty_number()
        self.add_egn()
        self.add_first_name()
        self.add_middle_name()
        self.add_last_name()
        self.add_subjects()
        self.add_sex()
        self.add_age()
        self.add_state()

    def __str__(self):
        subjects = " ".join([f"{subject}: {grade}" for subject, grade in self.subjects.items()])
        return (f"{self.faculty_number} {self.egn} {self.first_name} {self.middle_name} "
                f"{self.last_name} {self.sex} {self.age} {self.state} {subjects}")

    
class Group:
    def __init__(self, students: List[Student] = []):
        self._students = students

    @property
    def students(self):
        return self._students

    @students.setter
    def students(self, students):
        self._students = students

    def add_students(self):
        num_new_students = get_int("Enter number of new students: ")
        for _ in range(num_new_students):
            student = Student()
            student.add()
            self.students.append(student)

    def display(self):
        for student in self.students:
            print(student)

    def search_by_grade_in_BP(self):
        right_students = []
        lower_grade = get_int("Enter lower grade: ")
        upper_grade = get_int("Enter upper grade: ")
        for student in self.students:
            if student.subjects["BP"] >= lower_grade and student.subjects["BP"] <= upper_grade:
                right_students.append(student)
        for student in right_students:
            print(student)

def main():
    group = Group()
    while True:
        while True:
            print("1. Add students")
            print("2. Display students")
            print("3. Search by grade in BP")
            choice = int(input("Choose from 1 to 12: "))
            if choice in range(1, 13):
                break
            print("Invalid input")

        match(choice):
            case 1:
                group.add_students()
            case 2:
                group.display()
            case 3:
                group.search_by_grade_in_BP()
            case _ :
                print("TODO")


if __name__ == "__main__":
    main()
    
