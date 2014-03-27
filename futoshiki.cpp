// Riva Syafri Rachmatullah
// 13512036

#include <iostream>
#include <time.h>

using namespace std;

// Konstanta
#define N 5
#define M 9

// Tipe Bentukan
typedef struct {
	int matrix[M][M];
	bool boolean[N][N];
} FUTOSHIKI;

// Kamus Global
FUTOSHIKI F;
bool possible = true;
int test = 0;

// Header Prosedur dan Fungsi
void readinput();
// I.S.		: Bebas
// Proses	: Membaca input dari file eksternal
// F.S.		: F berisi soal futoshiki yang ingin diselesaikan

void printfutoshiki();
// I.S.		: F terdefinisi tidak kosong
// Proses	: Menampilkan futoshiki di layar
// F.S.		: Futoshiki ditampilkan di layar

void solve();
// I.S.		: F terdefinisi tidak kosong
// Proses	: Mengisi futoshiki sesuai kriteria
// F.S.		: F terjawab atau tidak bisa dikerjakan

bool validation(int i, int j);
// I.S.		: F, i, dan j terdefinisi tidak kosong
// Proses	: Mencari kembali checkpoint yang bisa diubah, jika bisa akan meng-increment
//			  angka pada checkpoint sekaligus mengubah angka pada checkpoint yang dilewati
//			  menjadi 0. apabila gagal hingga awal maka possible pun berubah
// F.S.		: F terjawab atau tidak bisa dikerjakan

bool signvalidation(int i, int j);
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
		printfutoshiki();
		cout << "waktu : " << (t2-t1) << " ms\n" << endl;
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
			cin >> F.matrix[i][j];
			if ((F.matrix[i][j] == 0) && ((i%2) == 0) && ((j%2) == 0))
				F.boolean[i/2][j/2] = true;
			else if ((F.matrix[i][j] != 0) && ((i%2) == 0) && ((j%2) == 0))
				F.boolean[i/2][j/2] = false;
		}
	}
	printfutoshiki();
}

void printfutoshiki() {
	// Kamus Lokal
	int i, j;
	FILE *f;

	// Algoritma
	for (i = 0; i < M; i++) {
		for (j = 0; j < M; j++) {
			if (i%2 == 0) {
				switch (F.matrix[i][j]) {
					case -1	:	cout << "< ";
								break;
					case -2 :	cout << "> ";
								break;
					case -3 :	cout << "  ";
								break;
					default :	cout << F.matrix[i][j] << " ";
								break;
				}
			} else {
				switch (F.matrix[i][j]) {
					case -1 :	cout << "^ ";
								break;
					case -2 :	cout << "v ";
								break;
					default :	cout << "  ";
								break;
				}
			}
		}
		cout << endl;
	}
	cout << endl;
}

void solve() {
	// Kamus Lokal
	int i, j;

	// Algoritma
	i = 0;
	while ((i < N) && (possible)) {
		j = 0;
		while ((j < N) && (possible)) {
			if (F.boolean[i][j]) {
				// true apabila harus dicari
				do {
					F.matrix[i*2][j*2]++;
					test++;
				} while ((F.matrix[i*2][j*2] <= 5) && (!validation(i,j)));
				if (F.matrix[i*2][j*2] <= 5)
					// lanjut ke kolom berikutnya
					j++;
				else {
					// kembali ke kolom sebelumnya
					F.matrix[i*2][j*2] = 0;
					do {
						if (j != 0)
							j--;
						else if ((i != 0) && (j == 0)) {
							i--;
							j = 4;
						}
					} while ((!F.boolean[i][j]) && !((i == 0) && (j == 0)));
					if ((i == 0) && (j == 0) && (((F.boolean[i][j]) && ((F.matrix[i*2][j*2] == 0))) || (!F.boolean[i][j])))
						// check apabila futoshiki bisa dikerjakan atau tidak
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
	if (signvalidation(i,j)) {
		// jika tanda 'lebih dari' atau 'kurang dari' sudah valid
		k = 0;
		while ((k < N) && (column)) {
			// cek kolom
			if ((k != j) && ((F.matrix[i*2][k*2] == F.matrix[i*2][j*2])))
				column = false;
			else
				k++;
		}
		if (column) {
			// jika kolom sudah valid
			k = 0;
			while ((k < N) && (row)) {
				// cek baris
				if ((k != i) && ((F.matrix[k*2][j*2] == F.matrix[i*2][j*2])))
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

bool signvalidation(int i, int j) {
	// Kamus Lokal
	bool valid[4] = { true,true,true,true };
	
	// Algoritma
	if (i > 0) {
		// mengecek tanda antar baris 1/2/3/4 dengan 1/2/3/4
		switch (F.matrix[i*2-1][j*2]) {
			case -1 :	if (F.matrix[(i-1)*2][j*2] < F.matrix[i*2][j*2])
							valid[0] = true;
						else
							valid[0] = false;
						break;
			case -2 :	if (F.matrix[(i-1)*2][j*2] > F.matrix[i*2][j*2])
							valid[0] = true;
						else
							valid[0] = false;
						break;
			default	: 	valid[0] = true;
						break;
		}
	}
	if ((i < 4) && (valid[0])) {
		// mengecek tanda antar baris 1/2/3/4 dengan 2/3/4/5
		switch (F.matrix[i*2+1][j*2]) {
			case -1 :	if (F.matrix[(i+1)*2][j*2] != 0) {
							if (F.matrix[i*2][j*2] < F.matrix[(i+1)*2][j*2])
								valid[1] = true;
							else
								valid[1] = false;
						} else 
							valid[1] = true;
						break;
			case -2 :	if (F.matrix[(i+1)*2][j*2] != 0) {
							if (F.matrix[i*2][j*2] > F.matrix[(i+1)*2][j*2])
								valid[1] = true;
							else
								valid[1] = false;
						} else 
							valid[1] = true;
						break;
			default	:	valid[1] = true;
						break;
		}
	}
	if ((j > 0) && (valid[1])) {
		// mengecek tanda antar kolom 2/3/4/5 dengan 1/2/3/4
		switch (F.matrix[i*2][j*2-1]) {
			case -1 :	if (F.matrix[i*2][(j-1)*2] < F.matrix[i*2][j*2])
							valid[2] = true;
						else
							valid[2] = false;
						break;
			case -2 :	if (F.matrix[i*2][(j-1)*2] > F.matrix[i*2][j*2])
							valid[2] = true;
						else
							valid[2] = false;
						break;
			default	:	valid[2] = true;
						break;
		}
	}
	if ((j < 4) && (valid[2])) {
		// mengecek tanda antar kolom 1/2/3/4 dengan 2/3/4/5
		switch (F.matrix[i*2][j*2+1]) {
			case -1 :	if (F.matrix[i*2][(j+1)*2] != 0) {
							if (F.matrix[i*2][j*2] < F.matrix[i*2][(j+1)*2])
								valid[3] = true;
							else
								valid[3] = false;
						} else 
							valid[3] = true;
						break;
			case -2 :	if (F.matrix[i*2][(j+1)*2] != 0) {
							if (F.matrix[i*2][j*2] > F.matrix[i*2][(j+1)*2])
								valid[3] = true;
							else
								valid[3] = false;
						} else 
							valid[3] = true;
						break;
			default	: 	valid[3] = true;
						break;
		}
	}
	return valid[0] && valid[1] && valid[2] && valid[3];
}
