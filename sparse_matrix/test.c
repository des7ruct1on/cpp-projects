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
    sparse_matrix<double> A(1, 3);
    sparse_matrix<double> B(3, 1);
    A.add(1, 0, 0);
    A.add(7, 1, 0);
    A.add(4, 2, 0);

    B.add(1, 0, 0);
    B.add(7, 0, 1);
    B.add(4, 0, 2);
    
    //B.add(4, 2, 2);

    A.print();
    cout << endl;
    B.print();
    B.multiply(A);
    sparse_matrix<double> C(B);
    cout << endl;
    C.print();


}
