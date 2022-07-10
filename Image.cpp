//!  An image class.
/*!
    A class with constructors, destructor, read, write, file type getting, message encoding and decoding functions.
*/

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <cstring>
#include "stb_image.h"
#include "stb_image_write.h"

#include "Image.h"

//! A constructor.
/*!
  A constructor that takes the filename.
  If the file was successfully loaded constructor displays the message specifying the filename
  and calculates the size of the file.
  If the file wasn't successfully loaded constructor displays the message specifying the filename.
*/
Image::Image(const char* filename) {
    if(read(filename)) {
        printf("Read %s\n", filename);
        size = w * h * channels; //!< A variable that stores the value of the image size.
    }
    else {
        printf("Failed to read %s\n", filename);
    }
}

//! A constructor.
/*!
  A constructor that takes the value of the image width, height and the number of the channels.
*/
Image::Image(int w, int h, int channels) : w(w), h(h), channels(channels) {
    size = w * h * channels; //!< A variable that stores the value of the image size.
    data = new uint8_t[size]; //!< A variable that stores image data, 1 bit - unit8_t.
}

//! A constructor.
/*!
  A constructor that copies the whole image data to another image.
*/
Image::Image(const Image& img) : Image(img.w, img.h, img.channels) {
    memcpy(data, img.data, size);
}

//! A destructor.
/*!
  A destructor that deletes all the image data.
*/
Image::~Image(){
    stbi_image_free(data);
}

//! A function variable.
/*!
  A function that takes the file name and returns the data.
  It loads the data from the file returns it.
  Return type: boolean.
*/
bool Image::read(const char* filename) {
    data = stbi_load(filename, &w, &h, &channels, 0);
    return data != NULL;
}

//! A function variable.
/*!
  A function that takes writes the data into the file.
  If the writing process was successful it prints out the message specifying the filename, weight, height, channels and size.
  If the writing process wasn't successful it prints out the message specifying the filename, weight, height, channels and size.
  Return type: boolean.
*/
bool Image::write(const char* filename) {
    ImageType type = getFileType(filename);
    int success;
    switch(type) {
        case ImageType::PNG:
            success = stbi_write_png(filename, w, h, channels, data, w*channels);
            break;
        case ImageType::BMP:
            success = stbi_write_bmp(filename, w, h, channels, data);
            break;
        case ImageType::JPG:
            success = stbi_write_jpg(filename, w, h, channels, data, 100);
            break;
        case ImageType::TGA:
            success = stbi_write_tga(filename, w, h, channels, data);
            break;
    }
    if (success != 0) {
        printf("Wrote %s, %d, %d, %d, %zu\n", filename, w, h, channels, size);
        return true;
    }
    else {
        printf("Failed to write %s, %d, %d, %d, %zu\n", filename, w, h, channels, size);
        return false;
    }
}

//! A function variable.
/*!
  A function that takes the file name and returns the file type.
  It extracts the file type from the file name and in default returns PNG type.
  If it doesn't find the '.' in the file path it returns unrecognized type.
*/
ImageType Image::getFileType(const char* filename) {
    const char* ext = strrchr(filename, '.');
    if(ext != nullptr) {
        if (strcmp(ext, ".png") == 0) {
            return ImageType::PNG;
        } else if (strcmp(ext, ".jpg") == 0) {
            return ImageType::JPG;
        } else if (strcmp(ext, ".bmp") == 0) {
            return ImageType::BMP;
        } else if (strcmp(ext, ".tga") == 0) {
            return ImageType::TGA;
        }
    }
    return ImageType::UNRECOGNIZED;
}

//! A function variable.
/*!
  A function that takes the message, checks encoding possibility, encodes the message if possible and returns it.
  If the size of the message is too large for the image then it returns the massage specifying the message and image size.
  It passes the message length to the data of the image and inserts the message to the image.
*/
Image& Image::encodeMessage(const char* message) {
    uint32_t len = strlen(message) * 8; //!< A variable that stores the length of the message.
                                        //!< Calculating how many bits are required to encode the message.

    if(false == checkEncodingPossibility(message)) {
        return *this;
    }

    for(uint8_t i = 0; i < STEG_HEADER_SIZE; ++i) {
        data[i] &= 0xFE;
        data[i] |= (len >> (STEG_HEADER_SIZE - 1 - i)) & 1UL;
    }

    for(uint32_t i = 0; i < len; ++i) {
        data[i + STEG_HEADER_SIZE] &= 0xFE;
        data[i + STEG_HEADER_SIZE] |= (message[i / 8] >> ((len - 1 - i) % 8)) & 1;
    }
    return *this;
}

//! A function variable.
/*!
  A function that takes the message, image and checks the possibility of encoding it into the bits of image.
  It prints out appropriate output (indicating the possibility).
  Return type: boolean.
*/
bool Image::checkEncodingPossibility(const char* message)
{
    uint32_t len = strlen(message) * 8;
    if((len + STEG_HEADER_SIZE) > size) {
        printf("This message is too large (%lu bits / %zu bits)\n", len + STEG_HEADER_SIZE, size);
        return false;
    }
    else return true;
}

//! A function variable.
/*!
  A function that takes the message, decodes the message and returns its size.
  It loads the bit after bit and puts the data into the buffer.
  The length of the message is given in bits so it needs to be divided by 8.
*/
Image& Image::decodeMessage(char* buffer, size_t* messageLenght) {
    uint32_t len = 0; //!< A variable that stores the length of the message.

    for (uint8_t i = 0; i < STEG_HEADER_SIZE; ++i) {
        len = (len << 1) | (data[i] & 1);
    }
    *messageLenght = len / 8;

    for (uint32_t i = 0; i < len; ++i ) {
        buffer[i/8] = (buffer[i / 8] << 1) | (data[i + STEG_HEADER_SIZE] & 1);
    }
    return *this;
}