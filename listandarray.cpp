#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;

struct Node
{
    char ch;
    int freq;
    Node *left;
    Node *right;
    Node *next;
};

Node *createNode(char ch, int freq)
{
    Node *node = new Node();
    node->ch = ch;
    node->freq = freq;
    node->left = node->right = node->next = nullptr;
    return node;
}

// Menghitung frekuensi karakter dalam string menggunakan array
vector<int> hitungFrekuensiArray(const string &text)
{

    vector<int> freq(256, 0);

    for (char c : text)
        freq[(unsigned char)c]++;

    return freq;
}

// Menyisipkan node baru ke dalam linked list yang sudah terurut berdasarkan frekuensi.
void insertSorted(Node *&head, Node *newNode)
{

    if (head == nullptr || newNode->freq < head->freq)
    {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node *temp = head;

    while (temp->next && temp->next->freq <= newNode->freq)
        temp = temp->next;

    newNode->next = temp->next;
    temp->next = newNode;
}

// Membangun pohon Huffman menggunakan linked list yang sudah terurut berdasarkan frekuensi.
Node *buildTreeLinkedList(Node *&head)
{

    while (head && head->next)
    {

        Node *left = head;
        Node *right = head->next;

        head = right->next;

        Node *parent = createNode('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;

        insertSorted(head, parent);
    }

    return head;
}

// Menghasilkan kode Huffman untuk setiap karakter dengan melakukan traversal pada pohon Huffman.
void generateCode(Node *root, string code, vector<string> &table)
{

    if (!root)
        return;

    if (!root->left && !root->right)
        table[(unsigned char)root->ch] = code;

    generateCode(root->left, code + "0", table);
    generateCode(root->right, code + "1", table);
}

// Mengubah string asli menjadi string biner berdasarkan kode Huffman yang dihasilkan.
string encode(const string &text, vector<string> &table)
{

    string result = "";

    for (char c : text)
        result += table[(unsigned char)c];

    return result;
}

// Menganalisis memori yang digunakan sebelum dan setelah kompresi.
void analisisMemori(string text, string encoded)
{

    size_t original = text.size() * 8;
    size_t compressed = encoded.size();

    cout << "\nAnalisis Memori\n";
    cout << "Memori teks asli: " << original << " bit\n";
    cout << "Memori setelah kompresi: " << compressed << " bit\n";
}

// Menampilkan tabel karakter, frekuensi, dan kode Huffman yang dihasilkan.
void printTable(vector<int> &freq, vector<string> &code)
{

    cout << "\nTabel Huffman\n";
    cout << "Karakter\tFrekuensi\tKode\n";

    for (int i = 0; i < 256; i++)
    {
        if (freq[i] > 0)
        {

            if ((char)i == ' ')
                cout << "[spasi]";
            else
                cout << (char)i;

            cout << "\t\t" << freq[i] << "\t\t" << code[i] << "\n";
        }
    }
}

int main()
{

    ifstream file("input.txt");

    if (!file.is_open())
    {
        cout << "File input.txt tidak ditemukan\n";
        return 0;
    }

    string text, line;

    while (getline(file, line))
    {
        text += line;
        text += " ";
    }

    file.close();

    cout << "Input teks:\n"
         << text << "\n\n";

    auto start = high_resolution_clock::now();

    vector<int> freq = hitungFrekuensiArray(text);

    Node *head = nullptr;

    // Menyisipkan karakter dan frekuensi ke dalam linked list yang terurut berdasarkan frekuensi.
    for (int i = 0; i < 256; i++)
        if (freq[i] > 0)
            insertSorted(head, createNode((char)i, freq[i]));

    Node *root = buildTreeLinkedList(head);

    vector<string> code(256);

    generateCode(root, "", code);

    string encoded = encode(text, code);

    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);

    printTable(freq, code);

    cout << "\nString Biner Hasil Encoding:\n";
    cout << encoded << "\n";

    cout << "\nWaktu Eksekusi: " << duration.count() << " microseconds\n";
    cout << "\n=== ujung program ===\n";

    analisisMemori(text, encoded);
}