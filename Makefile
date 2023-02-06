CXX := g++
CXXFLAGS :=
CXXLIBS :=
MarkovChainThingOBJS := MarkovChainThing/objs/MarkovChainThing.o MarkovChainThing/objs/HashTable.o MarkovChainThing/objs/HashItem.o MarkovChainThing/objs/hash_32a.o
WordlistMapperOBJS := WordlistMapper/WordlistMapper/objs/WordlistMapper.o WordlistMapper/WordlistMapper/objs/HashTable.o WordlistMapper/WordlistMapper/objs/HashItem.o WordlistMapper/WordlistMapper/objs/hash_32a.o
WordlistGeneratorOBJS := WordlistGenerator/objs/WordlistGenerator.o

CC := gcc
CFLAGS := -Wall
CFLAGS += `pkg-config --cflags gtk4`
CLIBS := -export-dynamic
CLIBS += `pkg-config --libs gtk4`
WordlistZombieGUIOBJS := WordlistZombieGUIPortable/objs/WordlistZombieGUI.o WordlistZombieGUIPortable/objs/parson.o


all: bin bin/MarkovChainThing bin/WordlistMapper bin/WordlistGenerator bin/WordlistZombieGUI

bin:
	mkdir bin
	
bin/MarkovChainThing: MarkovChainThing/objs MarkovChainThing/objs/MarkovChainThing.o MarkovChainThing/objs/HashTable.o MarkovChainThing/objs/HashItem.o MarkovChainThing/objs/hash_32a.o
	$(CXX) $(CXXFLAGS) $(CXXLIBS) -o bin/MarkovChainThing -lm $(MarkovChainThingOBJS)
MarkovChainThing/objs/MarkovChainThing.o: MarkovChainThing/MarkovChainThing.cpp
	$(CXX) $(CXXFLAGS) -c MarkovChainThing/MarkovChainThing.cpp -o MarkovChainThing/objs/MarkovChainThing.o
MarkovChainThing/objs/HashTable.o: ./MarkovChainThing/HashTable.cpp
	$(CXX) $(CXXFLAGS) -c MarkovChainThing/HashTable.cpp -o MarkovChainThing/objs/HashTable.o
MarkovChainThing/objs/HashItem.o: ./MarkovChainThing/HashItem.cpp
	$(CXX) $(CXXFLAGS) -c MarkovChainThing/HashItem.cpp -o MarkovChainThing/objs/HashItem.o
MarkovChainThing/objs/hash_32a.o: ./MarkovChainThing/hash_32a.cpp
	$(CXX) $(CXXFLAGS) -c MarkovChainThing/hash_32a.cpp -o MarkovChainThing/objs/hash_32a.o
MarkovChainThing/objs:
	mkdir MarkovChainThing/objs
	
	
bin/WordlistMapper: WordlistMapper/WordlistMapper/objs WordlistMapper/WordlistMapper/objs/WordlistMapper.o WordlistMapper/WordlistMapper/objs/HashTable.o WordlistMapper/WordlistMapper/objs/HashItem.o WordlistMapper/WordlistMapper/objs/hash_32a.o
	$(CXX) $(CXXFLAGS) $(CXXLIBS) -o bin/WordlistMapper -lm $(WordlistMapperOBJS)
WordlistMapper/WordlistMapper/objs/WordlistMapper.o:
	$(CXX) $(CXXFLAGS) -c WordlistMapper/WordlistMapper/WordlistMapper.cpp -o WordlistMapper/WordlistMapper/objs/WordlistMapper.o
WordlistMapper/WordlistMapper/objs/HashTable.o:
	$(CXX) $(CXXFLAGS) -c WordlistMapper/WordlistMapper/HashTable.cpp -o WordlistMapper/WordlistMapper/objs/HashTable.o
WordlistMapper/WordlistMapper/objs/HashItem.o:
	$(CXX) $(CXXFLAGS) -c WordlistMapper/WordlistMapper/HashItem.cpp -o WordlistMapper/WordlistMapper/objs/HashItem.o
WordlistMapper/WordlistMapper/objs/hash_32a.o:
	$(CXX) $(CXXFLAGS) -c WordlistMapper/WordlistMapper/hash_32a.cpp -o WordlistMapper/WordlistMapper/objs/hash_32a.o
WordlistMapper/WordlistMapper/objs:
	mkdir WordlistMapper/WordlistMapper/objs


bin/WordlistGenerator: WordlistGenerator/objs WordlistGenerator/objs/WordlistGenerator.o
	$(CXX) $(CXXFLAGS) $(CXXLIBS) -o bin/WordlistGenerator -lm $(WordlistGeneratorOBJS)
WordlistGenerator/objs/WordlistGenerator.o:
	$(CXX) $(CXXFLAGS) -c WordlistGenerator/WordlistGenerator.cpp -o WordlistGenerator/objs/WordlistGenerator.o
WordlistGenerator/objs:
	mkdir WordlistGenerator/objs
	

bin/WordlistZombieGUI: WordlistZombieGUIPortable/objs WordlistZombieGUIPortable/objs/WordlistZombieGUI.o WordlistZombieGUIPortable/objs/parson.o bin/Resources
	$(CC) $(CFLAGS) -o bin/WordlistZombieGUI $(WordlistZombieGUIOBJS) $(CLIBS)
WordlistZombieGUIPortable/objs/WordlistZombieGUI.o:
	$(CC) $(CFLAGS) -c WordlistZombieGUIPortable/WordlistZombieGUI.c -o WordlistZombieGUIPortable/objs/WordlistZombieGUI.o
WordlistZombieGUIPortable/objs/parson.o:
	$(CC) $(CFLAGS) -c WordlistZombieGUIPortable/parson.c -o WordlistZombieGUIPortable/objs/parson.o
WordlistZombieGUIPortable/objs:
	mkdir WordlistZombieGUIPortable/objs
bin/Resources:
	mkdir bin/Resources
	cp WordlistZombieGUIPortable/Resources/* bin/Resources


clean:
	rm -rf MarkovChainThing/objs/*.o WordlistMapper/WordlistMapper/objs/*.o WordlistGenerator/objs/*.o WordlistZombieGUIPortable/objs/*.o bin/MarkovChainThing bin/WordlistMapper bin/WordlistGenerator bin/WordlistZombieGUI
