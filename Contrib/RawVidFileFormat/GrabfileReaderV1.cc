#include "Ravl/Image/GrabfileReaderV1.hh"
#include "Ravl/Image/GrabfileCommon.hh"

#include "Ravl/Assert.hh"
#include "Ravl/DArray1d.hh"
#include <arpa/inet.h>
#include <stdint.h>

namespace RavlImageN {
//==========================================================================//

GrabfileReaderV1C::~GrabfileReaderV1C()
{
  if(m_infile.is_open()) {
    m_infile.close();
  }
}

//--------------------------------------------------------------------------//

// Open file and read file header.
bool GrabfileReaderV1C::Open(const char* const filename)
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

   // Set audio channel sizes.
    chansize = m_audio_buffer_size / 8;
    audioOffsets[0] = m_video_buffer_size;
    audioOffsets[1] = m_video_buffer_size+chansize;
    audioOffsets[2] = m_video_buffer_size+(2*chansize);
    audioOffsets[3] = m_video_buffer_size+(3*chansize);
    audioOffsets[4] = m_video_buffer_size+(4*chansize);
    audioOffsets[5] = m_video_buffer_size+(5*chansize);
    audioOffsets[6] = m_video_buffer_size+(6*chansize);
    audioOffsets[7] = m_video_buffer_size+(7*chansize);
    //Set video offsets.
    videoOffsets[0] = 0;

   //code to possible deal with time codes in the future.
    m_infile.read(reinterpret_cast<char*>(&dummy_int),4);
    m_frames_loaded = ntohl(dummy_int);
    m_infile.read(reinterpret_cast<char*>(&dummy_int),8);
    m_frame_rate = ntohl(dummy_int);
    UIntT id = m_infile.get();
    videomode = id;

    char id2 = m_infile.get();
    byteformat = int(id2);

    char id3 = m_infile.get();
    colourmode = int(id3);

    ok = Ok();
  }

  if(!ok) {
    Close();
  }

  return ok;
}

//--------------------------------------------------------------------------//

// Close file.
void GrabfileReaderV1C::Close()
{
  m_infile.close();
}

//--------------------------------------------------------------------------//

// Are there any problems with the IO?
bool GrabfileReaderV1C::Ok() const
{
  return m_infile.good();
}

//--------------------------------------------------------------------------//

bool GrabfileReaderV1C::HaveMoreFrames()
{
  m_infile.peek();
  return m_infile.eof();
}

//--------------------------------------------------------------------------//

// Read the next frame to a buffer.
bool GrabfileReaderV1C::GetNextFrame(BufferC<char> &bu, UIntT &vsize, UIntT &asize)   //(DVSBufferC &buffer)
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
      int csize = m_video_buffer_size + m_audio_buffer_size; 
      char * obuf = new char[csize];
      char * start = obuf;
      m_infile.read(bu.BufferAccess().DataStart(),csize);
      delete obuf;
   }
   ++m_frames_loaded;
   ++m_frame_number;
  }
  return ok;
}


BufferC<char> GrabfileReaderV1C::GetNextFrame()
{
  uint32_t dummy_int = 0;
  // Video buffer size
  m_infile.read(reinterpret_cast<char*>(&dummy_int), 4);

  // Audio buffer size
  m_infile.read(reinterpret_cast<char*>(&dummy_int), 4);
 
 
  bool ok = m_infile.good();
  if(ok) {
      if(IdToByteFormat(byteformat) == BITS_8) {
         
         BufferC<char> video(m_video_buffer_size);
         m_infile.read(video.BufferAccess().DataStart(),m_video_buffer_size);     
         ++m_frames_loaded;
	 ++m_frame_number;
         BufferC<char> audio(m_audio_buffer_size);
         m_infile.read(audio.BufferAccess().DataStart(),m_audio_buffer_size);
         return BufferC<char> (video.Size(),video.BufferAccess().DataStart(),true,true);
	 
         
      }
      if(IdToByteFormat(byteformat) == BITS_10_DVS) {
         //Convert to 8 Bits
         unsigned int osize = m_video_buffer_size * 3 / 4 ;
         char * obuf= new char[osize];
         char * start = obuf;
	 
         BufferC<char> temp(m_video_buffer_size);
         m_infile.read(temp.BufferAccess().DataStart(),m_video_buffer_size);
	 
         BufferC<char> audio(m_video_buffer_size);
         m_infile.read(audio.BufferAccess().DataStart(),m_audio_buffer_size);     

	 const char * vbuf = temp.BufferAccess().DataStart();
         for ( IntT vcount = 0 ; vcount < (m_video_buffer_size/4)  ; ++ vcount ) {
            *obuf++ = *vbuf++ ;
            *obuf++ = *vbuf++ ;
            *obuf++ = *vbuf++ ;
            vbuf ++ ;
	}
	++m_frames_loaded;
	++m_frame_number;
        return BufferC<char> (osize, start, true, true) ;
        delete obuf;
      }
  }
  
     return BufferC<char>();
  
}



} // End DVSN namespace
