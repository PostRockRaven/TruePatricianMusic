#include "TruePatricianMusic.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

Genre::Genre(){
    nil = new Album();
}

Genre::~Genre(){
}

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

int Genre::getRoot(std::string genre){
    for(int i=0; i<library.size(); i++){
        if(library[i]->genre == genre)
            return i;
    }
}

void Genre::printLibrary(Album *node){
    while(node!=nil){
        cout<<node->genre<<": "<<node->album<<" by "<<node->band<<" rated "<<node->rating<<endl;
        node=node->next;
    }
}

void Genre::printLibrary(){
    for(int i=0; i<library.size(); i++){
        printLibrary(library[i]);
    }
}

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
