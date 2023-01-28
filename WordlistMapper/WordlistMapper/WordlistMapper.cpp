//Wordlist Mapper.  This program is part of the Wordlist Zombie suite.
//Boost Software License - Version 1.0
//Written By PhillyStyle1026

#include "utf8.h"
#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void outputHelp() {
    std::cout << "WordlistMapper Usage:\n\nWordlistMapper --wordlist \"path\\to\\wordlist\" --output \"path\\to\\output file.txt\"\n\nOther Commands:\n--help : Output this help file\n/?     : Also output this help file.\n";
}

int main(int argc, char** argv)
{
    HashTable* ht = new HashTable(1024);
    char* wordlist_file_path = nullptr;
    char* output_file_path = nullptr;

    if (argc == 1) {
        std::cout << "\nTry: WordlistMapper --help\n";
        return 0;
    }

    //Check for --help
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            outputHelp();
            return 0;
        }
        if (strcmp(argv[i], "/?") == 0) {
            outputHelp();
            return 0;
        }
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--wordlist") == 0) {
            if (argc >= i + 1) {
                wordlist_file_path = argv[i + 1];
            }
        }
        if (strcmp(argv[i], "--output") == 0) {
            if (argc >= i + 1) {
                output_file_path = argv[i + 1];
            }
        }
    }

    if (wordlist_file_path == nullptr) {
        std::cout << "\n--wordlist may not be excluded from command.\n";
        return 0;
    }
    if (output_file_path == nullptr) {
        std::cout << "\n--output may not be excluded from command.\n";
        return 0;
    }

    // Open the test file (must be UTF-8 encoded)
    std::ifstream fs8(wordlist_file_path);
    if (!fs8.is_open()) {
        std::cout << "Could not open " << wordlist_file_path << std::endl;
        return 0;
    }

    unsigned line_count = 1;
    std::string line;
    // Play with all the lines in the file
    while (getline(fs8, line)) {
        // check for invalid utf-8 (for a simple yes/no check, there is also utf8::is_valid function)
        std::string::iterator end_it = utf8::find_invalid(line.begin(), line.end());
        if (end_it != line.end()) {
            std::cout << "Invalid UTF-8 encoding detected at line " << line_count << "\n";
            continue;
        }
        // Get the line length (at least for the valid part)
        ptrdiff_t length = utf8::distance(line.begin(), end_it);
        //std::cout << "Length of line " << line_count << " is " << length <<  "\n";

        std::string::iterator nextIT = line.begin();

        std::string mapping;

        for (int i = 0; i < length; i++) {
            unsigned int nextChr = utf8::next(nextIT, end_it);
            //cCvVNSU
            if ((nextChr == 'a') || (nextChr == 'e') || (nextChr == 'i') ||
                (nextChr == 'o') || (nextChr == 'u')) mapping.append("v");
            else if ((nextChr == 'A') || (nextChr == 'E') || (nextChr == 'I') ||
                (nextChr == 'O') || (nextChr == 'U')) mapping.append("V");
            else if ((nextChr >= '0') && (nextChr <= '9')) mapping.append("N");
            else if ((nextChr >= 'a') && (nextChr <= 'z')) mapping.append("c");
            else if ((nextChr >= 'A') && (nextChr <= 'Z')) mapping.append("C");
            else if (nextChr <= 255) mapping.append("S");
            else mapping.append("U");
        }

        if (line_count % 10000 == 0) std::cout << line_count << " Lines Processed.  Current Line = " << line << "\n";

        unsigned char *itemString = (unsigned char *)malloc(mapping.length()+1);
        strcpy((char *)itemString, mapping.c_str());
        ht->insertItem(itemString);
        line_count++;
    } 

    std::cout << "Processing Finished!  " << line_count << " Lines Processed.  Last Line = " << line << "\n";

    std::cout << "Sorting results... (" << ht->getItemCount() << " Items)\n";

    ht->doMergeSort();

    std::cout << "Outputting results!\n";
    std::ofstream outfile(output_file_path);

    outfile << "Wordlist Mapper 1.0" << std::endl;

    HashItem *hi = ht->getFirstItem();

    while (hi != nullptr) {
        outfile << hi->getCount() << " " << hi->getItemStr()  << std::endl;
        hi = hi->getNextItemHT();
    }

    outfile.close();
    std::cout << "Done!\n";
    return 0;
}
