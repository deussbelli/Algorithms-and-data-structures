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
            cout << "Черга порожня." << endl;
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
            cout << "Черга порожня." << endl;
            return -1;
        }

        return front->data;
    }

    // Get the back element of the queue
    int backValue() {
        if (isEmpty()) {
            cout << "Черга порожня." << endl;
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
            cout << "Черга порожня." << endl;
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

        cout << "Елемент не знайдено." << endl;
    }


    // Replace a specific element with a new value
    void replace(int oldValue, int newValue) {
        if (isEmpty()) {
            cout << "Черга порожня." << endl;
            return;
        }

        Node* curr = front;
        while (curr != NULL && curr->data != oldValue) {
            curr = curr->next;
        }

        if (curr == NULL) {
            cout << "Елемент не знайдено." << endl;
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
            cout << "Черга порожня." << endl;
            return;
        }

        cout << "[ Черга ]: ";
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
            cout << "Черга з приорітетом порожня." << endl;
            return;
        }

        PQNode* temp = front;
        front = front->next;
        delete temp;
    }

    // Get the front element of the priority queue
    int frontValue() {
        if (isEmpty()) {
            cout << "Черга з приорітетом порожня." << endl;
            return -1;
        }

        return front->data;
    }

    int backValue() {
        if (isEmpty()) {
            cout << "Черга з приорітетом порожня." << endl;
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
            cout << "Черга з приорітетом порожня." << endl;
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
            cout << "Елементу не знайдено." << endl;
            return;
        }

        PQNode* toRemove = temp->next;
        temp->next = temp->next->next;
        delete toRemove;
    }

    // Replace an element in the priority queue
    void replace(int oldValue, int newValue) {
        if (isEmpty()) {
            cout << "Черга з приорітетом порожня." << endl;
            return;
        }

        PQNode* temp = front;
        while (temp != NULL && temp->data != oldValue) {
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "Елементу не знайдено." << endl;
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
    cout << "Оберіть чергу:" << endl;
    cout << "[1] Звичайна черга." << endl;
    cout << "[2] Черга с приорітетом." << endl << endl;
    cout << "Обрати: "; cin >> choice;

    if (choice == 1) {
        Queue q;
        while (true) {
            cout << endl;
            cout << "[Оберіть метод]." << endl;
            cout << "1. Додати у чергу;" << endl;
            cout << "2. Очистити чергу;" << endl;
            cout << "3. Перший елемент;" << endl;
            cout << "4. Останній елемент;" << endl;
            cout << "5. Розмірність;" << endl;
            cout << "6. Вилучити певний елемент;" << endl;
            cout << "7. Перевірити, чи є елемент у черзі;" << endl;
            cout << "8. Показати чергу;" << endl;
            cout << "9. Замінити елемент;" << endl;
            cout << "10. Вийти." << endl;

            cout << "Обрати: "; cin >> choice;

            switch (choice) {
            case 1: {
                int value;
                cout << "Уведіть елемент, який потрібно додати до черги: ";
                cin >> value;
                q.enqueue(value);

                _getch();
                system("cls");
                break;
            }
            case 2: {
                q.dequeue();
                cout << "Чергу очищено.";

                _getch();
                system("cls");
                break;
            }
            case 3: {
                cout << "Перший елемент: " << q.frontValue() << endl;

                _getch();
                system("cls");
                break;
            }
            case 4: {
                cout << "Останній елемент: " << q.backValue() << endl;

                _getch();
                system("cls");
                break;
            }
            case 5: {
                cout << "Розмірність: " << q.size() << endl;
                
                _getch();
                system("cls");
                break;
            }
            case 6: {
                int value;
                cout << "Оберіть елемент, який хочете вилучити: "; cin >> value;

                q.remove(value);

                cout << "Елемент вилучено";
                
                _getch();
                system("cls");
                break;
            }
            case 7: {
                int value;
                cout << "Уведіть елемент, який потрібно знайти: ";
                cin >> value;
                if (q.contains(value)) {
                    cout << "Елемент знайдено у черзі." << endl;
                }
                else {
                    cout << "Елемент НЕ знайдено у черзі." << endl;
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
                cout << "Уведіть елемент, який хочете замінити: "; cin >> oldValue;
                cout << "На який хочете замінити: "; cin >> value;

                q.replace(oldValue, value);

                cout << "Операція пройшла успішно.";

                _getch();
                system("cls");
                break;
            }
            case 10: {
                return 0;
            }
            default: {
                cout << "[ error ]. Неправильно обрано дію. Спробуйте знову." << endl;
                
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
            cout << "[Оберіть метод]." << endl;
            cout << "1. Додати у чергу;" << endl;
            cout << "2. Очистити чергу;" << endl;
            cout << "3. Перший елемент;" << endl;
            cout << "4. Останній елемент;" << endl;
            cout << "5. Розмірність;" << endl;
            cout << "6. Перевірити, чи є елемент у черзі;" << endl;
            cout << "7. Вилучити певний елемент;" << endl;
            cout << "8. Замінити елемент;" << endl;
            cout << "9. Чи містить приорітетність;" << endl;
            cout << "10. Показати чергу;" << endl;
            cout << "11. Exit" << endl;

            cin >> choice;

            switch (choice) {
            case 1: {
                int value, priority;
                cout << "Уведіть елемент: ";
                cin >> value;
                cout << "Уведіть приорітетність: ";
                cin >> priority;
                pq.enqueue(value, priority);
             
                _getch();
                system("cls");
                break;
            }
            case 2: {
                pq.dequeue();

                cout << "Чергу очищено.";

                _getch();
                system("cls");
                break;
            }
            case 3: {
                int front = pq.frontValue();
                if (front != -1) {
                    cout << "Перший елемент: " << front << endl;
                }
                
                _getch();
                system("cls");
                break;
            }
            case 4: {
                    cout << "Останній елемент: " << pq.backValue() << endl;
               
                    _getch();
                    system("cls");
                    break;
            }
            case 5: {
                cout << "Розмірність: " << pq.size() << endl;
             
                _getch();
                system("cls");
                break;
            }
            case 6: {
                int value;
                cout << "Уведіть елемент: ";
                cin >> value;
                if (pq.contains(value)) {
                    cout << "Елемент міститься у черзі з приорітетом." << endl;
                }
                else {
                    cout << "Елемент НЕ міститься у черзі з приорітетом." << endl;
                }
               
                _getch();
                system("cls");
                break;
            }
            case 7: {
                int value;
                cout << "Уведіть елемент, який потрібно вилучити: ";
                cin >> value;
                pq.remove(value);
                cout << "Елемент вилучено.";
               
                _getch();
                system("cls");
                break;
            }
            case 8: {
                int oldValue, newValue;
                cout << "Уведіть елемент, який потрібно замінити: ";  cin >> oldValue;
                cout << "На який хочете замінити: ";  cin >> newValue;

                pq.replace(oldValue, newValue);
                cout << "Операція пройшла успішно.";

                _getch();
                system("cls");
                break;
            }
            case 9: {
                int p;
                cout << "Уведіть приорітетність для пошуку: ";
                cin >> p;
                if (pq.containsPriority(p)) {
                    cout << "Приорітетність " << p << " міститься у черзі." << endl;
                }
                else {
                    cout << "Приорітетність " << p << " НЕ міститься у черзі." << endl;
                }
               
                _getch();
                system("cls");
                break;
            }
            case 10: {
                cout << "[ Черга з приорітетом ]: ";
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
                cout << "[ error ]. Неправильно обрано дію. Спробуйте знову." << endl;
                break;
            }
            }
        }
    }
    else {
        cout << "[ error ]. Неправильно обрано дію. Спробуйте знову." << endl;
        return 1;
    }

    return 0;
}


/*черга 1*/

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

/*черга 2*/

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