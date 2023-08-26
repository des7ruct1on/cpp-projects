#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>

class sparse_matrix {
    vector<T> values;
    vector<pair<int, int>> indexes; // pair = row_ind, col_ind
    int columns;
    int rows;
    int size;
    T search_elem(pair<int, int> elem) {
        if (size == 0) {
            throw runtime_error("Matrix is empty");
        }
        int index = 0;
        bool found = false;
        for (auto i = indexes.begin(); i != indexes.end(); ++i) {
            if (*i == elem) {
                found = true;
                break;
            }
            index++;
        }
        if (found) {
            return values[index];
        } else {
            throw runtime_error("Element not found");
        }
    }
public:
    // constructor
    sparse_matrix(int size_col, int size_row) {
        columns = size_col;
        rows = size_row;
        size = size_col * size_row;
    }
    // copy-constructor
    sparse_matrix(const sparse_matrix & A) {
        columns = A.columns;
        rows = A.rows;
        indexes = A.indexes;
        values = A.values;
        size = A.size;
    }
    // operator =
    sparse_matrix& operator=(const sparse_matrix & A) {
        if (this != &A) {
            columns = A.columns;
            rows = A.rows;
            indexes = A.indexes;
            values = A.values;
            size = A.size;
        } 
        return *this;
    }
    // getting values & indexes
    T get_value(int ind) {
        return values[ind];
    }
    int get_size_rows() {
        return rows;
    }
    int get_size_cols() {
        return columns;
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
        return size;
    }

    // printing
    void print() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
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
    // destructor
    ~sparse_matrix() = default;



};
