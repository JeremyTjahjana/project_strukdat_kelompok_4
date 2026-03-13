#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <unordered_map>
#include <queue>

using namespace std;
using namespace chrono;

struct Node
{
    char ch;
    int freq;
    Node *left;
    Node *right;
};

Node *createNode(char ch, int freq)
{
    Node *node = new Node();
    node->ch = ch;
    node->freq = freq;
    node->left = node->right = nullptr;
    return node;
}

// comparator untuk priority queue (min heap)
struct compare
{
    bool operator()(Node *l, Node *r)
    {
        return l->freq > r->freq;
    }
};

// Menghitung frekuensi karakter menggunakan unordered_map
unordered_map<char, int> hitungFrekuensiMap(const string &text)
{
    unordered_map<char, int> freq;

    for (char c : text)
        freq[c]++;

    return freq;
}

// Membangun Huffman Tree menggunakan priority queue
Node *buildTreePriorityQueue(unordered_map<char, int> &freq)
{
    priority_queue<Node *, vector<Node *>, compare> pq;

    for (auto pair : freq)
        pq.push(createNode(pair.first, pair.second));

    while (pq.size() > 1)
    {
        Node *left = pq.top();
        pq.pop();

        Node *right = pq.top();
        pq.pop();

        Node *parent = createNode('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;

        pq.push(parent);
    }

    return pq.top();
}

// Membuat kode Huffman
void generateCode(Node *root, string code, unordered_map<char, string> &table)
{
    if (!root)
        return;

    if (!root->left && !root->right)
        table[root->ch] = code;

    generateCode(root->left, code + "0", table);
    generateCode(root->right, code + "1", table);
}

// Encoding teks
string encode(const string &text, unordered_map<char, string> &table)
{
    string result = "";

    for (char c : text)
        result += table[c];

    return result;
}

// Analisis memori
void analisisMemori(string text, string encoded)
{
    size_t original = text.size() * 8;
    size_t compressed = encoded.size();

    cout << "\nAnalisis Memori\n";
    cout << "Memori teks asli: " << original << " bit\n";
    cout << "Memori setelah kompresi: " << compressed << " bit\n";
}

// Menampilkan tabel Huffman
void printTable(unordered_map<char, int> &freq, unordered_map<char, string> &code)
{
    cout << "\nTabel Huffman\n";
    cout << "Karakter\tFrekuensi\tKode\n";

    for (auto pair : freq)
    {
        if (pair.first == ' ')
            cout << "[spasi]";
        else
            cout << pair.first;

        cout << "\t\t" << pair.second << "\t\t" << code[pair.first] << "\n";
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

    unordered_map<char, int> freq = hitungFrekuensiMap(text);

    Node *root = buildTreePriorityQueue(freq);

    unordered_map<char, string> code;

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