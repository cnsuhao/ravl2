#include "Ravl/Image/GrabfileReaderV1.hh"
#include "Ravl/Image/GrabfileCommon.hh"

#include "Ravl/Assert.hh"
#include "Ravl/DArray1d.hh"
#include <arpa/inet.h>
#include <stdint.h>

namespace RavlImageN {
//==========================================================================//

GrabfileReaderV1::~GrabfileReaderV1()
{
  if(m_infile.is_open()) {
    m_infile.close();
  }
}

//--------------------------------------------------------------------------//

// Open file and read file header.
bool GrabfileReaderV1::Open(const char* const filename) //, CardModeC& mode)
{
  // Is the file alread open? It shouldn't be!
  if(m_infile.is_open()) {
    RavlIssueError("GrabfileReaderV1: Class already contains an open file.");
  }

  bool ok = true;
  // Is the file a grabfile?
  if(ok) {
    m_infile.open(filename, std::ios::binary | std::ios::in);
    ok = IsGrabfile(m_infile);
  }

  // Is the version correct, (this code will only deal with version 1,
  // hence the hardcode below.
  if(ok) {
    ok = (FileVersion(m_infile) == m_version_number);
  }
  // We can now read the header.
  if(ok) {
    int dummy_int = 0;

    // Video buffer size
    m_infile.read(reinterpret_cast<char*>(&dummy_int), 4);
    m_video_buffer_size = ntohl(dummy_int);
  
    // Audio buffer size
    m_infile.read(reinterpret_cast<char*>(&dummy_int), 4);
    m_audio_buffer_size = ntohl(dummy_int);

   //code to possible deal with time codes in the future.
  //  m_infile.read(reinterpret_cast<char*>(&dummy_int),4);
  //  m_number_of_frames = ntohl(dummy_int);

   // m_infile.read(reinterpret_cast<char*>(&dummy_int),8);
   // m_frame_rate = ntohl(dummy_int);

    UIntT id = m_infile.get();
    //m_mode.VideoMode(IdToVideoMode(id));
    videomode = IdToVideoMode(id);

    char id2 = m_infile.get();
    //m_mode.ByteFormat(IdToByteFormat(id));
    //id = (uint8_t)id2;
    byteformat = int(id2);  //IdToByteFormat(id);

    char id3 = m_infile.get();
    //m_mode.ColourMode(IdToColourMode(id));
    colourmode = int(id3);  //IdToColourMode(id);

    //mode.VideoMode(m_mode.VideoMode());
    //mode.ByteFormat(m_mode.ByteFormat());
    //mode.ColourMode(m_mode.ColourMode());

    ok = Ok();
  }

  if(!ok) {
    Close();
  }

  return ok;
}

//--------------------------------------------------------------------------//

// Close file.
void GrabfileReaderV1::Close()
{
  m_infile.close();
}

//--------------------------------------------------------------------------//

// Are there any problems with the IO?
bool GrabfileReaderV1::Ok() const
{
  return m_infile.good();
}

//--------------------------------------------------------------------------//

bool GrabfileReaderV1::HaveMoreFrames()
{
  m_infile.peek();
  return m_infile.eof();
}

//--------------------------------------------------------------------------//

// Read the next frame to a buffer.
bool GrabfileReaderV1::GetNextFrametest(BufferC<char> &bu, UIntT &vsize, UIntT &asize)   //(DVSBufferC &buffer)
{
 
  // Set the card mode.
  bool ok = HaveMoreFrames();
  if(!ok) {
 
 
   uint32_t dummy_int = 0;
  // Video buffer size
  m_infile.read(reinterpret_cast<char*>(&dummy_int), 4);
  vsize = ntohl(dummy_int);

  // Audio buffer size
  m_infile.read(reinterpret_cast<char*>(&dummy_int), 4);
  asize = ntohl(dummy_int);
  
    if(m_infile.good()) {
      int csize = m_video_buffer_size; 
      char * obuf = new char[csize];
      char * start = obuf;
      m_infile.read(obuf,csize);
      bu = BufferC<char> (csize,start,false,false);
   }
   ++m_frames_loaded;
  }
  return ok;
}


BufferC<char> GrabfileReaderV1::BufferWithAVSize() {
   if(m_infile.good()) {
      int csize = m_video_buffer_size + 8; 
      char * obuf = new char[csize];
      char * start = obuf;
      m_infile.read(obuf,csize);
      return BufferC<char> (csize,start,false,false);
   }
   else {
      //infile not good so return null.
      return BufferC<char>();
   }
}


BufferC<char> GrabfileReaderV1::GetNextFrame()
{
  uint32_t dummy_int = 0;
  // Video buffer size
  m_infile.read(reinterpret_cast<char*>(&dummy_int), 4);
  //const unsigned int video_buffer_size = ntohl(dummy_int);

  // Audio buffer size
  m_infile.read(reinterpret_cast<char*>(&dummy_int), 4);
  //const unsigned int audio_buffer_size = ntohl(dummy_int);
 
 
  bool ok = m_infile.good();
  if(ok) {
      if(IdToByteFormat(byteformat) == BITS_8) {
     
         SArray1dC<char> ret(m_video_buffer_size);
         for(SizeT z = 0;z<ret.Size();z++) {
	    ret[z] = m_infile.get();
         }
         ++m_frames_loaded;
         return BufferC<char> (ret.Size(),ret.DataStart(),false,false);
	 
         
      }
      if(IdToByteFormat(byteformat) == BITS_10_DVS) {
         //Convert to 8 Bits
         unsigned int osize = m_video_buffer_size * 3 / 4 ; // reduce 10bit to 8.
         char * obuf= new char[osize];
         char * start = obuf;
	 
	 DArray1dC<char> ret(osize);
	 SArray1dC<char> temp(m_video_buffer_size);
	 
	 for(int z=0;z<m_video_buffer_size;z++) {
	    temp[z] = m_infile.get();
	 }

	 const char * vbuf = temp.DataStart();
         for ( IntT vcount = 0 ; vcount < (m_video_buffer_size/4)  ; ++ vcount ) {
            *obuf++ = *vbuf++ ;
            *obuf++ = *vbuf++ ;
            *obuf++ = *vbuf++ ;
            vbuf ++ ;
	}
	++m_frames_loaded;
        return BufferC<char> (osize, start, false, false) ; // memory will not be freed when buffer is destroyed !!!!!. Image usually deletes buffer.
       
      }
  }
  //else {
     return BufferC<char>();
  //}
/*
  if(ok) {
    ++m_frames_loaded;
  }
  
  return ok;*/
}



} // End DVSN namespace
