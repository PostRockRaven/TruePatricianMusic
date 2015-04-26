// THIS FILE INLCUDES THE CLASS

#ifndef TRUEPATRICIANMUSIC_H
#define TRUEPATRICIANMUSIC_H

#include <vector>
#include <string>

struct Album{
    std::string band;
    std::string album;
    std::string genre;
    int rating;

    int score;

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
        void recommend(std::string);
        Album *searchLibrary(std::string);
        void printLibrary();
        void addAlbumNode(std::string artist, std::string album, int rating, std::string genre);
        void printGenres();
        void genreRecommend(std::string genre);
        void patricianize();
        void GOAT();
        bool compare(std::string one, std::string two);
        int rateMyTaste(std::string album);
        int getRoot(std::string genre);
        std::string notInLibrary();
    protected:
    private:
        void printLibrary(Album *node);
        std::vector<Album*> library;
        Album *nil;
};
#endif // TRUEPATRICIANMUSIC_H
