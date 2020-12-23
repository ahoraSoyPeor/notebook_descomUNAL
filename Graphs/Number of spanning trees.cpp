/// Tested: not yet
///A -> adjacency matrix
///It is necessary to compute the D-A matrix, where D is a diagonal matrix
///that contains the degree of each node.
///To compute the number of spanning trees it's necessary to compute any
///D-A cofactor
///C(i, j) = (-1)^(i+j) * Mij
///Where Mij is the matrix determinant after removing row i and column j
double mat[MAX][MAX];
///call determinant(n - 1)
double determinant(int n) {
  double det = 1.0;
  for(int k = 0; k < n; k++) {
    for(int i = k+1; i < n; i++) {
      assert(mat[k][k] != 0);
      long double factor = mat[i][k]/mat[k][k];
      for(int j = 0; j < n; j++) {
        mat[i][j] = mat[i][j] - factor*mat[k][j];
      }
    }
    det *= mat[k][k];
  }
  return round(det);
}
