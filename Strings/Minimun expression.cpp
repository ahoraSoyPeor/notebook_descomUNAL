/// Complexity: O(|N|)
/// Tested: https://tinyurl.com/y6gfzgsm
int minimum_expression(string s) {
  s = s+s;
  int len = s.size(), i = 0, j = 1, k = 0;
  while(i+k < len && j+k < len) {
    if(s[i+k] == s[j+k]) k++;
    else if(s[i+k] > s[j+k]) i = i+k+1, k = 0;
    else j = j+k+1, k = 0;
    if(i == j) j++;
  }
  return min(i, j);
}
