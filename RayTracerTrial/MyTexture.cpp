#include "MyTexture.h"
#include <stdexcept>
#include <algorithm>

MyTexture::MyTexture() : width(1), height(1) {

    data.clear();
    data.shrink_to_fit();

    data.resize(width * height * 3);
}

MyTexture::MyTexture(int _width, int _height) : width(_width), height(_height) {
    
    data.clear();
    data.shrink_to_fit();


    if (width > 0 && height > 0) {
        data.resize(width * height * 3);
    } else {
        throw std::invalid_argument("Invalid texture dimensions");
    }
}

unsigned char* MyTexture::operator()(int x, int y) {
    int index = (y * width + x) * 3;
    

    if (index >= 0 && index < data.size()) {
        return &data[index];
    } else {
        throw std::out_of_range("Texture index out of range");
    }
}

unsigned char* MyTexture::getRawData() {
    return data.data();
}

int MyTexture::getWidth() {
    return width;
}

int MyTexture::getHeight() {
    return height;
}

void getPixel(int x, int y, unsigned char& r, unsigned char& g, unsigned char& b);


void MyTexture::setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b) {
    unsigned char* pixel = (*this)(x, y);
    
    pixel[0] = r;
    pixel[1] = g;
    pixel[2] = b;
}


void MyTexture::getPixel(int x, int y, unsigned char& r, unsigned char& g, unsigned char& b) {
    unsigned char* pixel = (*this)(x, y);
    r = pixel[0];
    g = pixel[1];
    b = pixel[2];
}