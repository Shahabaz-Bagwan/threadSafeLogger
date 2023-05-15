#pragma once
#include <chrono>
#include <cstdio>
#include <ctime>
#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/os.h>
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
    : output_{ fmt::output_file( filename.c_str(), fmt::file::WRONLY |
                                                     fmt::file::CREATE |
                                                     fmt::file::APPEND ) },
      minLevel_{ minLevel }
  {
  }

  template < typename... Args >
  void inline log( LogLevel level, Args&&... args )
  {
    if( level < minLevel_ ) {
      return;
    }
    std::string color_code;
    std::string level_string = levelToString( level );

    using namespace std::chrono;
    using namespace std::chrono;
    auto now          = system_clock::now();
    std::time_t now_c = system_clock::to_time_t( now );
    auto ms =
      duration_cast< std::chrono::milliseconds >( now.time_since_epoch() ) %
      1000;
    std::stringstream ss;
    ss << std::put_time( std::localtime( &now_c ), "%d_%m_%Y_%H_%M_%S" );
    ss << "." << std::setfill( '0' ) << std::setw( 3 ) << ms.count();
    std::string timeString = ss.str();
    std::lock_guard< std::mutex > lock( mutex_ );
    switch( level ) {
      case LogLevel::Trace:
        fmt::print( fg( fmt::color::white ), "[{}] [{:^7}] ", timeString,
                    "TRACE" );
        fmt::print( fg( fmt::color::white ), std::forward< Args >( args )... );
        fmt::print( "\n" );
        break;
      case LogLevel::Info:
        fmt::print( fg( fmt::color::green ), "[{}] [{:^7}] ", timeString,
                    "INFO" );
        fmt::print( fg( fmt::color::green ), std::forward< Args >( args )... );
        fmt::print( "\n" );
        break;
      case LogLevel::Warning:
        fmt::print( fg( fmt::color::yellow ), "[{}] [{:^7}] ", timeString,
                    "WARNING" );
        fmt::print( fg( fmt::color::yellow ), std::forward< Args >( args )... );
        fmt::print( "\n" );
        break;
      case LogLevel::Error:
        fmt::print( fg( fmt::color::red ), "[{}] [{:^7}] ", timeString,
                    "ERROR" );
        fmt::print( fg( fmt::color::red ), std::forward< Args >( args )... );
        fmt::print( "\n" );
        break;
      default:
        break;
    }

    // Write message to log file
    output_.print( "[{}] [{:^7}] ", timeString, levelToString( level ) );
    output_.print( std::forward< Args >( args )... );
    output_.print( "\n" );
  }

  ~Logger() { output_.close(); }

private:
  std::mutex mutex_;
  fmt::ostream output_;
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
};
