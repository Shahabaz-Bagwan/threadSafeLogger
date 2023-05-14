#include "fmt/compile.h"
#include <chrono>
#include <fmt/color.h>
#include <logger.hpp>

void Logger::log( LogLevel level, const std::string& message )
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
    duration_cast< std::chrono::milliseconds >( now.time_since_epoch() ) % 1000;
  std::stringstream ss;
  ss << std::put_time( std::localtime( &now_c ), "%d_%m_%Y_%H_%M_%S" );
  ss << "." << std::setfill( '0' ) << std::setw( 3 ) << ms.count();
  std::string timeString = ss.str();
  std::lock_guard< std::mutex > lock( mutex_ );
  switch( level ) {
    case LogLevel::Trace:
      fmt::print( fg( fmt::color::white ), "[{}] [TRACE] {}\n", timeString,
                  message );
      break;
    case LogLevel::Info:
      fmt::print( fg( fmt::color::green ), "[{}] [INFO] {}\n", timeString,
                  message );
      break;
    case LogLevel::Warning:
      fmt::print( fg( fmt::color::yellow ), "[{}] [WARNING] {}\n", timeString,
                  message );
      break;
    case LogLevel::Error:
      fmt::print( fg( fmt::color::red ), "[{}] [ERROR] {}\n", timeString,
                  message );
      break;
    default:
      break;
  }

  // Write message to log file
  if( log_stream_ ) {
    fmt::print( log_stream_, "[{}] [{}] {}\n", timeString,
                levelToString( level ),
                message ); // Print message to console
  }
}
