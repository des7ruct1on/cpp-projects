#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <sstream>
#include <typeinfo>
#include "sparse_matrix.hpp"


using namespace std;
int main() {
    sparse_matrix<double> A(5, 5);
    sparse_matrix<double> B(5, 5);
    A.add(1, 0, 0);
    A.add(2, 1, 1);
    A.add(3, 2, 2);
    A.add(4, 3, 3);
    A.add(5, 4, 4);

    B.add(1, 0, 1);
    B.add(2, 1, 2);
    B.add(4, 2, 2);
    B.add(3, 3, 1);
    //B.add(4, 2, 2);

    A.print();
    cout << endl;
    B.print();
    sparse_matrix<double> C(5, 5);
    C = A + B;
    cout << endl;
    C.print();


}
