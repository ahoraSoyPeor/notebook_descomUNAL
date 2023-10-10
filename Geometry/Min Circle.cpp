Circle min_circle( vector< pt > v ) {
  random_shuffle( v.begin(), v.end() );
  auto f2 = [&]( int a, int b ){
    Circle ans( v[a], v[b] );
    for( int i = 0; i < a; ++ i )
      if( ans.contains( v[i] ) == OUT )
        ans = Circle( v[i], v[a], v[b] );
    return ans;
  };

  auto f1 = [&]( int a ){
    Circle ans( v[a], 0.0L );
    for( int i = 0; i < a; ++ i )
      if( ans.contains( v[i] ) == OUT )
        ans = f2( i, a );
    return ans;
  };

  Circle ans( v[0], 0.0L );
  for( int i = 1; i < (int) v.size(); ++ i )
    if( ans.contains( v[i] ) == OUT )
      ans = f1( i );

  return ans;
}
