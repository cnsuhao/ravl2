// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: test_imgdiff.cc 4777 2005-01-18 14:28:18Z ees1wc $"
//! lib=RavlImage
//! file="Ravl/Image/Base/grabtest_imgdiff.cc"
#include "Ravl/String.hh"
#include "Ravl/DP/Port.hh"
#include "Ravl/DP/Pipes.hh"
#include "Ravl/StrStream.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/IO.hh"
 #include <iostream>
 #include <cstdlib>

 using namespace std;
using namespace RavlN;
using namespace RavlImageN;

 int main(int argc, char* argv[])
 {
   FILE *fp;
   char line[7];
   fp = popen("hostname","r");
   fgets(line,8,fp);
   pclose(fp);
   StringC hostname(line);
   if(hostname == "cvphd01") {

      //Run router.
      StringC routerlist("");
      fp = popen("hdrouter -xps Embedder_1","r");
      while ( fgets( line, sizeof line, fp)) {
           StringC temp(line);
           cat(routerlist,temp,routerlist);
      }
      pclose(fp);

      //Send the colour bars to cvphd01.
      if(!system("hdrouter -cp -sp HD_test -dp Embedder_1")) {
         //Worked.
      }
      else {
         cerr << "Could not call hdrouter to route colour bars." << endl;
         return 0;
      }
      
      //Grab one yuv frame.
      if(!system("/opt/bin/grabber -f yuv -end +00:00:00:01 -o /video/testyuvgrabframe.grab")) {
         //Worked.
      }
      else {
         cerr << "Could not call grabber for yuv grab." << endl;
         return 0;
      }      

      //Grab one rgb frame.
      if(!system("/opt/bin/grabber -f rgb -end +00:00:00:01 -o /video/testrgbgrabframe.grab")) {
         //Worked.
      }
      else {
         cerr << "Could not call grabber for rgb grab." << endl;
         return 0;
      }

     //Route Original source back to destination.
     StringC temp("");
     cat("hdrouter -cp -sp ",routerlist,temp);
     cat(temp," -dp Embedder_1",temp);
     if(!system(temp)) {
        //Worked.
     }
     else {
        cerr << "Could not call hdrouter to re route original source." << endl;
        return 0;
     }

     //Extract Images from grab files.
     if(!system("extract -v -i /video/testyuvgrabframe.grab -o /video/testyuvgrabframe.ppm")) {
        //Worked.
     }
     else {
        cerr << "Could not call extract for yuv extract." << endl;
        return 0;
     }          

     if(!system("extract -v -i /video/testrgbgrabframe.grab -o /video/testrgbgrabframe.ppm")) {
        //Worked.
     }
     else {
        cerr << "Could not call extract for rgb extract." << endl;
        return 0;
     }

     // Assume we've passed!
     bool passed = true;

     //Compare Red,Green and Blue pixel values.
     ImageC<ByteRGBValueC> rgb1;
     Load("/video/testyuvgrabframe0.ppm",rgb1);
     ImageC<ByteRGBValueC> rgb2;
     Load("/video/testrgbgrabframe0.ppm",rgb2);
 
     //Red.
     Index2dC Red(775,273);
     ByteRGBValueC red1 = rgb1.operator[](Red);
     ByteRGBValueC red2 = rgb2.operator[](Red);          

     //Green.
     Index2dC Green(894,331);
     ByteRGBValueC green1 = rgb1.operator[](Green);
     ByteRGBValueC green2 = rgb2.operator[](Green);

     //Blue.
     Index2dC Blue(660,270);
     ByteRGBValueC blue1 = rgb1.operator[](Blue);
     ByteRGBValueC blue2 = rgb2.operator[](Blue);

     //Compare red.
     if(red1 == red2) {
     }
     else {
        passed = false;
     }

     //Compare green.
     if(green1 == green2) {
     }
     else {
        passed = false;
     }

     //Compare Blue.
     if(blue1 == blue2) {
     }
     else {
        passed = false;
     }

     //Remove grab files.
     system("rm /video/testyuvgrabframe.grab");
     system("rm /video/testyuvgrabframe.grab.log");
     system("rm /video/testrgbgrabframe.grab");
     system("rm /video/testrgbgrabframe.grab.log");

     //Remove extracted images.
     system("rm /video/testrgbgrabframe0.ppm");
     system("rm /video/testyuvgrabframe0.ppm");

     return passed?0:1;

   }
   else {
      return 0;
   }

 }
