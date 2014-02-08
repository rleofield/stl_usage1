

#ifndef rlf_tFnFunctions_H
#define rlf_tFnFunctions_H

#include <string>
#include <string.h>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <vector>


#include "filehelper.h"
#include "t_filename.h"

using std::string;

namespace rlf_hfile {



   class NonCopyable {
      NonCopyable( const NonCopyable& );
      const NonCopyable&  operator= ( const NonCopyable& );
   protected:
      NonCopyable( ) { }
      virtual ~NonCopyable( ) { }
   };



   class tFnFunctions: public NonCopyable {

      bool operator==( const tFnFunctions& s )const;

   public:
      tFnFunctions() {}
      ~tFnFunctions() {}


      string const& Argv( uint32_t pos )const;
      void SetArgv( char* iargv[] );

      std::string working_folder()const;
      bool change_folder( std::string const& newPath )const;

      bool create_folder( std::string const& path )const;
      bool create_folders( std::string const& path )const;
      bool delete_recursive( std::string const& path )const;


      std::vector<rlf_filefn::t_filename> files_in_folder( std::string const& path, string const& include = "", string const& exclude = "" ) const;
      std::vector<rlf_filefn::t_filename> files_in_subfolders( std::string const& path, string const& include = "", string const& exclude = "" )const;
      std::vector<rlf_filefn::t_filename> subfolders( std::string const& path,  string const& include = "", string const& exclude = "" )const;

      bool isAbsolutePath( std::string const& path )const;

      std::string correct_slash_at_end( std::string const& path );
      std::string basename( std::string const& file );
      std::string extension( std::string const& file );


      bool file_exists( string const& fn ) ;
      bool path_exists( string const& path ) ;

      boost::uintmax_t file_size( std::string const& file ) ;


   };



} // end of namespace






#endif

//EOF

