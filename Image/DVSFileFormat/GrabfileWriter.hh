#if !defined(RAVL_GRABFILEWRITER_HEADER)
#define RAVL_GRABFILEWRITER_HEADER
//! rcsid="$Id: $"
//! author="Simon Tredwell"
//! docentry="Ravl.API.Images.Video.Video IO.DVS"
//! lib=DVS

#include "Ravl/Image/GrabfileCommon.hh"
#include "Ravl/Image/Utilities.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/SArray1d.hh"
//#include "Ravl/Image/CardMode.hh"

namespace RavlImageN {

//class DVSBufferC;
//class DVSCardC;
//class CardModeC;

//! userlevel=Normal
//: Write the data from the DVS capture system to a file.
// This is the base class for Grabfile writers. It should not contain
// any pure virtual functions except for Version().
class GrabfileWriter {
public:
  GrabfileWriter()
    :
    m_frame_number(-1),
    m_frames_written(0)
  {
    // Do nothing
  }

  virtual ~GrabfileWriter() {}

  //==========================================================================//

  typedef GrabfileCommon::frame_number_t frame_number_t;
  //: Type to store the frame number.

  virtual bool Openva(const char* const filename,
                    //DVSCardC& card,
                    //CardModeC& mode,
		    VideoModeT vmode,ByteFormatT bformat, ColourModeT cmode,IntT videobuffersize, IntT audiobuffersize) {
    return false;
  }
  //: Open file and write file header.
  //!return false
/*
  virtual bool Open(const char* const filename,
                    DVSCardC& card,
                    CardModeC& mode) {
     return false;
  }*/
  //: Open file and write file header.


  virtual void Close() {}
  //: Close file.

  virtual void Close(int numberofframes) {}
  //: Close file and write number of frames.

  virtual bool Ok() const {return false;}
  //: Are there any problems with the IO?
/*
  virtual bool PutFrame(const DVSBufferC &buffer) {return false;}
  //: Write frame.
   */
  virtual bool PutFrame2(BufferC<char> &fr,UIntT &te) {return false;}

  virtual bool PutFrameA(SArray1dC<char> &re) {return false;}
  //: Write frame.

  virtual void Reset(VideoModeT vmode,ByteFormatT bformat,IntT vbuf) {}
  //: Re write video properities data.

  virtual int VideoBuffer() {}
  //: Return video buffer size.

  virtual int Version() const = 0;
  //: The version of the writer.


  //--------------------------------------------------------------------------//

  frame_number_t FramesWritten() const { return m_frames_written; }
  //: The number of frames written to the file.


protected:
  frame_number_t m_frame_number;
  //: The frame number of the most recently written frame.

  frame_number_t m_frames_written;
  //: The number of frames written.

};

}

#endif // RAVL_GRABFILEWRITER_HEADER
