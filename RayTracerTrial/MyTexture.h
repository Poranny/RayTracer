#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <algorithm>

class MyTexture {
public:
    MyTexture();
    MyTexture(int width, int height);

    unsigned char* operator()(int x, int y);
    unsigned char* getRawData();

    int getWidth();
    int getHeight();

    void setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b);
    void getPixel(int x, int y, unsigned char& r, unsigned char& g, unsigned char& b);


private:
    std::vector<unsigned char> data;
    int width;
    int height;
};

#endif
