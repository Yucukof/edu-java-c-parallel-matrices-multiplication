rm -r log
mkdir -p log
make clean
make
./build/matrix_multiplication error 0 DEBUG > log/error.log
./build/matrix_multiplication missing 0 DEBUG > log/missing.log
./build/matrix_multiplication mismatch 0 DEBUG > log/mismatch.log

./build/matrix_multiplication rectangular 0 > log/sample-sequential.log
./build/matrix_multiplication rectangular 1 > log/sample-parallel.log

./build/matrix_multiplication simple 0 > log/simple-sequential.log
./build/matrix_multiplication simple 1 > log/simple-parallel.log

./build/matrix_multiplication medium 0 > log/medium-sequential.log
./build/matrix_multiplication medium 1 > log/medium-parallel.log

./build/matrix_multiplication large 0 > log/large-sequential.log
./build/matrix_multiplication large 1 > log/large-parallel.log

./build/matrix_multiplication humongous 0 > log/humongous-sequential.log
./build/matrix_multiplication humongous 1 > log/humongous-parallel.log

./build/matrix_multiplication gigantic 0 > log/gigantic-sequential.log
./build/matrix_multiplication gigantic 1 > log/gigantic-parallel.log

./build/matrix_multiplication nightmarish 0 > log/nightmarish-sequential.log
./build/matrix_multiplication nightmarish 1 > log/nightmarish-parallel.log
