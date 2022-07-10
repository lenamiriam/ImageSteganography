#include <memory>
#include <string>
#include <iostream>

#include "Image.h"

#define MAX_BUFFER_SIZE 256

//! A structure.
/*! A structure that stores check, encode, decode and get information functions, unique pointer and file name, message storing variables. */
struct ImageHelper {
    ImageHelper() {}
    ImageHelper(const std::string& _filename) : ImageHelper(_filename, {}) {}
    ImageHelper(const std::string& _filename, const std::string& _message) : filename(_filename), message(_message) {}

    //! A function variable.
    /*!
      A function that checks if it is possible to encode a message into the image.
    */
    void check();

    //! A function variable.
    /*!
      A function that encodes the message into the image.
    */
    void encode();


    //! A function variable.
    /*!
      A function that decodes the message into the image.
    */
    void decode();

    //! A function variable.
    /*!
      A function that displays the information about chosen file type and image size.
     */
    void getInfo();

    std::unique_ptr<Image> image; //!< A unique pointer that manages image object.
    const std::string filename; //!< A constant variable that stores the file name.
    const std::string message; //!< A constant variable that stores the message.
};