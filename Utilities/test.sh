g++ -std=c++17 gen.cpp -o gen
for((i = 0; ;++i));do
  echo $i
  ./gen $i > int
done
