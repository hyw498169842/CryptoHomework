#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

typedef uint8_t Byte;

int main(int argc, char **argv) {
    // input error check
    if (argc != 3) {
        cout << "Usage: ./RC4 [file name] [encrypt flag]" << endl;
        cout << "Or use 'make encrypt' with default plaintext" << endl;
        cout << "Or use 'make decrypt' with default ciphertext" << endl;
        exit(-1);
    }

    bool encrypt = atoi(argv[2]);
    // read key and start timing
    Byte key[128];
    ifstream fin("key", ios::binary);
    fin.read((char *)key, 128);
    fin.close();
    clock_t start = clock();
    // key-scheduling algorithm
    Byte S[256];
    for (int i = 0; i < 256; ++i) {
        S[i] = i;
    }
    for (int i = 0, j = 0; i < 256; ++i) {
        j = (j + S[i] + key[i & 0x7F]) & 0xFF;
        swap(S[i], S[j]);
    }
    // generate key stream
    Byte keyStream[2048];
    for (int i = 0, j = 0, k = 0; i < 2048; ++i) {
        j = (j + 1) & 0xFF;
        k = (k + S[j]) & 0xFF;
        swap(S[j], S[k]);
        keyStream[i] = S[(S[j] + S[k]) & 0xFF];
    }
    // encrypt and decrypt
    if (encrypt) {
        // read plain text
        ifstream fin(argv[1], ios::binary);
        Byte plaintext[2048], ciphertext[2048];
        fin.read((char *)plaintext, 2048);
        fin.close();
        // start encryption
        for (int i = 0; i < 2048; ++i) {
            ciphertext[i] = plaintext[i] ^ keyStream[i];
        }
        clock_t finish = clock();
        cout << "Time usage: " << (finish - start + 0.0) / CLOCKS_PER_SEC << endl;
        cout << "Encryption rate: " <<  CLOCKS_PER_SEC / (64 * (finish - start)) << " Mbps" << endl;
        // write result
        ofstream fout("encrypted", ios::binary);
        fout.write((char *)ciphertext, 2048);
        fout.close();
    } else {
        // read cipher text
        ifstream fin(argv[1], ios::binary);
        Byte plaintext[2048], ciphertext[2048];
        fin.read((char *)ciphertext, 2048);
        fin.close();
        // start decryption
        for (int i = 0; i < 2048; ++i) {
            plaintext[i] = ciphertext[i] ^ keyStream[i];
        }
        clock_t finish = clock();
        cout << "Time usage: " << (finish - start + 0.0) / CLOCKS_PER_SEC << endl;
        cout << "Decryption rate: " <<  CLOCKS_PER_SEC / (64 * (finish - start)) << " Mbps" << endl;
        // write result
        ofstream fout("decrypted", ios::binary);
        fout.write((char *)plaintext, 2048);
        fout.close();
    }
    // write the key stream
    ofstream fout("keystream", ios::binary);
    fout.write((char *)keyStream, 2048);
    fout.close();
    return 0;
}
