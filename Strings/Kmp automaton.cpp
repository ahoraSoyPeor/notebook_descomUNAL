/// Complexity: O(|N|*alphabet)
/// Tested: not yet
const int alpha = 256;
vector<vector<int>> kmp_automaton(string &t) {
  vector<vector<int>> aut( t.size() + 1, vector<int> ( alpha ) );
  aut[0][ t[0] ] = 1;
  for(int i = 1, j = 0; i <= t.size(); ++i) {
    aut[i] = aut[j];
    if(i < t.size()) {
      aut[i][ t[i] ] = i+1;
      j = aut[j][ t[i] ];
    }
  }
  return aut;
}
