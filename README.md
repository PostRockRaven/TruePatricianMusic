# TruePatricianMusic

A music finder. It has a catalog of records that you can add to and run several based commands. For example, you can have it rate your music as patrician or plebian :c. It uses a file of music rated by pitchfork we have put together. If one of the albums is not found, it will prompt the user to include it. You can also directly add a new album and create a new genre in the system. If you wish to add music to the mu.txt file, then you should hardcode a new line in the txt file with artist@album@rating@genre. The ratings are out of 100, and the strings can be as long as needed and can contain any characters that do not include "@". 

How to run:
You must download all files, TruePatricianMusic.cpp, TruePatricianMusic.h, main.h, and mu.txt. mu.txt is hardcoded into the program. Why? Because it is tedious to add everything, and it took a lot of time, so we want people to use it. The rest of the program is based on how it is set up as well. You simply add everything into a project in CodeBlocks, call it what you want, and change the build commands to compile in c++ 11, and g++ compiling. This will bring up the main menu, which you can run any of the options. Running is not very difficult unless you tamper with the files. Once again, download files, open codeblocks, create a new project, add these files and change the build commands to g++ and c++ 11, and you are ready to run!

Dependencies:
Only the included files. We tried our beest to not include third-party librarys. So, make sure you download TruePatricianMusic.h, because it is our library of class prototypes, where the definitions are included in the .cpp version of it. 4 files required to run:
main.cpp
TruePatricianMusic.cpp
TruePatricianMusic.h
mu.txt

System Requirements:
You must have a system that is running CodeBlocks IDE, or any other IDE. Any IDE will work, but CodeBlocks is the easiest to run that we have found because you do not need to compile multiple things in the terminal. CodeBlocks is available through Linux. If you cannot get CodeBlocks, you may use another IDE, but you must know how to compile multiple files in the terminal, or else you will only be making o object file, and it requires two to run (main.o and truepatricianmusic.o)

Group Members:
The team members are Branton DeMoss, Wilder Lavington, Adam Tammariello, and Jake Lazlo Bomark.

Contributers:
If you decided you wish to improve upon our system, pleace leave your name so we can give you credit!

Known bugs:
As of now, we are unable to sort the system. The system is based upon a vector with each node of the vector being a pointer tot he head of the linked list. We attemped using the quick sort, but it did not change anything. If you can figure out how to sort the pointers without destroying their links, it would be much appreciated.
