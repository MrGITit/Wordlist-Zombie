//Markov Chain Thing.  This program is part of the Wordlist Zombie suite.
//Boost Software License - Version 1.0
//Written By PhillyStyle1026

#include "utf8.h"
#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

unsigned char getChrMapping(unsigned int chr) {
    //cCvVNSU
    unsigned char mapping;

    if ((chr == 'a') || (chr == 'e') || (chr == 'i') || (chr == 'o') || (chr == 'u')) mapping = 'v';
    else if ((chr == 'A') || (chr == 'E') || (chr == 'I') || (chr == 'O') || (chr == 'U')) mapping = 'V';
    else if ((chr >= '0') && (chr <= '9')) mapping = 'N';
    else if ((chr >= 'a') && (chr <= 'z')) mapping = 'c';
    else if ((chr >= 'A') && (chr <= 'Z')) mapping = 'C';
    else if (chr <= 255) mapping = 'S';
    else mapping = 'U';

    return mapping;
}

void outputHelp() {
    std::cout << "MarkovChainThing Usage:\n\nMarkovChainThing --wordlist \"path\\to\\wordlist\" --output \"path\\to\\output file.txt\"\n\nOther Commands:\n--help : Output this help file\n/?     : Also output this help file.\n";
}

int main(int argc, char** argv)
{
    HashTable* ht = new HashTable(1024);
    char* wordlist_file_path = nullptr;
    char* output_file_path = nullptr;

    if (argc == 1) {
        std::cout << "\nTry: MarkovChainThing --help\n";
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
    std::ifstream fs(wordlist_file_path);
    if (!fs.is_open()) {
        std::cout << "Could not open " << wordlist_file_path << std::endl;
        return 0;
    }

    unsigned long long line_count = 1;
    std::string line;
    // Play with all the lines in the file
    while (getline(fs, line)) {
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

        unsigned char chr1mapping, chr2mapping;

        //First Get Root
        for (int i = 0; i < length; i++) {
            unsigned int nextChr = utf8::next(nextIT, end_it);
            chr1mapping = getChrMapping(nextChr);
            
            //POS T chr1map chr1
            unsigned char itemString[100];
            
            _itoa(i,(char *)&itemString, 10);
            
            strcat((char*)itemString, " T ");
            
            unsigned char chr1mapstr[3];
            chr1mapstr[0] = chr1mapping;
            chr1mapstr[1] = ' ';
            chr1mapstr[2] = '\0';
            strcat((char*)itemString, (char *)chr1mapstr);

            unsigned char* end = utf8::append(nextChr, itemString + strlen((char*)itemString));
            *end = '\0';
            
            unsigned char* itemString2 = (unsigned char*)malloc(strlen((char *)itemString)+1);
            if (itemString2 == NULL) {
                std::cout << "Error allocating memory!!" << "\n";
                break;
            }

            strcpy((char *)itemString2, (char *)itemString);

            //std::cout << itemString2 << "\n";

            HashItem* hsItm = new HashItem(itemString2);
            hsItm->setIsRoot(true);
            hsItm->setPos(i);
            hsItm->setChr1Map(chr1mapping);
            hsItm->setChr1(nextChr);
            ht->insertItem(hsItm);
        }
        
        nextIT = line.begin();
        bool firstchar = true;
        unsigned int ch1;

        //Next get Non-Root
        for (int i = 0; i < length; i++) {
            unsigned int ch2 = utf8::next(nextIT, end_it);

            if (firstchar)
            {
                firstchar = false;
                ch1 = ch2;
                continue;
            }

            chr1mapping = getChrMapping(ch1);
            chr2mapping = getChrMapping(ch2);

            //POS F chr1mapch2map ch1ch2
            unsigned char itemString[100];

            //Position
            _itoa(i-1, (char*)&itemString, 10);

            //F (for False (isroot))
            strcat((char*)itemString, " F ");

            unsigned char chr12mapstr[4];
            chr12mapstr[0] = chr1mapping;
            chr12mapstr[1] = chr2mapping;
            chr12mapstr[2] = ' ';
            chr12mapstr[3] = '\0';
            strcat((char*)itemString, (char*)chr12mapstr);

            unsigned char* end = utf8::append(ch1, itemString + strlen((char*)itemString));
            *end = '\0';
            end = utf8::append(ch2, itemString + strlen((char*)itemString));
            *end = '\0';

            unsigned char* itemString2 = (unsigned char*)malloc(strlen((char*)itemString) + 1);
            if (itemString2 == NULL) {
                std::cout << "Error allocating memory!!" << "\n";
                break;
            }

            strcpy((char*)itemString2, (char*)itemString);

            //std::cout << itemString2 << "\n";

            HashItem* hsItm = new HashItem(itemString2);
            hsItm->setIsRoot(false);
            hsItm->setPos(i-1);
            hsItm->setChr1Map(chr1mapping);
            hsItm->setChr2Map(chr2mapping);
            hsItm->setChr1(ch1);
            hsItm->setChr2(ch2);
            ht->insertItem(hsItm);
            ch1 = ch2;
        }



        if (line_count % 10000 == 0) std::cout << line_count << " Lines Processed.  Current Line = " << line << "\n";

        line_count++;
    }

    std::cout << "Processing Finished!  " << line_count << " Lines Processed.  Last Line = " << line << "\n";

    std::cout << "Sorting results... (" << ht->getItemCount() << " Items)\n";

    ht->doMergeSort();

    std::cout << "Outputting results!\n";
    std::ofstream outfile(output_file_path);

    outfile << "Markov Chain Thing 1.0" << std::endl;

    HashItem* hi = ht->getFirstItem();

    while (hi != nullptr) {
        outfile << hi->getCount() << " " << hi->getItemStr() << std::endl;
        hi = hi->getNextItemHT();
    }

    outfile.close();
    std::cout << "Done!\n";
    return 0;
}
