#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

// Array Stack

class ArrayStack {
    static const int CAPACITY = 10;
    int data[CAPACITY];
    int count = 0;

public:
    void push(int x) {
        if (count == CAPACITY)
            throw overflow_error("stack full");

        data[count++] = x;
    }

    int pop() {
        if (empty())
            throw underflow_error("stack empty");

        return data[--count];
    }

    bool empty() const {
        return count == 0;
    }
};


// Linked Stack

class LinkedStack {
    struct Node {
        int value;
        Node* next;
    };

    Node* topNode = nullptr;

public:
    ~LinkedStack() {
        while (!empty())
            pop();
    }

    void push(int x) {
        topNode = new Node{x, topNode};
    }

    int pop() {
        if (empty())
            throw underflow_error("stack empty");

        Node* old = topNode;
        int x = old->value;

        topNode = old->next;
        delete old;

        return x;
    }

    bool empty() const {
        return topNode == nullptr;
    }
};


// Array Queue

class ArrayQueue {
    static const int CAPACITY = 10;
    int data[CAPACITY];
    int front = 0;
    int count = 0;

public:
    void enqueue(int x) {
        if (count == CAPACITY)
            throw overflow_error("queue full");

        data[(front + count) % CAPACITY] = x;
        ++count;
    }

    int dequeue() {
        if (empty())
            throw underflow_error("queue empty");

        int x = data[front];

        front = (front + 1) % CAPACITY;
        --count;

        return x;
    }

    bool empty() const {
        return count == 0;
    }
};


// Linked Queue

class LinkedQueue {
    struct Node {
        int value;
        Node* next;
    };

    Node* first = nullptr;
    Node* last = nullptr;

public:
    ~LinkedQueue() {
        while (!empty())
            dequeue();
    }

    void enqueue(int x) {
        Node* node = new Node{x, nullptr};

        if (last)
            last->next = node;
        else
            first = node;

        last = node;
    }

    int dequeue() {
        if (empty())
            throw underflow_error("queue empty");

        Node* old = first;
        int x = old->value;

        first = first->next;

        if (!first)
            last = nullptr;

        delete old;

        return x;
    }

    bool empty() const {
        return first == nullptr;
    }
};


// Array Deque

class ArrayDeque {
    static const int CAPACITY = 10;
    int data[CAPACITY];
    int front = 0;
    int count = 0;

public:
    void pushFront(int x) {
        if (count == CAPACITY)
            throw overflow_error("deque full");

        front = (front + CAPACITY - 1) % CAPACITY;
        data[front] = x;
        ++count;
    }

    void pushBack(int x) {
        if (count == CAPACITY)
            throw overflow_error("deque full");

        data[(front + count) % CAPACITY] = x;
        ++count;
    }

    int popFront() {
        if (empty())
            throw underflow_error("deque empty");

        int x = data[front];

        front = (front + 1) % CAPACITY;
        --count;

        return x;
    }

    int popBack() {
        if (empty())
            throw underflow_error("deque empty");

        --count;

        return data[(front + count) % CAPACITY];
    }

    bool empty() const {
        return count == 0;
    }
};


// Linked Deque

class LinkedDeque {
    struct Node {
        int value;
        Node* prev;
        Node* next;
    };

    Node* first = nullptr;
    Node* last = nullptr;

public:
    ~LinkedDeque() {
        while (!empty())
            popFront();
    }

    void pushFront(int x) {
        Node* node = new Node{x, nullptr, first};

        if (first)
            first->prev = node;
        else
            last = node;

        first = node;
    }

    void pushBack(int x) {
        Node* node = new Node{x, last, nullptr};

        if (last)
            last->next = node;
        else
            first = node;

        last = node;
    }

    int popFront() {
        if (empty())
            throw underflow_error("deque empty");

        Node* old = first;
        int x = old->value;

        first = first->next;

        if (first)
            first->prev = nullptr;
        else
            last = nullptr;

        delete old;

        return x;
    }

    int popBack() {
        if (empty())
            throw underflow_error("deque empty");

        Node* old = last;
        int x = old->value;

        last = last->prev;

        if (last)
            last->next = nullptr;
        else
            first = nullptr;

        delete old;

        return x;
    }

    bool empty() const {
        return first == nullptr;
    }
};


// Test Stack

template <class Stack>
void testStack(const string& name) {
    Stack s;

    cout << "\n" << name << "\n";

    for (int i = 1; i <= 6; i++) {
        s.push(i);
        cout << "push " << i << "\n";
    }

    for (int i = 0; i < 6; i++)
        cout << "pop " << s.pop() << "\n";

    try {
        s.pop();
    }
    catch (const underflow_error&) {
        cout << "empty pop handled\n";
    }
}


// Test Queue

template <class Queue>
void testQueue(const string& name) {
    Queue q;

    cout << "\n" << name << "\n";

    for (int i = 1; i <= 6; i++) {
        q.enqueue(i);
        cout << "enqueue " << i << "\n";
    }

    for (int i = 0; i < 6; i++)
        cout << "dequeue " << q.dequeue() << "\n";

    try {
        q.dequeue();
    }
    catch (const underflow_error&) {
        cout << "empty dequeue handled\n";
    }
}


// Test deque

template <class Deque>
void testDeque(const string& name) {
    Deque d;

    cout << "\n" << name << "\n";

    d.pushBack(1);
    d.pushFront(2);
    d.pushBack(3);
    d.pushFront(4);
    d.pushBack(5);
    d.pushFront(6);

    cout << d.popFront() << " ";
    cout << d.popBack() << " ";
    cout << d.popFront() << " ";
    cout << d.popBack() << " ";
    cout << d.popFront() << " ";
    cout << d.popBack() << "\n";

    try {
        d.popFront();
    }
    catch (const underflow_error&) {
        cout << "empty deque removal handled\n";
    }
}


// main

int main() {

    testStack<ArrayStack>("ARRAY STACK");
    testStack<LinkedStack>("LINKED STACK");

    testQueue<ArrayQueue>("ARRAY QUEUE");
    testQueue<LinkedQueue>("LINKED QUEUE");

    testDeque<ArrayDeque>("ARRAY DEQUE");
    testDeque<LinkedDeque>("LINKED DEQUE");

    // Test full array handling
    try {
        ArrayStack s;

        for (int i = 0; i < 11; i++)
            s.push(i);
    }
    catch (const overflow_error&) {
        cout << "\nfull array handling PASS\n";
    }

    return 0;
}