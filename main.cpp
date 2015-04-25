#include <iostream>
#include "TruePatricianMusic.h"
using namespace std;

void mainMenu();

int main()
{
    Genre muLibrary;
    muLibrary.initializeLibrary("mu.txt");
    string option = " ";
    while(option!="8"){
        option.erase();
        int invalid = 0;
        while(option!="1"&&option!="2"&&option!="3"&&option!="4"&&option!="5"&&option!="6"&&option!="7"&&option!="8"){
            if(invalid>0){
                cout<<"Invalid Input"<<endl;
            }
            mainMenu();
            getline(cin,option);
            invalid++;
        }
        if(option=="1"){
            string album1, album2, album3;
            int ratingTotal = 0;
            cout<<"Why hello! I hope you are having a gr8 day m8! We have devised a flawless algorithm to determine your taste!"<<endl;
            cout<<"I am going to ask you to enter your three favorite albums!"<<endl;
            cout<<"1st: ";
            getline(cin,album1);
            cout<<"2nd: ";
            getline(cin,album2);
            cout<<"3rd: ";
            getline(cin,album3);
            ratingTotal+=muLibrary.rateMyTaste(album1);
            ratingTotal+=muLibrary.rateMyTaste(album2);
            ratingTotal+=muLibrary.rateMyTaste(album3);
            ratingTotal=ratingTotal/3;
            if(ratingTotal>89){
                cout<<"Congratulations on your true patrician taste!"<<endl;
            }
            else{
                cout<<"REEEEEEEEE! I apologize, but you do not have true patrician taste. :c"<<endl;
            }

        }
        else if(option=="2"){
        }
        if(option=="3"){
            string artist, album, genre, rating;
            int ratingInt;
            cout<<"Okay. Cool. Well first off, what band/artist are you adding?"<<endl;
            getline(cin,artist);
            cout<<"What is the album you want to put in?"<<endl;
            getline(cin,album);
            cout<<"Cool, cool. Our system is #/100 for ratings. Go to pitchfork, get that rating, and multiply it by 10 to get rid of that decimal."<<endl;
            getline(cin,rating);
            ratingInt=atoi(rating.c_str());
            cout<<"Last question, pick a genre, be specific. Either pick from this list, or if none fit, include another."<<endl;
            muLibrary.printGenres();
            getline(cin,genre);
            muLibrary.addAlbumNode(artist,album,ratingInt,genre);
            cout<<"k"<<endl;
        }
        else if(option=="4"){
            muLibrary.printLibrary();
        }
        else if(option=="5"){
        }
        else if(option=="6"){
        }
        else if(option=="7"){
        }
    }
    cout<<"lol"<<endl;
}

void mainMenu(){
    cout<<"======/mu/ menu lol======="<<endl;
    cout<<"1. R8 my taste!"<<endl;
    cout<<"2. Recommend me some tunes pls"<<endl;
    cout<<"3. Add music to the library"<<endl;
    cout<<"4. View the /mu/ library"<<endl;
    cout<<"5. GET OFF THE BOARD"<<endl;
}
