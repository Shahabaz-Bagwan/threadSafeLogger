#include <logger.hpp>

void Logger::log( LogLevel level, const std::string& message )
{
  std::lock_guard< std::mutex > lock( mutex_ );
  std::string color_code;
  std::string level_string = levelToString( level );
  if( level == LogLevel::Warning ) {
    color_code = "\033[33m"; // yellow
  } else if( level == LogLevel::Error ) {
    color_code = "\033[31m"; // red
  }
  std::time_t now =
    std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() );
  std::stringstream ss;
  ss << std::put_time( std::localtime( &now ), "%d_%m_%Y_%H_%M_%S" );
  std::string timestamp = ss.str();
  fmt::print( "[{}] [{}] {}{}\033[0m\n", timestamp, color_code,
              levelToString( level ), message );
  // fmt::print(log_stream_, "[{}] [{}] {}\n", timestamp, levelToString(level),
  // message);
}
