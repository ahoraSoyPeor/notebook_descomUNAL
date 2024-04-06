mt19937 / mt19937_64 
rng(chrono::steady_clock::now().
                time_since_epoch().count())
shuffle(permutation.begin(), permutation.end(), rng)
uniform_int_distribution<T> / uniform_real_distribution<T> dis(fr, to);
dis(rng)