#pragma once

#include <chrono>
#include <format>
#include <string>

#include "mkbase/sync/fair_mutex.hpp"

namespace monokuma::logging {
    enum LogLevel {
        FATAL = 0,
        ERROR = 1,
        WARNING = 2,
        INFO = 3,
        DEBUG = 4,
    };

    class DefaultColorLogger {
        std::string self_name_;
        std::ostream& out_;
        sync::fair::mutex sync_;
        LogLevel max_log_level_;
        bool use_ansi_colors_;

        static void monokuma_logging_write_log(std::ostream& output, sync::fair::mutex& sync, const std::string& logger_name,
            const std::string& logging_level_str, const std::string& fmt_str, const std::format_args& fmt_args) {
            std::lock_guard lock(sync);

            auto time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            auto* tm = std::localtime(&time_t);

            output << "[ " << std::put_time(tm, "%d.%m.%Y %H:%M:%S") << " ] ";
            output << "[ " << logger_name << " ] ";
            output << "[ " << logging_level_str << " ] ";

            std::string formatted;
            try {
                formatted = std::vformat(fmt_str, fmt_args);
            } catch (const std::format_error& fmt_error) {
                output << "Log format error: \"" << fmt_error.what() << "\" ==> \"" << fmt_str << "\"" << std::endl;
                return;
            }
            output << formatted << std::endl;
            output.flush();
        }
    public:
        DefaultColorLogger(const char* logger_name, LogLevel max_log_level, std::ostream& out, bool use_ansi_colors = true)
        : self_name_(logger_name), out_(out), max_log_level_(max_log_level), use_ansi_colors_(use_ansi_colors) {}

        void set_max_log_level(const LogLevel& new_max_log_level) { this->max_log_level_ = new_max_log_level; }

        template <class... ArgsT> void fatal(const std::string &fmt_str, ArgsT&&... args) {
            if (this->max_log_level_ < ERROR) return;
            auto fmt_args = std::make_format_args(std::forward<ArgsT>(args)...);
            if (this->use_ansi_colors_)
                monokuma_logging_write_log(this->out_, this->sync_, this->self_name_, "\033[41m\033[37mFATAL\033[0m", fmt_str, fmt_args);
            else
                monokuma_logging_write_log(this->out_, this->sync_, this->self_name_, "FATAL", fmt_str, fmt_args);
        }

        template <class... ArgsT> void error(const std::string &fmt_str, ArgsT&&... args) {
            if (this->max_log_level_ < ERROR) return;
            auto fmt_args = std::make_format_args(std::forward<ArgsT>(args)...);
            if (this->use_ansi_colors_)
                monokuma_logging_write_log(this->out_, this->sync_, this->self_name_, "\033[31mERROR\033[0m", fmt_str, fmt_args);
            else
                monokuma_logging_write_log(this->out_, this->sync_, this->self_name_, "ERROR", fmt_str, fmt_args);
        }

        template <class... ArgsT> void warning(const std::string &fmt_str, ArgsT&&... args) {
            if (this->max_log_level_ < WARNING) return;
            auto fmt_args = std::make_format_args(std::forward<ArgsT>(args)...);
            if (this->use_ansi_colors_)
                monokuma_logging_write_log(this->out_, this->sync_, this->self_name_, "\033[33mWARN\033[0m", fmt_str, fmt_args);
            else
                monokuma_logging_write_log(this->out_, this->sync_, this->self_name_, "WARN", fmt_str, fmt_args);
        }

        template <class... ArgsT> void info(const std::string &fmt_str, ArgsT&&... args) {
            if (this->max_log_level_ < INFO) return;
            auto fmt_args = std::make_format_args(std::forward<ArgsT>(args)...);
            if (this->use_ansi_colors_)
                monokuma_logging_write_log(this->out_, this->sync_, this->self_name_, "\033[32mINFO\033[0m", fmt_str, fmt_args);
            else
                monokuma_logging_write_log(this->out_, this->sync_, this->self_name_, "INFO", fmt_str, fmt_args);
        }

        template <class... ArgsT> void debug(const std::string &fmt_str, ArgsT&&... args) {
            if (this->max_log_level_ < DEBUG) return;
            auto fmt_args = std::make_format_args(std::forward<ArgsT>(args)...);
            if (this->use_ansi_colors_)
                monokuma_logging_write_log(this->out_, this->sync_, this->self_name_, "\033[34mDEBUG\033[0m", fmt_str, fmt_args);
            else
                monokuma_logging_write_log(this->out_, this->sync_, this->self_name_, "DEBUG", fmt_str, fmt_args);
        }    };
}