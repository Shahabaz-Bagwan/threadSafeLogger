// #include "fmt/compile.h"
// #include <chrono>
// #include <fmt/color.h>
// #include <logger.hpp>
//
// template < typename... Args >
// void Logger::log( LogLevel level,  Args&&... args )
// {
//   if( level < minLevel_ ) {
//     return;
//   }
//   std::string color_code;
//   std::string level_string = levelToString( level );
//
//   using namespace std::chrono;
//   using namespace std::chrono;
//   auto now          = system_clock::now();
//   std::time_t now_c = system_clock::to_time_t( now );
//   auto ms =
//     duration_cast< std::chrono::milliseconds >( now.time_since_epoch() ) % 1000;
//   std::stringstream ss;
//   ss << std::put_time( std::localtime( &now_c ), "%d_%m_%Y_%H_%M_%S" );
//   ss << "." << std::setfill( '0' ) << std::setw( 3 ) << ms.count();
//   std::string timeString = ss.str();
//   std::lock_guard< std::mutex > lock( mutex_ );
//   std::string message{};
//   switch( level ) {
//     case LogLevel::Trace:
//       message =
//         fmt::format( fg( fmt::color::white ), "[{}] [TRACE] ", timeString );
//       fmt::print( message );
//       fmt::print( std::forward< Args >( args )... );
//       fmt::print( "\n" );
//       break;
//     case LogLevel::Info:
//       message =
//         fmt::format( fg( fmt::color::green ), "[{}] [INFO] ", timeString );
//       fmt::print( message );
//       fmt::print( std::forward< Args >( args )... );
//       fmt::print( "\n" );
//       break;
//     case LogLevel::Warning:
//       message =
//         fmt::format( fg( fmt::color::yellow ), "[{}] [WARNING] ", timeString );
//       fmt::print( message );
//       fmt::print( std::forward< Args >( args )... );
//       fmt::print( "\n" );
//       break;
//     case LogLevel::Error:
//       message =
//         fmt::format( fg( fmt::color::red ), "[{}] [ERROR] ", timeString );
//       fmt::print( message );
//       fmt::print( std::forward< Args >( args )... );
//       fmt::print( "\n" );
//       break;
//     default:
//       break;
//   }
//
//   // Write message to log file
//   if( log_stream_ ) {
//     fmt::print( log_stream_, "[{}] [{}] {}\n", timeString,
//                 levelToString( level ),
//                  std::forward< Args >( args )...  ); // Print message to console
//   }
// }
