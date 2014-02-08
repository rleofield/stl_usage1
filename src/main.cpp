#include <iostream>
#include <algorithm>
#include <map>
#include <list>
#include <string.h>
#include <boost/algorithm/string.hpp>

#include "filetreewalk.h"
#include "stringhelper.h"
#include "t_filename.h"
#include "t_fncontrol.h"

using namespace std;
using namespace rlf_ftw;

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


int main() {

   vector<char> test;
   char const* CArray = "abcdeef";
   test.assign( CArray, CArray + sizeof( CArray ) );
   test.assign( CArray, CArray + strlen( CArray ) );

   string CppArray = "Cppabcdeef";
   test.assign( CppArray.begin(), CppArray.end() );

   list<char> testList( test.begin(), test.end() );

   testList.sort();

   sort( test.begin(), test.end() );

   string alleFolder = "/home/richard/wrk/snippets2";
   rlf_hfile::tFnFunctions t;

   rlf_ftw::ftw ftw( alleFolder );
   string pattern = ".svn; *";

   std::vector<rlf_filefn::t_filename> list = t.files_in_subfolders( alleFolder, "*", pattern );
   std::vector<rlf_filefn::t_filename> list1 = t.files_in_folder( alleFolder, "*", pattern );
   std::vector<rlf_filefn::t_filename> folders = t.subfolders( alleFolder );


   cout << endl;

   //   for_each( list.begin(), list.end(),
   //             []( rlf_filefn::t_filename const& s ){ cout << s.fullname() << endl; });
for( const rlf_filefn::t_filename & fn: list ) {
      //cout << fn.fullname() << endl;
   }

   //   for_each( list.begin(), list.end(), sout );

   cout << endl;
   cout << endl;


   random_shuffle( list.begin(), list.end() );

   for_each( list.begin(), list.end(), sout );
   cout << endl;
   cout << endl;
   cout << endl;

   map<string, rlf_filefn::t_filename> fnsorted;

   std::vector<rlf_filefn::t_filename>::const_iterator fnStart = list.begin();
   std::vector<rlf_filefn::t_filename>::const_iterator fnEnd = list.end();

for( const rlf_filefn::t_filename & fn: list ) {
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



