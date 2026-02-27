#pragma once

#include <system_error>
#include <stdexcept>
#include <string>

#ifdef ERROR_AUTO_TELLING
#include <iostream>
#include <mkbase/logging/logging.hpp>
#endif

#define FILENAME (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)
#define MK_TELL_ERROR(logger, error_obj) { auto __file_name = FILENAME; auto __line = __LINE__; logger.error("At {}:{} ==> \"{}\"", __file_name, __line, error_obj.what()); }

namespace monokuma::error {
    template <class T> concept has_exception_api = requires(const T& object) { { object.what() } -> std::same_as<const char*>; };

    class Error {
        std::string message_;

    public:
        Error(const std::exception& exception) {
            this->message_ = "std::exception: ";
            this->message_.append(exception.what());
        }

        Error(const std::system_error& system_error) {
            this->message_ = "std::system_error: ";
            this->message_.append(system_error.what());
        }

        Error(const std::runtime_error& runtime_error) {
            this->message_ = "std::runtime_error: ";
            this->message_.append(runtime_error.what());
        }

        Error(const std::invalid_argument& invalid_argument) {
            this->message_ = "std::invalid_argument: ";
            this->message_.append(invalid_argument.what());
        }

        Error(const std::logic_error& logic_error) {
            this->message_ = "std::logic_error: ";
            this->message_.append(logic_error.what());
        }

        Error& operator+=(const Error& other) {
            this->message_.append(" && ");
            this->message_.append(other.message_);
            return *this;
        }

        Error& operator+(const Error& other) {
            return *this += other;
        }

        Error(const std::out_of_range& out_of_range) {
            this->message_ = "std::out_of_range: ";
            this->message_.append(out_of_range.what());
        }

        template <has_exception_api T> Error(const T& error) {
        this->message_ = std::string(typeid(error).name()).substr(6); // If T is a struct, it will be ' MyErrorType'
            this->message_.append(": ");
            this->message_.append(error.what());
        }

        [[nodiscard]] const std::string& what() const noexcept { return this->message_; }
    };
}

#ifdef ERROR_AUTO_TELLING
#define MKERROR(error_constructor_args) ([&]() {\
        auto __filename = FILENAME; \
        auto __line = __LINE__; \
        auto __logger = monokuma::logging::DefaultColorLogger("Monokuma::ErrorTelling", monokuma::logging::ERROR, std::cout); \
        auto __error = monokuma::error::Error(error_constructor_args); \
        __logger.error("At {}:{} ==> {}", __filename, __line, __error.what()); \
        return __error; \
    }())
#else
#define MKERROR(error_constructor_args) monokuma::error::Error(error_constructor_args)
#endif