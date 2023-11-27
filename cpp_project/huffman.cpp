#include <iostream>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <sstream>

using namespace std;

// Define Huffman tree node
struct HuffmanNode {
    char data;
    unsigned frequency;
    HuffmanNode* left, * right;

    HuffmanNode(char data, unsigned frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

// Comparison function for priority queue
struct Compare {
    bool operator()(HuffmanNode* left, HuffmanNode* right) {
        return left->frequency > right->frequency;
    }
};

// Function to build Huffman tree and return the root
HuffmanNode* buildHuffmanTree(priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare>& minHeap) {
    while (minHeap.size() != 1) {
        HuffmanNode* left = minHeap.top();
        minHeap.pop();

        HuffmanNode* right = minHeap.top();
        minHeap.pop();

        HuffmanNode* newNode = new HuffmanNode('$', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        minHeap.push(newNode);
    }

    return minHeap.top();
}

// Function to traverse the Huffman tree and generate codes
void generateCodes(HuffmanNode* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (root) {
        if (!root->left && !root->right) {
            huffmanCodes[root->data] = code;
        }

        generateCodes(root->left, code + "0", huffmanCodes);
        generateCodes(root->right, code + "1", huffmanCodes);
    }
}

// Function to encode the input text using Huffman codes
string encodeText(string text, unordered_map<char, string>& huffmanCodes) {
    string encodedText = "";
    for (char c : text) {
        encodedText += huffmanCodes[c];
    }
    return encodedText;
}

// Function to print the encoded text
void printEncodedText(string encodedText) {
    cout << "Encoded Text: " << encodedText << endl;
}

int main() {
    const char* fileName = "input.txt";

    // Open the file
    std::ifstream inputFile(fileName);

    // Check if the file is open
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;  // Return an error code
    }

    // Read the content of the file into a string
    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string fileContent = buffer.str();

    // Close the file
    inputFile.close();

    // Display or use the content as needed
    std::cout << "Content of the input file:\n" << fileContent << std::endl;

    // Use fileContent to continue with Huffman coding

    // Count frequency of each character in the input text
    unordered_map<char, unsigned> frequencyMap;
    for (char c : fileContent) {
        frequencyMap[c]++;
    }

    // Create a priority queue of Huffman nodes
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> minHeap;
    for (auto pair : frequencyMap) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }

    // Build the Huffman tree
    HuffmanNode* root = buildHuffmanTree(minHeap);

    // Generate Huffman codes
    unordered_map<char, string> huffmanCodes;
    generateCodes(root, "", huffmanCodes);

    // Encode the input text
    string encodedText = encodeText(fileContent, huffmanCodes);

    // Print the encoded text
    printEncodedText(encodedText);

    // Use encodedText as needed
    
    return 0;
}