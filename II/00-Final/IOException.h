#ifndef PARKINGTICKETSIMULATOR_IOEXCEPTION_H
#define PARKINGTICKETSIMULATOR_IOEXCEPTION_H

#include <string>
#include <stdexcept>

/**
 * Exception class.
 * Extends std::runtime_error.
 * This class is used for catching any exceptions with file input and output.
 * It can capture the name of the function where an IO operation was performed
 * to be accessed by the .what() provided by the parent.
 */
class IOException : public std::runtime_error {
public:
    explicit IOException(const std::string &functionName)
            : runtime_error(
            "Failure resulted from function: " + functionName) {}
};

#endif //PARKINGTICKETSIMULATOR_IOEXCEPTION_H
