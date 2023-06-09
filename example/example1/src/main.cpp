#include <iostream>
#include <logger.hpp>
#include <sstream>
#include <string>
#include <thread>

static LogLevel stringToLevel( const std::string& levelStr )
{
  if( levelStr == "trace" ) {
    return LogLevel::Trace;
  } else if( levelStr == "info" ) {
    return LogLevel::Info;
  } else if( levelStr == "warning" ) {
    return LogLevel::Warning;
  } else if( levelStr == "error" ) {
    return LogLevel::Error;
  } else {
    return LogLevel::Info;
  }
}

void logWorker( Logger& logger )
{
  for( int i = 0; i < 5; i++ ) {
    logger.log( LogLevel::Trace, "{} {} {} {}", "Thread",
                ( std::ostringstream() << std::this_thread::get_id() ).str(),
                "Trace message", i );

    std::cout << "COUT Thread "
              << ( std::ostringstream() << std::this_thread::get_id() ).str()
              << " Trace message " << i << std::endl;

    logger.log( LogLevel::Info, "{} {} {} {}", "Thread",
                ( std::ostringstream() << std::this_thread::get_id() ).str(),
                "info message", i );

    std::cout << "COUT Thread "
              << ( std::ostringstream() << std::this_thread::get_id() ).str()
              << " info message " << i << std::endl;

    std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );

    std::cout << "COUT Thread "
              << ( std::ostringstream() << std::this_thread::get_id() ).str()
              << " warning message " << i << std::endl;

    logger.log( LogLevel::Warning, "{} {} {} {}", "Thread",
                ( std::ostringstream() << std::this_thread::get_id() ).str(),
                "warning message", i );

    std::cout << "COUT Thread "
              << ( std::ostringstream() << std::this_thread::get_id() ).str()
              << " error message " << i << std::endl;
    logger.log( LogLevel::Error, "{} {} {} {} {}", "Thread",
                ( std::ostringstream() << std::this_thread::get_id() ).str(),
                "error message", i, 3.14 );

    std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
  }
}

int main( int argc, char* argv[] )
{
  using namespace std;
  if( argc < 2 ) {
    std::cout << "Please provide input argument {trace, info, warning, error}"
              << std::endl;
    return 1;
  }
  Logger logger( "log.txt", stringToLevel( argv[ 1 ] ) );

  logger.log( LogLevel::Trace, "{} {} {}", "This is a trace message.", "hello",
              "hi" );
  logger.log( LogLevel::Info, "This is an info message." );
  std::thread t1( logWorker, std::ref( logger ) );
  logger.log( LogLevel::Warning, "This is a warning message." );
  logger.log( LogLevel::Error, "This is an error message." );

  std::thread t2( logWorker, std::ref( logger ) );
  t1.join();
  t2.join();
  return 0;
}
