#if !defined(LEGACYGRABFILEREADER_HH)
#define LEGACYGRABFILEREADER_HH
//! rcsid="$Id: $"
//! author="Simon Tredwell"
//! lib=RawVid

#include "Ravl/Image/GrabfileReader.hh"

#include <fstream>

#include "Ravl/Image/Utilities.hh"

namespace RavlImageN {

//class DVSBufferC;
//class CardModeC;

//! userlevel=Normal
//: Read legacy raw video files.
// This class will read grabfiles generated prior to the new grabfile
// format being introduced.
class LegacyGrabfileReaderC: public GrabfileReaderC {
public:
  LegacyGrabfileReaderC()
    :
    GrabfileReaderC()
  {
    // Do nothing
  }

  virtual ~LegacyGrabfileReaderC();

  //==========================================================================//

  virtual bool Open(const char* const filename);
  //: Open file and read file header.

  virtual void Close();
  //: Close file.

  virtual bool Ok() const;
  //: Are there any problems with the IO?

  virtual bool HaveMoreFrames();
  //: Check for more frames.

  virtual bool GetNextFrame(BufferC<char> &bu, UIntT &vsize, UIntT &asize);
  //: Read the next frame to a buffer.

  virtual int Version() const {return 0;}
  //: The version of the reader.

  virtual ByteFormatT getByteFormat() { 
  return byteformat;}
  //: Return the byte format.

  virtual ColourModeT getColourMode() { 
  return colourmode;}
  //: Return the colour mode.

  virtual RealT getFrameRate() {return m_frame_rate;}
  //: Return the frame rate.

  virtual IntT getNumberOfFrames() {return m_number_of_frames;}
  //: Return the number of frames.

  //--------------------------------------------------------------------------//

protected:

  std::ifstream m_infile;
  //: Input stream.

  IntT m_video_buffer_size;
  //: Video buffer size.

  IntT m_audio_buffer_size;
  //: Audio buffer size.

  IntT m_number_of_frames;
  //: Number of frames.

  RealT m_frame_rate;
  //: Frame rate.

  VideoModeT videomode;
  //: Video mode.

  ByteFormatT byteformat;
  //: Byte format.

  ColourModeT colourmode;
  //: Colour mode.
};

}


#endif // LEGACYGRABFILEREADER_HH
