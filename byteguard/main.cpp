#include <iostream>
#include <stdlib.h>
#include <openssl/sha.h>
#include <openssl/md5.h>
#include <fstream>
#include <vector>

using namespace std;

int main (int argc, char* argv[]) {
    if (argc != 4 || (string(argv[1]) != "sha256" && string(argv[1]) != "md5")) {
        cout << argc << endl;
        cout << argv[1] << endl;

        cout << "Usage: byteguard <algorithm> <expected_hash> <file>"
            "\n\n"
            "Arguments:\n"
            "\talgorithm        Hash algorithm (sha256 | md5)\n"
            "\texpected_hash    Original hash to verify against\n"
            "\tfile             Path to the file"
            "\n\n"
            "Example:\n"
            "\tbyteguard sha256 d2d2d2... file.txt" << endl;

        return 1;
    }

    string algorithm = argv[1];
    string original_hash = argv[2];
    string file_path = argv[3];

    ifstream file(file_path, std::ios::binary);
    vector <char> buffer(8192);

    string computed_hash = "";

    if (algorithm == "sha256") {
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
    
        while(file.good()) {
            file.read(buffer.data(), buffer.size());
            SHA256_Update(&sha256, buffer.data(), file.gcount());
        }
    
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_Final(hash, &sha256);
    
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            char buff[3];
            sprintf(buff, "%02x", hash[i]);
            computed_hash += buff;
        }
    }
    else if (algorithm == "md5") {
        MD5_CTX md5;
        MD5_Init(&md5);
        
        while(file.good()) {
            file.read(buffer.data(), buffer.size());
            MD5_Update(&md5, buffer.data(), file.gcount());
        }
    
        unsigned char hash[MD5_DIGEST_LENGTH];
        MD5_Final(hash, &md5);
    
        for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
            char buff[3];
            sprintf(buff, "%02x", hash[i]);
            computed_hash += buff;
        }
    }
    else {
        cout << "Error: Invalid Algorithm";
    }
    cout << endl;

    cout << "Original Hash:\t" << original_hash << endl;

    if (original_hash == computed_hash) {
        cout << "Computed Hash:\t\033[32m" << computed_hash << endl;
        cout << "File is safe!" << endl;
    }
    else {
        cout << "Computed Hash:\t\033[31m" << computed_hash << endl;
        cout << "File is corrupted, try downloading it again!" << endl;
    }

    return 0;
}