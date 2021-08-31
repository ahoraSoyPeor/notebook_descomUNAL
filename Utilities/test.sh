for((i = 0; ;++i));do
  echo $i
  ./gen $i > int
  ./sol < int > out || break
  ./real < int > outr || break
  diff out outr || break
done
