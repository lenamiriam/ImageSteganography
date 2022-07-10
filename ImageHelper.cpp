//!  An image helper class.
/*!
    A class with check, encode, decode, get information about file type functions.
*/

#include "ImageHelper.h"

//! A function variable.
/*!
  A function that checks if it is possible to encode a message into the image.
*/
void ImageHelper::check() {
    image = std::unique_ptr<Image>(new Image(filename.c_str()));
    if(nullptr == image) {
        std::cerr << "Image loading has not succeed." << std::endl;
    }
    auto res = image->checkEncodingPossibility(message.c_str());
    if(res) {
        std::cout << "It is possible to encode the message into the image" << std::endl;
        return;
    }
    std::cout << "It is not possible to encode the message into the image" << std::endl;
}

//! A function variable.
/*!
  A function that encodes the message into the image.
*/
void ImageHelper::encode() {
    image = std::unique_ptr<Image>(new Image(filename.c_str()));
    if(nullptr == image) {
        std::cerr << "Image loading has not succeed." << std::endl;
    }
    auto res = image->checkEncodingPossibility(message.c_str());
    if(res) {
        std::cout << "Check successful. Encoding..." << std::endl;
        image->encodeMessage(message.c_str());
        image->write(filename.c_str());
        return;
    }
    std::cout << "Encoding is not possible. Pre-check failed" << std::endl;
}

//! A function variable.
/*!
  A function that decodes the message into the image.
*/
void ImageHelper::decode() {
    image = std::unique_ptr<Image>(new Image(filename.c_str()));
    if(nullptr == image) {
        std::cerr << "Image loading has not succeed." << std::endl;
    }
    char buffer[MAX_BUFFER_SIZE]{0};
    size_t len = 0;
    image->decodeMessage(buffer, &len);

    printf("Decoding successful. Hidden message: %s (%zu)\n", buffer, len);
}

//! A function variable.
/*!
  A function that displays the information about chosen file type and image size.
*/
void ImageHelper::getInfo() {
    image = std::unique_ptr<Image>(new Image(filename.c_str()));
    if(nullptr == image) {
        std::cerr << "Image loading has not succeed." << std::endl;
    }
    auto format = image->getFileType(filename.c_str());
    switch(format) {
        case ImageType::BMP:
            std::cout << R"===(
                The BMP file format, also known as bitmap image file, device independent bitmap (DIB) file format and bitmap,
                is a raster graphics image file format used to store bitmap digital images,
                independently of the display device (such as a graphics adapter), especially on Microsoft Windows and OS/2 operating systems.
            )===" << std::endl;
            break;
        case ImageType::JPG:
            std::cout << R"===(
                JPEG is a commonly used method of lossy compression for digital images, particularly for those images produced by digital photography.
                The degree of compression can be adjusted, allowing a selectable tradeoff between storage size and image quality.
                JPEG typically achieves 10:1 compression with little perceptible loss in image quality.
            )===" << std::endl;
            break;
        case ImageType::PNG:
            std::cout << R"===(
                Portable Network Graphics (PNG, officially pronounced PING, colloquially pronounced PEE-en-JEE) is a raster-graphics file format that supports lossless data compression.
                PNG was developed as an improved, non-patented replacement for Graphics Interchange Format (GIF)
                — unofficially, the initials PNG stood for the recursive acronym "PNG's not GIF".
            )===" << std::endl;
            break;
        case ImageType::TGA:
            std::cout << R"===(
                Truevision TGA, often referred to as TARGA, is a raster graphics file format created by Truevision Inc. (now part of Avid Technology).
                It was the native format of TARGA and VISTA boards, which were the first graphic cards for IBM-compatible PCs to support Highcolor/truecolor display.
                This family of graphic cards was intended for professional computer image synthesis and video editing with PCs; for this reason, usual resolutions of TGA image files match those of the NTSC and PAL video formats.
            )===" << std::endl;
            break;
        default:
            std::cout << "Unrecognized (or unsupported) type." << std::endl;
            break;
    }
    std::cout << "Image size: " << image->size << std::endl;
}