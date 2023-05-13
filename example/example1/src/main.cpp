#include <iostream>
#include <logger.hpp>

int main( int argc, char* argv[] )
{
  using namespace std;
  // if( argc < 2 ) {
  //   std::cout << "Please provide input argument" << std::endl;
  //   return 1;
  // }
  Logger logger;
  logger.log( LogLevel::Trace, "This is a trace message." );
  logger.log( LogLevel::Info, "This is an info message." );
  logger.log( LogLevel::Warning, "This is a warning message." );
  logger.log( LogLevel::Error, "This is an error message." );

  return 0;
}
