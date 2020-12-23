/// Complexity: O(|text|+SUM(|pattern_i|)+matches)
/// Tested: https://tinyurl.com/y2zq594p
const static int alpha = 26;
int trie[N][alpha], fail[N], nodes;
void add(string &s, int i) {
  int cur = 0;
  for(char c : s) {
    int x = c-'a';
    if(!trie[cur][x]) trie[cur][x] = ++nodes;
    cur = trie[cur][x];
  }
  //cnt_word[cur]++;
  //end_word[cur] = i; // for i > 0
}
void build() {
  queue<int> q; q.push(0);
  while(q.size()) {
    int u = q.front(); q.pop();
    for(int i = 0; i < alpha; ++i) {
      int v = trie[u][i];
      if(!v) trie[u][i] = trie[ fail[u] ][i]; // construir automata
      else q.push(v);
      if(!u || !v) continue;
      fail[v] = trie[ fail[u] ][i];
      //fail_out[v] = end_word[ fail[v] ] ? fail[v] : fail_out[ fail[v] ];
      //cnt_word[v] += cnt_word[ fail[v] ]; // obtener informacion del fail_padre
    }
  }
}
