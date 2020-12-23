/// Complexity: O(|N|^2)
/// Tested: https://tinyurl.com/y23sh38k
vector<lf> X, F;
lf f(lf x) {
  lf answer = 0;
  for(int i = 0; i < (int)X.size(); i++) {
    lf prod = F[i];
    for(int j = 0; j < (int)X.size(); j++) {
      if(i == j) continue;
      prod = mul(prod, divide(sub(x, X[j]), sub(X[i], X[j])));
    }
    answer = add(answer, prod);
  }
  return answer;
}
