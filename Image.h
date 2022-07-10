//!  An image class.
/*!
  A class with an enum storing image types, a structure, constructors, destructor, read, write, file type getting, message encoding and decoding functions.
*/

#ifndef ImageSteganography_IMAGE_H
#define ImageSteganography_IMAGE_H

#endif //ImageSteganography_IMAGE_H

#include <cstdint>
#include <cstdio>

#define STEG_HEADER_SIZE sizeof(uint32_t) * 8

//! An enum.
/*! An enum that stores file types. */
enum class ImageType {
    UNRECOGNIZED, /*!< Enum value unrecognized (default). */
    PNG, /*!< Enum value PNG. */
    JPG, /*!< Enum value JPG. */
    BMP, /*!< Enum value BMP. */
    TGA  /*!< Enum value TGA. */
};

//! A structure.
/*! A structure that stores image data, the value of the image size, width, height, number of channels,
 * constructors, destructor, read, write, get file type, encode, decode message and check encoding possibility functions. */
struct Image {
    uint8_t* data = NULL; //!< A variable that stores the image data, 1 bit - unit8_t.
    size_t size = 0; //!< A variable that stores the value of the image size.
    int w; //!< A variable that stores the value of the image width.
    int h; //!< A variable that stores the value of the image height.
    int channels; //!< A variable that stores the number of channels of the image.
                  //!< Channels specify how many colours can one pixel combine (RGB or RGBA).

    //! A constructor.
    /*!
       A constructor that takes the filename.
    */
    Image(const char* filename);

    //! A constructor.
    /*!
      A constructor that takes the value of the image width, height and the number of the channels.
    */
    Image(int w, int h, int channels);

    //! A constructor.
    /*!
      A constructor that copies images.
    */
    Image(const Image& img);

    //! A destructor.
    /*!
      A destructor that destroys all image data.
    */
    ~Image();

    //! A function variable.
    /*!
      A function that takes the file name and returns the data.
      Return type: boolean.
    */
    bool read(const char* filename);

    //! A function variable.
    /*!
      A function that takes writes the data on the file and returns the message saying whether the process was successful or not.
      Return type: boolean.
    */
    bool write(const char* filename);

    //! A function variable.
    /*!
      A function that takes the file name and returns the file type.
    */
    ImageType getFileType(const char* filename);

    //! A function variable.
    /*!
      A function that encodes the message and returns it.
    */
    Image& encodeMessage(const char* message);

    //! A function variable.
    /*!
      A function that decodes the message and returns its size.
    */
    Image& decodeMessage(char* buffer, size_t* messageLenght);

    //! A function variable.
    /*!
      A function that checks the encoding possibility, based on message length.
      Return type: boolean.
    */
    bool checkEncodingPossibility(const char* message);
};
