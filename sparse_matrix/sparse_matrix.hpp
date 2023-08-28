#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>

class sparse_matrix {
    vector<T> values;
    vector<pair<int, int> > indexes; // pair = row_ind, col_ind
    int _columns;
    int _rows;
    int _size;
    // binary search
    T search_elem(pair<int, int> elem) {
        if (_size == 0) {
            throw runtime_error("Matrix is empty");
        }
        int left = 0;
        int right = indexes.size() - 1;
        int mid;
        bool found = false;
        while(left <= right) {
            mid = (right + left) / 2;
            if (indexes[mid].first == elem.first && indexes[mid].second == elem.second)  {
                found = true;
                break;
            } else if (indexes[mid].first < elem.first) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        if (found) {
            return values[mid];
        } else {
            throw runtime_error("Element not found");
        }
    }
public:
    // constructor
    sparse_matrix(int size_col, int size_row) {
        _columns = size_col;
        _rows = size_row;
        _size = size_col * size_row;
    }
    // copy-constructor
    sparse_matrix(const sparse_matrix & A) {
        _columns = A._columns;
        _rows = A._rows;
        indexes = A.indexes;
        values = A.values;
        _size = A._size;
    }
    // operator =
    sparse_matrix& operator=(const sparse_matrix & A) {
        if (this != &A) {
            _columns = A._columns;
            _rows = A._rows;
            indexes = A.indexes;
            values = A.values;
            _size = A._size;
        } 
        return *this;
    }
    // getting values & indexes
    T get_value(int ind) {
        return values[ind];
    }
    int get_size_rows() {
        return _rows;
    }
    int get_size_cols() {
        return _columns;
    }
    pair<int, int> get_index(int ind) {
        return indexes[ind];
    }
    // getting size of not null elements
    int count() {
        return values.size();
    }

    // getting size of all elements
    int size() {
        return _size;
    }

    // printing
    void print() {
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _columns; j++) {
                auto tmp = make_pair(i, j);
                try {
                    T elem = search_elem(tmp);
                    cout << elem << " ";

                } catch(...) {
                    cout << "0 ";
                }
            }
            cout << "\n";
        }
    }
    // addition
    void add(T val, int i, int j) {
        values.push_back(val);
        indexes.push_back(make_pair(i, j));
    }
    // removing element
    void remove_value(T val) {
        auto ind_iter = indexes.begin();
        auto val_iter = values.begin();
        while (val_iter != values.end()) {
            if (*val_iter == val) {
                val_iter = values.erase(val_iter);
                ind_iter = indexes.erase(ind_iter);
            } else {
                ++val_iter;
                ++ind_iter;
            }
        }
    }
    // add values from matrix
    void plus(sparse_matrix& A) {
        if (_columns != A._columns && _rows != A._rows) {
            throw runtime_error("Can`t be solved!");
        }
        int index_left = 0;
        int index_right = 0;
        while (index_left < indexes.size() && index_right < A.indexes.size()) {
            auto left = indexes[index_left];
            auto right = A.indexes[index_right];

            if (left.first == right.first && left.second == right.second) {
                values[index_left] += A.values[index_right];
                index_left++;
                index_right++;
            } else if (left.first < right.first || (left.first == right.first && left.second < right.second)) {
                index_left++;
            } else if (left.first > right.first || (left.first == right.first && left.second > right.second)) {
                values.insert(values.begin() + index_left, A.values[index_right]);
                indexes.insert(indexes.begin() + index_left, right);
                index_left++;
                index_right++;
            }
        }

        while (index_right < A.indexes.size()) {
            values.push_back(A.values[index_right]);
            indexes.push_back(A.indexes[index_right]);
            index_right++;
        }
    }

    void minus(sparse_matrix& A) {
        if (_columns != A._columns && _rows != A._rows) {
            throw runtime_error("Can`t be solved!");
        }
        int index_left = 0;
        int index_right = 0;
        while (index_left < indexes.size() && index_right < A.indexes.size()) {
            auto left = indexes[index_left];
            auto right = A.indexes[index_right];

            if (left.first == right.first && left.second == right.second) {
                values[index_left] -= A.values[index_right];
                index_left++;
                index_right++;
            } else if (left.first < right.first || (left.first == right.first && left.second < right.second)) {
                index_left++;
            } else if (left.first > right.first || (left.first == right.first && left.second > right.second)) {
                values.insert(values.begin() + index_left, -A.values[index_right]);
                indexes.insert(indexes.begin() + index_left, right);
                index_left++;
                index_right++;
            }
        }

        while (index_right < A.indexes.size()) {
            values.push_back(-A.values[index_right]);
            indexes.push_back(A.indexes[index_right]);
            index_right++;
        }
    }
    // operator +
    sparse_matrix& operator+(const sparse_matrix & A) {
        if (_columns != A._columns && _rows != A._rows) {
            throw runtime_error("Can`t be solved!");
        }
        int index_left = 0;
        int index_right = 0;
        while (index_left < indexes.size() && index_right < A.indexes.size()) {
            auto left = indexes[index_left];
            auto right = A.indexes[index_right];

            if (left.first == right.first && left.second == right.second) {
                values[index_left] += A.values[index_right];
                index_left++;
                index_right++;
            } else if (left.first < right.first || (left.first == right.first && left.second < right.second)) {
                index_left++;
            } else if (left.first > right.first || (left.first == right.first && left.second > right.second)) {
                values.insert(values.begin() + index_left, A.values[index_right]);
                indexes.insert(indexes.begin() + index_left, right);
                index_left++;
                index_right++;
            }
        }

        while (index_right < A.indexes.size()) {
            values.push_back(A.values[index_right]);
            indexes.push_back(A.indexes[index_right]);
            index_right++;
        }
        return *this;
    }
    // operator -
    sparse_matrix& operator-(const sparse_matrix & A) {
        if (_columns != A._columns && _rows != A._rows) {
            throw runtime_error("Can`t be solved!");
        }
        int index_left = 0;
        int index_right = 0;
        while (index_left < indexes.size() && index_right < A.indexes.size()) {
            auto left = indexes[index_left];
            auto right = A.indexes[index_right];

            if (left.first == right.first && left.second == right.second) {
                values[index_left] -= A.values[index_right];
                index_left++;
                index_right++;
            } else if (left.first < right.first || (left.first == right.first && left.second < right.second)) {
                index_left++;
            } else if (left.first > right.first || (left.first == right.first && left.second > right.second)) {
                values.insert(values.begin() + index_left, -A.values[index_right]);
                indexes.insert(indexes.begin() + index_left, right);
                index_left++;
                index_right++;
            }
        }

        while (index_right < A.indexes.size()) {
            values.push_back(-A.values[index_right]);
            indexes.push_back(A.indexes[index_right]);
            index_right++;
        }
        return *this;
    }

    // destructor
    ~sparse_matrix() = default;



};
