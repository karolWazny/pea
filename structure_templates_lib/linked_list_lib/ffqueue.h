#ifndef PEA_FFQUEUE_H
#define PEA_FFQUEUE_H

template <typename T>
class ffqueue{
public:
    explicit ffqueue(size_t capacity) : capacity(capacity){
        if(capacity)
            elements = new T[capacity];
        sharedPtr = std::shared_ptr<T[]>(elements);
    };
    ffqueue() : capacity(0){};
    T dequeue(){
        length--;
#if DEBUG
        if(tail == head)
            throw std::exception();
#endif
        auto output = elements[head];
        head++;
        if(head == capacity)
            head = 0;
        return output;
    };
    void enqueue(T element){
        length++;
        elements[tail] = element;
        tail++;
        if(tail == capacity)
            tail = 0;
#if DEBUG
    if(tail == head)
        throw std::exception();
#endif
    };
    size_t getCapacity(){return capacity;};
    size_t getLength(){return length;};
private:
    size_t length{};
    size_t capacity;
    size_t head{};
    size_t tail{};
    T* elements{};
    std::shared_ptr<T[]> sharedPtr{};
};

#endif //PEA_FFQUEUE_H
