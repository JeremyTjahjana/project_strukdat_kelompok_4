#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <unordered_map>

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

unordered_map<char, int> hitungFrekuensiMap(const string &text)
{
    unordered_map<char, int> freq;

    for (char c : text)
        freq[c]++;

    return freq;
}

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

void generateCode(Node *root, string code, unordered_map<char, string> &table)
{
    if (!root)
        return;

    if (!root->left && !root->right)
        table[root->ch] = code;

    generateCode(root->left, code + "0", table);
    generateCode(root->right, code + "1", table);
}

string encode(const string &text, unordered_map<char, string> &table)
{
    string result = "";

    for (char c : text)
        result += table[c];

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

void printTable(unordered_map<char, int> &freq, unordered_map<char, string> &code)
{
    cout << "\nTabel Huffman\n";
    cout << "Karakter\tFrekuensi\tKode\n";

    for (auto &entry : freq)
    {
        char c = entry.first;

        if (c == ' ')
            cout << "[spasi]";
        else
            cout << c;

        cout << "\t\t" << entry.second << "\t\t" << code[c] << "\n";
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

    Node *head = nullptr;

    for (auto &entry : freq)
        insertSorted(head, createNode(entry.first, entry.second));

    Node *root = buildTreeLinkedList(head);

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