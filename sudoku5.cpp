// Riva Syafri Rachmatullah
// 13512036

#include <iostream>
#include <ctime>
#include <cstdio>

using namespace std;

// Konstanta
#define M 25
#define N 5

// Tipe Bentukan
typedef struct {
	int matrix[M][M];
	bool boolean[M][M];
} SUDOKU;

// Kamus Global
SUDOKU BS;
bool possible = true;
int test = 0;

// Header Prosedur dan Fungsi
void readinput();
// I.S.		: Bebas
// Proses	: Membaca input dari file eksternal
// F.S.		: BS berisi soal sudoku yang ingin diselesaikan

void printsudoku();
// I.S.		: BS terdefinisi tidak kosong
// Proses	: Menampilkan sudoku di layar
// F.S.		: Futoshiki ditampilkan di layar

void solve();
// I.S.		: BS terdefinisi tidak kosong
// Proses	: Mengisi sudoku sesuai kriteria
// F.S.		: BS terjawab atau tidak bisa dikerjakan

bool validation(int i, int j);
// I.S.		: BS, i, dan j terdefinisi tidak kosong
// Proses	: Mencari kembali checkpoint yang bisa diubah, jika bisa akan meng-increment
//			  angka pada checkpoint sekaligus mengubah angka pada checkpoint yang dilewati
//			  menjadi 0. apabila gagal hingga awal maka possible pun berubah
// F.S.		: BS terjawab atau tidak bisa dikerjakan

bool boxvalidation(int i, int j);
// Memberikan hasil boolean true or false terhadap tanda 'lebih dari' atau 'kurang dari'

// Program Utama
int main() {
	// Kamus Lokal	
	bool possible = true;
	clock_t t1, t2;

	// Algoritma
	cout << "Question\t:\n" << endl;
	readinput();
	cout << "Answer\t\t:\n" << endl;
	t1 = clock();
	solve();
	t2 = clock();
	if (possible) {
		printsudoku();
		cout << "waktu : " << (t2-t1) << " ms" << endl;
		cout << "jumlah pengerjaan : " << test << " kali" << endl;
	} else
		cout << "Can't be solved";
	return 0;
}

// Realisasi Prosedur dan Fungsi
void readinput() {
	// Kamus Lokal
	int i, j;

	// Algoritma
	for (i = 0; i < M; i++) {
		for (j = 0; j < M; j++) {
			cin >> BS.matrix[i][j];	
			if (BS.matrix[i][j] == 0)
				BS.boolean[i][j] = true;
			else
				BS.boolean[i][j] = false;
		}
	}
	printsudoku();
}

void printsudoku() {
	// Kamus Lokal
	int i, j, k;
	FILE *f;

	// Algoritma
	for (i = 0; i < M; i++) {
		for (j = 0; j < M; j++) {
			printf("%c ",BS.matrix[i][j]+64);
			if (((j+1)%N == 0) && (j != M-1))
				cout << "| ";
		}
		cout << endl;
		if (((i+1)%N == 0) && (i != M-1)) {
			for (k = 0; k < M; k++) {
				cout << "--";
				if (((k+1)%N == 0) && (k != M-1))
					cout << "--";
			}
			cout << endl;
		}
	}
	cout << endl;
}

void solve() {
	// Kamus Lokal
	int i, j;

	// Algoritma
	i = 0;
	while ((i < M) && (possible)) {
		j = 0;
		while ((j < M) && (possible)) {
			if (BS.boolean[i][j]) {
				// true apabila harus dicari
				do {
					BS.matrix[i][j]++;
					test++;
				} while ((BS.matrix[i][j] <= M) && (!validation(i,j)));
				if (BS.matrix[i][j] <= M)
					// lanjut ke kolom berikutnya
					j++;
				else {
					// kembali ke kolom sebelumnya
					BS.matrix[i][j] = 0;
					do {
						if (j != 0)
							j--;
						else if ((i != 0) && (j == 0)) {
							i--;
							j = M-1;
						}
					} while ((!BS.boolean[i][j]) && !((i == 0) && (j == 0)));
					if ((i == 0) && (j == 0) && (((BS.boolean[i][j]) && ((BS.matrix[i][j] == 0))) || (!BS.boolean[i][j])))
						// check apabila sudoku bisa dikerjakan atau tidak
						possible = false;
				}
			} else
				j++;
		}
		i++;
	}
}

bool validation(int i, int j) {
	// Kamus Lokal
	int k;
	bool row = true, column = true;

	// Algoritma
	k = 0;
	while ((k < M) && (column)) {
		// cek kolom
		if ((k != j) && ((BS.matrix[i][k] == BS.matrix[i][j])))
			column = false;
		else
			k++;
	}
	if (column) {
		// jika kolom sudah valid
		if (boxvalidation(i,j)) {
			k = 0;
			while ((k < M) && (row)) {
				// cek baris
				if ((k != i) && ((BS.matrix[k][j] == BS.matrix[i][j])))
					row = false;
				else
					k++;
			}
			return row;
		} else
			return false;
	} else
		return false;
}

bool boxvalidation(int i, int j) {
	// Kamus Lokal
	int k, l, m, n, boxcol, boxrow;
	bool valid = true;

	// Algoritma
	boxrow = i/N;
	boxcol = j/N;
	k = boxrow*N;
	m = k + N;
	while ((k < m) && valid) {
		l = boxcol*N;
		n = l + N;
		while ((l < n) && valid) {
			if ((BS.matrix[i][j] == BS.matrix[k][l]) && !((k == i) && (j == l)))
				valid = false;
			else {
				l++;
			}
		}
		k++;
	}
	return valid;
}
