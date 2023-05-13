#include <chrono>
#include <logger.hpp>

void Logger::log( LogLevel level, const std::string& message )
{
  if( level < minLevel_ ) {
    return;
  }
  std::lock_guard< std::mutex > lock( mutex_ );
  std::string color_code;
  std::string level_string = levelToString( level );
  if( level == LogLevel::Warning ) {
    color_code = "\033[33m"; // yellow
  } else if( level == LogLevel::Error ) {
    color_code = "\033[31m"; // red
  }
  using namespace std::chrono;
  auto now          = system_clock::now();
  std::time_t now_c = system_clock::to_time_t( now );
  auto ms =
    duration_cast< std::chrono::milliseconds >( now.time_since_epoch() ) % 1000;
  std::stringstream ss;
  ss << std::put_time( std::localtime( &now_c ), "%d_%m_%Y_%H_%M_%S" );
  ss << "." << std::setfill( '0' ) << std::setw( 3 ) << ms.count();
  std::string timestamp = ss.str();
  fmt::print( "[{}] {} [ {} ] {}\033[0m\n", timestamp, color_code,
              levelToString( level ), message );
  fmt::print( log_stream_, "[{}] [{}] {}\n", timestamp, levelToString( level ),
              message );
}
