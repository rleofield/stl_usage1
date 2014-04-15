/* --------------------------------------------------------------------------
Copyright 2012 by Richard Albrecht
richard.albrecht@rleofield.de
www.rleofield.de

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
------------------------------------------------------------------------------
*/


//#include <vector>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/regex.hpp>

#include "filetreewalk.h"
#include "stringhelper.h"


using std::string;
using std::vector;
using namespace boost::filesystem;
using rlf_filefn::t_filename;
using rlf_hstring::split;

namespace rlf_ftw {
   namespace{
      bool path_exists_( boost::filesystem::path const& p ) {
         boost::filesystem::file_status s = status( p );
         if( boost::filesystem::is_directory( s ) ) {
            return true;
         }
         return false;
      }

      bool path_exists( string const& path ) {
         boost::filesystem::path p( path );
         return path_exists_( p );
      }
      bool is_folder( string const& path ) {
         boost::filesystem::path p( path );
         return boost::filesystem::is_directory( p );
      }
   }


   const string delimiters = ";, ";

   std::vector <t_filename > const& ftw::files()const {
      return _files;
   }
   std::vector <t_filename > const& ftw::dirs()const {
      return _dirs;
   }

   void ftw::path( std::string const& p ) {
      if( _path.path() != p ) {
         _path = p;
         _files.clear();
         _dirs.clear();
      }
   }
   void ftw::include_files( string const& i ) {
      _include_files = split( i, delimiters ) ;
   }
   void ftw::exclude_files( string const& i ) {
      _exclude_files = rlf_hstring::split( i, delimiters ) ;

   }
   void ftw::include_folders( string const& i ) {
      _include_folders = rlf_hstring::split( i, delimiters ) ;
   }
   void ftw::exclude_folders( string const& i ) {
      _exclude_folders = rlf_hstring::split( i, delimiters ) ;
   }

   bool ftw::filter_folder( boost::filesystem::path const& p ) {

      bool b = true;

      string n = p.string();

      for( auto s: _exclude_folders ) {
         if( s == "*" ) {  // excluded
            b = false;
            break;
         }
         if( s == "" ) {
            b = true;    // not excluded
            break;
         }

         if( boost::ends_with( n, s ) )
         {
            b = false; // excluded
            break;
         }
      }
      if( !b ) {
         return false;
      }
      b = false;

      for( auto s: _include_folders ) {
         if( s == "*" ) {// included
            b = true;
            break;
         }
         if( s == "" ) {  // included
            b = true;
            break;
         }

         if( boost::ends_with( n, s ) )
         {
            b = true; // included
            break;


          }

      }

      // b == true, wenn file verwendet wird
      return b;
   }

   bool ftw::filter_file( boost::filesystem::path const& p ) {

      bool b = true;

      string n = p.string();

      for( auto s: _exclude_files ) {
         if( s == "*" ) { // excluded
            b = false;
            break;
         }

         if( s == "" ) {
            b = true;// not excluded
            break;
         }
         if( boost::ends_with( n, s ) )
         {
            b = false; // excluded
            break;

         }
       }
      if( !b ) {
         return false;
      }

      // b == false, wenn file weggelassen wird
     b = false;
      for( auto s: _include_files ) {
         if( s == "*" ) { // included
            b = true;
            break;
         }
         if( s == "" ) { // included
            b = true;
            break;
         }


         if( boost::ends_with( n, s ) )
         {
            b = true; // included
            break;

         }

       }

      // b == true, wenn file verwendet wird
      return b;
   }



   void ftw::scan_folders() throw( bad_ftw ) {

      if( ! path_exists(_path.path()) ) {
         throw bad_ftw( "folder doesn't exist: " + _path.path() );
      }

      if( ! is_folder(_path.path() ) ) {
         throw bad_ftw( "input is not a folder: " + _path.path() );
      }

      //boost::regex pattern("*"); // list all files starting with a
      boost::filesystem::path  current_dir( _path.path() ); //

      for( recursive_directory_iterator iter( current_dir ), end;
           iter != end;
           ++iter ) {

         boost::filesystem::path p = iter->path();

         if( boost::filesystem::is_directory( p ) ) {
            std::string dname = p.string();
            bool b = filter_folder( p );

            if( b ) {
               t_filename fn;
               fn.path( dname );
               _dirs.push_back( fn );
            }
         }

         if( boost::filesystem::is_regular_file( p ) ) {
            std::string name = p.string();
            bool b = filter_file( p );

            if( b ) {
               t_filename fn( name );
               _files.push_back( fn );
            }
         }

         //    if (regex_match(name, pattern))
         //      std::cout << iter->path() << "\n";
      }
   }


   void ftw::scan_folder() throw( bad_ftw ) {
      if( ! path_exists(_path.path())  ) {
         throw bad_ftw( "folder doesn't exist: " + _path.path() );
      }

      if( ! is_folder(_path.path()) ) {
         throw bad_ftw( "input is not a folder: " + _path.path() );
      }

      //boost::regex pattern("*"); // list all files starting with a
      boost::filesystem::path  current_dir( _path.path() ); //

      for( directory_iterator iter( current_dir ), end;
           iter != end;
           ++iter ) {
         boost::filesystem::path p = iter->path();

         if( boost::filesystem::is_directory( p ) ) {
            std::string dname = p.string();
            bool b = filter_folder( p );

            if( b ) {
               t_filename fn;
               fn.path( dname );
               _dirs.push_back( fn );
            }
         }

         if( boost::filesystem::is_regular_file( p ) ) {
            std::string name = p.string();
            bool b = filter_file( p );

            if( b ) {
               t_filename fn( name );
               _files.push_back( fn );
            }
         }

         //    if (regex_match(name, pattern))
         //      std::cout << iter->path() << "\n";
      }
   }




}














// EOF


