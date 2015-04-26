// THIS IS THE FILE INCLUDES ALL FUNCTION DEFINITIONS

#include "TruePatricianMusic.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

/* this is a constructor for the Genre class. The Genre class is what contains the vector to store the pointers to each
linked list. The pre-conditions are none, but it creates a nil pointer to a new Album make sure no pointers overlap.
there are no returning conditions. */
Genre::Genre(){
    nil = new Album();
}

/* virtual circular set up. It does not return and does not require any preconditions. You do not need to set up this, simply leave be
so the program know what it is*/
Genre::~Genre(){
}

/* this initializes the library. if we use a different file for the initial library, change the hardcoded file name in the main.cpp
the preconditions are the filename, it must be a string. This will read in the tile, and put every album into a linked list and into
the appropriate place on the vector of pointers. Each place in the vector is associated to a different genre. There are no post conditions*/
void Genre::initializeLibrary(std::string filename){
    ifstream infile;
    infile.open(filename.c_str());
    if(infile.is_open()){
        int entries = -1;
        string line, parse, artist, album, genre, ratingStr;
        int counting;
        int rating;
        while(getline(infile,line)){        // while there are lines to get
            entries++;
            counting=-1;
            istringstream ss(line);
            while(getline(ss,parse,'@')){
                counting++;
                if(counting==0){
                    artist=parse;
                }
                else if(counting==1){
                    album=parse;
                }
                else if(counting==2){
                    ratingStr=parse;
                    rating=atoi(ratingStr.c_str());
                }
                else{
                    genre=parse;
                }
            }
            if(entries==1){
                Album *newOne = new Album(artist,album,rating,genre);
                newOne->next=nil;
                newOne->previous=nil;
                library.push_back(newOne);
            }
            if(entries>1){
                addAlbumNode(artist,album,rating,genre);
            }
        }
    }
    infile.close();
    /*sort(library.begin(),library.end(),[](const Album &a, const Album &b){
         return((a.genre.compare(b.genre)==-1));
    });*/
}

/* This adds a new album into the system. If the genre is not already in the system, it expands the vector containing all the
heads for each genre with the new one. If the genre already exists, it will find that genre in the vector, and scroll throguh
the linked list until it finds the appropriate placement based on its rating. The albums are sorted hightest rating to lowest
There is no post condition, but the pre condition is the artist, album, rating,and genre, in that order. The artist, album,
and genre must be strings, where the rating must be an int. */
void Genre::addAlbumNode(std::string artist, std::string album, int rating, std::string genre){
	Album *newOne = new Album(artist,album,rating,genre);
	int root=0;
	Album *temp;
	Album *temp2;
    newOne->next=nil;
    newOne->previous=nil;
	for(int n=0; n<library.size(); n++){
        if(library[n]->genre == genre){
            break;
        }
        else if(n == library.size()-1){
            library.push_back(newOne);
            return;
        }
	}
    root=getRoot(genre);
    temp=library[root];
    if(rating>(library[root]->rating)){
        newOne->band=library[root]->band;
        newOne->album=library[root]->album;
        newOne->rating=library[root]->rating;
        newOne->genre=library[root]->genre;
        library[root]->band=artist;
        library[root]->album=album;
        library[root]->rating=rating;
        library[root]->genre=genre;
        temp=library[root]->next;
        library[root]->next=newOne;
        newOne->previous=library[root];
        newOne->next=temp;
        temp->previous=newOne;
        return;
    }
    else{
        while(temp->next!=nil){
            temp=temp->next;
            if(rating>=(temp->rating)&&rating<(temp->previous->rating)){
                newOne->band=temp->band;
                newOne->album=temp->album;
                newOne->rating=temp->rating;
                newOne->genre=temp->genre;
                temp->band=artist;
                temp->album=album;
                temp->rating=rating;
                temp->genre=genre;
                temp2=temp->next;
                temp->next=newOne;
                newOne->previous=temp;
                newOne->next=temp2;
                return;
            }
        }
        temp->next=newOne;
        newOne->previous=temp;
        return;
    }
}

/* Returns the index of each head in the vector. It will find which head is the linked list for that genre, and return what
index it is at. The precondition is the genre of the album, and the return is an int, which we use to find and replace
the values here if neeeded */
int Genre::getRoot(std::string genre){
    for(int i=0; i<library.size(); i++){
        if(library[i]->genre == genre)
            return i;
    }
}

/* This prints the library. It is the recursive version of the function that goes through the linked list and prints
each album that it contains. its precondition is the node in the linked list and its return is none, but is does
cout the information of the album*/
void Genre::printLibrary(Album *node){
    while(node!=nil){
        cout<<node->genre<<": "<<node->album<<" by "<<node->band<<" rated "<<node->rating<<endl;
        node=node->next;
    }
}

/* This is the caller to print the library. no preconditions and no post conditions, but what is does is go throguh the vector
of genres and calls the print library recursive for each head of each genre in the vector */
void Genre::printLibrary(){
    for(int i=0; i<library.size(); i++){
        printLibrary(library[i]);
    }
}

/* This prints the genres in the vector. no post and no pre conditions exist, it simply couts the genres*/
void Genre::printGenres(){
    cout<<"Genres currently in the /mu/ library: ";
    for(int i=0; i<library.size(); i++){
        cout<<library[i]->genre;
        if(i!=library.size()-1){
            cout<<", ";
        }
    }
    cout<<endl;
}

/* A compare function. Because case sensitive is a pain in the ass and we do not want duplicates in the library,
we added this so you can ignore the case sensitivity and find the album, even if you accidently make "the" instead
of "The". The pre conditions are two string, of each album. The return is boolean, true or false, if the titles are the same.*/
bool Genre::compare(std::string one, std::string two){
    int same=0;
    if(one.length()==two.length()){
        for(int i=0; i<one.length(); i++){
            if(one[i]==two[i] || (one[i]+32)==two[i] || (two[i]+32)==one[i]){
                    same++;
            }
            else{
                return false;
            }
        }
        if(same==one.length()){
            return true;
        }
    }
    return false;
}

/* function to rate the users taste. The return is the int value of the album, which is its pitchfork rating. The precondition is
the string of the album. It finds the album in the library and returns its rating. if it is not found, then
it will ask the user to include all of the information by calling a new function */
int Genre::rateMyTaste(std::string album){
    Album *albumFind;
    int rate;
    for(int i=0; i<library.size(); i++){
        albumFind=library[i];
        while(albumFind!=nil){
            if(compare(album,albumFind->album)){
                rate=albumFind->rating;
                return rate;
            }
            albumFind=albumFind->next;
        }
    }
    notInLibrary();
    return rateMyTaste(notInLibrary());
}

/* as afore mentioned, this is the function that will call if the album was not found. There is no precondition, but it returns the string
of the album. This is because if the album is not found in rate my taste function, it is called again with the return string of this
album so the album will be found and its rating will be returned */
std::string Genre::notInLibrary(){
    string artist, album, genre, rate;
    int rating=0;
    cout<<"Oh no! One of your favorite's cannot seem to be found. Pls add it!"<<endl;
    cout<<"Artist: ";
    getline(cin,artist);
    cout<<"Album: ";
    getline(cin,album);
    cout<<"Rating (Remember # out of 100): ";
    getline(cin,rate);
    rating=atoi(rate.c_str());
    printGenres();
    getline(cin,genre);
    addAlbumNode(artist,album,rating,genre);
    return album;
}
