#include "Ravl/Image/GrabfileReader.hh"

//#include "Buffer.hh"
//#include "CardMode.hh"
#include "Ravl/Assert.hh"

#include <fstream>
#include <arpa/inet.h>

namespace RavlImageN {

//--------------------------------------------------------------------------//

const bool GrabfileReader::IsGrabfile(const char* const filename)
{
  std::ifstream infile(filename, std::ios::binary | std::ios::in);

  const bool match = IsGrabfile(infile);

  infile.close();

  return match;
}

//--------------------------------------------------------------------------//

const bool GrabfileReader::IsGrabfile(std::ifstream& infile)
{
  char file_id[4] = {0x00, 0x00, 0x00, 0x00};
  infile.read(file_id, 4);

  const bool match = (
                      GrabfileCommon::GrabfileFOURCC[0] == file_id[0] &&
                      GrabfileCommon::GrabfileFOURCC[1] == file_id[1] &&
                      GrabfileCommon::GrabfileFOURCC[2] == file_id[2] &&
                      GrabfileCommon::GrabfileFOURCC[3] == file_id[3]
                      );

  return match;
}

//--------------------------------------------------------------------------//

const int GrabfileReader::FileVersion(const char* const filename)
{
  uint32_t version = 0;

  std::ifstream infile(filename, std::ios::binary | std::ios::in);

  if(IsGrabfile(infile)) {
    version = FileVersion(infile);
  }

  infile.close();

  return version;
}

//--------------------------------------------------------------------------//

const int GrabfileReader::FileVersion(ifstream& infile)
{
  uint32_t version = 0;

  // Read the version
  if(infile.good()) {
    infile.read(reinterpret_cast<char*>(&version), 4);
  }

  return ntohl(version);
}

} // End DVSN namespace
