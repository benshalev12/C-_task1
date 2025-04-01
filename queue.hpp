//benshalev12@gmail.com

#ifndef SIMPLE_QUEUE_HPP
#define SIMPLE_QUEUE_HPP

class SimpleQueue {
private:
    int* data;
    int capacity;
    int front;
    int rear;
    int count;

public:
    SimpleQueue(int size);
    ~SimpleQueue();

    void enqueue(int value);
    int dequeue();
    bool isEmpty();
};

// Moved implementation here for simplicity
SimpleQueue::SimpleQueue(int size) {
    capacity = size;
    data = new int[capacity];
    front = 0;
    rear = -1;
    count = 0;
}

SimpleQueue::~SimpleQueue() {
    delete[] data;
}

void SimpleQueue::enqueue(int value) {
    if (count < capacity) {
        rear = (rear + 1) % capacity;
        data[rear] = value;
        count++;
    }
}

int SimpleQueue::dequeue() {
    if (count == 0) return -1;
    int value = data[front];
    front = (front + 1) % capacity;
    count--;
    return value;
}

bool SimpleQueue::isEmpty() {
    return count == 0;
}

#endif