#pragma once
#include <chrono>
#include <ctime>
#include <fmt/core.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <mutex>

enum class LogLevel
{
  Trace,
  Info,
  Warning,
  Error
};

class Logger
{
public:
  Logger() : log_stream_( "log.txt", std::ios::app ) {}

  void log( LogLevel level, const std::string& message );

private:
  std::mutex mutex_;
  std::ofstream log_stream_;

  static std::string levelToString( LogLevel level )
  {
    switch( level ) {
      case LogLevel::Trace:
        return "TRACE";
      case LogLevel::Info:
        return "INFO";
      case LogLevel::Warning:
        return "WARNING";
      case LogLevel::Error:
        return "ERROR";
      default:
        return "";
    }
  }
};
