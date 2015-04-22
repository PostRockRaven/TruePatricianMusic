#ifndef TRUEPATRICIANMUSIC_H
#define TRUEPATRICIANMUSIC_H

#include <vector>
#include <string>

struct Album{
    std::string band;
    std::string album;
    std::string genre;
    int rating;

    bool red;
    Album *parent;
    Album *leftChild;
    Album *rightChild;

    Album(){};

    Album(std::string _band, std::string _album, int _rating, std::string _genre){
        band = _band;
        album = _album;
        rating = _rating;
        genre = _genre;
        leftChild = NULL;
    	rightChild = NULL;
        parent = NULL;
        red = true;
    }

    bool operator<(const Album& other)const{
    if(genre.compare(other.genre)<0)
        return true;
    else return false;};

};

class Genre{
    public:
        ~Genre();
        Genre();
        void initializeLibrary(std::string);
        void printLibrary();
        void addAlbumNode(std::string artist, std::string album, int rating, std::string genre);
        void printGenres();
    protected:
    private:
        void DeleteAll(Album * node); //use this for the post-order traversal deletion of the tree
        void rbAddFixup(Album * node); // called after insert to fix tree
        void leftRotate(Album * x);
        void rightRotate(Album * x);
        void printLibrary(Album *node);
        Album *findMin(Album* node);
        Album *getRoot(std::string genre);
        Album *searchAlbumTree(Album * node, int rating);
        Album *nil;
        std::vector<Album> library;
};
#endif // TRUEPATRICIANMUSIC_H
