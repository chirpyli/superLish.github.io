// 稀疏表

#include<cstdint>
#include<iostream>
using namespace std;

const int MAX_STUDENT = 5000;
const int MAX_COURSE = 200;

class Node {
public:
    Node(const int student, const int course, const int score):student(student),course(course),score(score) {
        next_student = nullptr;
        next_course = nullptr;
    }

    int student;
    int course;
    int score;

    Node* next_student;
    Node* next_course;
};


class School {
public:
    School(){
        for (int i = 0; i < MAX_STUDENT; ++i) {
            this->students[i] = nullptr;
        }

        for (int i = 0; i < MAX_COURSE; ++i) {
            this->courses[i] = nullptr;
        }
    }
    void add(const int student, const int course, const int score);
    // void remove(const int student, const int course);    //删除节点的代码这里略
    const int search(const int student, const int course);

private:
    Node* students[MAX_STUDENT];
    Node* courses[MAX_COURSE];

};

void School::add(const int student, const int course, const int score) {
    Node* node = new Node(student, course, score);
    
    Node* student_head = this->students[student];
    Node* course_head = this->courses[course];
    this->students[student] = node;
    this->courses[course] = node;
    node->next_student = student_head;
    node->next_course = course_head;
}

const int School::search(const int student, const int course) {
    Node* p = this->students[student];
    while (p != nullptr) {
        if (p->course == course) {
            return p->score;
        }
        p = p->next_course;
    }

    return -1;
}

// void School::remove(const int student, const int course) {

// }


int main() {
    School s;
    s.add(1, 10, 100);
    int v = s.search(1, 10);
    cout << v << endl;

    return 0;
}