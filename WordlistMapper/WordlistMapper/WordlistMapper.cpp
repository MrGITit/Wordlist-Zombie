//Wordlist Mapper.  This program is part of the Wordlist Zombie suite.
//Boost Software License - Version 1.0
//Written By PhillyStyle1026

#include "utf8.h"
#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

#define FILE_READ_BUFF_SIZE 1024*1024

void processLine(char* lineBuff, unsigned long long linecount, HashTable* ht);

void outputHelp() {
	std::cout << "WordlistMapper Usage:\n\n"\
				 "WordlistMapper --wordlist \"path\\to\\wordlist\" --output \"path\\to\\output file.txt\"\n\n"\
				 "Other Commands:\n"\
				 "--help    : Output this help file\n"\
				 "/?        : Also output this help file.\n"\
				 "--version : version information\n";
}

void outputVersion() {
	std::cout << "Version: Wordlist Mapper v1.0.5-alpha - A part of the Wordlist Zombie program suite.\n";
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

	//Check for --version
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--version") == 0) {
			outputVersion();
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

	//I had to quit using ifstream, because it kept failing in the middle of reading files.
	//So now I fell back to good old fopen, and fread from C and it works great.  I probably
	//got speed improvements out of the deal too!

	FILE* pFile = fopen(wordlist_file_path, "rb");
	if (pFile == NULL) {
		std::cout << "Could not open " << wordlist_file_path << std::endl;
		return 0;
	}

	unsigned long long line_count = 1;

	char* getBuff = (char*)malloc(FILE_READ_BUFF_SIZE);
	char* lineBuff = (char*)malloc(FILE_READ_BUFF_SIZE);
	int overflowAmmount = 0;
	int lineStart = 0;
	int bytesRead = 0;
	unsigned long long linecount = 0;
	do {
		bytesRead = fread(getBuff + overflowAmmount, 1, FILE_READ_BUFF_SIZE - overflowAmmount, pFile);
		bytesRead = bytesRead + overflowAmmount;

		//Next Find lines
		for (int i = 0; i < bytesRead; i++) {
			if ((getBuff[i] == '\r') || (getBuff[i] == '\n')) {
				int lineEnd = i;
				//extract line
				if (lineStart != lineEnd) {
					memcpy(lineBuff, getBuff + lineStart, lineEnd - lineStart);
					lineBuff[lineEnd - lineStart] = '\0';

					//Now we can use our shiny new line
					linecount++;
					processLine(lineBuff, linecount, ht);

				}
				lineStart = lineEnd + 1;
			}
		}

		if (feof(pFile)) {
			//End of file reached! Whatever is left must be a word!!
			memcpy(lineBuff, getBuff + lineStart, bytesRead - lineStart);
			lineBuff[bytesRead - lineStart] = '\0';

			//Now we can use our shiny new line
			linecount++;
			processLine(lineBuff, linecount, ht);
			break;
		}

		if (lineStart == 0) {
			//No line found!  FAIL!
			break;
		}
		overflowAmmount = bytesRead - lineStart;
		memcpy(getBuff, getBuff + lineStart, overflowAmmount);
		lineStart = 0;
	} while (bytesRead != 0);

	std::cout << "Processing Finished!  " << linecount << " Lines Processed.  Last Line = " << lineBuff << "\n";

	fclose(pFile);
	free(getBuff);
	free(lineBuff);

	std::cout << "Sorting results... (" << ht->getItemCount() << " Items)\n";

	ht->doMergeSort();

	std::cout << "Outputting results!\n";
	std::ofstream outfile(output_file_path);

	outfile << "Wordlist Mapper 1.0" << std::endl;

	HashItem* hi = ht->getFirstItem();

	while (hi != nullptr) {
		outfile << hi->getCount() << " " << hi->getItemStr() << std::endl;
		hi = hi->getNextItemHT();
	}

	outfile.close();

	delete ht;

	std::cout << "Done!\n";
	return 0;
}

void processLine(char* lineBuff, unsigned long long linecount, HashTable* ht) {

	//check for invalid utf - 8 (for a simple yes / no check, there is also utf8::is_valid function)
	char* end_it = utf8::find_invalid(lineBuff, lineBuff + strlen(lineBuff));
	if (end_it != lineBuff + strlen(lineBuff)) {
		std::cout << "Invalid UTF-8 encoding detected at line " << linecount << "\n";
		return;
	}
	//Get the line length
	auto length = utf8::distance(lineBuff, end_it);

	char* nextIT = lineBuff;

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

	if (linecount % 10000 == 0) std::cout << linecount << " Lines Processed.  Current Line = " << lineBuff << "\n";

	unsigned char* itemString = (unsigned char*)malloc(mapping.length() + 1);
	strcpy((char*)itemString, mapping.c_str());
	ht->insertItem(itemString);

}
