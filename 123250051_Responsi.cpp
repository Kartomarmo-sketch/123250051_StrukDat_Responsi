#include <iostream>

using namespace std;

struct nodeQueue {
    int kode;
    string nama;
    nodeQueue* next;
};

struct nodeStack {
    int kode;
    string nama;
    nodeStack* next;
};

struct nodeTree {
    int kode;
    string nama;
    nodeTree* kiri;
    nodeTree* kanan;
};

nodeQueue* front = NULL;
nodeQueue* last = NULL;
nodeStack* top = NULL;
nodeTree* root = NULL;

nodeTree* tambah_tree(nodeTree* akar, int kode, string nama){
    if (akar == NULL){
        return new nodeTree {kode, nama, NULL, NULL};
    }

    if (kode < akar->kode) {
        akar->kiri = tambah_tree(akar->kiri, kode, nama);
    }else {
        akar->kanan = tambah_tree(akar->kanan, kode, nama);
    }
    return akar;
}

nodeTree* cari_tree(nodeTree* akar, int kode){
if (akar == NULL || akar->kode == kode){
    return akar;
}
if (kode < akar->kode){
    return cari_tree(akar->kiri, kode);
}
return cari_tree(akar->kanan, kode);
}

nodeTree* hapus_tree(nodeTree* akar, int kode){
if (akar == NULL){
    return NULL;
}
if (kode < akar->kode){
    akar->kiri = hapus_tree(akar->kiri,kode);
}else if(kode > akar->kode){
    akar->kanan = hapus_tree(akar->kanan,kode);
} else{
    if (akar->kiri == NULL){
        nodeTree* temp = akar->kanan;
        delete akar;
        return temp;
    }else if (akar->kanan == NULL){
        nodeTree* temp = akar->kiri;
        delete akar;
        return temp;
    }
    nodeTree* temp = akar->kanan;
    while (temp->kiri !=NULL){
        temp = temp->kiri;
    }
    akar->kode=temp->kode;
    akar->nama=temp->nama;
    akar->kanan=hapus_tree(akar->kanan,temp->kode);
}
return akar;
}

void preorder(nodeTree* akar, int& no){
if (akar == NULL){
    return;
}
cout << no << ". [" << akar->kode << "]" << akar->nama << endl;
no++;
preorder(akar->kiri, no);
preorder(akar->kanan, no);
}

void inorder(nodeTree* akar, int& no){
if (akar == NULL){
    return;
}
preorder(akar->kiri, no);
cout << no << ". [" << akar->kode << "]" << akar->nama << endl;
no++;
preorder(akar->kanan, no);    
}

void postorder(nodeTree* akar, int& no){
if (akar == NULL){
    return;
}
preorder(akar->kiri, no);
preorder(akar->kanan, no);  
cout << no << ". [" << akar->kode << "]" << akar->nama << endl;
no++;  
}

void tambah_energi(){
    int kode;
    string nama;
    cout << "Masukkan kode energi: ";
    cin >> kode;
    if (cin.fail() || kode <=0){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Nomor kode harus berupa angka > 0!" << endl << endl;
        return;
    }

    nodeQueue* q = front;
    while (q != NULL) {
        if (q->kode == kode){
            cout << "kode yang anda masukkan sudah terpakai!"<<endl<<endl;
            return;
        }
        q = q->next;
    }

    nodeStack* s = top;
    while (q != NULL) {
        if (q->kode == kode){
            cout << "kode yang anda masukkan sudah terpakai!"<<endl<<endl;
            return;
        }
        s = s->next;
    }

    cout << "Masukkan nama energi anda: ";
    cin.ignore();
    getline(cin, nama);
    if(nama.empty()){
        cout <<"nama energi harus diisi!"<<endl<<endl;
        return;
    }

    nodeQueue* nb = new nodeQueue {kode, nama, NULL};
    if (front == NULL){
        front = last = nb;
    }else {
        last->next = nb;
        last = nb;
    }
    cout << "Berhasil masukkan energi!"<<endl << endl;
}

void lihat_antrean(){
    if (front == NULL) {
        cout << "Antrean energi masih kosong" << endl<<endl;
        return;
    }

    cout << "====energi yang tersedia dalam antrean==="<<endl<<endl;
    nodeQueue* nb = front;
    int no = 1;
    while (nb != NULL){
        cout << no << ". [" << nb->kode << "]" << nb->nama << endl;
        nb = nb->next;
        no++;
    }
    cout << endl;
}

void proses_energi(){
    if (front == NULL) {
        cout << "Antrean energi masih kososng" << endl<<endl;
        return;
    }
    
    nodeQueue* hapus = front;
    nodeStack* nb = new nodeStack {hapus->kode, hapus->nama, top};
    top = nb;
    root = tambah_tree(root, hapus->kode, hapus->nama);
    cout << "Berhasil memproses energi " << hapus->nama << "!" << endl << endl;
    front = hapus->next;
    if (front == NULL){
        last = NULL;
    }
    delete hapus;
}

void riwayat(){
    if (top == NULL){
         cout << "Energi yang sudah diproses masih kosong!" << endl<<endl;
        return;       
    }
    cout << "===energi yang sudah selesai==" << endl <<endl;
    nodeStack* nb = top;
    int no = 1;
    while (nb != NULL){
        cout << no << ". [" << nb->kode << "]" << nb->nama << endl;
        nb = nb->next;
        no++;
    }
    cout << endl;    
}

void hapus_atas(){
    if (top == NULL){
         cout << "Energi yang sudah diproses masih kosong!" << endl<<endl;
        return;       
    }
    
    nodeStack* hapus = top;
    top = hapus->next;
    cout << "Riwayat Energi "<< hapus->nama <<" teratas telah dihapus."<<endl<<endl;
    delete hapus;
}

void cari_energi(){
    if (root == NULL){
        cout << "Organ belum ada isinya!" << endl << endl;
        return;
    }

    int kode;
    cout << "Masukkan kode energi: ";
    cin >> kode;
    if (cin.fail() || kode <=0){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Nomor kode harus berupa angka > 0!" << endl << endl;
        return;
    }
    nodeTree* hasil = cari_tree(root, kode);
    if (hasil == NULL){
        cout << "Energi dengan kode " << kode << "tidak terdapat di dalam organ!" << endl << endl;
        return;
    }
    cout << "Ditemukan: [" << hasil->kode << "]" << hasil->nama << endl<<endl;
}

void isi_organ(){
    if (root == NULL){
        cout << "Organ belum ada isinya!" << endl << endl;
        return;
    }
    
    char pil;
    int no = 1;
    cout << "===isi organ yang tersedia=="<< endl << endl;
    cout << "1. Pre-order"<<endl;
    cout << "1. In-order"<<endl;
    cout << "1. Post-order"<<endl << endl;
    cout << "Masukkan pilihan anda: ";
    cin >> pil;
    cout << endl;
    switch(pil) {
        case '1':{
            preorder(root, no);
            break;
        }
        case '2':{
            inorder(root, no);
            break;
        }
        case '3':{
            postorder(root, no);
            break;
        }
        default: {
            cout << "Pilihan yang anda masukkan salah!"<<endl;
        }
    }
    cout <<endl;
}

void gunakan_energi(){
    if (root == NULL){
        cout << "Organ belum ada isinya!" << endl << endl;
        return;
    }
    
    int kode;
    cout << "masukkan kode energi: ";
    cin >> kode;
        if (cin.fail() || kode <=0){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Nomor kode harus berupa angka > 0!" << endl << endl;
        return;
    }

    nodeTree* hasil = cari_tree(root,kode);
    if (hasil == NULL){
        cout << "energi dengan kode " << kode << " tidak ada dalam organ!"<<endl<<endl;
        return;
    }

    cout << "Energi "<< hasil->nama << "berhasil digunakan!"<<endl<<endl;
    root = hapus_tree(root, kode);
}

int main(){
    char pil = '0';
    while (pil !='9'){
        cout << "=== Sistem Organ Inti Nirwana ==="<<endl<<endl;
        cout << "1. Tambah Energi" <<endl;
        cout << "2. Lihat Energi Dalam Antran" <<endl;
        cout << "3. Proses Energi" <<endl;
        cout << "4. Lihat Energi Yang Sudah Terserap" <<endl;
        cout << "5. Hapus Riwayat Energi Teratas" <<endl;
        cout << "6. Cari Energi di Organ" <<endl;
        cout << "7. Lihat Isi Organ" <<endl;
        cout << "8. Gunakan Energi" <<endl;
        cout << "9. Keluar" <<endl;
        cout << "Masukkan Pilihan Anda: ";
        cin >> pil;
        switch(pil){
            case '1': {
                char pil_tambah = 'y';
                while (pil_tambah == 'y' || pil_tambah == 'Y') {
                    tambah_energi();
                    cout << "Apakah anda ingin menambah energi lagi? (y/n) :";
                    cin >> pil_tambah;
                }
                break;
            }
            case '2': {
                lihat_antrean();
                break;
            }
            case '3': {
                proses_energi();
                break;
            } 
            case '4': {
                riwayat();
                break;
            }  
            case '5': {
                hapus_atas();
                break;
            }   
            case '6': {
                cari_energi();
                break;
            }    
            case '7': {
                isi_organ();
                break;
            }
            case '8': {
                gunakan_energi();
                break;
            }    
            case '9': {
                cout << "Program akan dikeluarkan.";
                exit(0);
            }         
            default: {
                cout << "pilihan yang anda masukkan salah!" << endl;
                cout << "Silahkan coba lagi!"<<endl<<endl;
            }
        }

    }
}