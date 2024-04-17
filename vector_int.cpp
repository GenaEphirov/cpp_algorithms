#include <iostream>
#include <string>

class My_vector {
private:
    int capacity = 8;
    int size_ = 0;
    int* list = new int[capacity];

    void expand() {
        capacity *= 2;
        int* new_list = new int[capacity];
        for (int i = 0; i < size_; ++i) {
            new_list[i] = list[i];
        }
        delete[] list;
        
        list = new_list;
    }

    void collapse() {
        capacity /= 2;
        int* new_list = new int[capacity];
        for (int i = 0; i < size_; ++i) {
            new_list[i] = list[i];
        }
        delete[] list;
        
        list = new_list;
    }

public:
    int get(int pos) {
        if (0 <= pos && pos < size_) {
            return list[pos];
        } else {
            return '?';
        }
    }

    int size() {return size_;}

    void push_back(int value) {
        int i = size_;
        list[i] = value;
        ++size_;

        if (size_ >= capacity) {
            expand();
        }
    }

    int pop_back() {
        if (size_ == 0) {
            return '?';
        }
        --size_;
        if (size_ < capacity/4) {
            collapse();
        }
        return list[size_];
    }
};
std::ostream &operator<<(std::ostream &os, My_vector& m) { 
    std::string output = "[";
    for (int i = 0; i < m.size(); ++i){
        int elem = m.get(i);
        output += std::to_string(elem);
        if (i+1 != m.size()) {
            output += ", ";
        }
    }
    return os << output + "]"; 
}

int main(){
    My_vector test_vector;
    for (int i = 0; i < 100; ++i) {
        test_vector.push_back(i);
    }
    for (int i = 0; i < 50; ++i) {
        test_vector.pop_back();
    }
    std::cout << test_vector << "\n";
    std::cout << test_vector.get(49) << "\n";

    int wait;
    std::cin >> wait;
    return 0;
}
