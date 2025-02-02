MAX_NAME_LENGTH = 32

class Student:
    def __init__(self, faculty_number: str, egn: str, first_name: str, middle_name: str,
                 last_name: str, subjects: dict, sex: str, age: int, state: str):
        if not (faculty_number and egn and first_name and middle_name and last_name
                and subjects and sex and age and state):
            raise ValueError("Missing data")
        
        self.faculty_number = faculty_number
        self.egn = egn
        self.first_name = first_name
        self.middle_name = middle_name
        self.last_name = last_name
        self.subjects = subjects
        self.sex = sex
        self.age = age
        self.state = state


    @property
    def faculty_number(self):
        return self._faculty_number
    
    @faculty_number.setter
    def faculty_number (self, faculty_number):
        if len(faculty_number) == 8 and faculty_number.isdecimal():
            self._faculty_number = faculty_number

    
    @property
    def egn(self):
        return self._egn

    @egn.setter
    def egn(self, egn):
        if len(egn) == 10 and egn.isdecimal():
            self._egn = egn

    
    @property
    def first_name(self):
        return self._first_name

    @first_name.setter
    def first_name(self, first_name):
        if len(first_name) <= MAX_NAME_LENGTH and first_name.isalpha():
            self._first_name = first_name

    
    @property
    def middle_name(self):
        return self._middle_name

    @middle_name.setter
    def middle_name(self, middle_name):
        if len(middle_name) <= MAX_NAME_LENGTH and middle_name.isalpha():
            self._middle_name = middle_name

    
    @property
    def last_name(self):
        return self._last_name

    @last_name.setter
    def last_name(self, last_name):
        if len(last_name) <= MAX_NAME_LENGTH and last_name.isalpha():
            self._last_name = last_name

    
    @property
    def subjects(self):
        return self._subjects

    @subjects.setter
    def subjects(self, subjects):
        self._subjects = subjects

    
    @property
    def sex(self):
        return self._sex

    @sex.setter
    def sex(self, sex):
        if sex in ["M", "F"]:
            self._sex = sex

    
    @property
    def age(self):
        return self._age

    @age.setter
    def age(self, age):
        if age >= 10 and age <= 100:
            self._age = age

    
    @property
    def state(self):
        return self._state

    @state.setter
    def state(self, state):
        if state not in ["Active", "On leave", "Graduated"]:
            raise ValueError("Invalid state")
        self._state = state

    def display(self):
        print(self.faculty_number, self.egn, self.first_name, self.middle_name, self.last_name,
              self.sex, self.age, self.state, end=" ")
        for subject in self.subjects:
            print(subject, ": ", self.subjects[subject], sep="", end=" ")
        print()
        

student_1 = Student("24621948", "0391002864", "Oleksandr", "Oleksandrovich", "Kuzhylnyi",
                    {"BP": 5, "Math": 6, "Digital logic": 6, "Electronics": 5, "English": 6 },
                    "M", 18, "Active")

student_1.display()

def main():
    while True:
        choice = int(input("Choose from 1 to 12:\n"))
        if choice in range(1, 13):
            break

        print("Invalid input")

    match(choice):
        case 1:
            print("a")
        case 2:
            print("b")
        case _ :
            print("else")


def get_int(prompt):
    while True:
        try:
            return int(input(prompt))
        except ValueError:
            print("Not an integer.")


if __name__ == "__main__":
    main()