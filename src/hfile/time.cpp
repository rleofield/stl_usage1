#include <iostream>
#include <sstream>
#include <chrono>


#include <mutex>


static std::mutex mutex;

#define HAS_STD_PUT_TIME 0

using std::string;

namespace rlf_time {

   const size_t bufsize = 80;

   std::string now( string format = "%H:%M:%S." ) {

      std::stringstream now;

      auto tp = std::chrono::system_clock::now();
      auto ms = std::chrono::duration_cast<std::chrono::milliseconds>( tp.time_since_epoch() );

      time_t seconds = std::chrono::duration_cast<std::chrono::seconds>( ms ).count();
#if HAS_STD_PUT_TIME
      now << std::put_time( std::localtime( &seconds ), "%T." );
#else

      char buffer[bufsize]; // holds "21:31:42"

      // localtime() is not threadsafe
      std::lock_guard<std::mutex> lock( mutex );
      struct tm* today = localtime( &seconds );

      if( strftime( buffer, bufsize, format.c_str(), today ) ) {
         now << buffer;
      }

#endif // HAS_STD_PUT_TIME
      return now.str();
   }

   std::string now_ms( string format = "%H:%M:%S." ) {

      std::stringstream now;

      auto tp = std::chrono::system_clock::now();
      auto ms = std::chrono::duration_cast<std::chrono::milliseconds>( tp.time_since_epoch() );
      size_t modulo = ms.count() % 1000;

      time_t seconds = std::chrono::duration_cast<std::chrono::seconds>( ms ).count();
#if HAS_STD_PUT_TIME
      now << std::put_time( std::localtime( &seconds ), "%T." );
#else
      char buffer[bufsize]; // holds "21:31:42"
      // localtime() is not threadsafe
      std::lock_guard<std::mutex> lock( mutex );
      struct tm* today = localtime( &seconds );

      if( strftime( buffer, bufsize, format.c_str(), today ) ) {
         now << buffer;
      }

#endif // HAS_STD_PUT_TIME

      // ms
      now.fill( '0' );
      now.width( 3 );
      now << modulo;
      string t = now.str();
      std::cout << t << std::endl;
      return t;
   }

}

// EOF
