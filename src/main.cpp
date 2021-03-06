#include <iostream>
#include <algorithm>
#include <map>
#include <list>
#include <string.h>
#include <boost/algorithm/string.hpp>

#include "filetreewalk.h"
#include "stringhelper.h"
#include "t_filename.h"
#include "fn_control.h"

using namespace std;
using namespace rlf_ftw;
using rlf_filefn::t_filename;
using namespace rlf_hfile::fn_control;
using rlf_ftw::tExcludeFolders;
using rlf_ftw::tIncludeFiles;


void sout( rlf_filefn::t_filename const& s ) {
   // hier kann man mit jedem File etwas machen
   cout << s.fullname() << endl;

}

void fnmapout( std::pair<string, rlf_filefn::t_filename> const& p ) {
   // hier kann man mit jedem File etwas machen
   cout << p.second.base()  << endl;

}
void fmapout( std::pair<string, string> const& p ) {
   // hier kann man mit jedem File etwas machen
   cout << p.second  << endl;
   int i = 0;

}
void foldererase_generate_commandline1( std::pair<string, string> const& p ) {
   string temp =  "del /S /F /Q " + p.second;
   cout << temp  << endl;
}
void foldererase_generate_commandline( std::pair<string, string> const& p ) {
   string temp =  "rmdir /S /Q " + p.second;
   cout << temp  << endl;
}

vector<int8_t>  test_assign_c_array() {
   vector<int8_t> test;
   char const* CArray = "abcdeef";
   test.assign( CArray, CArray + sizeof( CArray ) );
   test.assign( CArray, CArray + strlen( CArray ) );
   return test;
}
vector<int8_t>  test_assign_string() {
   string CppArray = "Cppabcdeef";
   vector<int8_t> test;
   test.assign( CppArray.begin(), CppArray.end() );
   return test;
}


struct C {
   C() {}
   C( const C& ) {
      std::cout << "A copy was made.\n";
   }
};

C f() {
   return C();
}



int main() {
   std::cout << "Hello World!\n";
   //C obj = f();

   vector<int8_t> test = test_assign_c_array();

   test = test_assign_string();

   list<char> testList( test.begin(), test.end() );

   testList.sort();

   sort( test.begin(), test.end() );

   string base = "./src/";


   // rlf_ftw::ftw ftw( alleFolder );
   string pattern = ".cpp";

   rlf_ftw::ftw ftw;

   tExcludeFolders ExcludeFolder;
   ExcludeFolder.contains = ".svn, .tmp, Debug, Release, html";
   tIncludeFiles inc;
   inc.last = ".cpp, .h";
   ftw.path( base );
   ftw.set_exclude_folders( ExcludeFolder );
   ftw.set_include_files( inc );
   ftw.scan_folders();
   //rlf_ftw::ftwReturn ret = ftw.ret;

   std::vector<t_filename> files = ftw.files(); //rlf_hfile::fn_control::files_in_subfolders( alleFolder, include, exclude );
   //std::vector<t_filename> folderfiles = rlf_hfile::fn_control::files_in_folder( alleFolder, include, exclude );
   std::vector<t_filename> folders = ftw.folders();// rlf_hfile::fn_control::subfolders( alleFolder );

   size_t c = folders.size(); //rlf_hfile::fn_control::get_folder_count(alleFolder);

   cout << endl;
   string e = " end ";
   for_each( files.begin(), files.end(),
   [&e]( rlf_filefn::t_filename const & s ) {
      cout << s.fullname() << e << endl;
   }
           );

   for( auto & fn : files ) {
      sout( fn );
   }

   //   for_each( list.begin(), list.end(), sout );

   cout << endl;
   cout << endl;


   random_shuffle( files.begin(), files.end() );

   for_each( files.begin(), files.end(), sout );
   cout << endl;
   cout << endl;
   cout << endl;

   map<string, rlf_filefn::t_filename> fnsorted;


   for( const rlf_filefn::t_filename & fn : files ) {
      string temp = fn.base();
      fnsorted[temp] =  fn;
   }

   for_each( fnsorted.begin(), fnsorted.end(), fnmapout );

   map<string, string> fsorted;
   std::vector<rlf_filefn::t_filename>::const_iterator fStart = folders.begin();
   std::vector<rlf_filefn::t_filename>::const_iterator fEnd = folders.end();

   while( fStart != fEnd ) {
      string temp = fStart->base();

      if( rlf_hstring::last_char( temp ) == '\\' ) {
         temp = rlf_hstring::remove_last( temp );
      }

      if( boost::ends_with( temp, pattern ) ) {
         fsorted[fStart->base()] =  fStart->base();
      }

      ++fStart;
   }


   // control out
   for_each( fsorted.begin(), fsorted.end(), fmapout );

   // generate del command for alle files in a folder
   for_each( fsorted.begin(), fsorted.end(), foldererase_generate_commandline );


   int i = 0;

}



