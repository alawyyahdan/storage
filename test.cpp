#include <iostream>
#include <string>
using namespace std;

class Mobil_pickup {
private:
    string merk;
    int jenis_bbm;
    int isi_silinder;
    int l_bak;
    int p_bak;
    int t_bak;
    double berat_max;
    double brt_diangkut;
    int vol_diangkut;
    bool bawa_pasir;    
    bool bawa_barang;   
    
    // Variabel untuk BBM dan perjalanan
    double kapasitas_bbm;     
    double bbm_saat_ini;      
    double konsumsi_bbm;      
    double jarak_tempuh;      
    const double HARGA_BENSIN = 10000;
    const double HARGA_SOLAR = 7000;

public:
    Mobil_pickup() {
        brt_diangkut = 0;
        vol_diangkut = 0;
        bawa_pasir = false;
        bawa_barang = false;
        kapasitas_bbm = 45;   
        bbm_saat_ini = 0;     
        konsumsi_bbm = 0;     
        jarak_tempuh = 0;
    }

    // Setter dan Getter dasar
    void set_merk(string nama) {
        this->merk = nama;
    }
    
    string get_merk() {
        return merk;
    }

    void set_bak(int p, int l, int t) {
        this->p_bak = p;
        this->l_bak = l;
        this->t_bak = t;
    }
    
    int get_bak() {
        return p_bak * l_bak * t_bak;
    }

    void set_jenis_bbm(int tipe) {
        this->jenis_bbm = tipe;
        // Set konsumsi BBM berdasarkan jenis kendaraan
        if(merk == "Carry") {
            konsumsi_bbm = 15;  // 15 km/liter
        } else if(merk == "Grand Max") {
            konsumsi_bbm = 10;  // 10 km/liter
        }
    }
    
    int get_jenis_bbm() {
        return jenis_bbm;
    }

    void set_isi_silinder(int jumlah) {
        this->isi_silinder = jumlah;
    }
    
    int get_isi_silinder() {
        return isi_silinder;
    }

    void set_berat_max(double berat) {
        this->berat_max = berat;
    }
    
    double get_berat_max() {
        return berat_max;
    }

    // Method untuk BBM
    bool isi_bbm(double jumlah) {
        if (bbm_saat_ini + jumlah <= kapasitas_bbm) {
            bbm_saat_ini += jumlah;
            return true;
        }
        return false;
    }

    double cek_sisa_bbm() {
        return bbm_saat_ini;
    }

    double get_konsumsi_bbm() {
        return konsumsi_bbm;
    }

    double cek_total_jarak() {
        return jarak_tempuh;
    }

    bool pakai_bbm(double jarak) {
        double bbm_terpakai = jarak / konsumsi_bbm;
        if (bbm_terpakai <= bbm_saat_ini) {
            bbm_saat_ini -= bbm_terpakai;
            jarak_tempuh += jarak;
            return true;
        }
        return false;
    }

    double hitung_biaya_perjalanan(double jarak) {
        double bbm_terpakai = jarak / konsumsi_bbm;
        return bbm_terpakai * (jenis_bbm == 1 ? HARGA_BENSIN : HARGA_SOLAR);
    }

    // Method untuk muatan
    void set_nilai_angkut() {
        this->brt_diangkut = 0;
        this->vol_diangkut = 0;
        this->bawa_pasir = false;
        this->bawa_barang = false;
    }

    bool isi_barang(double berat) {
        if (bawa_pasir) {
            cout << "Tidak bisa mengisi barang karena sedang mengangkut pasir!" << endl;
            return false;
        }
        if (brt_diangkut + berat <= berat_max) {
            brt_diangkut += berat;
            bawa_barang = true;
            return true;
        }
        return false;
    }

    bool isi_pasir(int volume) {
        if (bawa_barang) {
            cout << "Tidak bisa mengisi pasir karena sedang mengangkut barang!" << endl;
            return false;
        }
        int kapasitas_bak = p_bak * l_bak * t_bak;
        if (vol_diangkut + volume <= kapasitas_bak) {
            vol_diangkut += volume;
            bawa_pasir = true;
            return true;
        }
        return false;
    }

    double turun_barang(double berat) {
        if (!bawa_barang) {
            cout << "Tidak ada barang yang diangkut!" << endl;
            return brt_diangkut;
        }
        if (berat <= brt_diangkut) {
            brt_diangkut -= berat;
            if (brt_diangkut == 0) {
                bawa_barang = false;
            }
            return brt_diangkut;
        }
        return brt_diangkut;
    }

    int turun_pasir(int volume) {
        if (!bawa_pasir) {
            cout << "Tidak ada pasir yang diangkut!" << endl;
            return vol_diangkut;
        }
        if (volume <= vol_diangkut) {
            vol_diangkut -= volume;
            if (vol_diangkut == 0) {
                bawa_pasir = false;
            }
            return vol_diangkut;
        }
        return vol_diangkut;
    }

    void tampilkan_status() {
        cout << "\nStatus Mobil Pickup:" << endl;
        cout << "Merk: " << merk << endl;
        cout << "Jenis BBM: " << (jenis_bbm == 1 ? "Bensin" : "Solar") << endl;
        cout << "Isi Silinder: " << isi_silinder << " cc" << endl;
        cout << "Dimensi Bak (p x l x t): " << p_bak << " x " << l_bak << " x " << t_bak << " dm" << endl;
        cout << "Volume Bak: " << get_bak() << " liter" << endl;
        cout << "Berat Maksimal: " << berat_max << " kg" << endl;
        
        // Info BBM dan Perjalanan
        cout << "Kapasitas BBM: " << kapasitas_bbm << " liter" << endl;
        cout << "BBM Saat Ini: " << bbm_saat_ini << " liter" << endl;
        cout << "Konsumsi BBM: " << konsumsi_bbm << " km/liter" << endl;
        cout << "Total Jarak Tempuh: " << jarak_tempuh << " km" << endl;
        cout << "Estimasi Sisa Jarak: " << (bbm_saat_ini * konsumsi_bbm) << " km" << endl;
        
        cout << "Status Muatan: ";
        if (bawa_barang) {
            cout << "Mengangkut Barang (" << brt_diangkut << " kg)" << endl;
        } else if (bawa_pasir) {
            cout << "Mengangkut Pasir (" << vol_diangkut << " liter)" << endl;
        } else {
            cout << "Kosong" << endl;
        }
    }
};

int main() {
    Mobil_pickup pickup;
    string merk;
    int pilihan, jenis_bbm, isi_silinder, p, l, t;
    double berat_max;

    cout << "=== PROGRAM MOBIL PICKUP ===" << endl;
    cout << "Masukkan data mobil pickup:" << endl;
    cout << "Merk (Carry/Grand Max): "; 
    getline(cin, merk);
    pickup.set_merk(merk);

    cout << "Jenis BBM (1: Bensin, 2: Solar): "; 
    cin >> jenis_bbm;
    pickup.set_jenis_bbm(jenis_bbm);

    cout << "Isi Silinder (cc): "; 
    cin >> isi_silinder;
    pickup.set_isi_silinder(isi_silinder);

    cout << "Dimensi Bak (dalam dm)" << endl;
    cout << "Panjang: "; cin >> p;
    cout << "Lebar: "; cin >> l;
    cout << "Tinggi: "; cin >> t;
    pickup.set_bak(p, l, t);

    cout << "Berat Maksimal (kg): "; 
    cin >> berat_max;
    pickup.set_berat_max(berat_max);

    do {
        cout << "\n=== MENU ===" << endl;
        cout << "1. Tampilkan Status Pickup" << endl;
        cout << "2. Isi Barang" << endl;
        cout << "3. Isi Pasir" << endl;
        cout << "4. Turunkan Barang" << endl;
        cout << "5. Turunkan Pasir" << endl;
        cout << "6. Reset Muatan" << endl;
        cout << "7. Isi BBM" << endl;
        cout << "8. Catat Perjalanan" << endl;
        cout << "9. Cek Sisa BBM" << endl;
        cout << "10. Cek Total Jarak Tempuh" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch(pilihan) {
            case 1: {
                pickup.tampilkan_status();
                break;
            }
            case 2: {
                double berat;
                cout << "Masukkan berat barang (kg): ";
                cin >> berat;
                if (pickup.isi_barang(berat)) {
                    cout << "Berhasil menambahkan barang!" << endl;
                } else {
                    cout << "Gagal! Melebihi berat maksimal." << endl;
                }
                break;
            }
            case 3: {
                int volume;
                cout << "Masukkan volume pasir (liter): ";
                cin >> volume;
                if (pickup.isi_pasir(volume)) {
                    cout << "Berhasil menambahkan pasir!" << endl;
                } else {
                    cout << "Gagal! Melebihi kapasitas bak." << endl;
                }
                break;
            }
            case 4: {
                double berat;
                cout << "Masukkan berat barang yang akan diturunkan (kg): ";
                cin >> berat;
                double sisa = pickup.turun_barang(berat);
                cout << "Sisa berat muatan: " << sisa << " kg" << endl;
                break;
            }
            case 5: {
                int volume;
                cout << "Masukkan volume pasir yang akan diturunkan (liter): ";
                cin >> volume;
                int sisa = pickup.turun_pasir(volume);
                cout << "Sisa volume muatan: " << sisa << " liter" << endl;
                break;
            }
            case 6: {
                pickup.set_nilai_angkut();
                cout << "Muatan telah direset!" << endl;
                break;
            }
            case 7: {
                double jumlah;
                cout << "Masukkan jumlah BBM yang akan diisi (liter): ";
                cin >> jumlah;
                if (pickup.isi_bbm(jumlah)) {
                    cout << "Berhasil mengisi BBM!" << endl;
                } else {
                    cout << "Gagal! Melebihi kapasitas tangki." << endl;
                }
                break;
            }
            case 8: {
                double jarak;
                cout << "Masukkan jarak perjalanan (km): ";
                cin >> jarak;
                double biaya = pickup.hitung_biaya_perjalanan(jarak);
                if (pickup.pakai_bbm(jarak)) {
                    cout << "Perjalanan berhasil!" << endl;
                    cout << "Biaya BBM: Rp. " << biaya << endl;
                    cout << "Sisa BBM: " << pickup.cek_sisa_bbm() << " liter" << endl;
                } else {
                    cout << "BBM tidak cukup untuk perjalanan ini!" << endl;
                }
                break;
            }
            case 9: {
                cout << "Sisa BBM saat ini: " << pickup.cek_sisa_bbm() << " liter" << endl;
                break;
            }
            case 10: {
                cout << "Total jarak tempuh: " << pickup.cek_total_jarak() << " km" << endl;
                break;
            }
            case 0: {
                cout << "Program selesai!" << endl;
                break;
            }
            default: {
                cout << "Pilihan tidak valid!" << endl;
            }
        }
    } while (pilihan != 0);

    return 0;
}
