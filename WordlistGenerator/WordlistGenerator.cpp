//Wordlist Generator.  This program is part of the Wordlist Zombie suite.
//Boost Software License - Version 1.0
//Written By PhillyStyle1026

#include "utf8.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

#define MAX_OUTSTR_LEN 1024*1024
#define FILE_READ_BUFF_SIZE 1024*1024

struct markovRootStruct {
	unsigned long chr;
	unsigned char chrmap;
	unsigned long long count;
	double weight;
};

struct markovStruct {
	unsigned long chr1;
	unsigned long chr2;
	unsigned char chr1map;
	unsigned char chr2map;
	unsigned long long count;
	double weight;
};

struct markovChr1Struct {
	unsigned long chr1;
	unsigned char chr1map;
	std::vector<markovStruct*>* msv;
};

struct wordlistMapStruct {
	unsigned char* strMap;
	unsigned long long count;
	double weight;
};

double rand2()
{
	return (double)rand() / (double)RAND_MAX;
}

bool processLineMarkovChainFile(char* lineBuff, unsigned long long linecount, std::vector<std::vector<markovRootStruct*>>& positionRoot, std::vector<std::vector<markovChr1Struct*>>& positionMarkov);
bool loadMarkovChainFile(const char* markov_file_path, std::vector<std::vector<markovRootStruct*>>& positionRoot, std::vector<std::vector<markovChr1Struct*>>& positionMarkov);
void setMarkovWeights(std::vector<std::vector<markovRootStruct*>>& positionRoot, std::vector<std::vector<markovChr1Struct*>>& positionMarkov, bool unweightedOutput, bool halfweightedOutput);
bool loadWordMapFile(const char* wordlist_map_file_path, std::vector<wordlistMapStruct*>& wordlistMapVector);
void setWordMapWeights(std::vector<wordlistMapStruct*>& wordlistMapVector, bool unweightedOutput, bool halfweightedOutput);

void outputHelp() {
	std::cout << "WordlistGenerator Usage:\n\n"\
				 "WordlistGenerator --number <Number of words to generate> --markov \"path\\to\\markov file.txt\" --wordmap \"path\\to\\word map file.txt\" --output \"path\\to\\output file.txt\"\n\n"\
				 "Other Commands:\n"\
				 "--help         : Output this help file\n"\
				 "/?             : Also output this help file.\n"\
				 "--unweighted   : Remove weighted output in an attempt to generate less duplicates.\n"\
				 "--halfweighted : Relax the weighted output in an attempt to balance between weighted output and unweighted output.\n"\
				 "--version      : version information\n";
}

void outputVersion() {
	std::cout << "Version: Wordlist Generator v1.0.2-alpha - A part of the Wordlist Zombie program suite.\n";
}

int main(int argc, char** argv)
{
	char* markov_file_path = nullptr;
	char* wordlist_map_file_path = nullptr;
	char* output_file_path = nullptr;
	std::vector<std::vector<markovRootStruct*>> positionRoot;
	positionRoot.resize(100);

	std::vector<std::vector<markovChr1Struct*>> positionMarkov;
	positionMarkov.resize(100);

	std::vector<wordlistMapStruct*> wordlistMapVector;

	unsigned long long wordsToGenerate = 0;
	bool unweightedOutput=false, halfweightedOutput=false;

	if (argc == 1) {
		std::cout << "\nTry: WordlistGenerator --help\n";
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
		if (strcmp(argv[i], "--number") == 0) {
			if (argc >= i + 1) {
				wordsToGenerate = strtoull(argv[i + 1], NULL, 10);
			}
		}
		if (strcmp(argv[i], "--markov") == 0) {
			if (argc >= i + 1) {
				markov_file_path = argv[i + 1];
			}
		}
		if (strcmp(argv[i], "--wordmap") == 0) {
			if (argc >= i + 1) {
				wordlist_map_file_path = argv[i + 1];
			}
		}
		if (strcmp(argv[i], "--output") == 0) {
			if (argc >= i + 1) {
				output_file_path = argv[i + 1];
			}
		}
		if (strcmp(argv[i], "--unweighted") == 0) {
			unweightedOutput = true;
		}
		if (strcmp(argv[i], "--halfweighted") == 0) {
			halfweightedOutput = true;
		}
	}

	if (wordsToGenerate == 0) {
		std::cout << "\n--number may not be excluded from command line, or 0.\n";
		return 0;
	}

	if ((markov_file_path == nullptr) && (wordlist_map_file_path == nullptr)) {
		std::cout << "\--markov and --wordmap may not be exluded from command line.\n";
		return 0;
	}

	if (markov_file_path == nullptr) {
		std::cout << "\--markov may not be exluded from command line.\n";
		return 0;
	}

	if (wordlist_map_file_path == nullptr) {
		std::cout << "\--wordmap may not be exluded from command line.\n";
		return 0;
	}

	if (output_file_path == nullptr) {
		std::cout << "\n--output may not be excluded from command line.\n";
		return 0;
	}

	if ((unweightedOutput == true) && (halfweightedOutput == true)) {
		std::cout << "\nYou may not use --unweighted and --halfweighted at the same time.\n";
	}

	if (markov_file_path != nullptr)
		if (!loadMarkovChainFile(markov_file_path, positionRoot, positionMarkov)) return 0;

	setMarkovWeights(positionRoot, positionMarkov, unweightedOutput, halfweightedOutput);

	if (wordlist_map_file_path != nullptr)
		if (!loadWordMapFile(wordlist_map_file_path, wordlistMapVector)) return 0;

	setWordMapWeights(wordlistMapVector, unweightedOutput, halfweightedOutput);

	srand(time(NULL));


	std::cout << "Outputting results!";
	std::ofstream outfile(output_file_path);

	unsigned char* outstr = (unsigned char *)malloc(MAX_OUTSTR_LEN);

	int genPercent = 0;
	int i = 0;

	while (i < wordsToGenerate) {
		//First get the wordlist mapping
		double r = rand2();
		unsigned char* strMap = nullptr;
		for (int j = 0; j < wordlistMapVector.size(); j++) {
			if (r <= wordlistMapVector[j]->weight) {
				strMap = wordlistMapVector[j]->strMap;
				break;
			}
		}

		if (strMap != nullptr) {

			//Next we find letters using markov chains
			unsigned int chr0 = 0;

			//Find first char using positionRoot
			//Try 100 times
			int rcount = 0;
			while ((chr0 == 0) && (rcount < 100)) {
				r = rand2();
				for (int j = 0; j < positionRoot[0].size(); j++) {
					if ((r <= positionRoot[0][j]->weight) &&
						(positionRoot[0][j]->chrmap == strMap[0])) {
						chr0 = positionRoot[0][j]->chr;
						break;
					}
				}
				rcount++;
			}
			if (chr0 == 0) {
				continue; //FAIL!
			}

			//Success!  Now lets try the rest with the markov chains as much as possible
			unsigned char* end = utf8::append(chr0, outstr);
			*end = '\0';

			const int mapLen = strlen((char*)strMap);

			unsigned int prevchar = chr0;
			unsigned int nextchar = 0;
			for (int j = 1; j < mapLen; j++) { //Notice that j starts at position 1 and not zero
				bool found = false;

				std::vector<markovStruct*>* msv = nullptr;
				//Try 100 times
				int rcount = 0;
				while ((found == false) && (rcount < 100)) {
					r = rand2();
					for (int k = 0; k < positionMarkov[j].size(); k++) {
						if (positionMarkov[j][k]->chr1 == prevchar) {
							msv = positionMarkov[j][k]->msv;
							found = true;
							break;
						}
					}
					rcount++;
				}
				if (found) {
					bool found2 = false;

					rcount = 0;
					while ((found2 == false) && (rcount < 100)) {
						r = rand2();
						for (int m = 0; m < msv->size(); m++) {
							if ((r <= msv->at(m)->weight) && (msv->at(m)->chr2map == strMap[j])) {
								nextchar = msv->at(m)->chr2;
								found2 = true;
								break;
							}
						}
						rcount++;
					}
					if (found2 == false) {
						r = rand2();
						//If no match is found then use root to compensate
						for (int n = 0; n < positionRoot[j].size(); n++) {
							if (r <= positionRoot[j][n]->weight) {
								nextchar = positionRoot[j][n]->chr;
								break;
							}
						}
					}
				}
				else {
					r = rand2();
					//If no match is found then use root to compensate
					for (int n = 0; n < positionRoot[j].size(); n++) {
						if (r <= positionRoot[j][n]->weight) {
							nextchar = positionRoot[j][n]->chr;
							break;
						}
					}
				}

				end = utf8::append(nextchar, end);
				*end = '\0';
				if ((end - outstr) >= (MAX_OUTSTR_LEN - 5)) {
					//close enough.
					//The minus 5 is in there because a unicode character could be up to 4 long,
					//and then you have to rememmber the null terminator.  So I buffer the buffer
					//by 5 just to be safe.
					break;
				}
				prevchar = nextchar;
			}
		}
		else {
			continue;
		}
		outfile << outstr << "\n";
		if (100 * (i + 1) / wordsToGenerate > genPercent) {
			genPercent = 100 * (i + 1) / wordsToGenerate;
			std::cout << "\rOutputting results! (" << genPercent << "% Complete)";
		}
		i++;
	}

	outfile.close();
	free(outstr);

	//Free up memory before we exit.
	for (int i = 0; i < positionRoot.size(); i++) {
		unsigned long long totalCount = 0;
		for (int j = 0; j < positionRoot[i].size(); j++) {
			delete positionRoot[i][j];
		}
	}

	for (int i = 0; i < positionMarkov.size(); i++) {
		unsigned long long totalCount = 0;
		for (int j = 0; j < positionMarkov[i].size(); j++) {
			if (positionMarkov[i][j] != NULL) {
				unsigned long long totalCount = 0;
				for (int k = 0; k < positionMarkov[i][j]->msv->size(); k++) {
					markovStruct* ms = positionMarkov[i][j]->msv->at(k);
					delete ms;
				}
				delete positionMarkov[i][j]->msv;
			}
		}
	}

	std::cout << "\nDone!\n";
	return 0;
}


bool loadMarkovChainFile(const char* markov_file_path, std::vector<std::vector<markovRootStruct*>>& positionRoot, std::vector<std::vector<markovChr1Struct*>>& positionMarkov) {
	std::cout << "Processing Markov Chain File.\n";

	//I had to quit using ifstream, because it kept failing in the middle of reading files.
	//So now I fell back to good old fopen, and fread from C and it works great.  I probably
	//got speed improvements out of the deal too!

	FILE* pFile = fopen(markov_file_path, "rb");
	if (pFile == NULL) {
		std::cout << "Could not open " << markov_file_path << std::endl;
		return false;
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
					if (processLineMarkovChainFile(lineBuff, linecount, positionRoot, positionMarkov) == false) {
						fclose(pFile);
						free(getBuff);
						free(lineBuff);
						return false;
					}

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
			if (processLineMarkovChainFile(lineBuff, linecount, positionRoot, positionMarkov) == false) {
				fclose(pFile);
				free(getBuff);
				free(lineBuff);
				return false;
			}
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

	std::cout << "Processing Finished!  " << linecount << " Lines Processed.\n";

	fclose(pFile);
	free(getBuff);
	free(lineBuff);

	return true;
}

bool processLineMarkovChainFile(char* lineBuff, unsigned long long linecount, std::vector<std::vector<markovRootStruct*>>& positionRoot, std::vector<std::vector<markovChr1Struct*>>& positionMarkov) {
	// check for invalid utf-8 (for a simple yes/no check, there is also utf8::is_valid function)
	char* end_it = utf8::find_invalid(lineBuff, lineBuff + strlen(lineBuff));
	if (end_it != lineBuff + strlen(lineBuff)) {
		std::cout << "Invalid UTF-8 encoding detected at line " << linecount << "\n";
		return false;
	}

	// Get the line length (at least for the valid part)
	auto length = utf8::distance(lineBuff, end_it);

	char* nextIT = lineBuff;

	//First Get Root
	if (linecount == 1) {
		if (strcmp(lineBuff,"Markov Chain Thing 1.0") != 0) {
			std::cout << "Error: Invalid Markov Chain Thing File.\n";
			return false;
		}
	}
	else {
		if (strlen(lineBuff) == 0) return true;  //Last line is ""

		char* numberEnd;

		unsigned long long count = strtoull(lineBuff, &numberEnd, 10);

		unsigned long position = strtoul(numberEnd + 1, &numberEnd, 10);

		//std::cout << count << " " << position << "\n";

		if (*(numberEnd + 1) == 'T') {
			//It is a root character
			//get char mapping
			unsigned char chrmapping = *(numberEnd + 3);

			//get char
			nextIT += numberEnd + 5 - lineBuff;
			unsigned int nextChr = 0;
			try {
				nextChr = utf8::next(nextIT, end_it);
			}
			catch (const std::exception& e) {
				std::cout << "Warning: Small error reading Markov File. (Don't worrry, this probably isn't a problem)\n";
				return true;
			}

			//Fill struct
			markovRootStruct* mrs = new markovRootStruct();
			mrs->chr = nextChr;
			mrs->chrmap = chrmapping;
			mrs->count = count;
			mrs->weight = 0.0; //We find weight later

			//Add it to vector!
			//Make sure vector is big enough.
			if (positionRoot.size() < position + 1) {
				positionRoot.resize(positionRoot.size() + 100); //Add another hundo
			}
			//Add!
			positionRoot[position].push_back(mrs);
		}
		else {
			//It is a markov chain thing
			//get char mapping
			unsigned char chr1mapping = *(numberEnd + 3);
			unsigned char chr2mapping = *(numberEnd + 4);

			//get chars
			nextIT += numberEnd + 6 - lineBuff;
			unsigned int nextChr1 = 0;
			try {
				nextChr1 = utf8::next(nextIT, end_it);
			}
			catch (const std::exception& e) {
				std::cout << "Warning: Small error reading Markov File. (Don't worrry, this probably isn't a problem)\n";
				return true;
			}

			unsigned int nextChr2 = 0;
			try {
				nextChr2 = utf8::next(nextIT, end_it);
			}
			catch (const std::exception& e) {
				std::cout << "Warning: Small error reading Markov File. (Don't worrry, this probably isn't a problem)\n";
				return true;
			}

			//Fill structs
			markovChr1Struct* mc1s = new markovChr1Struct();
			markovStruct* ms = new markovStruct();
			mc1s->chr1 = nextChr1;
			mc1s->chr1map = chr1mapping;
			mc1s->msv = new std::vector<markovStruct*>;

			ms->chr1 = nextChr1;
			ms->chr2 = nextChr2;
			ms->chr1map = chr1mapping;
			ms->chr2map = chr2mapping;
			ms->count = count;
			ms->weight = 0.0;

			//Add!
			//First Check if there is already a markovChr1Struct that is the same as ours
			//Make sure vector is big enough.
			if (positionMarkov.size() < position + 1) {
				positionMarkov.resize(positionMarkov.size() + 100); //Add another hundo
			}

			bool found = false;
			std::vector<markovStruct*>* msv = nullptr;
			for (int j = 0; j < positionMarkov[position].size(); j++) {
				if (positionMarkov[position][j]->chr1 == nextChr1) {
					msv = positionMarkov[position][j]->msv;
					found = true;
					break;
				}
			}

			if (found) {
				//Add to msv
				msv->push_back(ms);
			}
			else {
				//Add to positionMarkov AND msv
				positionMarkov[position].push_back(mc1s);
				mc1s->msv->push_back(ms);
			}
		}
	}
	return true;
}

void setMarkovWeights(std::vector<std::vector<markovRootStruct*>>& positionRoot, std::vector<std::vector<markovChr1Struct*>>& positionMarkov, bool unweightedOutput, bool halfweightedOutput) {
	
	if ((unweightedOutput == false) && (halfweightedOutput == false)) {
		std::cout << "Setting weights for Markov Chain.\n";

		//Set Weights for Root
		for (int i = 0; i < positionRoot.size(); i++) {
			unsigned long long totalCount = 0;
			for (int j = 0; j < positionRoot[i].size(); j++) {
				totalCount += positionRoot[i][j]->count;
			}
			double prevweight = 0;
			for (int j = 0; j < positionRoot[i].size(); j++) {
				prevweight = positionRoot[i][j]->weight = prevweight + ((double)positionRoot[i][j]->count / (double)totalCount);
			}
		}

		//Set Weights for Markov chain things
		for (int i = 0; i < positionMarkov.size(); i++) {
			unsigned long long totalCount = 0;
			for (int j = 0; j < positionMarkov[i].size(); j++) {
				if (positionMarkov[i][j] != NULL) {
					unsigned long long totalCount = 0;
					for (int k = 0; k < positionMarkov[i][j]->msv->size(); k++) {
						markovStruct* ms = positionMarkov[i][j]->msv->at(k);
						totalCount += ms->count;
					}
					double prevweight = 0;
					for (int k = 0; k < positionMarkov[i][j]->msv->size(); k++) {
						markovStruct* ms = positionMarkov[i][j]->msv->at(k);
						prevweight = ms->weight = prevweight + ((double)ms->count / (double)totalCount);
					}
				}
			}
		}
	}
	else if (unweightedOutput == true) {
		std::cout << "Unweighting the weights for Markov Chain.\n";
		//Set Equal Weights for Root
		for (int i = 0; i < positionRoot.size(); i++) {
			double c = (double)1 / (double)positionRoot[i].size();

			double prevweight = 0;
			for (int j = 0; j < positionRoot[i].size(); j++) {
				prevweight = positionRoot[i][j]->weight = prevweight + c;
			}
		}

		//Set Equal Weights for Markov chain things
		for (int i = 0; i < positionMarkov.size(); i++) {
			unsigned long long totalCount = 0;
			for (int j = 0; j < positionMarkov[i].size(); j++) {
				if (positionMarkov[i][j] != NULL) {
					double c = (double)1 / (double)positionMarkov[i][j]->msv->size();

					double prevweight = 0;
					for (int k = 0; k < positionMarkov[i][j]->msv->size(); k++) {
						markovStruct* ms = positionMarkov[i][j]->msv->at(k);
						prevweight = ms->weight = prevweight + c;
					}
				}
			}
		}
	}
	else if (halfweightedOutput == true) {
		//Set Half-Weights for Root
		std::cout << "Half-Weighting the weights for Markov Chain.\n";
		for (int i = 0; i < positionRoot.size(); i++) {
			double c = (double)1 / (double)positionRoot[i].size();
			unsigned long long totalCount = 0;
			for (int j = 0; j < positionRoot[i].size(); j++) {
				totalCount += positionRoot[i][j]->count;
			}

			double prevweightFull = 0;
			double prevweightEqual = 0;
			for (int j = 0; j < positionRoot[i].size(); j++) {
				prevweightFull = prevweightFull + ((double)positionRoot[i][j]->count / (double)totalCount);
				prevweightEqual = prevweightEqual + c;
				positionRoot[i][j]->weight = ((prevweightFull + prevweightEqual) / 2);
			}
		}

		//Set Half-Weights for Markov chain things
		for (int i = 0; i < positionMarkov.size(); i++) {
			unsigned long long totalCount = 0;
			for (int j = 0; j < positionMarkov[i].size(); j++) {
				if (positionMarkov[i][j] != NULL) {
					double c = (double)1 / (double)positionMarkov[i][j]->msv->size();
					unsigned long long totalCount = 0;
					for (int k = 0; k < positionMarkov[i][j]->msv->size(); k++) {
						markovStruct* ms = positionMarkov[i][j]->msv->at(k);
						totalCount += ms->count;
					}
					double prevweightFull = 0;
					double prevweightEqual = 0;
					for (int k = 0; k < positionMarkov[i][j]->msv->size(); k++) {
						markovStruct* ms = positionMarkov[i][j]->msv->at(k);
						prevweightFull = prevweightFull + ((double)ms->count / (double)totalCount);
						prevweightEqual = prevweightEqual + c;
						ms->weight = ((prevweightFull + prevweightEqual) / 2);
					}
				}
			}
		}
	}

	//Code to make sure the weights are right
	//for (int i = 0; i < positionRoot.size(); i++) {
	//	for (int j = 0; j < positionRoot[i].size(); j++) {
	//		std::cout << positionRoot[i][j]->weight << " ";
	//	}
	//	std::cout << "\n\n";
	//}
	//for (int i = 0; i < positionMarkov.size(); i++) {
	//	for (int j = 0; j < positionMarkov[i].size(); j++) {
	//		if (positionMarkov[i][j] != NULL) {
	//			for (int k = 0; k < positionMarkov[i][j]->msv->size(); k++) {
	//				markovStruct* ms = positionMarkov[i][j]->msv->at(k);
	//				std::cout << ms->weight << " ";
	//			}
	//			std::cout << "\n\n";
	//		}
	//	}
	//	std::cout << "\n\n";
	//}

}

bool loadWordMapFile(const char* wordlist_map_file_path, std::vector<wordlistMapStruct*>& wordlistMapVector) {
	std::cout << "Processing Wordlist Map File.\n";

	std::ifstream fs(wordlist_map_file_path);
	if (!fs.is_open()) {
		std::cout << "Could not open " << wordlist_map_file_path << std::endl;
		return 0;
	}

	unsigned int line_count = 1;
	std::string line;
	// Play with all the lines in the file
	while (getline(fs, line)) {

		if (line_count == 1) {
			if (line.compare("Wordlist Mapper 1.0") != 0) {
				std::cout << "Error: Invalid Wordlist Mapper File.\n";
				return false;
			}
		}
		else {
			char* numberEnd;

			unsigned long long count = strtoull(line.c_str(), &numberEnd, 10);

			unsigned char* strMapping = (unsigned char*)numberEnd + 1;


			//Fill struct
			wordlistMapStruct* wms = new wordlistMapStruct();
			wms->strMap = (unsigned char*)malloc(strlen((char*)strMapping) + 1);
			wms->count = count;
			wms->weight = 0.0; //We find weight later

			strcpy((char*)wms->strMap, (char*)strMapping);

			//Add it to vector!
			wordlistMapVector.push_back(wms);
		}

		line_count++;
	}

	std::cout << "Processing Finished!  " << line_count << " Lines Processed.\n";
	fs.close();
}

void setWordMapWeights(std::vector<wordlistMapStruct*>& wordlistMapVector, bool unweightedOutput, bool halfweightedOutput) {

	if ((unweightedOutput == false) && (halfweightedOutput == false)) {
		std::cout << "Setting weights for wordlist map.\n";
		unsigned long long totalCount = 0;
		for (int i = 0; i < wordlistMapVector.size(); i++) {
			totalCount += wordlistMapVector[i]->count;
		}
		double prevweight = 0;
		for (int i = 0; i < wordlistMapVector.size(); i++) {
			prevweight = wordlistMapVector[i]->weight = prevweight + ((double)wordlistMapVector[i]->count / (double)totalCount);
		}
	}
	else if (unweightedOutput == true) {
		std::cout << "Unweighting weights for wordlist map.\n";
		double c = (double)1 / (double)wordlistMapVector.size();

		double prevweight = 0;
		for (int i = 0; i < wordlistMapVector.size(); i++) {
			prevweight = wordlistMapVector[i]->weight = prevweight + c;
		}
	}
	else if (halfweightedOutput == true) {
		std::cout << "Half-Weighting weights for wordlist map.\n";
		double c = (double)1 / (double)wordlistMapVector.size();
		unsigned long long totalCount = 0;
		for (int i = 0; i < wordlistMapVector.size(); i++) {
			totalCount += wordlistMapVector[i]->count;
		}
		double prevweightFull = 0;
		double prevweightEqual = 0;
		for (int i = 0; i < wordlistMapVector.size(); i++) {
			prevweightFull = prevweightFull + ((double)wordlistMapVector[i]->count / (double)totalCount);
			prevweightEqual = prevweightEqual + c;
			wordlistMapVector[i]->weight = ((prevweightFull + prevweightEqual) / 2);
		}
	}
}