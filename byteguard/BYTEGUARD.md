# Byteguard
**Byteguard** is a lightweight command-line tool written in C++ for verifying file integrity using cryptographic hash functions. It computes the hash of a file and compares it against a provided reference hash.

## Features
- Supports **SHA-256** and **MD5**
- Memory-efficient (reads files in chunks)

## Usage
```bash
byteguard <algorithm> <expected_hash> <file>
```

### Arguments
- `algorithm` — Hash algorithm to use (`sha256` | `md5`)
- `expected_hash` — Original hash value (hex string)
- `file` — Path to the file

## Example
```bash
byteguard sha256 d77eb5f888937528a53c0155844391a10505a749ec87119b981fdd76d297c83b file.txt
```

## Build Instructions

### Requirements
- C++ compiler (g++)
- OpenSSL development libraries

```bash
sudo apt install libssl-dev
```

### Compile
```bash
g++ main.cpp -o byteguard -lssl -lcrypto
```

## How It Works
1. Opens the file in **binary mode**
2. Reads the file in **8KB chunks**
3. Feeds each chunk into the hash function
4. Converts the final hash to a **hex string**
5. Compares it with the provided hash
