#include <cstddef>
#include <cstdint>
#include <iostream>

/*
A simple class implementing a circular buffer.
This buffer does not wrap and instead has a 
"full" state. It also contains minimal iterator 
support to be able to easily log out contents of 
the buffer. 
*/
template<typename T, size_t N>
class CircularBuffer {
    private:
    T buffer[N];
    size_t head = 0;
    size_t tail = 0;
    size_t count = 0;

    public:
    // push
    bool push(T item){
        // check to see if full
        if(count == N){
            return false;
        }
        buffer[tail] = item;
        tail = (tail + 1) % N;
        count++;
        return true;
    }

    // pop
    bool pop(T& item){
        // check to see if empty 
        if (count == 0 ){
            return false;
        }
        item = buffer[head];
        head = (head + 1) % N;
        count--;
        return true;
    }

    // size
    bool full(){return (count == N) ? true : false;};
    bool empty(){return (count != 0) ? false : true;};
    int size(){return count;};

    // iterator support
    T* begin() { return &buffer[head]; }  
    T* end()   { return &buffer[tail]; }
};

int main(){
    CircularBuffer<uint8_t, 8> testBuffer;

    // Populate with some data
    testBuffer.push(1);
    testBuffer.push(4);
    testBuffer.push(5);
    testBuffer.push(3);

    // test pop and log out
    uint8_t pop_val;
    testBuffer.pop(pop_val);
    std::cout << "popped value: " << static_cast<int>(pop_val) << std::endl;
    
    // log out remaining contents of buffer
    for (const auto x : testBuffer){
        std::cout << "Buffer value: " << static_cast<int>(x) << std::endl;
    }
    return 0;
}