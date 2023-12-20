#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <string>
#include <iomanip>

class CinemaQueue {
private:
    std::vector<std::pair<std::string, std::string>> tempatduduk;

public:
    void enqueue(const std::string& customer, const std::string& kursi) {
        tempatduduk.push_back(std::make_pair(customer, kursi));
    }

    std::string dequeue() {
        if (!tempatduduk.empty()) {
            std::string customer = tempatduduk.back().first;
            tempatduduk.pop_back();
            return customer;
        }
        return "";
    }

    bool empty() const {
        return tempatduduk.empty();
    }

    void print_tempatduduk() const {
    if (tempatduduk.empty()) {
        std::cout << "Kursi Tidak Dipesan" << std::endl;
    } else {
        std::cout << std::setw(15) << std::left << "Customer" << " | " << std::setw(10) << std::right << "Kursi" << std::endl;
        std::cout << std::setfill('-') << std::setw(29) << "-" << std::setfill(' ') << std::endl;

        for (const auto& data_order : tempatduduk) {
            std::cout << std::setw(15) << std::left << data_order.first << " | " << std::setw(10) << std::right << data_order.second << std::endl;
        }
    }

    system("pause");
    system("cls");
}

    size_t size() const {
        return tempatduduk.size();
    }

    std::pair<std::string, std::string>& operator[](size_t index) {
        return tempatduduk.at(index);
    }

    const std::pair<std::string, std::string>& operator[](size_t index) const {
        return tempatduduk.at(index);
    }

    void edit_urutan(size_t index, const std::string& new_kursi) {
        if (index < tempatduduk.size()) {
            tempatduduk[index].second = new_kursi;
        }
    }

    void hapus_urutan(size_t index) {
        if (index < tempatduduk.size()) {
            tempatduduk.erase(tempatduduk.begin() + index);
        }
    }
};

class opsi_tempat_duduk {
private:
    std::stack<std::string> kursi_tersedia;
    std::unordered_set<std::string> kursi_terpilih;

public:
    opsi_tempat_duduk() {
        // Initialize kursi_tersedia from A1 to E5 in reverse order
        for (char row = 'E'; row >= 'A'; row--) {
            for (int col = 1; col <= 5; col++) {
                std::string kursi = std::string(1, row) + std::to_string(col);
                kursi_tersedia.push(kursi);
            }
        }
    }

    std::string pilih_kursi(const std::string& kursi) {
        if (kursi_terpilih.find(kursi) != kursi_terpilih.end()) {
            return "Kursi " + kursi + " Sudah Dipesan. Tolong Pilih Kursi Lain!";
        }

        kursi_terpilih.insert(kursi);
        return "";
    }

    void retur_kursi(const std::string& kursi) {
        kursi_terpilih.erase(kursi);
        kursi_tersedia.push(kursi);
    }

    bool cek_kursi_tersedia(const std::string& kursi) {
        char row = kursi[0];
        int col = 0;

        if (kursi.length() > 1) {
            try {
                col = std::stoi(kursi.substr(1));
            } catch (const std::exception&) {
                return false;
            }
        }

        return row >= 'A' && row <= 'E' && col >= 1 && col <= 5;
    }
};

void tambah_customer(CinemaQueue& queue, opsi_tempat_duduk& pilihan_kursi) {
    std::string nama_kustomer;
    std::cout << "Masukkan Nama Kustomer: ";
    std::cin >> nama_kustomer;

    std::string kursi;
    bool cek_kursi_tersedia = false;
    do {
        std::cout << "Masukkan Pilihan Kursi (A1-E5): ";
        std::cin >> kursi;

        if (!pilihan_kursi.cek_kursi_tersedia(kursi)) {
            std::cout << "Kursi Invalid. Masukkan Urutan Kursi (A1-E5)!!" << std::endl;
        } else {
            std::string errorMessage = pilihan_kursi.pilih_kursi(kursi);
            if (!errorMessage.empty()) {
                std::cout << errorMessage << std::endl;
            } else {
                cek_kursi_tersedia = true;
                queue.enqueue(nama_kustomer, kursi);
                std::cout << "Kursi " << kursi << " dipesan oleh " << nama_kustomer << "." << std::endl;
                //std::cout << "Customer " << nama_kustomer << " telah memesan kursi - " << kursi << "." << std::endl;
            }
        }
    } while (!cek_kursi_tersedia);

    system("pause");
    system("cls");
}

void print_urutan_customer(const CinemaQueue& queue) {
    //size_t index;
    //std::cout << index;
    queue.print_tempatduduk();
}

void edit_urutan_customer(CinemaQueue& queue, opsi_tempat_duduk& pilihan_kursi) {
    size_t index;
    std::string new_kursi;

    std::cout << "Masukkan Urutan Customer yang Akan Diedit: ";
    std::cin >> index;

    if (index < queue.size()) {
        std::cout << "Masukkan Kursi yang Baru: ";
        std::cin >> new_kursi;

        if (pilihan_kursi.cek_kursi_tersedia(new_kursi)) {
            std::string oldSeat = queue.size() > index ? queue[index].second : "";
            std::string errorMessage = pilihan_kursi.pilih_kursi(new_kursi);
            if (!errorMessage.empty()) {
                std::cout << errorMessage << std::endl;
            } else {
                if (!oldSeat.empty()) {
                    pilihan_kursi.retur_kursi(oldSeat);
                }
                queue.edit_urutan(index, new_kursi);
                std::cout << "Urutan Berhasil di-Update!" << std::endl;
            }
        } else {
            std::cout << "Kursi Invalid. Masukkan Urutan Kursi (A1-E5)!!" << std::endl;
        }
    } else {
        std::cout << "Urutan Kursi Invalid!!" << std::endl;
    }
    system("pause");
    system("cls");
}

void hapus_urutan_customer(CinemaQueue& queue, opsi_tempat_duduk& pilihan_kursi) {
    size_t index;
    std::cout << "Masukkan Urutan Customer yang Akan Dihapus : ";
    std::cin >> index;

    if (index < queue.size()) {
        std::string kursi = queue.size() > index ? queue[index].second : "";
        if (!kursi.empty()) {
            queue.hapus_urutan(index);
            pilihan_kursi.retur_kursi(kursi);
            std::cout << "Urutan Terhapus!" << std::endl;
        }
    } else {
        std::cout << "Urutan Invalid!!" << std::endl;
    }
    system("pause");
    system("cls");
}




void printlogo() {
std::cout <<
    R"( _    _ _______ _       _____  ______  ______   _____  _    _      __
| |  / |_______) |     / ___ \|  ___ \(_____ \ / ___ \| |  / )    / /
| | / / _____  | |    | |   | | | _ | |_____) ) |   | | | / /    / /____
| |< < |  ___) | |    | |   | | || || |  ____/| |   | | |< <    |___   _)
| | \ \| |_____| |____| |___| | || || | |     | |___| | | \ \       | |
|_|  \_)_______)_______)_____/|_||_||_|_|      \_____/|_|  \_)      |_|
)" ; std::cout << "=============================" << std::endl;
}

void start_program() {
    CinemaQueue queue;
    opsi_tempat_duduk pilihan_kursi;

    int pil;
    while (true) {
        printlogo();
        std::cout << "1. Tambah Customer dan Pilih Kursi" << std::endl;
        std::cout << "2. Tampilkan Urutan Customer" << std::endl;
        std::cout << "3. Edit Urutan Customer" << std::endl;
        std::cout << "4. Delete Urutan Customer" << std::endl;
        std::cout << "5. Keluar Program" << std::endl;
        std::cout << "=============================" << std::endl;
        std::cout << "Masukkan Pilihan: "; std::cin >> pil;
        std::cout << "=============================" << std::endl;
        switch (pil) {
            case 1:
                tambah_customer(queue, pilihan_kursi);
                break;
            case 2:
                print_urutan_customer(queue);
                break;
            case 3:
                edit_urutan_customer(queue, pilihan_kursi);
                break;
            case 4:
                hapus_urutan_customer(queue, pilihan_kursi);
                break;
            case 5:
                std::cout << "Keluar Program" << std::endl;
                return;
            default:
                std::cout << "Tidak terdapat opsi, tolong ulangi!" << std::endl;
        }
    }
}

int main() {
    start_program();
    return 0;
}

