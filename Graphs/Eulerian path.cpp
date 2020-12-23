/// Complexity: O(|N|)
/// Tested: https://tinyurl.com/y85t8e83
struct edge {
  int v; //list<edge>::iterator rev;
  edge(int v) : v(v) {}
};
void add_edge(int a, int b) {
  g[a].push_front(edge(b)); // auto ia = g[a].begin();
	g[b].push_front(edge(a)); // auto ib = g[b].begin();
	//ia->rev=ib; ib->rev=ia;
}
/// for undirected uncomment and check for path existance
bool eulerian(vector<int> &tour) { /// directed graph
  int one_in = 0, one_out = 0, start = -1;
  bool ok = true;
  for (int i = 0; i < n; i++) {
    if(out[i] && start == -1) start = i;
    if(out[i] - in[i] == 1) one_out++, start = i;
    else if(in[i] - out[i] == 1) one_in++;
    else ok &= in[i] == out[i];
  }
  ok &= one_in == one_out && one_in <= 1;
  if (ok) {
    function<void(int)> go = [&](int u) {
      while(g[u].size()) {
        int v = g[u].front().v;
        g[v].erase(g[u].front().rev);
        g[u].pop_front();
        go(v, tour);
      }
      tour.push_back(u);
    };
    go(start);
    reverse(tour.begin(), tour.end());
    if(tour.size() == edges + 1) return true;
  }
  return false;
}
