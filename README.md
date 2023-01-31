# Wordlist Zombie
 Bring your wordlists back to life with Wordlist Zombie! Wordlist Zombie uses Markov Chains, and Consonant / Vowel maps to generate wordlists.

![Wordlist Zombie GUI](WordlistZombieScreenshot.png?raw=true)

Wordlist Zombie is a suite of 4 programs.

* Markov Chain Thing
* Wordlist Mapper
* Wordlist Generator
* Wordlist Zombie GUI

## Markov Chain Thing

Markov Chain thing is the program you use to create markov chains from wordlists.  These generated Markov Chain files can then be used in Wordlist Generator to create wordlists.

#### Usage is as follows:

MarkovChainThing --wordlist "path\to\wordlist.txt" --output "path\to\output.txt"

## Wordlist Mapper

Wordlist Mapper is the program you use to create Consonant / Vowel maps from wordlists.  These generated Map files can then be used in Wordlist Generator to create wordlists.

#### Usage is as follows:

WordlistMapper --wordlist "path\to\wordlist.txt" --output "path\to\output.txt"

## Wordlist Generator

Wordlist Generator is where the magic happens as they say.  Wordlist Generator uses the output of Markov Chain Thing, and Wordlist Mapper to generate whole new wordlists.

#### Usage is as follows:

WordlistGenerator --number (Number of words to generate) --markov "path\to\markov\file.txt" --wordmap "path\to\wordmap\file.txt" --output "path\to\output.txt"

## Wordlist Zombie GUI

Wordlist Zombie GUI is a Graphical User Interface for the Wordilst Zombie suite of applications.  It is pictured in the screenshot above.  Just fill in the textboxes and hit generate, and it launches the proper program with the proper command line paramaters.

## Current State of things and relaxed roadmap

Linux build is here!  Type make in the clone directory to build! (binaries go to the bin folder)

I still have some ideas for this project.  I'm not done yet!

I also would like to code my own sort program to add to the suite to sort and deduplicate the output of Wordlist Generator.  I will try my hardest to make sure it sorts the same way GNU Sort does so that it meets the current standard of sorting wordlists.  Mine just probably wont perform as fast and that is OK.
