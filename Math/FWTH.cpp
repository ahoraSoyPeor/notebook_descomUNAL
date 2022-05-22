//Haddamard-Transform
vector< long long > haddamard( vector< long long > a, bool inverse )
{
  int n = (int) a.size();

  for( int k = 1; k < n; k <<= 1 )
  {
    for( int i = 0; i < n; i += 2 * k )
    {
      for( int j = 0; j < k; ++ j )
      {
        long long u = a[i+j], v = a[i+j+k];
        a[i+j] = u + v;
        a[i+j+k] = u - v;
      }
    }

    if( inverse )
      for( auto &x : a )
        x >>= 1;
  }
  return a;
}

//XOR convolution, |A| = |B| = power of two
vector< long long > FWHT( vector< long long > a, vector< long long > b )
{
  auto h_a = haddamard( a, false ), h_b = haddamard( b, false );

  vector< long long > h_c( a.size() );
  for( int i = 0; i < (int) a.size(); ++ i )
    h_c[i] = 1LL * h_a[i] * h_b[i];

  return haddamard( h_c, true );
}
