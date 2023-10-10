pair < pt, pt >  closest_points ( vector< pt > v ) {
  sort( v.begin(), v.end() );
  pair< pt, pt > ans;
  lf d2 = INF;

  function< void( int, int ) > solve = [&]( int l, int r ) {
    if( l == r ) return;

    int mid = ( l + r ) / 2;
    lf x_mid = v[mid].x;
    solve( l, mid );
    solve( mid + 1, r );

    vector< pt > aux;
    int p1 = l, p2 = mid + 1;
    while ( p1 <= mid && p2 <= r ) {
      if( v[p1].y < v[p2].y ) aux.push_back( v[p1++] );
      else aux.push_back( v[p2++] );
    }
    while( p1 <= mid ) aux.push_back( v[p1++] );
    while( p2 <= r ) aux.push_back( v[p2++] );

    vector < pt > nb;
    for( int i = l; i <= r; ++ i ) {
      v[i] = aux[i-l];
      lf dx = ( x_mid - v[i].x );
      if( dx * dx < d2 )
        nb.push_back( v[i] );
    }

    for( int i = 0; i < (int) nb.size(); ++ i ) {
      for( int k = i + 1; k < (int) nb.size(); ++ k ) {
        lf dy = ( nb[k].y - nb[i].y );
        if( dy * dy > d2 ) break;
        lf nd2 = dis2( nb[i], nb[k] );
        if( nd2 < d2 ) d2 = nd2, ans = {nb[i], nb[k]};
      }
    }
  };
  solve( 0, v.size() -1 );
  return ans;
}
