// Declare number generator
mt19937 / mt19937_64 
rng(chrono::steady_clock::now().
                time_since_epoch().count())
// Use it to shuffle a vector
shuffle(permutation.begin(), permutation.end(), rng)
// Use it to generate a random number between [fr, to]
uniform_int_distribution<T> / uniform_real_distribution<T> dis(fr, to);
dis(rng)