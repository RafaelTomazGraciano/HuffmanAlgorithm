# Huffman Algorithm

![C Language](https://img.shields.io/badge/language-C-blue.svg)

## Project Description

This project implements the Huffman coding algorithm in C, a widely used method for lossless data compression.

## How it Works

The Huffman Algorithm project processes an input text file (`input.txt`) through several key stages to achieve compression and decompression:

1.  **File Reading**: The program first reads the content of the `input.txt` file into memory.

2.  **Frequency Table Creation**: It then constructs a frequency table, counting the occurrences of each character in the input text. This table is crucial for determining the probability of each character, which is fundamental to Huffman coding.

3.  **Ordered List Generation**: Based on the frequency table, an ordered list (min-priority queue) of nodes is created. Each node represents a character and its frequency, and the list is sorted in ascending order of frequencies.

4.  **Huffman Tree Construction**: The core of the algorithm involves building the Huffman tree. This is done by repeatedly combining the two nodes with the lowest frequencies from the ordered list, creating a new parent node whose frequency is the sum of its children's frequencies. This process continues until only one node remains, which is the root of the Huffman tree.

5.  **Dictionary Generation**: Once the Huffman tree is built, a unique binary code (the dictionary) is generated for each character by traversing the tree. A '0' is assigned for a left traversal and a '1' for a right traversal. Characters with higher frequencies will naturally have shorter codes.

6.  **Encoding**: The original input text is then encoded using the generated Huffman dictionary, converting the character stream into a binary string.

7.  **Decoding**: For verification and demonstration, the encoded binary string can be decoded back into the original text using the Huffman tree, proving the lossless nature of the compression.

8.  **Compression**: The encoded binary string is written to a file (`compressed.huff`) in a byte-efficient manner. This involves packing the bits into bytes to minimize file size.

9.  **Decompression**: Finally, the `compressed.huff` file can be decompressed using the Huffman tree to reconstruct the original `output.txt` file, which should be identical to the initial `input.txt`.



## How to Run

To compile and run this Huffman Algorithm project, follow these steps:

1.  **Clone the repository**:

    ```bash
    git clone https://github.com/RafaelTomazGraciano/HuffmanAlgorithm.git
    ```
1.  **Open directory**:

    ```bash
    cd HuffmanAlgorithm
    ```

3.  **Prepare the input file**:

    Place your desired text content in a file named `input.txt` in the root directory of the cloned repository. This will be the file that the Huffman algorithm compresses.

4.  **Compile the project**:

    The project includes a `makefile` for easy compilation. Open your terminal in the `HuffmanAlgorithm` directory and run:

    ```bash
    make
    ```

    This command will compile `HuffmanAlgorithm.c` and `functions.c` and create an executable file named `huffman`.

5.  **Run the executable**:

    Execute the compiled program:

    ```bash
    ./huffman
    ```

    Upon execution, the program will:
    *   Read content from `input.txt`.
    *   Generate `compressed.huff` (the compressed output).
    *   Generate `output.txt` (the decompressed output, which should be identical to `input.txt`).
