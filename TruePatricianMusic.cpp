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
	nil->red = false;
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
                newOne->parent=nil;
                newOne->leftChild=nil;
                newOne->rightChild=nil;
                newOne->red=true;
                library.push_back(*newOne);
            }
            if(entries>1){
                for(int i=0;i<library.size();i++){
                    if(library[i].genre==genre){
                        addAlbumNode(artist,album,rating,genre);
                        break;
                    }
                    else if(i==library.size()-1){
                        Album *newOne = new Album(artist,album,rating,genre);
                        newOne->parent=nil;
                        newOne->leftChild=nil;
                        newOne->rightChild=nil;
                        newOne->red=true;
                        library.push_back(*newOne);
                        break;
                    }
                }
            }
        }
    }
    sort(library.begin(),library.end());
}

void Genre::rbAddFixup(Album *node){
	    Album *y;
	    Album *root = getRoot(node->genre);
	    while((node != root)&&(node->parent->red)){
	        if(node->parent == node->parent->parent->leftChild){
	            y = node->parent->parent->rightChild; // uncle
	            if(y->red){
	                node->parent->red = false; // set parent black
	                y->red = false;            // set uncle black
	                node->parent->parent->red = true; // set grandparent red
	                node = node->parent->parent;  // set node to grandparent
	            }
	            else{
	                if( node == node->parent->rightChild){
	                    node = node->parent;   // set node to parent
	                    leftRotate(node);      // left rotate
	                }
	                node->parent->red = false;   // set parent black
	                node->parent->parent->red = true;   // set grandparent red
	                rightRotate(node->parent->parent);    // right rotate grandparent
	            }
	        }
	        else{
	            y = node->parent->parent->leftChild;
	            if(node->parent=nil){
                    return;
	            }
                if(y->red){
	                node->parent->red = false;  // set parent black
	                y->red = false;             // set uncle black
	                node->parent->parent->red = true;  // set grandparent red
	                node = node->parent->parent;      // set node to grandparent
	            }
	            else{
	                if(node == node->parent->leftChild){
	                    node = node->parent;  // set node to parent
	                    rightRotate(node);    // right rotate
	                }
	                node->parent->red = false;  // set parent black
	                node->parent->parent->red = true; // set grandparent red
	                leftRotate(node->parent->parent);  // left rotate
	            }
	        }
	    }
        for(int i=0; i<library.size(); i++){
            if(node->genre==library[i].genre){
                library[i].red=false;
        }
    }
}

void Genre::leftRotate(Album * x){
	    Album *y;
	    y = x->rightChild;
	    x->rightChild = y->leftChild;  // y's left subtree becomes x's right subtree
	    if (y->leftChild != nil) {
	    	y->leftChild->parent = x;
	    }
	    y->parent = x->parent;      // y's new parent was x's parent
	    if (x->parent == nil) {   // if not at root, set the parent to point to y instead of x
        for(int i=0; i<library.size(); i++){
            if(y->genre==library[i].genre){
                library[i]=*y;
            }
        }
	    } else if (x == x->parent->leftChild) {
	    	x->parent->leftChild = y;     // x was on left of its parent
	    } else {
	    	x->parent->rightChild = y;    // x was on right of its parent
	    }
	    y->leftChild = x;          // put x on y's left
	    x->parent = y;
	}

void Genre::rightRotate(Album *x) {
	Album *y;
	y = x->leftChild;
	x->leftChild = y->rightChild;   // y's right subtree becomes x's left subtree
    if (y->rightChild != nil) {
    	y->rightChild->parent = x;
    }
    y->parent = x->parent;          // y's new parent was x's parent
    if (x->parent == nil) {      // if not at root, set the parent to point to y instead of x
        for(int i=0; i<library.size(); i++){
            if(x->genre==library[i].genre){
                library[i]=*y;
            }
        }
    } else if (x == x->parent->leftChild) {
    	x->parent->leftChild = y;     // x was on left of its parent
    } else {
    	x->parent->rightChild = y;    // x was on right of its parent
    }
    y->rightChild = x;            // put x on y's right
    x->parent = y;
}

Album* Genre::findMin(Album* node){
    while(node->leftChild != nil){
        node = node->leftChild;
    }
    return node;
}

Album* Genre::searchAlbumTree(Album * node, int rating){
    if (node == nil)
        return nil;
    else if (node->rating == rating)
        return node;
    else{
        if(rating<node->rating)
            return searchAlbumTree(node->leftChild,rating);

        else
            return searchAlbumTree(node->rightChild,rating);
    }
}

void Genre::addAlbumNode(std::string artist, std::string album, int rating, std::string genre){
	Album *newNode = new Album(artist,album,rating,genre);
	Album *temp=nil;
	Album *parent=nil;
	Album *root = getRoot(genre);
	for(int n=0; n<library.size(); n++){
        if(library[n].genre == genre){
            break;
        }
        else if(n == library.size()-1){
            Album *newOne = new Album(artist,album,rating,genre);
            newOne->parent=nil;
            newOne->leftChild=nil;
            newOne->rightChild=nil;
            newOne->red=true;
            library.push_back(*newOne);
            sort(library.begin(),library.end());
            return;
        }
	}
	if (root == nil) { // add this movie as the root
        cout<<"should not happen"<<endl;
		newNode->leftChild=nil;
		newNode->rightChild=nil;
		newNode->parent=nil;
        for(int i=0; i<library.size(); i++){
            if(newNode->genre==library[i].genre){
                library[i]=*newNode;
            }
        }
	} else {
		temp = getRoot(genre);
		while (temp != nil) { // keep traversing until hit a leaf
            parent = temp;
			if (rating>=temp->rating) {
                 temp = temp->leftChild;
			} else {
                 temp = temp->rightChild;
			}
		}
		newNode->leftChild=nil;
		newNode->rightChild=nil;
		newNode->parent = parent;  // update parent of new node
		if (rating>=parent->rating) { // add new node as left or right child
			parent->leftChild = newNode;
		} else
			parent->rightChild = newNode;
	}
    rbAddFixup(newNode);
    return;
}

Album *Genre::getRoot(std::string genre){
    for(int i=0; i<library.size(); i++){
        if(library[i].genre == genre)
            return &library[i];
    }
}

void Genre::printLibrary(Album *node){
    if(node->leftChild!=nil){
        printLibrary(node->leftChild);
    }
    cout<<node->genre<<": "<<node->album<<" by "<<node->band<<" rated "<<node->rating<<endl;
    if(node->rightChild!=nil){
        printLibrary(node->rightChild);
    }
}

void Genre::printLibrary(){
    for(int i=0; i<library.size(); i++){
        printLibrary(&library[i]);
    }
}

void Genre::printGenres(){
    cout<<"Genres currently in the /mu/ library: ";
    for(int i=0; i<library.size(); i++){
        cout<<library[i].genre;
        if(i!=library.size()-1){
            cout<<", ";
        }
    }
    cout<<endl;
}
