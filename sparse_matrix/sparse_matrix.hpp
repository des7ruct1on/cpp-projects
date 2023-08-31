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
    // linear search
    T search_elem(pair<int, int> elem) {
        for (size_t i = 0; i < indexes.size(); ++i) {
            if (indexes[i].first == elem.first && indexes[i].second == elem.second) {
                return values[i];
            }
        }
        throw runtime_error("Element not found");
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
        auto pr = make_pair(i, j);
        values.push_back(val);
        indexes.push_back(pr);
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
                //index_left++;
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
    // multiply functions
    void multiply(const sparse_matrix & A) {
        if (_columns != A._rows) {
            throw runtime_error("Can`t be solved!");
        }

        vector<T> _values;
        vector<pair<int, int> > _indexes;
        // res size
        int size_col_res = A._columns;
        int size_row_res = _rows;

        int need_col = 0;
        int need_row = 0;

        int i = 0;

        bool _next = false;

        while (true) {
            if (i == values.size() && need_col == A._columns) {
                break;
            }

            if (need_col == A._columns) {
                need_col = 0;
                need_row++;
                i = 0;
            }

            if (_next) {
                i = 0;
                _next = false;
            }

            int _val1 = values[i];
            int _row1 = indexes[i].first;
            int _col1 = indexes[i].second;

            if (_row1 != need_row) {
                i++;
                continue;
            }

            int _val2, _row2, _col2, _res_col;

            static int mult = 0;
            
            int _size = A.values.size();
            for (int j = 0; j < _size; j++) {
                _val2 = A.values[j];
                _row2 = A.indexes[j].first;
                _col2 = A.indexes[j].second;

                if (_col2 == need_col && _col1 == _row2) {
                    mult += _val1 * _val2;
                    _res_col = _col2;
                    break;
                }
            }

            int tmp_row = indexes[i + 1].first;

            if (tmp_row != _row1 || i == values.size() - 1) {
                if (mult != 0) {
                    auto pr = make_pair(_row1, _res_col);
                    _values.push_back(mult);
                    _indexes.push_back(pr);
                }

                need_col++;
                _next = true;
                mult = 0;
            }
            i++;
        }

        values.clear();
        indexes.clear();
        values = _values;
        indexes = _indexes;
        _columns = size_col_res;
        _rows = size_row_res;
        _size = _columns * _rows;

        
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
    // operator *
    sparse_matrix& operator*(const sparse_matrix & A) {
        if (_columns != A._rows) {
            throw runtime_error("Can`t be solved!");
        }

        vector<T> _values;
        vector<pair<int, int> > _indexes;
        // res size
        int size_col_res = A._columns;
        int size_row_res = _rows;

        int need_col = 0;
        int need_row = 0;

        int i = 0;

        bool _next = false;

        while (true) {
            if (i == values.size() && need_col == A._columns) {
                break;
            }

            if (need_col == A._columns) {
                need_col = 0;
                need_row++;
                i = 0;
            }

            if (_next) {
                i = 0;
                _next = false;
            }

            int _val1 = values[i];
            int _row1 = indexes[i].first;
            int _col1 = indexes[i].second;

            if (_row1 != need_row) {
                i++;
                continue;
            }

            int _val2, _row2, _col2, _res_col;

            static int mult = 0;
            
            int _size = A.values.size();
            for (int j = 0; j < _size; j++) {
                _val2 = A.values[j];
                _row2 = A.indexes[j].first;
                _col2 = A.indexes[j].second;

                if (_col2 == need_col && _col1 == _row2) {
                    mult += _val1 * _val2;
                    _res_col = _col2;
                    break;
                }
            }

            int tmp_row = indexes[i + 1].first;

            if (tmp_row != _row1 || i == values.size() - 1) {
                if (mult != 0) {
                    auto pr = make_pair(_row1, _res_col);
                    _values.push_back(mult);
                    _indexes.push_back(pr);
                }

                need_col++;
                _next = true;
                mult = 0;
            }
            i++;
        }

        values.clear();
        indexes.clear();
        values = _values;
        indexes = _indexes;
        _columns = size_col_res;
        _rows = size_row_res;
        _size = _columns * _rows;

        return *this;
    }

    // destructor
    ~sparse_matrix() = default;



};
