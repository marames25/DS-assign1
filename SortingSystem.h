#ifndef SORTINGSYSTEM_H
#define SORTINGSYSTEM_H
#include "bits/stdc++.h"
#define endl '\n'
using namespace std;
using namespace chrono;


namespace okasha {
struct node {
    int value;
    node* next;
};    
class queue {
protected:
    node* front, * back;
    int counter;
public:
    ~queue() {
        while (front) {
            node* next = front->next;
            delete front;
            front = next;
        }
    }
    queue() : front(nullptr), back(nullptr),counter(0) {}
    void push(int val) {
        node* new_node = new node{ val, nullptr };
        if (front == nullptr) {
            front = back = new_node;
        }
        else {
            back->next = new_node;
            back = new_node;
        }
        counter++;
    }
    int pop() {
        if (front) {
            int val = front->value;
            node* next = front->next;
            if (front == back) back = nullptr;
            delete front;
            front = next;
            return val;
        }
        else {
            throw out_of_range("trying to pop an empty queue\n");
        }
    }
    bool empty() {
        return (!front && !back);
    }
};

class bucket : public okasha::queue {
public:
    int* sort_data() {
        int* temp = new int[counter];
        for (int i = 0; !this->empty(); i++) {
            temp[i] = this->pop();
        }
        sort(temp, temp + counter);
        return temp;
    }
    int size() {
        return counter;
    }
};
}


template <typename T>
class SortingSystem {
private:
    T* data;  // Dynamic array for storing input data
    int size; // Size of the array
    bool is_string;
    ifstream &file;

    void merge(int left, int right); // Merge Sort Helper
    int partition(int low, int high); // Quick Sort Helper
    void measureSortTime(void (SortingSystem::*sortFunc)()); // Measure sorting time
    void measureSortTime(void (SortingSystem::* sortFunc)(int, int)); // Measure sorting time

    int getNumberFromUser(string prompt) {
        int number;
        while (true) {
            cout << prompt;
            cin >> number;
            if (cin.fail()) {
                cin.clear(); 
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                cout << "Invalid input, Please enter a valid integer.\n";
            } else {
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                break;
            }
        }
        return number;
    }
    
    int getNumberFromFile(const string& prompt) {
        int number;
        string line;

        while (true) {
            cout << prompt;

            if (!getline(file, line)) {
                cout << "No more input in the file or failed to read.\n";
                exit(1);  // Stop the program if we run out of inputs
            }

            stringstream ss(line);
            ss >> number;

            if (ss.fail() || !ss.eof()) {
                cout << "Invalid input, Please enter a valid integer.\n";
            }
            else {
                break;
            }
        }
        return number;
    }

public:
    SortingSystem(bool is_string, ifstream &inFile);
    ~SortingSystem();

    void insertionSort();
    void selectionSort();
    void bubbleSort();
    void shellSort();
    void mergeSort(int left, int right); 
    void quickSort(int left, int right);
    
    template <typename U = T>
    typename std::enable_if<std::is_integral<U>::value>::type
    countSort();

    template <typename U = T>
    typename std::enable_if<std::is_integral<U>::value>::type
    radixSort();

    template <typename U = T>
    typename std::enable_if<std::is_integral<U>::value>::type
    bucketSort();
    
    template <typename U = T>
    typename std::enable_if<!std::is_integral<U>::value>::type
    countSort() { cout << "Count Sort is not available for this type.\n"; }

    template <typename U = T>
    typename std::enable_if<!std::is_integral<U>::value>::type
    radixSort() { cout << "Radix Sort is not available for this type.\n"; }

    template <typename U = T>
    typename std::enable_if<!std::is_integral<U>::value>::type
    bucketSort() { cout << "Bucket Sort is not available for this type.\n"; }

    void displayData();

    void showMenu(); 
};

template<typename T>
SortingSystem<T>::SortingSystem(bool is_str, ifstream& inFile): file(inFile) {
    this->size = getNumberFromFile("Enter the size of the array: ");
    data = new T[size];
    cout << "\nEnter the element of the array space separated: ";
    for (int i = 0; i < size; ++i) {
        if (!(file >> data[i])) {
            cerr << "Error: couldn't read element " << i + 1 << " from file." << endl;
            exit(1);
        }
    }
    cout << endl;
}

template<typename T>
SortingSystem<T>::~SortingSystem() {
    delete[] data;
}

template <typename T>
void SortingSystem<T>::insertionSort() {
    for (int i = 0; i < size; i++) {
        T temp = data[i];
        int j = i - 1;
        for (; j >= 0; j--) {
            if (temp < data[j]) {
                data[j + 1] = data[j];
            }
            else break;
        }
        data[j+1] = temp;
        this->displayData();
    }
}

template<typename T>
void SortingSystem<T>::selectionSort() {
    for (int i = 0; i < size; i++) {
        T mini = data[i];
        int pos = i;
        for (int j = i; j < size; j++) {
            if (data[j] < mini) {
                mini = data[j];
                pos = j;
            }
        }
        swap(data[i], data[pos]);
        this->displayData();
    }
}

template<typename T>
void SortingSystem<T>::bubbleSort() {
     for (int i = 0; i < size; i++) {
        for (int j = 1; j < size - i; j++) {
            if (data[j] < data[j - 1]) {
                swap(data[j], data[j - 1]);
                this->displayData();
            }

        }
    }
}

template<typename T>
void SortingSystem<T>::shellSort() {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            T temp = data[i];
            int j;
            for (j = i; j >= gap && data[j - gap] > temp; j -= gap) {
                data[j] = data[j - gap];
            }
            data[j] = temp;
            this->displayData();
        }
    }
}

template<typename T>
void SortingSystem<T>::mergeSort(int left, int right) {
    if (left >= right) {
        return;
    }
    int middle = (left + right) / 2;
    mergeSort(left, middle);
    mergeSort(middle + 1, right);
    merge(left, right);
    displayData();
}

template<typename T>
void SortingSystem<T>::quickSort(int left, int right) {
     if (left < right) {
         int pivot = partition(left, right);
         cout << "Current Pivot : " << pivot << endl;
         displayData();
        quickSort(left, pivot - 1);
        quickSort(pivot + 1, right);
    }
}
template <typename T>
template <typename U>
typename std::enable_if<std::is_integral<U>::value>::type
SortingSystem<T>::countSort() {
    if constexpr (!std::is_integral_v<T>) {
        static_assert(std::is_integral_v<T>, "countSort() is only available for integral types.");
    }
    int k = INT_MIN;
    for (int i = 0; i < size; i++) k = max(k, data[i]);
    int pre[k + 1] {}, result[k + 1] {};
    for (int i = 0; i < size; i++) pre[data[i]]++;
    // cummulative to know the order of each element
    for (int i = 1; i <= k; i++) pre[i] += pre[i - 1];
    for (int i = size - 1; i >= 0; i--) {
        // -1 to acsses the right position (zero based)
        result[--pre[data[i]]] = data[i];
    }
    for (int i = 0; i < k; i++) cout << result[i] << ' ';
    cout << endl;
}
template <typename T>
template <typename U>
typename std::enable_if<std::is_integral<U>::value>::type
SortingSystem<T>::radixSort() {
    if constexpr (!std::is_integral_v<T>) {
        static_assert(std::is_integral_v<T>, "");
    }
    int max_digits = 0;
    {
        int temp = *max_element(data, data + size);
        max_digits = (temp == 0) ? 1 : log10(temp) + 1;
    }
    for (int i = 0, mod = 1; i < max_digits; i++) {
        okasha::queue bins[10]{};
        for (int j = 0; j < size; j++) {
            bins[data[j] % (10 * mod) / mod].push(data[j]);
        }
        int current = 0;
        for (auto& bin : bins) {
            while (!bin.empty()) {
                data[current++] = bin.pop();
            }
            this->displayData();
        }
        mod *= 10;
    }
}

template <typename T>
template <typename U>
typename std::enable_if<std::is_integral<U>::value>::type
SortingSystem<T>::bucketSort() {
    if constexpr (!std::is_integral_v<T>) {
        static_assert(std::is_integral_v<T>, "");
    }
    // computing number of buckets and bucket width
    int k = ceil(log2(size)); // number of buckets
    int mini = INT_MAX, maxi = INT_MIN;
    for (int i = 0; i < size; i++) {
        mini = min(mini, data[i]);
        maxi = max(maxi, data[i]);
    }
    int bucket_width = (maxi - mini) / k;

    // filling the buckets
    okasha::bucket buckets[k];
    for (int i = 0; i < size; i++) {
        int position = (data[i] - mini) / (bucket_width+1);
        buckets[position].push(data[i]);
    }

    // moving the sorted buckets into the original array
    int index = 0;
    for (auto& b : buckets) {
        int* temp = b.sort_data();
        for (int i = 0; i < b.size(); i++) {
            data[index++] = temp[i];
        }
        this->displayData();
    }
}

template <typename T>
void SortingSystem<T>::merge(int left, int right) {
    int middle = (left + right) / 2;
    int n1 = middle - left + 1, n2 = right - middle;
    T v1[n1], v2[n2];
    for (int i = left, j = 0; i <= middle; i++,j++) v1[j] = data[i];
    for (int i = middle + 1, j = 0; i <= right; i++, j++) v2[j] = data[i];


    int l = 0, r = 0, org = left;
    while (l < n1 && r < n2) {
        if (v1[l] < v2[r]) {
            data[org++] = v1[l++];
        }
        else {
            data[org++] = v2[r++];
        }
    }

    while (l < n1) data[org++] = v1[l++];
    while (r < n2) data[org++] = v2[r++];
}

template<typename T>
int SortingSystem<T>::partition(int low, int high){
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<int> dist(low, high);
    int pivot = dist(gen);
    swap(data[pivot], data[low]);
    int i = low, j = low + 1;
    while (j <= high) {
        if (data[j] < data[low]) {
            swap(data[++i], data[j]);
        }
        j++;
    }
    swap(data[i], data[low]);
    return i;
}

template<typename T>
void SortingSystem<T>::displayData() {
    cout << "current data: ";
    for (int i = 0; i < this->size; i++) cout << data[i] << ' ';
    cout << endl;
}

template<typename T>
void SortingSystem<T>::measureSortTime(void(SortingSystem::* sortFunc)()) {
    auto start = high_resolution_clock::now();  
    (this->*sortFunc)(); 
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken: " << duration.count() << " ms" << endl;
}

template<typename T>
void SortingSystem<T>::measureSortTime(void(SortingSystem::* sortFunc)(int, int)) {
    auto start = high_resolution_clock::now();
    (this->*sortFunc)(0,size-1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken: " << duration.count() << " ms" << endl;
}

template<typename T>
void SortingSystem<T>::showMenu() {
    cout << "1:Insertion Sort\n";
    cout << "2:Selection Sort\n";
    cout << "3:Bubble Sort\n";
    cout << "4:Shell Sort\n";
    cout << "5:Merge Sort\n";
    cout << "6:Quick Sort\n";
    this->is_string || cout << "7:Count Sort\n";
    this->is_string || cout << "8:Radix Sort\n";
    this->is_string || cout << "9:Bucket Sort\n";
    bool invalid_choice = true;
    while (invalid_choice) {
        invalid_choice = false;
        int choice = getNumberFromUser("Please Select a sorting algorithm (1:9)\n");
        switch (choice)
        {
        case 1:
            measureSortTime(this->insertionSort);
            break;
        case 2:
            measureSortTime(this->selectionSort);
            break;
        case 3:
            measureSortTime(this->bubbleSort);
            break;
        case 4:
            measureSortTime(this->shellSort);
            break;
        case 5:
            measureSortTime(this->mergeSort);
            this->displayData();
            break;
        case 6:
            measureSortTime(this->quickSort);
            this->displayData();
            break;
        case (7):
            measureSortTime(this->countSort);
            break;
        case (8):
            measureSortTime(this->radixSort);
            break;
        case (9):
            measureSortTime(this->bucketSort);
            break;
        default:
            invalid_choice = true;
        }
    }
}


#endif