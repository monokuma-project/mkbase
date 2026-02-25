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
    class Error {
        std::string message_;

        static void tell(const Error& self) {
#ifdef ERROR_AUTO_TELLING
            static auto logger = logging::DefaultColorLogger("Monokuma::ErrorTelling", logging::LogLevel::ERROR, std::cerr);
            //logger.error("{}", self.what());
            MK_TELL_ERROR(logger, self);
#endif
        }
    public:
        Error(const std::exception& exception) {
            this->message_ = "std::exception: ";
            this->message_.append(exception.what());
            tell(*this);
        }

        Error(const std::system_error& system_error) {
            this->message_ = "std::system_error: ";
            this->message_.append(system_error.what());
            tell(*this);
        }

        Error(const std::runtime_error& runtime_error) {
            this->message_ = "std::runtime_error: ";
            this->message_.append(runtime_error.what());
            tell(*this);
        }

        Error(const std::invalid_argument& invalid_argument) {
            this->message_ = "std::invalid_argument: ";
            this->message_.append(invalid_argument.what());
            tell(*this);
        }

        Error(const std::logic_error& logic_error) {
            this->message_ = "std::logic_error: ";
            this->message_.append(logic_error.what());
            tell(*this);
        }

        Error(const std::ios_base::failure& ios_error) {
            this->message_ = "std::ios_base::failure: ";
            this->message_.append(ios_error.what());
            tell(*this);
        }

        Error& operator+=(const Error& other) {
            this->message_.append(" && "); this->message_.append(other.message_);
            tell(*this);
            return *this;
        }

        Error& operator+(const Error& other) {
            return *this += other;
        }


        const std::string& what() const noexcept { return this->message_; }
    };
}