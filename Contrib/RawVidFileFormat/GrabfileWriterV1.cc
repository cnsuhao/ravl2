#include "Ravl/Image/GrabfileWriterV1.hh"
#include "Ravl/Assert.hh"
#include "Ravl/StrStream.hh"
#include "Ravl/SArray1d.hh"
#include <arpa/inet.h>

namespace RavlImageN {
//==========================================================================//

GrabfileWriterV1C::~GrabfileWriterV1C()
{
  if(m_outfile.is_open()) {
    Close();
  }
}

//--------------------------------------------------------------------------//

// Open file and write file header.
bool GrabfileWriterV1C::Open(const char* const filename,
			  VideoModeT videomode, ByteFormatT byteformat, ColourModeT colourmode, IntT videobuffersize,IntT audiobuffersize)
{
  bool ok = true;
 
  // Reset the frame count.
  m_frames_written = 0;

  // Is the file already open? It shouldn't be!
  if(m_outfile.is_open()) {
    RavlIssueError("GrabfileWriterV1: Class already contains an open file.")
  }

  if(ok) {
    m_outfile.open(filename, std::ios::binary | std::ios::out);
    ok = Ok();
  }
  
  if(ok) {
    char file_id[4] = {'G', 'r', 'a', 'b'};
    m_outfile.write(file_id, 4);

    uint32_t header_version = m_version_number;
  
    header_version = htonl(header_version);
    m_outfile.write(reinterpret_cast<char*>(&header_version), 4);

    uint32_t dummy_int = 0;

    // Video buffer size
    dummy_int = htonl(videobuffersize);

    m_outfile.write(reinterpret_cast<char*>(&dummy_int), 4);
    m_video_buffer_size = videobuffersize;

    // Audio buffer size
    dummy_int = htonl(audiobuffersize);
    m_outfile.write(reinterpret_cast<char*>(&dummy_int), 4);
    m_audio_buffer_size = dummy_int;

   //TimeCode.
   IntT nf = 3;
   m_outfile.write(reinterpret_cast<char*>(&nf),4);
   dummy_int = htonl(frame_rate);
  
   m_outfile.write(reinterpret_cast<char*>(&dummy_int),8);
 
    const uint8_t mode_id = VideoModeToId(videomode);
    m_outfile.put(mode_id);

    const uint8_t byte_format_id = ByteFormatToId(byteformat);
    m_outfile.put(byte_format_id);
    m_byte_format = byte_format_id;

    const uint8_t colour_mode_id =  ColourModeToId(colourmode);
    m_outfile.put(colour_mode_id);

    ok = Ok();
  }

  return ok;
}


//--------------------------------------------------------------------------//

// Close file.
void GrabfileWriterV1C::Close()
{
   m_outfile.flush();
   m_outfile.seekp(nbrframes-4);
   uint32_t dummy_int = htonl(m_frames_written);
   m_outfile.write(reinterpret_cast<char*>(&dummy_int),4);
  m_outfile.close();
}

//--------------------------------------------------------------------------//
// Are there any problems with the IO?
bool GrabfileWriterV1C::Ok() const
{
  return m_outfile.good();
}

//--------------------------------------------------------------------------//

int GrabfileWriterV1C::VideoBuffer() {
   return m_video_buffer_size;
   }


void GrabfileWriterV1C::Reset(VideoModeT vmode,ByteFormatT bformat, IntT vbuf) {
   int currentpos = m_outfile.tellp();
   uint32_t dummy_int = 0;
   //Re write video buffer size.
   m_outfile.seekp(vbpos-4);
   dummy_int = htonl(vbuf);
   m_outfile.write(reinterpret_cast<char*>(&dummy_int), 4);
   m_video_buffer_size = vbuf;
   
   //Re write video mode.
   m_outfile.seekp(vmpos-1);
   const uint8_t mode_id = VideoModeToId(vmode); //modein.VideoMode());
   m_outfile.put(mode_id);
   
   //Re write Byte format.
   m_outfile.seekp(bfpos-1);
   const uint8_t byte_format_id = ByteFormatToId(bformat);  //modein.ByteFormat());
   m_outfile.put(byte_format_id);
   m_byte_format = byte_format_id;

   m_outfile.seekp(currentpos);
}

bool GrabfileWriterV1C::PutFrame(BufferC<char> &fr,UIntT &te) {
     // Write the frame data.
  if(m_outfile.good()) {
    uint32_t dummy_int = 0;

    // Video buffer size
    dummy_int = htonl(m_video_buffer_size);
    m_outfile.write(reinterpret_cast<char*>(&dummy_int), 4);

    // Audio buffer size
    dummy_int = htonl(m_audio_buffer_size);
    m_outfile.write(reinterpret_cast<char*>(&dummy_int), 4);

    m_outfile.write(fr.BufferAccess().DataStart(),fr.BufferAccess().Size());

    }
    ++m_frames_written;
    return true;

}

// Write frame.
bool GrabfileWriterV1C::PutFrame(SArray1dC<char> &ar)
{
  // Write the frame header.

  // Write the frame data.
  if(m_outfile.good()) {
    uint32_t dummy_int = 0;

    // Video buffer size
    dummy_int = htonl(m_video_buffer_size);
    m_outfile.write(reinterpret_cast<char*>(&dummy_int), 4);

    // Audio buffer size
    dummy_int = htonl(m_audio_buffer_size);
    m_outfile.write(reinterpret_cast<char*>(&dummy_int), 4);
    //If data is 10 bits.
    if(m_byte_format == 1) {

    const char * vbuf = ar.DataStart() ;
    unsigned int osize = m_video_buffer_size; //10bit frame size.
    char * obuf= new char[osize] ;
    char * start = obuf ;
    for ( IntT vcount = 0 ; vcount < (m_video_buffer_size / 4)  ; ++ vcount )
		{
      *obuf++ = *vbuf++ ;
      *obuf++ = *vbuf++ ;
      *obuf++ = *vbuf++ ;
      obuf ++ ;
		}
        m_outfile.write(start,osize);	


    }
    else {
       if((int)ar.Size() < m_video_buffer_size) {
          SArray1dC<char> temp(m_video_buffer_size - ar.Size());
          temp.Fill('0');
          ar.Append(temp);
      }
      m_outfile.write(ar.DataStart(),ar.Size());
      m_outfile.flush();
    }
  }
  
  ++m_frames_written;
  return true;
}



} // End DVSN namespace
