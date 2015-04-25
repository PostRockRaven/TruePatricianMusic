#ifndef TRUEPATRICIANMUSIC_H
#define TRUEPATRICIANMUSIC_H

#include <vector>
#include <string>

struct Album{
    std::string band;
    std::string album;
    std::string genre;
    int rating;

    Album *next = NULL;
    Album *previous = NULL;

    Album(){};

    Album(std::string _band, std::string _album, int _rating, std::string _genre){
        band = _band;
        album = _album;
        rating = _rating;
        genre = _genre;
    }
};

class Genre{
    public:
        ~Genre();
        Genre();
        void initializeLibrary(std::string);
        void printLibrary();
        void addAlbumNode(std::string artist, std::string album, int rating, std::string genre);
        void printGenres();
        bool compare(std::string one, std::string two);
        int rateMyTaste(std::string album);
        std::string notInLibrary();
    protected:
    private:
        void printLibrary(Album *node);
        int getRoot(std::string genre);
        std::vector<Album*> library;
        Album *nil;
};
#endif // TRUEPATRICIANMUSIC_H
