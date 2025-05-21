#include <iostream>
using namespace std;

struct Buku
{
    char judul[50];
    char penulis[50];
};

struct Node
{
    Buku data;
    Node *next;
    Node *prev;
};

Node *buatNode(Buku data)
{
    Node *newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    return newNode;
}

void sisipDepan(Node **head, Buku data)
{
    Node *newNode = buatNode(data);
    newNode->next = *head;
    if (*head != NULL)
    {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

void sisiBelakang(Node **head, Buku data)
{
    Node *newNode = buatNode(data);
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }
    Node *bantu = *head;
    while (bantu->next != NULL)
    {
        bantu = bantu->next;
    }
    bantu->next = newNode;
    newNode->prev = bantu;
}

bool cariBuku(char a[], char b[])
{
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0')
    {
        if (a[i] != b[i])
            return false;
        i++;
    }
    return (a[i] == '\0' && b[i] == '\0');
}

void hapusBuku(Node **head, char judul[])
{
    if (*head == NULL)
    {
        cout << "List Kosong" << endl;
        return;
    }

    Node *bantu = *head;
    while (bantu != NULL)
    {
        if (cariBuku(bantu->data.judul, judul))
        {
            Node *hapus = bantu;
            if (bantu == *head)
            {
                *head = bantu->next;
                if (*head != NULL)
                {
                    (*head)->prev = NULL;
                }
            }
            else
            {
                bantu->prev->next = bantu->next;
                if (bantu->next != NULL)
                {
                    bantu->next->prev = bantu->prev;
                }
            }
            bantu = bantu->next;
            delete hapus;
            cout << "Buku dengan judul " << judul << " berhasil dihapus." << endl;
            return;
        }
        bantu = bantu->next;
    }
    cout << "Buku dengan judul " << judul << " tidak ditemukan." << endl;
}

void tampilBuku(Node *head)
{
    if (head == nullptr)
    {
        cout << "Daftar buku kosong." << endl;
        return;
    }
    Node *bantu = head;
    int i = 1;
    cout << "=== Daftar Buku ===" << endl;
    while (bantu != nullptr)
    {
        cout << i << ". " << bantu->data.judul << " - " << bantu->data.penulis << endl;
        bantu = bantu->next;
        i++;
    }
}

void menu(Node *&head)
{
    int pilihan;
    Buku data;
    char cariJudul[50];

    do
    {
        cout << "=== MENU MANAJEMEN DAFTAR BUKU ===" << endl;
        cout << "1. Tambah Buku di Depan" << endl;
        cout << "2. Tambah Buku di Belakang" << endl;
        cout << "3. Hapus Buku berdasarkan Judul" << endl;
        cout << "4. Tampilkan Daftar Buku" << endl;
        cout << "5. Keluar" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan)
        {
        case 1:
            cout << "Masukkan Judul Buku: ";
            cin.getline(data.judul, 50);
            cout << "Masukkan Nama Penulis: ";
            cin.getline(data.penulis, 50);
            sisipDepan(&head, data);
            break;

        case 2:
            cout << "Masukkan Judul Buku: ";
            cin.getline(data.judul, 50);
            cout << "Masukkan Nama Penulis: ";
            cin.getline(data.penulis, 50);
            sisiBelakang(&head, data);
            break;

        case 3:
            cout << "Masukkan Judul Buku yang ingin dihapus: ";
            cin.getline(cariJudul, 50);
            hapusBuku(&head, cariJudul);
            break;

        case 4:
            cout << "=== DAFTAR BUKU ===" << endl;
            tampilBuku(head);
            break;

        case 5:
            cout << "Keluar dari program." << endl;
            break;

        default:
            cout << "Pilihan tidak valid." << endl;
            break;
        }

    } while (pilihan != 5);
}

int main()
{
    Node *head = nullptr;
    menu(head);
    return 0;
}