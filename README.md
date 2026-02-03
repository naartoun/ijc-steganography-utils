# C Steganography & Bitset Utilities

A low-level C implementation of steganographic tools designed to conceal messages within **PPM images** using Least Significant Bit (LSB) manipulation. The project is built upon a custom, highly optimized **Bitset library** that manages memory at the bit level.

## 🧩 Core Components

### 1. Custom Bitset Implementation (`bitset.h`)
Instead of using standard arrays, this project implements a memory-efficient bit array structure capable of handling millions of bits with minimal overhead.
* **Dual Implementation:** The library offers two compilation modes for performance analysis:
    * **Macros:** Preprocessor-expanded logic for zero-overhead execution.
    * **Inline Functions:** Type-safe alternatives (`-DUSE_INLINE`) for better debugging and safety.
* **Features:**
    * Dynamic allocation (`bitset_alloc`) vs. Static stack allocation (`bitset_create`).
    * `O(1)` bit manipulation (set, get, toggle) using bitwise operators.
    * Boundary checks and `static_assert` for compile-time safety.

### 2. Steganography Decoder (`steg-decode.c`)
The core utility reads a binary **PPM (Portable Pixel Map)** image and extracts a hidden message.
* **Algorithm:** The message is encoded in the **Least Significant Bits (LSB)** of specific color bytes.
* **Security:** Instead of using sequential bytes, the data is distributed based on **Prime Numbers** calculated via the Sieve of Eratosthenes, making linear detection difficult.
* **Input:** Binary PPM format (P6), handling raw RGB data buffers.



### 3. Sieve of Eratosthenes (`eratosthenes.c`)
An optimized implementation of the prime number finding algorithm used to determine the data distribution pattern.
* Implemented using the custom Bitset library to minimize memory footprint.
* Capable of sieving primes up to N = 333,000,000 efficiently.



## 🔧 Build

The project uses a `Makefile` to manage build targets and optimization flags (`-O2`, `-g`).

### Compilation
```bash
# Build standard version (Macros)
make

# Build version with Inline Functions (for profiling)
make primes-i
```
### Usage

**Decoding a hidden message:**
```bash
./steg-decode secret_image.ppm
```
## ⚠️ Academic Integrity Disclaimer
This repository contains the source code for a university project. It is published for **educational and portfolio purposes only**.
Current students of FIT VUT are strongly advised **not to copy** any part of this code for their own assignments, as it may violate academic integrity policies and result in disciplinary action.

