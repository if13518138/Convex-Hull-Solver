# Convex Hull Problem Solver
by : William

Merupakan suatu solver dari permasalahan convex hull dengan menggunakan algoritma brute force
Complexity : O(n^3)

## GETTING STARTED
Untuk menjalankan program ini, silahkan mengikuti langkah - langkah berikut:
1. Akses direktori bin
2. Jalankan program main yang telah dikompilasi sebelumnya
3. Masukkan jumlah titik yang diinginkan
4. Silahkan dicoba :)

## USAGE
### PREREQUISTED
1. Suatu terminal untuk menjalankan program (Powershell, CMD, linux terminal)
1. Telah tersedia modul matplotlib Python (untuk visualisasi convex hull)
### COMPILE PROGRAM:
Notes : Kompilasi Program dijalankan di komputer berbasis Linux yang telah terdapat Python 3.6 serta modul Matplotlib
        dijalankan pada komputer berbasis Linux (Linux Mint)
Langkah:
1. Akses direktori src
1. Ketik ```g++ main.cpp -I/usr/include/python2.7 -lpython2.7 -o main``` pada terminal untuk kompilasi dengan python 2 (python 2.7)
1. Ketik ```g++ main.cpp -I/usr/include/python3.6m -lpython3.6m -o main``` pada terminal untuk kompilasi dengan python 3 (python 3.6)
### EXECUTE PROGRAM (pada Linux OS):
1. Ketik ```./main``` pada terminal (setelah proses kompilasi)
2. Klik Enter untuk menjalankan 

DIBUAT DENGAN:
1. Program utama dibuat dengan C++ 11 (g++7.4.0)
2. Tampilan / Visualisasi dari convex hull menggunakan modul matplotlib-cpp dengan menggunakan versi Python 3.6.9

REFERENCE :
[Matplotlib-CPP](https://github.com/lava/matplotlib-cpp)
