//Wordlist Generator.  This program is part of the Wordlist Zombie suite.
//Boost Software License - Version 1.0
//Written By PhillyStyle1026

#include "utf8.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <cstring>
#include <thread>
#include <future>

#define MAX_OUTSTR_LEN 1024*1024
#define FILE_READ_BUFF_SIZE 1024*1024
#define MAX_THREADS 1000
#define DEFAULT_THREADS 50

//RNG DEFINES
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

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

struct wgThreadStructt {
	std::vector<std::vector<markovRootStruct*>>* positionRoot;
	std::vector<std::vector<markovChr1Struct*>>* positionMarkov;
	std::vector<wordlistMapStruct*>* wordlistMapVector;
	int rnd;
};

double rand2()
{
	return (double)rand() / (double)RAND_MAX;
}

bool processLineMarkovChainFile(char* lineBuff, unsigned long long linecount, std::vector<std::vector<markovRootStruct*>>& positionRoot, std::vector<std::vector<markovChr1Struct*>>& positionMarkov, bool toStdout);
bool loadMarkovChainFile(const char* markov_file_path, std::vector<std::vector<markovRootStruct*>>& positionRoot, std::vector<std::vector<markovChr1Struct*>>& positionMarkov, bool toStdout);
void setMarkovWeights(std::vector<std::vector<markovRootStruct*>>& positionRoot, std::vector<std::vector<markovChr1Struct*>>& positionMarkov, bool unweightedOutput, bool halfweightedOutput, bool toStdout);
bool loadWordMapFile(const char* wordlist_map_file_path, std::vector<wordlistMapStruct*>& wordlistMapVector, bool toStdout, bool useMinWordLength, bool useMaxWordLength, int minWordLength, int maxWordLength);
void setWordMapWeights(std::vector<wordlistMapStruct*>& wordlistMapVector, bool unweightedOutput, bool halfweightedOutput, bool toStdout);
unsigned char* threadGenerateWord(wgThreadStructt* ts);

//RNG
void init_genrand(unsigned long s, unsigned long* mt, int& mti);
unsigned long genrand_int32(unsigned long* mt, int& mti);
double genrand_real1(unsigned long* mt, int& mti);



void outputHelp() {
	std::cout << "WordlistGenerator Usage:\n\n"\
		"WordlistGenerator --number <Number of words to generate> --markov \"path\\to\\markov file.txt\" --wordmap \"path\\to\\word map file.txt\" --output \"path\\to\\output file.txt\"\n\n"\
		"Other Commands:\n"\
		"--help          : Output this help file\n"\
		"/?              : Also output this help file.\n"\
		"--unweighted    : Remove weighted output in an attempt to generate less duplicates.\n"\
		"--halfweighted  : Relax the weighted output in an attempt to balance between weighted output and unweighted output.\n"\
		"--threads       : Number of threads to use in wordlist generation.  Default is currently 50 threads.\n"\
		"--minwordlength : Minimum output word length."\
		"--maxwordlength : Maximum output word length."\
		"--version       : version information\n";
}

void outputVersion() {
	std::cout << "Version: Wordlist Generator v1.0.3-alpha - A part of the Wordlist Zombie program suite.\n";
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
	unsigned long maxThreads = DEFAULT_THREADS;
	bool unweightedOutput = false, halfweightedOutput = false;
	bool toStdout = false;
	bool useMinWordLength = false, useMaxWordLength = false;
	int minWordLength = 0, maxWordLength = 0;

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
		if (strcmp(argv[i], "--threads") == 0) {
			if (argc >= i + 1) {
				maxThreads = strtoul(argv[i + 1], NULL, 10);
			}
		}
		if (strcmp(argv[i], "--minwordlength") == 0) {
			if (argc >= i + 1) {
				useMinWordLength = true;
				minWordLength = strtoul(argv[i + 1], NULL, 10);
			}
		}
		if (strcmp(argv[i], "--maxwordlength") == 0) {
			if (argc >= i + 1) {
				useMaxWordLength = true;
				maxWordLength = strtoul(argv[i + 1], NULL, 10);
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

	if (output_file_path == nullptr) {
		toStdout = true;
	}

	if (wordsToGenerate == 0) {
		if (toStdout == false) std::cout << "\n--number may not be excluded from command line, or 0.\n";
		return 0;
	}

	if ((markov_file_path == nullptr) && (wordlist_map_file_path == nullptr)) {
		if (toStdout == false) std::cout << "\n--markov and --wordmap may not be exluded from command line.\n";
		return 0;
	}

	if (markov_file_path == nullptr) {
		if (toStdout == false) std::cout << "\n--markov may not be exluded from command line.\n";
		return 0;
	}

	if (wordlist_map_file_path == nullptr) {
		if (toStdout == false) std::cout << "\n--wordmap may not be exluded from command line.\n";
		return 0;
	}

	if ((unweightedOutput == true) && (halfweightedOutput == true)) {
		if (toStdout == false) std::cout << "\nYou may not use --unweighted and --halfweighted at the same time.\n";
		return 0;
	}

	if (maxThreads > MAX_THREADS) {
		maxThreads = MAX_THREADS;
		if (toStdout == false) std::cout << "\nMax threads is currently " << MAX_THREADS << ".  Using " << MAX_THREADS << " threads.\n";
	}

	if (markov_file_path != nullptr)
		if (!loadMarkovChainFile(markov_file_path, positionRoot, positionMarkov, toStdout)) return 0;

	setMarkovWeights(positionRoot, positionMarkov, unweightedOutput, halfweightedOutput, toStdout);

	if (wordlist_map_file_path != nullptr)
		if (!loadWordMapFile(wordlist_map_file_path, wordlistMapVector, toStdout, useMinWordLength, useMaxWordLength, minWordLength, maxWordLength)) return 0;

	setWordMapWeights(wordlistMapVector, unweightedOutput, halfweightedOutput, toStdout);

	srand(time(NULL));

	if (toStdout == false) std::cout << "Outputting results! Using " << maxThreads << " Threads!\n";
	std::ofstream outfile;
	if (toStdout == false) outfile.open(output_file_path);

	int genPercent = 0;
	int i = 0;

	while (i < wordsToGenerate) {
		//Lets launch us some threads straight into outer space!
		wgThreadStructt* ts[MAX_THREADS];
		std::future<unsigned char*> futures[MAX_THREADS];

		for (int j = 0; j < maxThreads; j++) {
			ts[j] = new wgThreadStructt();
			ts[j]->positionMarkov = &positionMarkov;
			ts[j]->positionRoot = &positionRoot;
			ts[j]->wordlistMapVector = &wordlistMapVector;
			ts[j]->rnd = rand();

			futures[j] = std::async(threadGenerateWord, ts[j]);
		}

		for (int j = 0; j < maxThreads; j++) {
			unsigned char* outstr = futures[j].get();
			if (toStdout == false) outfile << outstr << "\n";
			else std::cout << outstr << "\n";
			free(outstr);
			delete ts[j];
		}

		i += maxThreads;

		if (100 * (i) / wordsToGenerate > genPercent) {
			genPercent = 100 * (i) / wordsToGenerate;
			if (toStdout == false) {
				std::cout << "\r(" << genPercent << "% Complete)";
				fflush(stdout);
			}
		}
		//i++;
	}

	if (toStdout == false) outfile.close();

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

	if (toStdout == false) std::cout << "\nDone!\n";
	return 0;
}

unsigned char* threadGenerateWord(wgThreadStructt* ts) {
	unsigned char* outstr = (unsigned char*)malloc(MAX_OUTSTR_LEN);

	static unsigned long mt[N]; /* the array for the state vector  */
	static int mti = N + 1; /* mti==N+1 means mt[N] is not initialized */
	init_genrand((unsigned long)time(NULL) ^ std::hash<std::thread::id>{}(std::this_thread::get_id()) ^ ts->rnd, mt, mti);

	//srand((int)time(NULL) ^ std::hash<std::thread::id>{}(std::this_thread::get_id()));
	//Other Options:
	//std::hash<std::thread::id>{}(std::this_thread::get_id())
	//std::hash<std::thread::id>()(std::this_thread::get_id())

	while (true) {
		double r = genrand_real1(mt, mti);
		unsigned char* strMap = nullptr;
		for (int j = 0; j < ts->wordlistMapVector->size(); j++) {
			if (r <= ts->wordlistMapVector->at(j)->weight) {
				strMap = ts->wordlistMapVector->at(j)->strMap;
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
				r = genrand_real1(mt, mti);
				for (int j = 0; j < ts->positionRoot->at(0).size(); j++) {
					if ((r <= ts->positionRoot->at(0).at(j)->weight) &&
						(ts->positionRoot->at(0).at(j)->chrmap == strMap[0])) {
						chr0 = ts->positionRoot->at(0).at(j)->chr;
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
					r = genrand_real1(mt, mti);
					for (int k = 0; k < ts->positionMarkov->at(j).size(); k++) {
						if (ts->positionMarkov->at(j).at(k)->chr1 == prevchar) {
							msv = ts->positionMarkov->at(j).at(k)->msv;
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
						r = genrand_real1(mt, mti);
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
						r = genrand_real1(mt, mti);
						//If no match is found then use root to compensate
						for (int n = 0; n < ts->positionRoot->at(j).size(); n++) {
							if (r <= ts->positionRoot->at(j).at(n)->weight) {
								nextchar = ts->positionRoot->at(j).at(n)->chr;
								break;
							}
						}
					}
				}
				else {
					r = genrand_real1(mt, mti);
					//If no match is found then use root to compensate
					for (int n = 0; n < ts->positionRoot->at(j).size(); n++) {
						if (r <= ts->positionRoot->at(j).at(n)->weight) {
							nextchar = ts->positionRoot->at(j).at(n)->chr;
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
		break;
	}

	return outstr;
}

/* initializes mt[N] with a seed */
void init_genrand(unsigned long s, unsigned long* mt, int& mti)
{
	mt[0] = s & 0xffffffffUL;
	for (mti = 1; mti < N; mti++) {
		mt[mti] =
			(1812433253UL * (mt[mti - 1] ^ (mt[mti - 1] >> 30)) + mti);
		/* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
		/* In the previous versions, MSBs of the seed affect   */
		/* only MSBs of the array mt[].                        */
		/* 2002/01/09 modified by Makoto Matsumoto             */
		mt[mti] &= 0xffffffffUL;
		/* for >32 bit machines */
	}
}

/* generates a random number on [0,0xffffffff]-interval */
unsigned long genrand_int32(unsigned long* mt, int& mti)
{
	unsigned long y;
	static unsigned long mag01[2] = { 0x0UL, MATRIX_A };
	/* mag01[x] = x * MATRIX_A  for x=0,1 */

	if (mti >= N) { /* generate N words at one time */
		int kk;

		if (mti == N + 1)   /* if init_genrand() has not been called, */
			init_genrand(5489UL, mt, mti); /* a default initial seed is used */

		for (kk = 0; kk < N - M; kk++) {
			y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
			mt[kk] = mt[kk + M] ^ (y >> 1) ^ mag01[y & 0x1UL];
		}
		for (; kk < N - 1; kk++) {
			y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
			mt[kk] = mt[kk + (M - N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
		}
		y = (mt[N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
		mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ mag01[y & 0x1UL];

		mti = 0;
	}

	y = mt[mti++];

	/* Tempering */
	y ^= (y >> 11);
	y ^= (y << 7) & 0x9d2c5680UL;
	y ^= (y << 15) & 0xefc60000UL;
	y ^= (y >> 18);

	return y;
}

/* generates a random number on [0,1]-real-interval */
double genrand_real1(unsigned long* mt, int& mti)
{
	return genrand_int32(mt, mti) * (1.0 / 4294967295.0);
	/* divided by 2^32-1 */
}


bool loadMarkovChainFile(const char* markov_file_path, std::vector<std::vector<markovRootStruct*>>& positionRoot, std::vector<std::vector<markovChr1Struct*>>& positionMarkov, bool toStdout) {
	if (toStdout == false) std::cout << "Processing Markov Chain File.\n";

	//I had to quit using ifstream, because it kept failing in the middle of reading files.
	//So now I fell back to good old fopen, and fread from C and it works great.  I probably
	//got speed improvements out of the deal too!

	FILE* pFile = fopen(markov_file_path, "rb");
	if (pFile == NULL) {
		if (toStdout == false) std::cout << "Could not open " << markov_file_path << std::endl;
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
					if (processLineMarkovChainFile(lineBuff, linecount, positionRoot, positionMarkov, toStdout) == false) {
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
			if (processLineMarkovChainFile(lineBuff, linecount, positionRoot, positionMarkov, toStdout) == false) {
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

	if (toStdout == false) std::cout << "Processing Finished!  " << linecount << " Lines Processed.\n";

	fclose(pFile);
	free(getBuff);
	free(lineBuff);

	return true;
}

bool processLineMarkovChainFile(char* lineBuff, unsigned long long linecount, std::vector<std::vector<markovRootStruct*>>& positionRoot, std::vector<std::vector<markovChr1Struct*>>& positionMarkov, bool toStdout) {
	// check for invalid utf-8 (for a simple yes/no check, there is also utf8::is_valid function)
	char* end_it = utf8::find_invalid(lineBuff, lineBuff + strlen(lineBuff));
	if (end_it != lineBuff + strlen(lineBuff)) {
		if (toStdout == false) std::cout << "Invalid UTF-8 encoding detected at line " << linecount << "\n";
		return false;
	}

	// Get the line length (at least for the valid part)
	auto length = utf8::distance(lineBuff, end_it);

	char* nextIT = lineBuff;

	//First Get Root
	if (linecount == 1) {
		if (strcmp(lineBuff, "Markov Chain Thing 1.0") != 0) {
			if (toStdout == false) std::cout << "Error: Invalid Markov Chain Thing File.\n";
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
				if (toStdout == false) std::cout << "Warning: Small error reading Markov File. (Don't worrry, this probably isn't a problem)\n";
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
				if (toStdout == false) std::cout << "Warning: Small error reading Markov File. (Don't worrry, this probably isn't a problem)\n";
				return true;
			}

			unsigned int nextChr2 = 0;
			try {
				nextChr2 = utf8::next(nextIT, end_it);
			}
			catch (const std::exception& e) {
				if (toStdout == false) std::cout << "Warning: Small error reading Markov File. (Don't worrry, this probably isn't a problem)\n";
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

void setMarkovWeights(std::vector<std::vector<markovRootStruct*>>& positionRoot, std::vector<std::vector<markovChr1Struct*>>& positionMarkov, bool unweightedOutput, bool halfweightedOutput, bool toStdout) {

	if ((unweightedOutput == false) && (halfweightedOutput == false)) {
		if (toStdout == false) std::cout << "Setting weights for Markov Chain.\n";

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
		if (toStdout == false) std::cout << "Unweighting the weights for Markov Chain.\n";
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
		if (toStdout == false) std::cout << "Half-Weighting the weights for Markov Chain.\n";
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

bool loadWordMapFile(const char* wordlist_map_file_path, std::vector<wordlistMapStruct*>& wordlistMapVector, bool toStdout, bool useMinWordLength, bool useMaxWordLength, int minWordLength, int maxWordLength) {
	if (toStdout == false) std::cout << "Processing Wordlist Map File.\n";

	std::ifstream fs(wordlist_map_file_path);
	if (!fs.is_open()) {
		if (toStdout == false) std::cout << "Could not open " << wordlist_map_file_path << std::endl;
		return false;
	}

	unsigned int line_count = 1;
	std::string line;
	// Play with all the lines in the file
	while (getline(fs, line)) {

		if (line_count == 1) {
			if (line.compare("Wordlist Mapper 1.0") != 0) {
				if (toStdout == false) std::cout << "Error: Invalid Wordlist Mapper File.\n";
				return false;
			}
		}
		else {
			char* numberEnd;

			unsigned long long count = strtoull(line.c_str(), &numberEnd, 10);

			unsigned char* strMapping = (unsigned char*)numberEnd + 1;

			if (useMinWordLength == true) {
				if (strlen((char*)strMapping) < minWordLength) {
					continue;
				}
			}

			if (useMaxWordLength == true) {
				if (strlen((char*)strMapping) > maxWordLength) {
					continue;
				}
			}

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

	if (toStdout == false) std::cout << "Processing Finished!  " << line_count << " Lines Processed.\n";
	fs.close();
	return true;
}

void setWordMapWeights(std::vector<wordlistMapStruct*>& wordlistMapVector, bool unweightedOutput, bool halfweightedOutput, bool toStdout) {

	if ((unweightedOutput == false) && (halfweightedOutput == false)) {
		if (toStdout == false) std::cout << "Setting weights for wordlist map.\n";
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
		if (toStdout == false) std::cout << "Unweighting weights for wordlist map.\n";
		double c = (double)1 / (double)wordlistMapVector.size();

		double prevweight = 0;
		for (int i = 0; i < wordlistMapVector.size(); i++) {
			prevweight = wordlistMapVector[i]->weight = prevweight + c;
		}
	}
	else if (halfweightedOutput == true) {
		if (toStdout == false) std::cout << "Half-Weighting weights for wordlist map.\n";
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
