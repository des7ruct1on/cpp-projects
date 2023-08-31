# sparse matrix
In this programm i realize a sparse matrix class on c++ lang 
> `private`
>- vector values - vector of not-null elements values
>- vector indexes - vector of not-null elements indexes
>- _columns - amount of columns
>- _rows - amount of rows
>- T search_elem - linear function of finding selected element

> `public`
>- sparse_matrix(int size_col, int size_row) - constructor
>- sparse_matrix(const sparse_matrix & A) - copy-constructor
>- sparse_matrix& operator=(const sparse_matrix & A) - operator '='
>- T get_value(int ind) - function to get value
>- int get_size_rows() - function to get size of rows
>- int get_size_cols() - function to get size of columns
>- pair<int, int> get_index(int ind) - function to get an index value from vector
>- int count() - function to get size of values vector
>- int size() - function to get size of vector(including zero`s)
>- void print() - function to print a sparse matrix in regular view
>- void add(T val, int i, int j) - function to add a value to the matrix
>- void remove_value(T val) - function to remove element from matrix
>- void plus(sparse_matrix& A) - function to summarise two sparse matrixes
>- void minus(sparse_matrix& A) - function to minus two matrixes 
>- void multiply(sparse_matrix& A) - function to multiply two matrixes
>- sparse_matrix& operator+(const sparse_matrix & A) - operator '+'
>- sparse_matrix& operator-(const sparse_matrix & A) - operator '-'
>- sparse_matrix& operator*(const sparse_matrix & A) - operator '*'
>- ~sparse_matrix() - destructor