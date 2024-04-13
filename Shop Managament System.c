#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BARANG 100
#define MAX_TANGGAL 20
#define MAX_TRANSAKSI 100
#define FILENAME "UD.Antony.txt"

void simpanData(char daftar_barang[MAX_BARANG][MAX_BARANG], int stok[MAX_BARANG], int harga[MAX_BARANG], int jumlah_barang,
                char daftar_transaksi[MAX_TRANSAKSI][MAX_TANGGAL][MAX_BARANG], int jumlah_transaksi, int total_harga_transaksi[MAX_TRANSAKSI])
{
    FILE *file = fopen(FILENAME, "w");

    if (file == NULL)
    {
        printf("Gagal membuka file.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "======= STOK BARANG =======\n", jumlah_barang);
    fprintf(file, "Barang   Stok    Harga\n", jumlah_barang);

    for (int i = 0; i < jumlah_barang; i++)
    {
        fprintf(file, "%s    |%d    |%d\n", daftar_barang[i], stok[i], harga[i]);
    }

    fprintf(file, "======= TRANSAKSI =======\n", jumlah_transaksi);
    fprintf(file, "Tanggal  Barang  Jumlah Barang   Harga Total", jumlah_transaksi);

    for (int i = 0; i < jumlah_transaksi; i++)
    {
        fprintf(file, "%s | %s | %s | %d\n", daftar_transaksi[i][0], daftar_transaksi[i][1], daftar_transaksi[i][2], total_harga_transaksi[i]);
    }

    fclose(file);
}

void bacaData(char daftar_barang[MAX_BARANG][MAX_BARANG], int stok[MAX_BARANG], int harga[MAX_BARANG], int *jumlah_barang,
              char daftar_transaksi[MAX_TRANSAKSI][MAX_TANGGAL][MAX_BARANG], int *jumlah_transaksi, int total_harga_transaksi[MAX_TRANSAKSI])
{
    FILE *file = fopen(FILENAME, "r");

    if (file == NULL)
    {
        printf("File tidak ditemukan. Membuat file baru.\n");
        return;
    }

    fscanf(file, "%d", jumlah_barang);

    for (int i = 0; i < *jumlah_barang; i++)
    {
        fscanf(file, "%s | %d | %d", daftar_barang[i], &stok[i], &harga[i]);
    }

    fscanf(file, "%d", jumlah_transaksi);

    for (int i = 0; i < *jumlah_transaksi; i++)
    {
        fscanf(file, "%s | %s | %s | %d", daftar_transaksi[i][0], daftar_transaksi[i][1], daftar_transaksi[i][2], &total_harga_transaksi[i]);
    }

    fclose(file);
}

void tambahStok(char daftar_barang[MAX_BARANG][MAX_BARANG], int stok[MAX_BARANG], int harga[MAX_BARANG], int *jumlah_barang, char nama_barang[MAX_BARANG], int jumlah, int harga_barang)
{
    int i;
    for (i = 0; i < *jumlah_barang; i++)
    {
        if (strcmp(daftar_barang[i], nama_barang) == 0)
        {
            stok[i] += jumlah;
            harga[i] = harga_barang;
            printf("Stok %s berhasil ditambahkan sebanyak %d.\n", nama_barang, jumlah);
            printf("Stok sekarang: %d\n", stok[i]);
            simpanData(daftar_barang, stok, harga, *jumlah_barang, NULL, 0, NULL); // Save data to file
            return;
        }
    }

    strcpy(daftar_barang[*jumlah_barang], nama_barang);
    stok[*jumlah_barang] = jumlah;
    harga[*jumlah_barang] = harga_barang;
    (*jumlah_barang)++;
    printf("Barang %s berhasil ditambahkan ke dalam stok sebanyak %d.\n", nama_barang, jumlah);
    printf("Stok sekarang: %d\n", stok[*jumlah_barang - 1]);
    simpanData(daftar_barang, stok, harga, *jumlah_barang, NULL, 0, NULL); // Save data to file
}

void catatPenjualan(char daftar_barang[MAX_BARANG][MAX_BARANG], int stok[MAX_BARANG], int harga[MAX_BARANG], int *jumlah_barang,
                    char daftar_transaksi[MAX_TRANSAKSI][MAX_TANGGAL][MAX_BARANG], int *jumlah_transaksi, int total_harga_transaksi[MAX_TRANSAKSI],
                    char nama_barang[MAX_BARANG], int jumlah, char tanggal[MAX_TANGGAL])
{
    int i;
    for (i = 0; i < *jumlah_barang; i++)
    {
        if (strcmp(daftar_barang[i], nama_barang) == 0)
        {
            if (stok[i] >= jumlah)
            {
                strcpy(daftar_transaksi[*jumlah_transaksi][0], tanggal);
                strcpy(daftar_transaksi[*jumlah_transaksi][1], nama_barang);
                sprintf(daftar_transaksi[*jumlah_transaksi][2], "%d", jumlah);

                total_harga_transaksi[*jumlah_transaksi] = jumlah * harga[i];

                stok[i] -= jumlah;
                (*jumlah_transaksi)++;

                printf("Penjualan %s sebanyak %d pada tanggal %s berhasil dicatat.\n", nama_barang, jumlah, tanggal);
                printf("Total harga: %d\n", total_harga_transaksi[*jumlah_transaksi - 1]);
                printf("Stok sekarang: %d\n", stok[i]);
                simpanData(daftar_barang, stok, harga, *jumlah_barang, daftar_transaksi, *jumlah_transaksi, total_harga_transaksi); // Save data to file
            }
            else
            {
                printf("Stok %s tidak mencukupi untuk melakukan penjualan sebanyak %d.\n", nama_barang, jumlah);
                printf("Stok sekarang: %d\n", stok[i]);
            }
            return;
        }
    }

    printf("Barang %s tidak ditemukan dalam stok.\n", nama_barang);
}

void buatLaporan(char daftar_transaksi[MAX_TRANSAKSI][MAX_TANGGAL][MAX_BARANG], int jumlah_transaksi, int total_harga_transaksi[MAX_TRANSAKSI], char jenis_laporan[MAX_TANGGAL])
{
    printf("Laporan %s:\n", jenis_laporan);

    for (int i = 0; i < jumlah_transaksi - 1; i++)
    {
        for (int j = 0; j < jumlah_transaksi - i - 1; j++)
        {
            if (strcmp(daftar_transaksi[j][0], daftar_transaksi[j + 1][0]) > 0)
            {
                char temp[MAX_TANGGAL][MAX_BARANG];
                strcpy(temp[0], daftar_transaksi[j][0]);
                strcpy(temp[1], daftar_transaksi[j][1]);
                strcpy(temp[2], daftar_transaksi[j][2]);

                int temp_harga = total_harga_transaksi[j];

                strcpy(daftar_transaksi[j][0], daftar_transaksi[j + 1][0]);
                strcpy(daftar_transaksi[j][1], daftar_transaksi[j + 1][1]);
                strcpy(daftar_transaksi[j][2], daftar_transaksi[j + 1][2]);

                total_harga_transaksi[j] = total_harga_transaksi[j + 1];

                strcpy(daftar_transaksi[j + 1][0], temp[0]);
                strcpy(daftar_transaksi[j + 1][1], temp[1]);
                strcpy(daftar_transaksi[j + 1][2], temp[2]);

                total_harga_transaksi[j + 1] = temp_harga;
            }
        }
    }

    for (int i = 0; i < jumlah_transaksi; i++)
    {
        if (strstr(daftar_transaksi[i][0], jenis_laporan) != NULL)
        {
            printf("%s: %s sebanyak %s, Total Harga: %d\n", daftar_transaksi[i][0], daftar_transaksi[i][1], daftar_transaksi[i][2], total_harga_transaksi[i]);
        }
    }
}

void lihatStok(char daftar_barang[MAX_BARANG][MAX_BARANG], int stok[MAX_BARANG], int harga[MAX_BARANG], int jumlah_barang)
{
    printf("Stok Barang:\n");

    for (int i = 0; i < jumlah_barang; i++)
    {
        printf("%s: Stok %d, Harga %d\n", daftar_barang[i], stok[i], harga[i]);
    }
}

void lihatSemuaTransaksi(char daftar_transaksi[MAX_TRANSAKSI][MAX_TANGGAL][MAX_BARANG], int jumlah_transaksi, int total_harga_transaksi[MAX_TRANSAKSI])
{
    printf("Semua Transaksi:\n");

    for (int i = 0; i < jumlah_transaksi; i++)
    {
        printf("%s: %s sebanyak %s, Total Harga: %d\n", daftar_transaksi[i][0], daftar_transaksi[i][1], daftar_transaksi[i][2], total_harga_transaksi[i]);
    }
}

void tampilkanMenu()
{
    printf("\n===== Menu Toko U.D. Antony =====\n");
    printf("1. Tambah Stok Barang\n");
    printf("2. Catat Penjualan\n");
    printf("3. Lihat Laporan\n");
    printf("4. Lihat Stok Barang\n");
    printf("5. Lihat Semua Transaksi\n");
    printf("6. Keluar\n");
    printf("Pilih menu (1-6): ");
}

int main()
{
    char daftar_barang[MAX_BARANG][MAX_BARANG];
    int stok[MAX_BARANG];
    int harga[MAX_BARANG];
    int jumlah_barang = 0;

    char daftar_transaksi[MAX_TRANSAKSI][MAX_TANGGAL][MAX_BARANG];
    int jumlah_transaksi = 0;
    int total_harga_transaksi[MAX_TRANSAKSI];

    int pilihan;
    char nama_barang[MAX_BARANG];
    int jumlah;
    char tanggal[MAX_TANGGAL];
    char jenis_laporan[MAX_TANGGAL];
    int harga_barang;

    // Load existing data from the file
    bacaData(daftar_barang, stok, harga, &jumlah_barang, daftar_transaksi, &jumlah_transaksi, total_harga_transaksi);

    do
    {
        tampilkanMenu();
        scanf("%d", &pilihan);

        if (pilihan == 1)
        {
            printf("Masukkan nama barang: ");
            scanf("%s", nama_barang);
            printf("Masukkan jumlah stok yang ditambahkan: ");
            scanf("%d", &jumlah);
            printf("Masukkan harga barang: ");
            scanf("%d", &harga_barang);
            tambahStok(daftar_barang, stok, harga, &jumlah_barang, nama_barang, jumlah, harga_barang);
        }
        else if (pilihan == 2)
        {
            printf("Masukkan nama barang: ");
            scanf("%s", nama_barang);
            printf("Masukkan jumlah penjualan: ");
            scanf("%d", &jumlah);
            printf("Masukkan tanggal penjualan (YYYY-MM-DD): ");
            scanf("%s", tanggal);
            catatPenjualan(daftar_barang, stok, harga, &jumlah_barang, daftar_transaksi, &jumlah_transaksi, total_harga_transaksi, nama_barang, jumlah, tanggal);
        }
        else if (pilihan == 3)
        {
            printf("Pilih jenis laporan:\n");
            printf("1. Harian\n");
            printf("2. Mingguan\n");
            printf("3. Bulanan\n");
            printf("4. Tahunan\n");
            printf("Pilih jenis laporan (1-4): ");
            int jenis;
            scanf("%d", &jenis);

            if (jenis == 1)
            {
                printf("Masukkan tanggal laporan (YYYY-MM-DD): ");
                scanf("%s", jenis_laporan);
                buatLaporan(daftar_transaksi, jumlah_transaksi, total_harga_transaksi, jenis_laporan);
            }
            else if (jenis == 2)
            {
                printf("Masukkan tahun laporan (YYYY): ");
                scanf("%s", jenis_laporan);
                strcat(jenis_laporan, "-W");
                printf("Masukkan minggu laporan (01-53): ");
                char minggu[MAX_TANGGAL];
                scanf("%s", minggu);
                if (strlen(minggu) == 1)
                {
                    strcat(jenis_laporan, "0");
                }
                strcat(jenis_laporan, minggu);
                buatLaporan(daftar_transaksi, jumlah_transaksi, total_harga_transaksi, jenis_laporan);
            }
            else if (jenis == 3)
            {
                printf("Masukkan tahun laporan (YYYY): ");
                scanf("%s", jenis_laporan);
                strcat(jenis_laporan, "-");
                printf("Masukkan bulan laporan (01-12): ");
                char bulan[MAX_TANGGAL];
                scanf("%s", bulan);
                strcat(jenis_laporan, bulan);
                buatLaporan(daftar_transaksi, jumlah_transaksi, total_harga_transaksi, jenis_laporan);
            }
            else if (jenis == 4)
            {
                printf("Masukkan tahun laporan (YYYY): ");
                scanf("%s", jenis_laporan);
                buatLaporan(daftar_transaksi, jumlah_transaksi, total_harga_transaksi, jenis_laporan);
            }
            else
            {
                printf("Pilihan tidak valid. Silakan pilih lagi.\n");
            }
        }
        else if (pilihan == 4)
        {
            lihatStok(daftar_barang, stok, harga, jumlah_barang);
        }
        else if (pilihan == 5)
        {
            lihatSemuaTransaksi(daftar_transaksi, jumlah_transaksi, total_harga_transaksi);
        }
        else if (pilihan == 6)
        {
            printf("Terima kasih. Program selesai.\n");
            simpanData(daftar_barang, stok, harga, jumlah_barang, daftar_transaksi, jumlah_transaksi, total_harga_transaksi);
        }
        else
        {
            printf("Pilihan tidak valid. Silakan pilih lagi.\n");
        }

    } while (pilihan != 6);

    return 0;
}