/// Complexity: O(|N|*alphabet)
/// Tested: not yet
const int alpha = 256;
int aut[N][alpha];
void kmp_automaton(string &t) {
  aut[0][ t[0] ] = 1;
  for(int i = 1, j = 0; i <= t.size(); ++i) {
    for(int c = 0; c < alpha; ++c) aut[i][c] = aut[j][c];
    if(i < t.size()) {
      aut[i][ t[i] ] = i+1;
      j = aut[j][ t[i] ];
    }
  }
}