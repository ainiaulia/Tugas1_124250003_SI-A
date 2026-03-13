#include <iostream>
#include <cctype>
#include <iomanip>
#include <cstdio>
using namespace std;

struct Film{
	char judul[100];
	int harga;
	int tahun;
	float rating;
};

Film dataFilm[100];
int jumlahData = 0;
bool sudahSort = false;
const char* filename = "netfilm_db.txt";

void simpanFile(){
    FILE *fptr = fopen(filename,"w");
    if(fptr == NULL){
        cout<<"Gagal Membuka File!\n";
        return;
    }
    for(int i=0;i<jumlahData;i++){
        fprintf(fptr,"%s;%d;%d;%.1f\n", dataFilm[i].judul, dataFilm[i].harga, dataFilm[i].tahun, dataFilm[i].rating);
    }
    fclose(fptr);
}

void bacaFile(){
    FILE *fptr = fopen(filename,"r");
    if(fptr == NULL) return;

    while(fscanf(fptr," %[^;];%d;%d;%f", dataFilm[jumlahData].judul, &dataFilm[jumlahData].harga, &dataFilm[jumlahData].tahun, &dataFilm[jumlahData].rating) != EOF){
        jumlahData++;
    }
    fclose(fptr);
}

void lower(char teks[]){
    for(int i=0; teks[i] != '\0'; i++){
        teks[i] = tolower(teks[i]);
    }
}

int bandingJudul(char a[], char b[]){
    int i=0;
    while(a[i] != '\0' && b[i] != '\0'){
        if(a[i] < b[i]) return -1;
        if(a[i] > b[i]) return 1;
        i++;
    }
    if(a[i]=='\0' && b[i]=='\0') return 0;
    if(a[i]=='\0') return -1;
    return 1;
}

void menu(){
    cout<<"=============================================\n";
    cout<<"           NETFILM SYSTEM - MENU\n";
    cout<<"=============================================\n";
    cout<<"[1] Tambah Film Baru\n";
    cout<<"[2] Lihat Katalog Film\n";
    cout<<"[3] Urutkan Abjad (Bubble Sort)\n";
    cout<<"[4] Urutkan Rating (Quick Sort)\n";
    cout<<"[5] Cari Film\n";
    cout<<"[0] Keluar & Simpan\n";
    cout<<"=============================================\n";
}

void input(){
    int jumlah;
	cout << "========================================\n";
	cout << "               INPUT FILM               \n";
	cout << "========================================\n";
    cout << "Jumlah film yang ingin diinput: ";
    cin >> jumlah;

    for(int i = 0; i < jumlah; i++){
		cout << "========================================\n";
        cin.ignore();
        cout << "\nJudul  : "; cin.getline(dataFilm[jumlahData].judul,100);
        lower(dataFilm[jumlahData].judul);

        cout << "Harga  : "; cin >> dataFilm[jumlahData].harga;

        cout << "Tahun  : "; cin >> dataFilm[jumlahData].tahun;

        cout << "Rating : "; cin >> dataFilm[jumlahData].rating;
        cout << endl;
        jumlahData++;
    }
    cout << "\n========================================\n";
    cout << "[ SUKSES!! ] Data Berhasil Ditambahkan\n";
    cout << "========================================\n";
}

void tampilData(){
    if(jumlahData == 0){
        cout << "Data Film Masih Kosong!\n";
        return;
    }
    cout<<"----------------------------------------------------------------\n";
    cout<<"       N E T F L I X   C O N T E N T   K A T A L O G\n";
    cout<<"----------------------------------------------------------------\n";
    cout << left << setw(5) << "ID" << setw(30) << "JUDUL" << setw(12) << "HARGA" << setw(8) << "TAHUN" << setw(6) << "RATING" << endl;
    cout<<"----------------------------------------------------------------\n";

    for(int i=0;i<jumlahData;i++){
        cout << left << setw(5) << i+1 << setw(30) << dataFilm[i].judul << setw(12) << dataFilm[i].harga << setw(8) << dataFilm[i].tahun << setw(6) << dataFilm[i].rating << endl;
        cout<<"----------------------------------------------------------------\n";
    }
}

void bubbleSort(){
    for(int i = 0; i < jumlahData - 1; i++){
        for(int j = 0; j < jumlahData - i - 1; j++){
            int k = 0;
            while(dataFilm[j].judul[k] == dataFilm[j+1].judul[k] && dataFilm[j].judul[k] != '\0' && dataFilm[j+1].judul[k] != '\0'){
                k++;
            }
            if(dataFilm[j].judul[k] > dataFilm[j+1].judul[k]){
                swap(dataFilm[j], dataFilm[j+1]);
            }
        }
    }
    sudahSort = true;
}

void quickSort(int low,int high){
    int i = low;
    int j = high;
    float pivot = dataFilm[(low+high)/2].rating;
    while(i <= j){
        while(dataFilm[i].rating > pivot) i++;
        while(dataFilm[j].rating < pivot) j--;

        if(i <= j){
            swap(dataFilm[i],dataFilm[j]);
            i++;
            j--;
        }
    }

    if(low < j) quickSort(low,j);
    if(i < high) quickSort(i,high);
}

void linearSearch(){
    char cari[100];
    cin.ignore();

    cout<<"Masukkan Judul Film : "; cin.getline(cari,100);
    lower(cari);
	cout << "========================================\n";
	
    for(int i=0;i<jumlahData;i++){
        if(bandingJudul(dataFilm[i].judul,cari)==0){
            cout<<"\n[FOUND] "<< dataFilm[i].judul <<" ("<< dataFilm[i].tahun<<")\n";
            return;
        }
    }
    cout<<"\n[!]Film tidak ditemukan\n";
}

void binarySearch(){
    char cari[100];
    cin.ignore();

    cout << "Masukkan Judul Lengkap : "; cin.getline(cari,100);
    lower(cari);
	cout << "========================================\n";
    int kiri = 0;
    int kanan = jumlahData - 1;

    while(kiri <= kanan){
        int tengah = (kiri + kanan)/2;
        int hasil = bandingJudul(dataFilm[tengah].judul,cari);
        
        if(hasil == 0){
            cout << "\n[FOUND] " << dataFilm[tengah].judul << " (" <<dataFilm[tengah].tahun <<")\n";
            return;
        }
        else if(hasil < 0)
        kiri = tengah + 1;
        else
        kanan = tengah - 1;
    }
    cout<<"\n[!]Film tidak ditemukan. Pastikan Data Sudah di-sort A-Z.\n";
}

void searchFilm(){
    if(jumlahData == 0){
        cout << "Data Film Masih Kosong!\n";
        return;
    }
    
    if(jumlahData < 30){
		cout << "========================================\n";
        cout << "             Linear Search\n";
        cout << "========================================\n";
        linearSearch();
    } else{
        cout << "========================================\n";
        cout << "             Binary Search\n";
		cout << "========================================\n";
        if(!sudahSort){
            cout << "Data akan diurutkan dulu...\n";
            bubbleSort();
        }
        binarySearch();
    }
}

void pause(){
    cout<<"\nTekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
}

int main(){
    bacaFile();
    int pilih;

    do{
        system("cls");
        menu();

        cout << "\nPilih Menu > "; cin >> pilih;

        system("cls");

        switch(pilih){
            case 1:
                input();
                pause();
                break;
            case 2:
                tampilData();
                pause();
                break;
            case 3:
                bubbleSort();
                tampilData();
                cout << "\n================================================================\n";
                cout << "[ SUKSES!! ] Katalog Berhasil Diurutkan Berdasarkan Abjad A-Z.\n";
                cout << "================================================================\n";
                pause();
                break;
            case 4:
                quickSort(0,jumlahData-1);
                tampilData();
                cout << "\n================================================================\n";
                cout << "[ SUKSES!! ] Katalog Berhasil Diurutkan Berdasarkan Rating Tertinggi.\n";
                cout << "================================================================\n";
				pause();
				break;
            case 5:
                searchFilm();
                pause();
                break;
            case 0:
                simpanFile();
                cout<<"\nData berhasil disimpan. Program Keluar.\n";
                break;
        }
        
    }while(pilih!=0);
}

