#ifndef PEA_FFSTACK_H
#define PEA_FFSTACK_H

template <typename T>
class ffstack{
public:
    explicit ffstack(size_t size) : size(size){
        elements = new T[size];
        sharedPtr = std::shared_ptr<T[]>(elements);
    };
    ffstack() : size(0), elements(nullptr), sharedPtr(nullptr){};
    T& getCurrent(){
#if DEBUG
            if(!stackPtr){
                std::cout << "DEBUG: trying to access current element of empty ffstack\n";
                throw std::exception();
            }
#endif
        return elements[stackPtr - 1];
    };
    T pop(){
#if DEBUG
        if(!stackPtr){
                std::cout << "DEBUG: trying to pop empty ffstack\n";
                throw std::exception();
        }
#endif
        return elements[--stackPtr];
    };
    void push(T element){
#if DEBUG
        if(stackPtr == size){
                std::cout << "DEBUG: stack overflow\n";
                throw std::exception();
        }
#endif
        elements[stackPtr++] = element;
    };
    class UpwardIterator{
    public:
        explicit UpwardIterator(ffstack* parent) : parent(parent), index(0){
            elements = parent->elements;
        };
        bool hasNext(){
            return index < parent->stackPtr;
        };
        T& next(){
            return elements[index++];
        };
    private:
        ffstack* parent;
        T* elements;
        size_t index;
    };
    class DownwardIterator{
    public:
        explicit DownwardIterator(ffstack* parent) : parent(parent){
            elements = parent->elements;
            index = parent->stackPtr;
        };
        bool hasNext(){
            return index > 0;
        };
        T& next(){
            return elements[--index];
        };
    private:
        ffstack* parent;
        T* elements;
        size_t index;
    };
    UpwardIterator upwardIterator(){
        return UpwardIterator(this);
    }
    DownwardIterator downwardIterator(){
        return DownwardIterator(this);
    }
private:
    size_t size;
    size_t stackPtr{};
    T* elements;
    std::shared_ptr<T[]> sharedPtr;
};

#endif //PEA_FFSTACK_H
