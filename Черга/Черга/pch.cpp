//
// pch.cpp
//
#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

// Node class for a queue
class Node {
public:
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = NULL;
    }
};

// Queue class
class Queue {
public:
    Node* front;
    Node* rear;

    Queue() {
        front = NULL;
        rear = NULL;
    }

    // Add element to the queue
    void enqueue(int value) {
        Node* newNode = new Node(value);

        if (isEmpty()) {
            front = newNode;
            rear = newNode;
            return;
        }

        rear->next = newNode;
        rear = newNode;
    }

    // Remove element from the queue
    void dequeue() {
        if (isEmpty()) {
            cout << "����� �������." << endl;
            return;
        }

        if (front == rear) {
            front = NULL;
            rear = NULL;
            return;
        }

        Node* temp = front;
        front = front->next;
        delete temp;
    }

    // Get the front element of the queue
    int frontValue() {
        if (isEmpty()) {
            cout << "����� �������." << endl;
            return -1;
        }

        return front->data;
    }

    // Get the back element of the queue
    int backValue() {
        if (isEmpty()) {
            cout << "����� �������." << endl;
            return -1;
        }

        return rear->data;
    }

    // Check if the queue is empty
    bool isEmpty() {
        return (front == NULL && rear == NULL);
    }

    // Get the size of the queue
    int size() {
        int count = 0;
        Node* temp = front;
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void remove(int value) {
        if (isEmpty()) {
            cout << "����� �������." << endl;
            return;
        }

        if (front->data == value) {
            dequeue();
            return;
        }

        Node* prev = front;
        Node* temp = front->next;
        while (temp != NULL) {
            if (temp->data == value) {
                prev->next = temp->next;
                delete temp;
                if (prev->next == NULL) {
                    rear = prev;
                }
                return;
            }
            prev = temp;
            temp = temp->next;
        }

        cout << "������� �� ��������." << endl;
    }


    // Replace a specific element with a new value
    void replace(int oldValue, int newValue) {
        if (isEmpty()) {
            cout << "����� �������." << endl;
            return;
        }

        Node* curr = front;
        while (curr != NULL && curr->data != oldValue) {
            curr = curr->next;
        }

        if (curr == NULL) {
            cout << "������� �� ��������." << endl;
            return;
        }

        curr->data = newValue;
    }

    // Check if an element is in the queue
    bool contains(int value) {
        Node* temp = front;
        while (temp != NULL) {
            if (temp->data == value) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void showQueue() {
        if (isEmpty()) {
            cout << "����� �������." << endl;
            return;
        }

        cout << "[ ����� ]: ";
        Node* temp = front;
        while (temp != NULL) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// Node class for a priority queue
class PQNode {
public:
    int data;
    int priority;
    PQNode* next;

    PQNode(int value, int p) {
        data = value;
        priority = p;
        next = NULL;
    }
};

// Priority Queue class
class PriorityQueue {
public:
    PQNode* front;

    PriorityQueue() {
        front = NULL;
    }

    // Add element to the priority queue
    void enqueue(int value, int p) {
        PQNode* newNode = new PQNode(value, p);

        if (isEmpty() || p < front->priority) {
            newNode->next = front;
            front = newNode;
        }
        else {
            PQNode* temp = front;
            while (temp->next != NULL && temp->next->priority <= p) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }

    // Remove element from the priority queue
    void dequeue() {
        if (isEmpty()) {
            cout << "����� � ���������� �������." << endl;
            return;
        }

        PQNode* temp = front;
        front = front->next;
        delete temp;
    }

    // Get the front element of the priority queue
    int frontValue() {
        if (isEmpty()) {
            cout << "����� � ���������� �������." << endl;
            return -1;
        }

        return front->data;
    }

    int backValue() {
        if (isEmpty()) {
            cout << "����� � ���������� �������." << endl;
            return -1;
        }

        PQNode* temp = front;
        while (temp->next != NULL) {
            temp = temp->next;
        }

        return temp->data;
    }

    // Check if the priority queue is empty
    bool isEmpty() {
        return (front == NULL);
    }

    // Get the size of the priority queue
    int size() {
        int count = 0;
        PQNode* temp = front;
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }
        return count;
    }


    // Check if an element is in the priority queue
    bool contains(int value) {
        PQNode* temp = front;
        while (temp != NULL) {
            if (temp->data == value) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    // Remove an element from the priority queue
    void remove(int value) {
        if (isEmpty()) {
            cout << "����� � ���������� �������." << endl;
            return;
        }

        if (front->data == value) {
            dequeue();
            return;
        }

        PQNode* temp = front;
        while (temp->next != NULL && temp->next->data != value) {
            temp = temp->next;
        }

        if (temp->next == NULL) {
            cout << "�������� �� ��������." << endl;
            return;
        }

        PQNode* toRemove = temp->next;
        temp->next = temp->next->next;
        delete toRemove;
    }

    // Replace an element in the priority queue
    void replace(int oldValue, int newValue) {
        if (isEmpty()) {
            cout << "����� � ���������� �������." << endl;
            return;
        }

        PQNode* temp = front;
        while (temp != NULL && temp->data != oldValue) {
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "�������� �� ��������." << endl;
            return;
        }

        temp->data = newValue;
    }

    // Check if an element with a given priority is in the priority queue
    bool containsPriority(int p) {
        PQNode* temp = front;
        while (temp != NULL) {
            if (temp->priority == p) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
};


int test() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;
    cout << "������ �����:" << endl;
    cout << "[1] �������� �����." << endl;
    cout << "[2] ����� � ����������." << endl << endl;
    cout << "������: "; cin >> choice;

    if (choice == 1) {
        Queue q;
        while (true) {
            cout << endl;
            cout << "[������ �����]." << endl;
            cout << "1. ������ � �����;" << endl;
            cout << "2. �������� �����;" << endl;
            cout << "3. ������ �������;" << endl;
            cout << "4. ������� �������;" << endl;
            cout << "5. ���������;" << endl;
            cout << "6. �������� ������ �������;" << endl;
            cout << "7. ���������, �� � ������� � ����;" << endl;
            cout << "8. �������� �����;" << endl;
            cout << "9. ������� �������;" << endl;
            cout << "10. �����." << endl;

            cout << "������: "; cin >> choice;

            switch (choice) {
            case 1: {
                int value;
                cout << "������ �������, ���� ������� ������ �� �����: ";
                cin >> value;
                q.enqueue(value);

                _getch();
                system("cls");
                break;
            }
            case 2: {
                q.dequeue();
                cout << "����� �������.";

                _getch();
                system("cls");
                break;
            }
            case 3: {
                cout << "������ �������: " << q.frontValue() << endl;

                _getch();
                system("cls");
                break;
            }
            case 4: {
                cout << "������� �������: " << q.backValue() << endl;

                _getch();
                system("cls");
                break;
            }
            case 5: {
                cout << "���������: " << q.size() << endl;
                
                _getch();
                system("cls");
                break;
            }
            case 6: {
                int value;
                cout << "������ �������, ���� ������ ��������: "; cin >> value;

                q.remove(value);

                cout << "������� ��������";
                
                _getch();
                system("cls");
                break;
            }
            case 7: {
                int value;
                cout << "������ �������, ���� ������� ������: ";
                cin >> value;
                if (q.contains(value)) {
                    cout << "������� �������� � ����." << endl;
                }
                else {
                    cout << "������� �� �������� � ����." << endl;
                }
                
                _getch();
                system("cls");
                break;
            }
            case 8: { 
                q.showQueue();
                
                _getch();
                system("cls");
                break;
            }
            case 9: {
                int oldValue, value;
                cout << "������ �������, ���� ������ �������: "; cin >> oldValue;
                cout << "�� ���� ������ �������: "; cin >> value;

                q.replace(oldValue, value);

                cout << "�������� ������� ������.";

                _getch();
                system("cls");
                break;
            }
            case 10: {
                return 0;
            }
            default: {
                cout << "[ error ]. ����������� ������ ��. ��������� �����." << endl;
                
                _getch();
                system("cls");
                break;
            }
            }
        }
    }
    else if (choice == 2) {
        PriorityQueue pq;
        while (true) {
            cout << endl;
            cout << "[������ �����]." << endl;
            cout << "1. ������ � �����;" << endl;
            cout << "2. �������� �����;" << endl;
            cout << "3. ������ �������;" << endl;
            cout << "4. ������� �������;" << endl;
            cout << "5. ���������;" << endl;
            cout << "6. ���������, �� � ������� � ����;" << endl;
            cout << "7. �������� ������ �������;" << endl;
            cout << "8. ������� �������;" << endl;
            cout << "9. �� ������ ������������;" << endl;
            cout << "10. �������� �����;" << endl;
            cout << "11. Exit" << endl;

            cin >> choice;

            switch (choice) {
            case 1: {
                int value, priority;
                cout << "������ �������: ";
                cin >> value;
                cout << "������ ������������: ";
                cin >> priority;
                pq.enqueue(value, priority);
             
                _getch();
                system("cls");
                break;
            }
            case 2: {
                pq.dequeue();

                cout << "����� �������.";

                _getch();
                system("cls");
                break;
            }
            case 3: {
                int front = pq.frontValue();
                if (front != -1) {
                    cout << "������ �������: " << front << endl;
                }
                
                _getch();
                system("cls");
                break;
            }
            case 4: {
                    cout << "������� �������: " << pq.backValue() << endl;
               
                    _getch();
                    system("cls");
                    break;
            }
            case 5: {
                cout << "���������: " << pq.size() << endl;
             
                _getch();
                system("cls");
                break;
            }
            case 6: {
                int value;
                cout << "������ �������: ";
                cin >> value;
                if (pq.contains(value)) {
                    cout << "������� �������� � ���� � ����������." << endl;
                }
                else {
                    cout << "������� �� �������� � ���� � ����������." << endl;
                }
               
                _getch();
                system("cls");
                break;
            }
            case 7: {
                int value;
                cout << "������ �������, ���� ������� ��������: ";
                cin >> value;
                pq.remove(value);
                cout << "������� ��������.";
               
                _getch();
                system("cls");
                break;
            }
            case 8: {
                int oldValue, newValue;
                cout << "������ �������, ���� ������� �������: ";  cin >> oldValue;
                cout << "�� ���� ������ �������: ";  cin >> newValue;

                pq.replace(oldValue, newValue);
                cout << "�������� ������� ������.";

                _getch();
                system("cls");
                break;
            }
            case 9: {
                int p;
                cout << "������ ������������ ��� ������: ";
                cin >> p;
                if (pq.containsPriority(p)) {
                    cout << "������������ " << p << " �������� � ����." << endl;
                }
                else {
                    cout << "������������ " << p << " �� �������� � ����." << endl;
                }
               
                _getch();
                system("cls");
                break;
            }
            case 10: {
                cout << "[ ����� � ���������� ]: ";
                PQNode* temp = pq.front;
                while (temp != NULL) {
                    cout << temp->data << "(" << temp->priority << ") ";
                    temp = temp->next;
                }
                cout << endl;
               
                _getch();
                system("cls");
                break;
            }
            case 11: {
                return 0;
            }
            default: {
                cout << "[ error ]. ����������� ������ ��. ��������� �����." << endl;
                break;
            }
            }
        }
    }
    else {
        cout << "[ error ]. ����������� ������ ��. ��������� �����." << endl;
        return 1;
    }

    return 0;
}


/*����� 1*/

TEST(QueueTest, EnqueueTest) {
    Queue q;
    EXPECT_TRUE(q.isEmpty());
    q.enqueue(1);
    EXPECT_FALSE(q.isEmpty());
    EXPECT_EQ(q.frontValue(), 1);
    EXPECT_EQ(q.backValue(), 1);
    q.enqueue(2);
    EXPECT_EQ(q.size(), 2);
    EXPECT_EQ(q.frontValue(), 1);
    EXPECT_EQ(q.backValue(), 2);
}

TEST(QueueTest, DequeueTest) {
    Queue q;
    q.dequeue();  // nothing should happen
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.dequeue();
    EXPECT_EQ(q.size(), 2);
    EXPECT_EQ(q.frontValue(), 2);
    EXPECT_EQ(q.backValue(), 3);
    q.dequeue();
    q.dequeue();
    EXPECT_TRUE(q.isEmpty());
}

TEST(QueueTest, FrontValueTest) {
    Queue q;
    EXPECT_EQ(q.frontValue(), -1);
    q.enqueue(1);
    EXPECT_EQ(q.frontValue(), 1);
    q.enqueue(2);
    EXPECT_EQ(q.frontValue(), 1);
}

TEST(QueueTest, BackValueTest) {
    Queue q;
    EXPECT_EQ(q.backValue(), -1);
    q.enqueue(1);
    EXPECT_EQ(q.backValue(), 1);
    q.enqueue(2);
    EXPECT_EQ(q.backValue(), 2);
}

TEST(QueueTest, SizeTest) {
    Queue q;
    EXPECT_EQ(q.size(), 0);
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    EXPECT_EQ(q.size(), 3);
    q.dequeue();
    EXPECT_EQ(q.size(), 2);
}

TEST(QueueTest, RemoveTest) {
    Queue q;
    q.remove(1);  // nothing should happen
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.remove(2);
    EXPECT_EQ(q.size(), 2);
    EXPECT_FALSE(q.contains(2));
    EXPECT_EQ(q.frontValue(), 1);
    EXPECT_EQ(q.backValue(), 3);
    q.remove(1);
    q.remove(3);
    EXPECT_TRUE(q.isEmpty());
}

TEST(QueueTest, ReplaceTest) {
    Queue q;
    q.replace(1, 2);  // nothing should happen
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.replace(2, 4);
    EXPECT_EQ(q.size(), 3);
    EXPECT_FALSE(q.contains(2));
    EXPECT_TRUE(q.contains(4));
    EXPECT_EQ(q.frontValue(), 1);
    EXPECT_EQ(q.backValue(), 3);
    q.replace(1, 5);
    q.replace(3, 6);
    EXPECT_TRUE(q.contains(5));
    EXPECT_TRUE(q.contains(6));
}

TEST(QueueTest, ContainsTest) {
    Queue q;
    EXPECT_FALSE(q.contains(1));
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    EXPECT_TRUE(q.contains(2));
    q.remove(2);
    EXPECT_FALSE(q.contains(2));
}

/*����� 2*/

TEST(PriorityQueueTest, EnqueueAndDequeue) {
    PriorityQueue q;
    EXPECT_EQ(q.isEmpty(), true);

    q.enqueue(5, 1);
    EXPECT_EQ(q.isEmpty(), false);
    EXPECT_EQ(q.frontValue(), 5);

    q.enqueue(10, 2);
    EXPECT_EQ(q.frontValue(), 5);

    q.enqueue(3, 3);
    EXPECT_EQ(q.frontValue(), 5);

    q.dequeue();
    EXPECT_EQ(q.frontValue(), 10);

    q.dequeue();
    EXPECT_EQ(q.frontValue(), 3);

    q.dequeue();
    EXPECT_EQ(q.isEmpty(), true);
}

TEST(PriorityQueueTest, FrontAndBack) {
    PriorityQueue q;
    EXPECT_EQ(q.isEmpty(), true);

    q.enqueue(5, 1);
    EXPECT_EQ(q.frontValue(), 5);
    EXPECT_EQ(q.backValue(), 5);

    q.enqueue(10, 2);
    EXPECT_EQ(q.frontValue(), 5);
    EXPECT_EQ(q.backValue(), 10);

    q.enqueue(3, 3);
    EXPECT_EQ(q.frontValue(), 5);
    EXPECT_EQ(q.backValue(), 3);
}

TEST(PriorityQueueTest, Size) {
    PriorityQueue q;
    EXPECT_EQ(q.size(), 0);

    q.enqueue(5, 1);
    EXPECT_EQ(q.size(), 1);

    q.enqueue(10, 2);
    EXPECT_EQ(q.size(), 2);

    q.enqueue(3, 3);
    EXPECT_EQ(q.size(), 3);

    q.dequeue();
    EXPECT_EQ(q.size(), 2);

    q.dequeue();
    EXPECT_EQ(q.size(), 1);

    q.dequeue();
    EXPECT_EQ(q.size(), 0);
}

TEST(PriorityQueueTest, Contains) {
    PriorityQueue q;
    EXPECT_EQ(q.contains(5), false);

    q.enqueue(5, 1);
    EXPECT_EQ(q.contains(5), true);
    EXPECT_EQ(q.contains(10), false);

    q.enqueue(10, 2);
    EXPECT_EQ(q.contains(10), true);

    q.enqueue(3, 3);
    EXPECT_EQ(q.contains(3), true);

    q.dequeue();
    EXPECT_EQ(q.contains(5), false);
}

TEST(PriorityQueueTest, Remove) {
    PriorityQueue q;
    EXPECT_EQ(q.contains(5), false);

    q.enqueue(5, 1);
    q.enqueue(10, 2);
    q.enqueue(3, 3);

    q.remove(10);
    EXPECT_EQ(q.contains(10), false);
    EXPECT_EQ(q.size(), 2);

    q.remove(5);
    EXPECT_EQ(q.contains(5), false);
    EXPECT_EQ(q.size(), 1);

    q.remove(5);
    EXPECT_EQ(q.size(), 1);
}

TEST(PriorityQueueTest, Replace) {
    PriorityQueue q;
    q.enqueue(5, 1);
    q.enqueue(10, 2);
    q.enqueue(3, 3);

    q.replace(10, 7);
    EXPECT_EQ(q.contains(10), false);
    EXPECT_EQ(q.contains(7), true);
    EXPECT_EQ(q.size(), 3);

    q.replace(5, 2);
    EXPECT_EQ(q.contains(5), false);
    EXPECT_EQ(q.contains(2), true);
    EXPECT_EQ(q.size(), 3);

    q.replace(8, 4);
    EXPECT_EQ(q.contains(8), false);
    EXPECT_EQ(q.size(), 3);
}

TEST(PriorityQueueTest, ContainsPriority) {
    PriorityQueue q;
    EXPECT_EQ(q.containsPriority(1), false);

    q.enqueue(10, 1);
    q.enqueue(20, 2);
    q.enqueue(30, 3);

    EXPECT_EQ(q.containsPriority(1), true);
    EXPECT_EQ(q.containsPriority(2), true);
    EXPECT_EQ(q.containsPriority(3), true);
    EXPECT_EQ(q.containsPriority(4), false);

    q.dequeue();

    EXPECT_EQ(q.containsPriority(1), false);
    EXPECT_EQ(q.containsPriority(2), true);
    EXPECT_EQ(q.containsPriority(3), true);
    EXPECT_EQ(q.containsPriority(4), false);

    q.remove(20);

    EXPECT_EQ(q.containsPriority(1), false);
    EXPECT_EQ(q.containsPriority(2), false);
    EXPECT_EQ(q.containsPriority(3), true);
    EXPECT_EQ(q.containsPriority(4), false);

    q.remove(30);

    EXPECT_EQ(q.containsPriority(1), false);
    EXPECT_EQ(q.containsPriority(2), false);
    EXPECT_EQ(q.containsPriority(3), false);
    EXPECT_EQ(q.containsPriority(4), false);
}