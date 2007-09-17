#include "Ravl/Image/LegacyGrabfileReader.hh"

#include "Ravl/Assert.hh"
#include "Ravl/Image/Utilities.hh"
#include <arpa/inet.h>

namespace RavlImageN {
//==========================================================================//

LegacyGrabfileReader::~LegacyGrabfileReader()
{
  if(m_infile.is_open()) {
    m_infile.close();
  }
}

//--------------------------------------------------------------------------//
/*
// Open file and read file header.
bool LegacyGrabfileReader::Open(const char* const filename, CardModeC& mode)
{
  // Is the file alread open? It shouldn't be!
  if(m_file) {
    RavlIssueError("LegacyGrabfileReader: Class already contains an open file.")
  }

  bool ok = true;

  // Open the file.
  if(ok) {
    m_file = fopen(filename, "rb");
    ok = (m_file != 0);
  }

  // Now we open the file again (temporarily) to get the header information!
  FILE * data_file = fopen(filename, "rb");

  DVSBufferC file_buffer(data_file);

  // set mode for playback
  mode.VideoMode(file_buffer.VideoMode());
  mode.ByteFormat(file_buffer.ByteFormat()) ;
  mode.ColourMode(file_buffer.ColourMode()) ;

  fclose(data_file);

  return ok;
}
*/
// Open file and read file header.
bool LegacyGrabfileReader::Open(const char* const filename) //, CardModeC& mode)
{
  // Is the file alread open? It shouldn't be!
  if(m_infile.is_open()) {
    RavlIssueError("LegacyGrabfileReader: Class already contains an open file.");
  }

  bool ok = true;
  // Is the file a grabfile?
  //if(ok) {
    m_infile.open(filename, std::ios::binary | std::ios::in);
  //  ok = IsGrabfile(m_infile);
  //}
  // Is the version correct, (this code will only deal with version 1,
  // hence the hardcode below.
  /*if(ok) {
    ok = (FileVersion(m_infile) == m_version_number);
  }*/
  // We can now read the header.
  if(ok) {
   /* int dummy_int = 0;

    // Video buffer size
    m_infile.read(reinterpret_cast<char*>(&dummy_int), 4);
    m_video_buffer_size = dummy_int;
    //cout << "m_video_buffer_size is " << dummy_int << endl;
  
    // Audio buffer size
    m_infile.read(reinterpret_cast<char*>(&dummy_int), 4);
    m_audio_buffer_size = dummy_int;


    //TFVectorC<SizeT, numAudioOffsets> audioOffsets;
    //TFVectorC<SizeT, numVideoOffsets> videoOffsets;

    VideoOffsetsT videoOffsets;
    AudioOffsetsT audioOffsets;
    char videooffsets[8];
    char audiooffsets[32];
    m_infile.read(videooffsets,8);
    m_infile.read(audiooffsets,32);
    IntT frames;
    RealT frameRate;
    char framesarr[4];
    char frameratearr[8];
    m_infile.read(framesarr,4);
    m_infile.read(frameratearr,8);
    
    //char videomodearr[4];
    m_infile.read(reinterpret_cast<char*>(&videomode),4);
    
    //uint8_t id = m_infile.get();
    //m_mode.VideoMode(IdToVideoMode(id));
    //videomode = IdToVideoMode(id);

    //char id2 = m_infile.get();
    //char byteformatarr[4];
    m_infile.read(reinterpret_cast<char*>(&byteformat),4);
    //m_mode.ByteFormat(IdToByteFormat(id));
    //id = (uint8_t)id2;
    //cout << "Saving byte format " << IdToByteFormat(id2) << endl;
    //byteformat = int(id2);  //IdToByteFormat(id);
    

    //char id3 = m_infile.get();
    m_infile.read(reinterpret_cast<char*>(&colourmode),4);
    
    //m_mode.ColourMode(IdToColourMode(id));
    //colourmode = int(id3);  //IdToColourMode(id);

    AudioChannelsT audioChannels;
    AudioBitsT audioBits;
    AudioFreqT audioFreq;
    
    char audiochannels[4];
    char audiobits[4];
    char audiofreq[4];

    m_infile.read(audiochannels,4);
    m_infile.read(audiobits,4);
    m_infile.read(audiofreq,4);
  */ 
    //mode.VideoMode(m_mode.VideoMode());
    //mode.ByteFormat(m_mode.ByteFormat());
    //mode.ColourMode(m_mode.ColourMode());

    ok = Ok();
  }

  //if(!ok) {
  //  Close();
 // }

  return ok;
}

//--------------------------------------------------------------------------//

// Close file.
void LegacyGrabfileReader::Close()
{
  //fclose (m_file);
  //m_file = 0;
  m_infile.close();
}


//-------------------------------------------------------------------------//
bool LegacyGrabfileReader::HaveMoreFrames()
{
  m_infile.peek();
  return m_infile.eof();
}



//--------------------------------------------------------------------------//

// Are there any problems with the IO?
bool LegacyGrabfileReader::Ok() const
{
  return m_infile.good();
}

//--------------------------------------------------------------------------//
/*
// Read the next frame to a buffer.
bool LegacyGrabfileReader::GetNextFrame(DVSBufferC &buffer)
{
  const bool ok = buffer.Load(m_file);

  if(ok) {
    ++m_frames_loaded;
  }

  return ok;
}
*/

// Read the next frame to a buffer.
bool LegacyGrabfileReader::GetNextFrametest(BufferC<char> &bu, UIntT &vsize, UIntT &asize)   //(DVSBufferC &buffer)
{
  bool ok = HaveMoreFrames();
 
  if(!ok) {
 
   uint32_t dummy_int = 0;
   UIntT vbtemp = 0;
  // Video buffer size  
  m_infile.read(reinterpret_cast<char*>(&vbtemp), sizeof(vbtemp));
  vsize = vbtemp;
  m_video_buffer_size = vbtemp;
  
  // Audio buffer size
  m_infile.read(reinterpret_cast<char*>(&dummy_int), 4);
  asize = dummy_int;
  m_audio_buffer_size = asize;
   
    VideoOffsetsT videoOffsets;
    AudioOffsetsT audioOffsets;
    char videooffsets[8];
    char audiooffsets[32];
    
    m_infile.read(videooffsets,8);
    
    m_infile.read(audiooffsets,32);
    //IntT frames;
    //RealT frameRate;
    char framesarr[4];
    char framesratearr[8];
  
    m_infile.read(framesarr,4);
   
    m_infile.read(framesratearr,8);

    m_infile.read(reinterpret_cast<char*>(&videomode),4);

    ByteFormatT temp;
    m_infile.read(reinterpret_cast<char*>(&temp),4);
    
    byteformat = temp;

    ColourModeT cmt;
    m_infile.read(reinterpret_cast<char*>(&cmt),4);
    colourmode = cmt;
    

    //AudioChannelsT audioChannels;
    //AudioBitsT audioBits;
    //AudioFreqT audioFreq;
    char audiochannels[4];
    char audiobits[4];
    char audiofreq[4];
  
    m_infile.read(audiochannels,4);
   
    m_infile.read(audiobits,4);
 
    m_infile.read(audiofreq,4);
   
    if(m_infile.good()) {
      int csize = m_video_buffer_size + m_audio_buffer_size; 
      char * obuf = new char[csize];
      char * start = obuf;
      m_infile.read(obuf,csize);
      bu = BufferC<char> (csize,start,false,false);
   }
   ++m_frames_loaded;
  }
  
  return ok;
}




} // End DVSN namespace
