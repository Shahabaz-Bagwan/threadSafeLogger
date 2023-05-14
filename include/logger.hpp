#pragma once
#include <chrono>
#include <cstdio>
#include <ctime>
#include <fmt/core.h>
#include <fmt/chrono.h>
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
  Logger( std::string const& filename, LogLevel minLevel )
    : log_stream_{ std::fopen( filename.c_str(), "a" ) }, minLevel_{ minLevel }
  {
  }

  void log( LogLevel level, const std::string& message );

  ~Logger() { std::fclose( log_stream_ ); }

private:
  std::mutex mutex_;
  std::FILE* log_stream_;
  LogLevel minLevel_{ LogLevel::Info };

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

  // std::string getTimeStamp()
  // {
  //   auto time                            = std::chrono::system_clock::now();
  //   std::chrono::duration< double > diff = time.time_since_epoch();
  //   auto milliseconds =
  //     std::chrono::duration_cast< std::chrono::milliseconds >( diff );
  //   auto time_point = std::chrono::time_point< std::chrono::system_clock >(
  //     std::chrono::milliseconds( milliseconds ) );
  //   auto time_string =
  //     fmt::format( "{:%Y-%m-%d %H:%M:%S.%f}", fmt::localtime( *time_point ) );
  //   return time_string;
  // }
};
