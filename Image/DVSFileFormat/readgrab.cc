// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////
//! rcsid="$Id: readgrab.cc 5240 2005-12-06 17:16:50Z sennis $"
//! lib=DVSFileFormat
//! file="DVSFileFormat/readgrab.cc"
//! example=readgrab.cc
//! docentry="DVSFileFormat.readgrab.cc"
//! userlevel=Normal
//! author="Simon Ennis"
//! date="21/05/2007"

//: Loading and saving image sequences

#include "Ravl/Option.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ImgIO.hh"
#include "Ravl/Image/ByteYUV422Value.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/IO.hh"
#include "Ravl/Image/ImageConv.hh"
#include "Ravl/DP/Port.hh"
///////////////////////////////////////////////////
//#include "Ravl/DVS/Buffer.hh"
#include "Ravl/Image/CardMode.hh"
#include "Ravl/Image/Types.hh"
#include   "Ravl/Image/Deinterlace.hh"
#include "Ravl/Image/NewGrabfileReader.hh"
#include "Ravl/Image/NewGrabfileWriter.hh"
#include <iostream>
#include <fstream>
#include <arpa/inet.h>


//#include "Ravl/DVS/LowLevelCard.hh" // only needed for PrintBits and debugging !!

#include "Ravl/BinStream.hh"
#include   "Ravl/Exception.hh"

//#include "Ravl/DVS/GrabfileReaderV1.hh"
//#include "Ravl/DVS/LegacyGrabfileReader.hh"
//#include "Ravl/DVS/NewGrabfileReader.hh"
/////////////////////////////////////////////////////
using namespace RavlN;
using namespace RavlImageN;
using namespace DVSN;

int main(int argc,char **argv) 
{  
  // Process options.
  
  OptionC option(argc,argv);
  StringC ifmt = option.String("if","","Input format. ");
  StringC ifilename = option.String("i","","Input stream.");
  StringC ofilename = option.String("o","@X","Output stream.");
  //StringC gfilename = option.String("g","","grab file.");
  option.Check();
  /*
  DPIPortC<ImageC<ByteRGBValueC> > inputStream;
  DPOPortC<ImageC<ByteRGBValueC> > outputStream;
  ImageC<ByteRGBValueC> image;
  ImageC<ByteRGBValueC> image2;
  */
  DPIPortC<ImageC<ByteYUV422ValueC> > inputStream;
  DPOPortC<ImageC<ByteYUV422ValueC> > outputStream;
  ImageC<ByteYUV422ValueC> image;
  ImageC<ByteYUV422ValueC> image2;
  


////////////////////////////////////////////////////////////
/*
    std::ifstream infile1,infile2;

    infile1.open(ifilename, std::ios::binary | std::ios::in);

    infile2.open(ofilename, std::ios::binary | std::ios::in);
    char in1[1];
    char in2[1];
    int t = 0;
    char read41[4];
    char read42[4];
    infile1.read(read41,4);
    infile2.read(read42,4);
    if(read41[0] != read42[0]) {
       cout << "error 1st 4" << endl;
    }
    infile1.read(read41,4);
    infile2.read(read42,4);
    if(read41[0] != read42[0]) {
        cout << "error 2nd 4" << endl;
    }
    
    uint8_t id1 = infile1.get();
    uint8_t id2 = infile2.get();
    if(id1 != id2) {
       cout << "1st id error." << endl;
    }

    id1 = infile1.get();
    id2 = infile2.get();
    if(id1 != id2) {
       cout << "2nd id error." << endl;
    }

    id1 = infile1.get();
    id2 = infile2.get();
    if(id1 != id2) {
       cout << "3rd id error." << endl;
    }

    infile1.read(read41,4);
    infile2.read(read42,4);
    if(read41[0] != read42[0]) {
       cout << "error in 2nd to last 4 read." << endl;
    }
    cout << "video buffer size 1 is " << read41 << endl;
    cout << "video buffer size 2 is " << read42 << endl;

    infile1.read(read41,4);
    infile2.read(read42,4);
    if(read41[0] != read42[0]) {
       cout << "error in last 4 read." << endl;
    }
    int firstindex = 0;
    int errortotal = 0;
    while(!infile1.eof()) {
       infile1.read(in1,1);
       infile2.read(in2,1);
       if(in1[0] != in2[0]) {
          //cout << "char " << t << " is not equal." << endl;
	  errortotal ++;
	  if(firstindex == 0) {
             firstindex = t;
	  }
       }
       t++;
   }

   cout << "first index is " << firstindex << endl;
   cout << "total t is " << t << endl;
   cout << "total - error total is " << t - errortotal << endl;
   cout << "error total is " << errortotal << endl;
*/

///////////////////////////////////////////////////
//test grabfilereader.

//  GrabfileReader* file_reader_pointer = 0;

  //if(legacy_reader) {
    //file_reader_pointer = new LegacyGrabfileReader();
  //} else {
//    file_reader_pointer = new GrabfileReaderV1();
  //}

  // Configure the card mode correctly depending on the hardware.
  //CardModeC mode;
  //GrabfileReader& file_reader = new GrabfileReaderV1();   //= *file_reader_pointer;

  //file_reader.Open(gfilename, mode);
  //cout << "file_reader was successful" << endl;


//////////////////////////////////////////////////////////////
//Test grab file reader.
/*
    //char z;
    //cout << "char size is " << sizeof(z) << endl;
    cout << "ByteT size is " << sizeof(ByteT) << endl;
    GrabfileReader* file_reader_pointer;
    //GrabfileReader& file_read;
    CardModeC mode;
    file_reader_pointer = NewGrabfileReader(ifilename, false);
    if(file_reader_pointer->Open(ifilename, mode)) {
      cout << "Grabfile successfully opened." << endl;      
    }
    GrabfileReader& file_read = *file_reader_pointer;  
    //BufferC<char> res;
    //char res[400950];
    //char res[1245184];
      DArray1dC<char> res(831488);
    //DVSBufferC buf(1245184,0);
    cout << "About to read next frame." << endl;
    //if(file_read.GetNextFrame(buf)) {
    if(file_read.GetNextFrame(res)) {
       //do nothing.
    }
    else {
       //oops no frames left.
       return false;
    }
    cout << "After reading frame." << endl;
    //for(Array2dIterC<char> it(res);it;it++) {
       //cout << "size of char in res is " << sizeof(res.BufferAccess()[0]) << endl;

    //}
        UIntT xDim=0, yDim=0 ;
    //if(!GetDimensions(mode.VideoMode(),xDim,yDim)) {
        //Unsuccessfully got dimensions.
  	//xDim = 576 ; 
	//yDim = 720;
	xDim = 1080;
	yDim = 1920;
	//RavlIssueWarning("\nDont know which image size to use for this format ! will try 1080x1920"); 
    //}
   // BufferC<char> result(1245184,res,true);
    char re[res.Size()];
    for(SizeT q=0;q<res.Size();q++) {
       re[q] = res[q];
    }
    BufferC<char> result(res.Size(),re);
    //result = res.Buffer();
    cout << "BufferC result size is " << result.Size() << endl;
    //ImageC<ByteRGBValueC> image1(xDim,yDim);
    //for(int t=0;t<result.Size();t++) {
    //   ByteRGBValueC by = (ByteRGBValueC) result.BufferAccess()[t];
    //   image1[t] = by;
   // }
    int j = 0;
    int loopnum = 0;
    //ImageC<ByteRGBValueC> ret(576,720); 
    //Array2dC<ByteRGBValueC> a2d(297,450);
   // for(Array2dIterC<ByteRGBValueC> it(ret);it;it++) {
   //    it.Data() = ByteRGBValueC((ByteT)res[j],(ByteT)res[j+1],(ByteT)res[j+2]);
       //ByteRGBValueC brgb(result[i],result[i+1],result[i+2]);
   //    j+=3;
   //    loopnum ++;
  // }
    cout << "loopnum is " << loopnum << endl;
    cout << "result index is " << j << endl; 
    cout << "1245184/3 is " << 1245184/3 << endl;
    //cout << "bufferc size is " << buf.BufferAccess().Size() << endl;
    ImageC<ByteYUV422ValueC> image1( xDim, yDim, (ByteYUV422ValueC*) & result.BufferAccess()[0], true); // image is only valid while buffer exists !
    //ImageC<ByteRGBValueC> head;
    //image = Interlace( ret );
    //ImageC<ByteRGBValueC> convert = ByteDVSYUV422ImageCT2ByteDVSRGBImageCT(image1);
    image = Interlace(image1);
    //image = image1;
    cout << "image1 size is " << image1.Size() << endl;
    cout << "image size is " << image.Size() << endl;
    //cout << "saving grabf ile to " << ofilename << endl;
    //FILE * output = fopen(ofilename,"w");
    //buf.Save(output);
    //for(Array2dIterC<ByteRGBValueC> it(image1);it;it++) {
       //cout << it.Data().Red() << " " << it.Data().Green() << " " << it.Data().Blue() << " " << endl; 
 
    //}
     if(!Save(ofilename,convert,"jpeg",true)) {
       cout << "Failed to save to file '" << ofilename << endl;
       return 1;
     }
    //Image is correct at this point.
    
     //result.~BufferC();
     //res[0];
     //result = NULL;
 //    cout << "readgrab finished." << endl;

*/

/*

 std::ifstream m_infile;
 m_infile.open(ifilename, std::ios::binary | std::ios::in);
 char res[1310804];
 cout << "about to read" << endl;
 m_infile.read(res,1310804);
 cout << "after read" << endl;
 m_infile.close();

*/
/*
    CardModeC modesave;
    modesave.ColourMode(RGB_RGB);
    modesave.ByteFormat(BITS_8);
    modesave.VideoMode(PAL);

    GrabfileWriter* file_writer_pointer = 0;
    file_writer_pointer = NewGrabfileWriter(1);
    file_writer_pointer->Open(ofilename, modesave,1245184,0);
    GrabfileWriter& file_writer = *file_writer_pointer;
    int i = 0;
    SArray1dC<char> chararray(1245184);
    for(Array2dIterC<ByteRGBValueC> it(image);it;it++)  {
       ByteRGBValueC rgc = it.Data();
       //cout << "sizeof(rgc.Red()) " << sizeof(rgc.Red()) << endl;
       //m_outfile.write(reinterpret_cast<char*>(&rgc.Red()),sizeof(rgc.Red()));
      // m_outfile.write(reinterpret_cast<char*>(&rgc.Green()),sizeof(rgc.Green()));
      // m_outfile.write(reinterpret_cast<char*>(&rgc.Blue()),sizeof(rgc.Blue()));
       chararray[i] = (char)(rgc.Red());  //reinterpret_cast<unsigned char>(rgc.Red());
       chararray[i+1] = (char)(rgc.Green());
       chararray[i+2] = (char)(rgc.Blue());
       //strostm << Imgcopy;   //reinterpret_cast<char*>(&Imgcopy);
       //it.Data() = reinterpret_cast<char>(imgarray);
       i+=3;
   }
   //for(int y=0;y<1245184;y++) {
   //   chararray[y] = res[y];
   //}


    file_writer.PutFrame(chararray);
    file_writer.Close();
    cout << "file written" << endl;
*/
/////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

/*
   cout << "head size is " << image.Size() << endl;
   cout << "Loading image" << endl;
//   ByteRGBValueC rgbc(0,0,0);
//   image.Fill(rgbc);
    //Test generic load and save mechamism.
  if(!Load(ifilename,image)) {
    cerr << "Failed to load file '" << ifilename << "' \n";
    return 1;
  }
  cout << "saving image" << endl;
  */
/*
 std::ofstream m_outfile;
  int m_video_buffer_size;
  //: The video buffer size in bytes.

  int m_audio_buffer_size;
  //: The audio buffer size in bytes.

  //if(ok) {
    m_outfile.open(ofilename, std::ios::binary | std::ios::out);
    //ok = Ok();
  //}
  
  //if(ok) {
    char file_id[4] = {'G', 'r', 'a', 'b'};
    m_outfile.write(file_id, 4);

    uint32_t header_version = 1;
    header_version = htonl(header_version);
    m_outfile.write(reinterpret_cast<char*>(&header_version), 4);

    uint32_t dummy_int = 0;

    // Video buffer size
    //dummy_int = htonl(card.InputFifo().VideoBufferSize());
    dummy_int = htonl(1244160);  //400950;  //1449790;
    //cout << "videobuffersize is " << dummy_int << endl;
    m_outfile.write(reinterpret_cast<char*>(&dummy_int), 4);
    m_video_buffer_size = 1244160;
    //cout << "m_video_buffer_size is " << m_video_buffer_size;

    // Audio buffer size
    //dummy_int = htonl(card.InputFifo().AudioBufferSize());
    dummy_int = htonl(0);
    m_outfile.write(reinterpret_cast<char*>(&dummy_int), 4);
    m_audio_buffer_size = 0;

   //timecode
   TimeCodeC tc(00,00,00,01);
   cout << "Time code in readgrab is " << tc.ToText() << endl;
   //m_outfile.write(tc.ToText().chars(),4);


   // CardModeC mode;
   // mode.ColourMode(RGB_RGB);
   // mode.ByteFormat(BITS_8);
   // mode.VideoMode(PAL);

    const uint8_t mode_id = VideoModeToId(mode.VideoMode());
    m_outfile.put(mode_id);

    const uint8_t byte_format_id = ByteFormatToId(mode.ByteFormat());
    m_outfile.put(byte_format_id);

    const uint8_t colour_mode_id =  ColourModeToId(mode.ColourMode());
    m_outfile.put(colour_mode_id);


   
    SArray1dC<char> chararray(image.Size() * 3);
    //SArray1dC<char> chararray(1245184);
    //cout << "Imgcopy size is " << image.Size() << endl;
    int i = 0;

    // Video buffer size
   dummy_int = htonl(m_video_buffer_size);
    m_outfile.write(reinterpret_cast<char*>(&dummy_int), 4);

    // Audio buffer size
    dummy_int = htonl(m_audio_buffer_size);
    m_outfile.write(reinterpret_cast<char*>(&dummy_int), 4);
    //cout << "sizeof(ByteT) " << sizeof(ByteT) << endl;
    ImageC<ByteRGBValueC> dimage;
    dimage = DeInterlace(image);
    for(Array2dIterC<ByteRGBValueC> it(dimage);it;it++)  {
       ByteRGBValueC rgc = it.Data();
       //cout << "sizeof(rgc.Red()) " << sizeof(rgc.Red()) << endl;
       m_outfile.write(reinterpret_cast<char*>(&rgc.Red()),sizeof(rgc.Red()));
       m_outfile.write(reinterpret_cast<char*>(&rgc.Green()),sizeof(rgc.Green()));
       m_outfile.write(reinterpret_cast<char*>(&rgc.Blue()),sizeof(rgc.Blue()));
     //  chararray[i] = (rgc.Red());  //reinterpret_cast<unsigned char>(rgc.Red());
     //  chararray[i+1] = (rgc.Green());
     //  chararray[i+2] = (rgc.Blue());
       //strostm << Imgcopy;   //reinterpret_cast<char*>(&Imgcopy);
       //it.Data() = reinterpret_cast<char>(imgarray);
       i++;
   } 
   //TimeCodeC tc(00,00,00,01);
   //m_outfile.write(tc.ToText().chars(),8);
  // for(int e=0;e<1245184;e++) {
  //    m_outfile.write(reinterpret_cast<char*>(&res[e]),1);
   //   m_outfile.put(res[e]);
 //  }
   //m_outfile.write(reinterpret_cast<char*>(&dummy_int), 4);
   //m_outfile.write(reinterpret_cast<char*>(&dummy_int), 4);

 //   StrOStreamC strostm;
 //   strostm << image;
 //   m_outfile.write(strostm.String().chars(),strostm.String().Size());
    cout << "i is " << i << endl;
    cout << "i * 3 is " << i*3 << endl;
    cout << "image rows is " << image.Rows() << endl;
    cout << "image cols is " << image.Cols() << endl;
    // StrOStreamC strostm;
    //strostm << reinterpret_cast<char*>(&image);
    //UIntT size = strostm.Size();
    //bufc = DVSBufferC(size,0);
    //cout << "strostrm size is " << size << endl;
    //StrIStreamC stristrm(strostm.String());
    //IStreamC isc(stristrm.is());
    //m_outfile.write(reinterpret_cast<char*>(&image),image.Size());
   // CardModeC modesave;
   // modesave.ColourMode(RGB_RGB);
   // modesave.ByteFormat(BITS_8);
   // modesave.VideoMode(PAL);

   // GrabfileWriter* file_writer_pointer = 0;
   // file_writer_pointer = NewGrabfileWriter(1);
   // file_writer_pointer->Open(ofilename, modesave,chararray.Size(),0);
   // GrabfileWriter& file_writer = *file_writer_pointer;

  //  file_writer.PutFrame(chararray);
    TimeCodeC tc2(00,00,00,02);
    //m_outfile.write(tc2.ToText().chars(),4);
    m_outfile.close();

    cout << "after m_outfile.close()" << endl;
*/

  //ImageC<ByteRGBValueC> convert = ByteDVSYUV422ImageCT2ByteDVSRGBImageCT(image);
/*  cout << "The image size b4 writing to grab file is " << endl;
  if(!Save(ofilename,image)) {
    cerr << "Failed to save to file '" << ofilename << "' \n";
    return 1;
  }
  */
//////////////////////////////////////////////////////////////////////////////
/*  CardModeC mode;
  GrabfileReader* file_reader_pointer = 0;

  file_reader_pointer = NewGrabfileReader(ifilename, false);

  if(!file_reader_pointer) {
    cerr<<"Unable to find suitable file reader for "<<ifilename<<endl;
    cerr<<"File version: "<<GrabfileReader::FileVersion(ifilename)<<endl;
    return 1;
  }

  GrabfileReader& file_reader = *file_reader_pointer;

  file_reader.Open(ifilename, mode);

  cout << "ColourMode b4 getnextframe is " << mode.ColourMode() << endl;

  DVSBufferC buf;
  file_reader.GetNextFrame(buf);
  cout << "ColourMode after getnextframe is " << buf.ColourMode() << endl;
*/
///////////////////////////////////////////////////////////////////////////////

    //Test DPIO stream for a sequence of images.
    if(!OpenISequence(inputStream,ifilename)) {
      // Failed to open input file.
      // Report an error...
      cout << "failed to open in put stream" << endl;
      return 1;
    }

    if(!OpenOSequence(outputStream,ofilename)) {
      // Failed to open output file.
      // Report an error..
      cout << "failed to open out put stream" << endl;
      return 1;
    }
    //cout << "new compiled readgrab" << endl;
    //image2 = inputStream.Get();
    //cout << "inputStream.IsGetEOS() is " << inputStream.IsGetEOS() << endl;
    //for(;inputStream.IsGetEOS();) { // Get next image, stop if none.
    int num = 0;
    //while(!inputStream.IsGetEOS()) {
    //cout << "About to load image." << endl;
    while(inputStream.Get(image)) { // Get next image, stop if none.
      try {
          //cout << "inputstream.IsGetEOS value is " << inputStream.IsGetEOS() << endl;
          //cout << "getting image" << endl;
	  //cout << "IsGetReady() is " << inputStream.IsGetReady() << endl;
         //image = inputStream.Get();
         //cout << "converting image" << endl;
         //ImageC<ByteRGBValueC> conv = ByteDVSYUV422ImageCT2ByteDVSRGBImageCT(image);
         //cout << "saving image sized " << image.Size() << endl;
	 /*StringC sa("/video/ees1se/hippo/image" + (StringC)num + ".jpg");
	//StringC sa("/home/cvsspraid/cvsspraid1/cvsspst/ees1se/readgrabsavimage.jpg");
	 //ImageC<ByteRGBValueC> dimage;
	 //dimage = DeInterlace(image);
	 if(!Save(sa,image,"jpeg",true)) {
           cout << "error saving image" << endl;
	 }*/
         outputStream.Put(image);
      }
      catch(RavlN::DataNotReadyC) {
         break;
      }
      //cout << "num is " << num << endl;
      num++;
    }
   
   
  return 0;
};
