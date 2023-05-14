#pragma once
#include <chrono>
#include <cstdio>
#include <ctime>
#include <fmt/chrono.h>
#include <fmt/color.h>
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
  Logger( std::string const& filename, LogLevel minLevel )
    : log_stream_{ std::fopen( filename.c_str(), "a" ) }, minLevel_{ minLevel }
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
    std::string message{};
    switch( level ) {
      case LogLevel::Trace:
        message =
          fmt::format( fg( fmt::color::white ), "[{}] [TRACE]\t", timeString );
        fmt::print( message );
        message = fmt::format( fg( fmt::color::white ),
                               std::forward< Args >( args )... );
        fmt::print( message );
        fmt::print( "\n" );
        break;
      case LogLevel::Info:
        message =
          fmt::format( fg( fmt::color::green ), "[{}] [INFO]\t", timeString );
        fmt::print( message );
        message = fmt::format( fg( fmt::color::green ),
                               std::forward< Args >( args )... );
        fmt::print( message );
        fmt::print( "\n" );
        break;
      case LogLevel::Warning:
        message = fmt::format( fg( fmt::color::yellow ), "[{}] [WARNING]\t",
                               timeString );
        fmt::print( message );
        message = fmt::format( fg( fmt::color::yellow ),
                               std::forward< Args >( args )... );
        fmt::print( message );
        fmt::print( "\n" );
        break;
      case LogLevel::Error:
        message =
          fmt::format( fg( fmt::color::red ), "[{}] [ERROR]\t", timeString );
        fmt::print( message );
        message =
          fmt::format( fg( fmt::color::red ), std::forward< Args >( args )... );
        fmt::print( message );
        fmt::print( "\n" );
        break;
      default:
        break;
    }

    // Write message to log file
    if( log_stream_ ) {
      message = fmt::format( "[{}] [{}]", timeString, levelToString( level ) );
      fmt::print( log_stream_, message );
      fmt::print( log_stream_, "\t" );
      message = fmt::format( std::forward< Args >( args )... );
      fmt::print( log_stream_, message );
      fmt::print( log_stream_, "\n" );
    }
  }

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
};
