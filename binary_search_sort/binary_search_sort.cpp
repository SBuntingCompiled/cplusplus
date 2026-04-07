#include <cstddef>
#include <iostream>
#include <iomanip>

/*
A class to illustrate a binary search and sort implementation.
The sort for this particular class uses a heap sort. It was 
decided to make this templated to help extend out its use
cases. 
*/
template<typename T, size_t N>
class BinarySearchSort{
    public:
    BinarySearchSort(const T* data, size_t count) :
        sorted_{false} {
            size_t n = (count < N) ? count : N;
            for (size_t i = 0; i < n; i++) {
                data_[i] = data[i];
            }
        };
    ~BinarySearchSort() = default;

    bool Search(const T& target, int& index);
    void Sort();
    void Print();

    private:
    T data_[N];
    bool sorted_;

    void Heapify(size_t heapSize, size_t i);
};

template<typename T, size_t N>
bool BinarySearchSort<T, N>::Search(const T& target, int& index){
    // guard against unsorted data
    if(!sorted_){
        return false; 
    }

    int lo{0};
    int hi{static_cast<int>(N) - 1};
    bool found{false};
    while (!found && (lo <= hi)){
        int mid = lo + ((hi - lo) / 2);
        
        if(target == data_[mid]){
            index = mid;
            found = true;
        }
        
        // check to see if data is lower half and adjust hi
        else if (target < data_[mid]){
            hi = mid - 1;
        }
        else { // in upper half so move lo up
            lo = mid + 1;
        }
    }

    return found;
}

template<typename T, size_t N>
void BinarySearchSort<T, N>::Sort(){
    // build max-heap from the bottom up
    for (int i = static_cast<int>(N/2 - 1); i >= 0; i--) {
        Heapify(N, static_cast<size_t>(i));
    }

    // extract elements one by one
    for (size_t i = N - 1; i > 0; i--) {
        // swap root (largest) with last element in current heap
        std::swap(data_[0], data_[i]);
        // restore heap property on the shrunk heap
        Heapify(i, 0);
    }

    sorted_ = true;
}

template<typename T, size_t N>
void BinarySearchSort<T, N>::Heapify(size_t heapSize, size_t i) {
    size_t largest = i;
    size_t left    = (2 * i) + 1;
    size_t right   = (2 * i) + 2;

    // is left child larger than current largest?
    if (left < heapSize && data_[left] > data_[largest])
        largest = left;

    // is right child larger than current largest?
    if (right < heapSize && data_[right] > data_[largest])
        largest = right;

    // if largest is not the parent, swap and recurse downward
    if (largest != i) {
        std::swap(data_[i], data_[largest]);
        Heapify(heapSize, largest);
    }
}

template<typename T, size_t N>
void BinarySearchSort<T, N>::Print(){
    std::cout << std::fixed << std::setprecision(2);
    for (size_t i = 0; i < N; i++) {
        std::cout << data_[i];
        if (i < N - 1) std::cout << ", ";
    }
    std::cout << std::defaultfloat << "\n";
}

int main(){
    // --- integer example ---
    int values[] = {3, 1, 8, 5, 2, 7, 4};
    BinarySearchSort<int, 7> bss(values, 7);

    // Print data out before sorting
    std:: cout << "Data before sort:" << std::endl;
    bss.Print();

    // search before sorting — should be rejected
    int idx = -1;
    bool found = bss.Search(7, idx);
    std::cout << "Search before sort: "
              << (found ? "found" : "rejected (not sorted)") << "\n";

    // sort, then print sorted order
    bss.Sort();
    std::cout << "Sorted successfully.\n";
    bss.Print();

    // search for a value that exists
    found = bss.Search(7, idx);
    std::cout << "Search(7): "
              << (found ? "found at index " + std::to_string(idx) : "not found")
              << "\n";

    // search for a value that does not exist
    found = bss.Search(99, idx);
    std::cout << "Search(99): "
              << (found ? "found" : "not found") << "\n";

    // --- float example: shows the template works for other types ---
    float fvals[] = {3.3f, 1.1f, 8.8f, 5.5f, 2.2f};
    BinarySearchSort<float, 5> fbss(fvals, 5);

    // Print data out before sorting
    std:: cout << "Data before sort:" << std::endl;
    fbss.Print();
    fbss.Sort();

    // Print data out after sorting
    std:: cout << "Data after sort:" << std::endl;
    fbss.Print();

    found = fbss.Search(5.5f, idx);
    std::cout << "Float search(5.5): "
              << (found ? "found at index " + std::to_string(idx) : "not found")
              << "\n";

    return 0;
}
