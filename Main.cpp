//!  A main class.
/*!
    A class with enum storing modes - flags, print help, check if operation mode is specified, parse command line and main functions.
*/

#include <iostream>
#include <vector>
#include <memory>

#include "ImageHelper.h"

std::string filepath; //!< A variable that stores the file path.
std::string message; //!< A variable that stores the message.

//! An enum.
/*! An enum that stores modes - flags. */
enum class MODE {
    NOT_SPECIFIED, /*!< Enum value NOT_SPECIFIED. */
    INFO, /*!< Enum value INFO. */
    CHECK, /*!< Enum value CHECK. */
    ENCRYPT, /*!< Enum value ENCRYPT. */
    DECRYPT /*!< Enum value DECRYPT. */
};
MODE operatingMode = MODE::NOT_SPECIFIED;

//! A function variable.
/*!
  A function that displays help message.
*/
void printHelp() {
    std::cout << R"===(Usage and arguments:
              -i, --info  Specify file path. Check if file path extends supported format. If yes, program delivers file: format, size, location, last modification timestamp.
              -e, --encrypt  Specify file path and message. Check if file path extends supported format. If yes, the given message is write down on the image.
              -d, --decrypt  Specify file path from from which you want to read the message. Checks if file path extends supported format.
              -c, --check  Specify file path and message. Check if the given message could be wrote down on/read from the given file.
              -h, --help  Displays help message (this one).)===" << std::endl;
}

//! A function variable.
/*!
  A function that checks if the operation mode was specified - takes the mode and returns it if it wasn't specified.
  Return type: boolean.
*/
bool checkIfOperationModeSpecified(const MODE& m) {
    return m == MODE::NOT_SPECIFIED;
}

//! A function variable.
/*!
  A function that takes the number of the arguments and the vector of the arguments value given by user in command line
  and disposes an appropriate message.
  Return type: int.
*/
int parseCommandLine(size_t numArgs, const std::vector<std::string>& argv) {
    if(numArgs < 2) {
        std::cerr << "Less than 2 arguments specified. Read help output." << std::endl;
        return -1;
    }
    for (uint32_t argIndex = 1; argIndex < numArgs; argIndex++) {
        const auto &currArg = argv[argIndex];
        auto hasMoreArgs = [=](uint32_t ind) {
            return (ind + 1 < numArgs);
        };
        if(currArg == "-i" || currArg == "--info") {
            if(!checkIfOperationModeSpecified(operatingMode)) {
                std::cerr << "Only one mode (-i, -e, -c, -d) specified allowed." << std::endl;
            }
            operatingMode = MODE::INFO;
            if(hasMoreArgs(argIndex)) {
                argIndex++;
                filepath = argv[argIndex];
            }
            else {
                std::cerr << currArg << ", missing next argument (filepath)." << std::endl;
                return -1;
            }
        }
        else if(currArg == "-e" || currArg == "--encrypt") {
            if(!checkIfOperationModeSpecified(operatingMode)) {
                std::cerr << "Only one mode (-i, -e, -c, -d) specified allowed." << std::endl;
            }
            operatingMode = MODE::ENCRYPT;
            if(hasMoreArgs(argIndex)) {
                argIndex++;
                filepath = argv[argIndex];
            }
            else {
                std::cerr << currArg << ", missing next argument (filepath, message)." << std::endl;
                return -1;
            }
            if(hasMoreArgs(argIndex)) {
                argIndex++;
                message = argv[argIndex];
            }
             else {
                std::cerr << currArg << ", missing next argument (message)." << std::endl;
                return -1;
            }
        }
        else if(currArg == "-d" || currArg == "--decrypt") {
            if(!checkIfOperationModeSpecified(operatingMode)) {
                std::cerr << "Only one mode (-i, -e, -c, -d) specified allowed." << std::endl;
            }
            operatingMode = MODE::DECRYPT;
            if(hasMoreArgs(argIndex)) {
                argIndex++;
                filepath = argv[argIndex];
            }
            else {
                std::cerr << currArg << ", missing next argument (filepath)." << std::endl;
                return -1;
            }
        }
        else if(currArg == "-c" || currArg == "--check") {
            if(!checkIfOperationModeSpecified(operatingMode)) {
                std::cerr << "Only one mode (-i, -e, -c, -d) specified allowed." << std::endl;
            }
            operatingMode = MODE::CHECK;
            if(hasMoreArgs(argIndex)) {
                argIndex++;
                filepath = argv[argIndex];
            }
            else {
                std::cerr << currArg << ", missing next argument (filepath, message)." << std::endl;
                return -1;
            }
            if(hasMoreArgs(argIndex)) {
                argIndex++;
                message = argv[argIndex];
            }
            else {
                std::cerr << currArg << ", missing next argument (message)." << std::endl;
                return -1;
            }
        }
        else {
            std::cerr << "Unknown option specified" << std::endl;
            return -1;
        }
    }
    return 0;
}

//! A main function variable.
/*!
  A function that takes the number of the given arguments and those arguments and displays appropriate output
  (depending on the chosen flag - mode).
*/
int main(int argc, char** argv) {
    auto parseResult = parseCommandLine(argc, std::vector<std::string>(argv, argv+argc));
    if(0 != parseResult) {
        printHelp();
        return -1;
    }
    ImageHelper imHelper(filepath, message);
    switch(operatingMode) {
        case MODE::CHECK:
            imHelper.check();
            break;
        case MODE::DECRYPT:
            imHelper.decode();
            break;
        case MODE::ENCRYPT:
            imHelper.encode();
            break;
        case MODE::INFO:
            imHelper.getInfo();
            break;
        default:
            break;
    }
    return 0;
}