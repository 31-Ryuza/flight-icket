#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <random>

using namespace std;

struct FlightPackage
{
    int economyPrice;
    int businessPrice;
    int firstClassPrice;
};

struct FlightReceipt
{
    string destination;
    string flightType;
};

struct Transaction
{
    string id;
    string date;
    string destination;
    string flightType;
    int passengerAmount;
    int totalPrice;
};

struct CustomerProfile
{
    string name;
    string email;
    string phone;
};

const int MAX_TRANSACTIONS = 100;
Transaction transactions[MAX_TRANSACTIONS];
int transactionCount = 0;
int saldo = 100000000;
CustomerProfile customer;

string formatRupiah(int number)
{
    stringstream ss;
    ss.imbue(locale(""));
    ss << fixed << setprecision(0) << number;

    string str = ss.str();
    int n = str.length() - 3;
    while (n > 0)
    {
        str.insert(n, ".");
        n -= 3;
    }

    return "Rp. " + str;
}

void displayTransactions()
{
    cout << ">> Riwayat Transaksi: \n" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    cout << "================== \n" << endl;
    for (int i = 0; i < transactionCount; ++i)
    {
        if (i != 0)
        {
            cout << "------------------" << endl;
        }
        cout << "Transaksi " << i + 1 << ": \n" << endl;
        cout << "ID: " << transactions[i].id << endl;
        cout << "Tanggal Pemesanan: " << transactions[i].date << endl;
        cout << "Tujuan: " << transactions[i].destination << endl;
        cout << "Tipe Penerbangan: " << transactions[i].flightType << endl;
        cout << "Jumlah Penumpang: " << transactions[i].passengerAmount << endl;
        cout << "Total Harga: " << formatRupiah(transactions[i].totalPrice) << endl;

    }
    cout << endl;
    cout << "==================" << endl;
}

void showProfile()
{
    cout << ">> Profile: \n" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    cout << "================== \n" << endl;
    cout << "Nama: " << customer.name << endl;
    cout << "Email: " << customer.email << endl;
    cout << "phone: " << customer.phone << endl;
    cout << endl;
    cout << "==================" << endl;
}

void getCustomerProfile()
{
    cout << "Masukkan nama Anda: ";
    getline(cin, customer.name);
    cout << "Masukkan email Anda: ";
    getline(cin, customer.email);
    cout << "Masukkan nomor telepon Anda: ";
    getline(cin, customer.phone);
}

string generateRandomId()
{
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    int len = 8;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, sizeof(alphanum) - 2);

    string id;
    for (int i = 0; i < len; ++i)
    {
        id += alphanum[dis(gen)];
    }

    return id;
}

int main()
{
    int menu = 0;
    int destination = 0;
    string dateOrder = "";
    string destinationName = "";
    int flightType = 0;
    string flightTypeName = "";
    int passengerAmount = 0;
    int price = 0;
    int totalPrice = 0;
    string purchase = "";
    bool retry = false;
    bool retryMenu = true;

    const int numDestinations = 3;
    const int numFlightTypes = 3;

    int packagePrice[numDestinations][numFlightTypes] =
    {
        {1500000, 3000000, 5000000},
        {1200000, 2800000, 4000000},
        {1000000, 2000000, 3000000}
    };

    cout << "##################################################" << endl;
    getCustomerProfile();

    while (retryMenu)
    {
        cout << endl;
        cout << "##################################################" << endl;
        cout << endl;
        cout << "Selamat datang, " << customer.name << "! di Mercu Airlines \n" << endl;
        cout << endl;
        cout << "Saldo anda, " << formatRupiah(saldo) << endl;
        cout << endl;
        cout << "Pilih Menu" << endl;
        cout << "1. Pesan Tiket" << endl;
        cout << "2. Lihat Transaksi" << endl;
        cout << "3. Lihat Profile" << endl;
        cout << "4. Keluar" << endl;
        cout << "Jawaban : ";
        cin >> menu;

        switch (menu)
        {
        case 1:
            cout << "Tanggal Pemesanan (yyyy-mm-dd): ";
            cin >> dateOrder;
            cout << endl ;
            cout << ">> Memesan Penerbangan \n" << endl;

            retry = true;
            while (retry)
            {
                cout << "Pilih tujuan" << endl;
                cout << "1. Bali / Denpasar (DPS)" << endl;
                cout << "2. Makassar (UPG)" << endl;
                cout << "3. Medan (KNO)" << endl;
                cout << "Jawaban : ";
                cin >> destination;

                if (destination == 1)
                {
                    destinationName = "Bali / Denpasar (DPS)";
                    retry = false;
                }
                else if (destination == 2)
                {
                    destinationName = "Makassar (UPG)";
                    retry = false;
                }
                else if (destination == 3)
                {
                    destinationName = "Medan (KNO)";
                    retry = false;
                }
                else
                {
                    cout << endl;
                    cout << "Pilihan destinasi tidak valid \n" << endl;
                }
            }

            retry = true;
            while (retry)
            {
                cout << endl ;
                cout << "Kelas Penerbangan" << endl;
                cout << "1. Economy" << endl;
                cout << "2. Business" << endl;
                cout << "3. First Class" << endl;
                cout << "Jawaban : ";
                cin >> flightType;

                if (flightType == 1)
                {
                    flightTypeName = "Economy";
                    retry = false;
                }
                else if (flightType == 2)
                {
                    flightTypeName = "Business";
                    retry = false;
                }
                else if (flightType == 3)
                {
                    flightTypeName = "First Class";
                    retry = false;
                }
                else
                {
                    cout << endl;
                    cout << "Pilihan kelas penerbangan tidak valid" << endl;
                }
            }

            cout << endl;
            cout << "Jumlah Penumpang : ";
            cin >> passengerAmount;

            price = packagePrice[destination -1][flightType -1];
            totalPrice = price * passengerAmount;
            saldo = saldo - totalPrice;

            if(saldo < 0){
                cout << "Total harga : " << formatRupiah(totalPrice) << endl;
                cout << "Saldo anda  : " << formatRupiah(saldo + totalPrice) << endl;
                cout << "Saldo anda kurang" << endl;
                retryMenu = false;
                break;
            }

            cout << endl;
            cout << ">> Rincian Harga \n" << endl;
            cout << "Kota Tujuan       : " << destinationName << endl;
            cout << "Tanggal Pemesanan : " << dateOrder << endl;
            cout << "Kelas Penerbangan : " << flightTypeName << endl;
            cout << "Harga tiket       : " << formatRupiah(price) << endl;
            cout << "Jumlah penumpang  : " << passengerAmount << endl;
            cout << "Total harga       : " << formatRupiah(totalPrice) << endl;
            cout << "Sisa saldo        : " << formatRupiah(saldo) << endl;

            cout << endl;
            cout << "Apakah ingin melanjutkan pembayaran? (y/n) : ";
            cin.ignore();
            getline(cin, purchase);

            cout << endl;
            if (purchase == "y" || purchase == "Y")
            {
                cout << ">> Memproses pembelian \n" << endl;

                string ticketId = generateRandomId();
                transactions[transactionCount] = {ticketId, dateOrder, destinationName, flightTypeName, passengerAmount, totalPrice};
                transactionCount++;

                std::this_thread::sleep_for(std::chrono::seconds(3));

                cout << "## Pembelian berhasil dilakukan. \n" << endl;
                cout << "ID Tiket Anda: " << ticketId << endl;
                cout << "Anda akan dikembalikan ke menu sesaat lagi \n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                cout << endl;
            }
            else
            {
                cout << "Pembayaran di batalkan \n" << endl;
            }

            break;
        case 2:
            cout << endl;
            displayTransactions();
            break;
        case 3:
            cout << endl;
            showProfile();
            break;
        case 4:
            retryMenu = false;
            break;
        default:
            cout << "Input salah" << endl;
            break;
        }
    }

    return 0;
}
