#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>

using namespace std;

typedef uint8_t Byte;
typedef uint64_t Lane;

// parameters of SHA-3-256
const int b = 1600;
const int r = 1088;
const int c = 512;
const int rate = 136;
const int rot[24] = {
     1,  3,  6, 10, 15, 21, 28, 36, 45, 55,  2, 14,
    27, 41, 56,  8, 25, 43, 62, 18, 39, 61, 20, 44
};
const int pi[24] = {
    10,  7, 11, 17, 18,  3,  5, 16,  8, 21, 24,  4,
    15, 23, 19, 13, 12,  2, 20, 14, 22,  9,  6,  1
};
const Lane iota[24] = {
    0x0000000000000001, 0x0000000000008082, 0x800000000000808a,
    0x8000000080008000, 0x000000000000808b, 0x0000000080000001,
    0x8000000080008081, 0x8000000000008009, 0x000000000000008a,
    0x0000000000000088, 0x0000000080008009, 0x000000008000000a,
    0x000000008000808b, 0x800000000000008b, 0x8000000000008089,
    0x8000000000008003, 0x8000000000008002, 0x8000000000000080,
    0x000000000000800a, 0x800000008000000a, 0x8000000080008081,
    0x8000000000008080, 0x0000000080000001, 0x8000000080008008
};

void KECCAK_p(Byte S[]) {
    #define ROTL(x, n) (((x) << (n)) | ((x) >> (64 - n)))
    Lane C[5], *lane = (Lane *)S;
    for (int i = 0; i < 24; ++i) {
        // theta function
        C[0] = lane[0] ^ lane[5] ^ lane[10] ^ lane[15] ^ lane[20];
        C[1] = lane[1] ^ lane[6] ^ lane[11] ^ lane[16] ^ lane[21];
        C[2] = lane[2] ^ lane[7] ^ lane[12] ^ lane[17] ^ lane[22];
        C[3] = lane[3] ^ lane[8] ^ lane[13] ^ lane[18] ^ lane[23];
        C[4] = lane[4] ^ lane[9] ^ lane[14] ^ lane[19] ^ lane[24];
        for (int y = 0; y < 25; y += 5) {
            lane[0 + y] ^= C[4] ^ ROTL(C[1], 1);
            lane[1 + y] ^= C[0] ^ ROTL(C[2], 1);
            lane[2 + y] ^= C[1] ^ ROTL(C[3], 1);
            lane[3 + y] ^= C[2] ^ ROTL(C[4], 1);
            lane[4 + y] ^= C[3] ^ ROTL(C[0], 1);
        }
        // rho function and pi function
        Lane walker = lane[1], temp = lane[pi[0]];
        for (int t = 0; t < 24; temp = lane[pi[++t]]) {
            lane[pi[t]] = ROTL(walker, rot[t]);
            walker = temp;
        }
        // chi function
        for (int y = 0; y < 25; y += 5) {
            C[0] = lane[0 + y];
            C[1] = lane[1 + y];
            C[2] = lane[2 + y];
            C[3] = lane[3 + y];
            C[4] = lane[4 + y];
            lane[0 + y] ^= (~C[1]) & C[2];
            lane[1 + y] ^= (~C[2]) & C[3];
            lane[2 + y] ^= (~C[3]) & C[4];
            lane[3 + y] ^= (~C[4]) & C[0];
            lane[4 + y] ^= (~C[0]) & C[1];
        }
        // iota function
        lane[0] ^= iota[i];
    }
}

int main(int argc, char **argv) {
    // input error check
    if (argc != 2) {
        cout << "Usage: ./SHA-3-256 [file name]" << endl;
        cout << "Or use 'make encrypt' with default plaintext" << endl;
        exit(-1);
    }
    // read plaintext and make padding
    const int paddedSize = (16 * 1024 / r + 1) * rate;
    Byte plaintext[paddedSize];
    ifstream fin(argv[1], ios::binary);
    fin.read((char *)plaintext, 2048);
    fin.close();
    memset(&plaintext[2048], 0, paddedSize - 2048);
    plaintext[2048] = 0x06;
    plaintext[paddedSize - 1] = 0x80;
    // start encryption
    clock_t start = clock();
    Byte S[b]; memset(S, 0, b);
    Lane *SLane = (Lane *)S, *plainLane = (Lane *)plaintext;
    for (int i = 0; i < 272; i += 17, KECCAK_p(S)) {
        SLane[0]  ^= plainLane[0 + i];
        SLane[1]  ^= plainLane[1 + i];
        SLane[2]  ^= plainLane[2 + i];
        SLane[3]  ^= plainLane[3 + i];
        SLane[4]  ^= plainLane[4 + i];
        SLane[5]  ^= plainLane[5 + i];
        SLane[6]  ^= plainLane[6 + i];
        SLane[7]  ^= plainLane[7 + i];
        SLane[8]  ^= plainLane[8 + i];
        SLane[9]  ^= plainLane[9 + i];
        SLane[10] ^= plainLane[10 + i];
        SLane[11] ^= plainLane[11 + i];
        SLane[12] ^= plainLane[12 + i];
        SLane[13] ^= plainLane[13 + i];
        SLane[14] ^= plainLane[14 + i];
        SLane[15] ^= plainLane[15 + i];
        SLane[16] ^= plainLane[16 + i];
    }
    Lane result[34]; memcpy(result, SLane, rate);
    KECCAK_p(S); memcpy(result + 17, SLane, rate);
    clock_t finish = clock();
    cout << "Time usage: " << (finish - start + 0.0) / CLOCKS_PER_SEC << endl;
    cout << "Encryption rate: " <<  CLOCKS_PER_SEC / (64 * (finish - start)) << " Mbps" << endl;
    // write back the result
    ofstream fout("encrypted", ios::binary);
    fout.write((char *)result, 32);
    fout.close();
    return 0;
}
