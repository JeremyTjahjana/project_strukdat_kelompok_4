#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <chrono>

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
// buat bandingin priority queue
struct Compare
{
    bool operator()(Node *a, Node *b)
    {
        return a->freq > b->freq; // min-heap: frekuensi terkecil di atas
    }
};
// itung freq character pake arr
vector<int> hitungFrekuensiArray(const string &text)
{
    vector<int> freq(256, 0);

    for (char c : text)
        freq[(unsigned char)c]++;

    return freq;
}

// tree huffmann - priority queue
Node *buildTreePriorityQueue(vector<int> &freq)
{
    priority_queue<Node *, vector<Node *>, Compare> pq;

    // inp character dan freq
    for (int i = 0; i < 256; i++)
        if (freq[i] > 0)
            pq.push(createNode((char)i, freq[i]));

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
void generateCode(Node *root, string code, vector<string> &table)
{
    if (!root)
        return;

    if (!root->left && !root->right)
        table[(unsigned char)root->ch] = code;

    generateCode(root->left, code + "0", table);
    generateCode(root->right, code + "1", table);
}
string encode(const string &text, vector<string> &table)
{
    string result = "";

    for (char c : text)
        result += table[(unsigned char)c];

    return result;
}
void analisisMemori(string text, string encoded)
{
    size_t original = text.size() * 8;
    size_t compressed = encoded.size();

    cout << "\nAnalisis Memori\n";
    cout << "Memori teks asli: " << original << " bit\n";
    cout << "Memori setelah kompresi: " << compressed << " bit\n";
}
// tabel character, freq, code huffman
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
    ifstream file("project_strukdat_kelompok_4/input.txt");
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

    // hitung freq dgn arr
    vector<int> freq = hitungFrekuensiArray(text);

    // huffman tree pake priority queue
    Node *root = buildTreePriorityQueue(freq);

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