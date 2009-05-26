//! author="Rachel Gartshore"


#ifndef MY_DEFINITIONS_HH
#define MY_DEFINITIONS_HH

#include "Ravl/Point2d.hh"
#include "Ravl/Index2d.hh"
#include "Ravl/StdMath.hh"
#include "Ravl/Angle.hh"

#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"

#include <iostream>
#include <iomanip>

using namespace RavlN;
using namespace RavlImageN;

namespace HollyN
{

#define debug 0
#define debugMain 1
#define debugMap 0
#define debugpos 0
#define debug_accum 0 // debug the AccumulatorC
#define debuggui 0 // debug the GUI_FunctionsC
#define debugWE 0 // debug the World_ElementC
#define debugHE 0 // debug the Half Edge Mesh
#define debugHE_move 0 // debug moving a half edge mesh point
#define debugHE_flip 0 // debug flipping an edge
#define debugVPS 0 // debug the viewpoint planning strategies
#define debug_randomMap 0 // debug the random map generation
#define debug_Drawing 0
#define debug_View 0
#define debug_Seen 0
#define debugPos 0
#define debugBins 0

#define testingAll 1

  typedef ImageC<ByteRGBValueC> ImageT;

  // FIXME - calculate (not measure!) the camera and lens offsets
  const RealT cam_offset = 110; // rotation centre of robot to camera rotation axis (mm)
  const RealT lens_offset = 40; // rotation centre of robot to camera rotation axis (mm)

  // Camera parameters calculated from Calibration
  //const RealT Kuf = 100.0; // to test the error on rotation algorithm
  //const RealT Uo = 128.0; // to test the error on rotation algorithm
  const RealT Kuf = 533.94; //for wintv card with sony_dvi //637.7; // for sony_ccd camera / 879 for meteor1
  const RealT Uo = 278.20; //for wintv card with sony_dvi //225.98; // for sony ccd camera / 368 for meteor1
  const int Image_Width = 480; // for wintv card with sony_dvi // 460; for sony_ccd camera

  const IndexRange2dC Map_Size( Index2dC(-3000,-3000), Index2dC(7000,6000) );
  const IndexC Extra_Offset(250);
    
  // threshold value for corner choice - set for morpheus camera
  const RealT corner_threshold = 0.01;
  // number of pixels to ignore at start and end of scan line
  const int ignore_pixels = 10;

  const RealT pixel_uncertainty = 0.00314;
  const RealT robot_position_uncertainty = 50.0/4.0; // 10; // 10mm of uncertainty
  const RealT accumulator_threshold = 0.0001;

  // points added to the map, if they are within <distance_threshold> - classed as same point
  const RealT mahalanobis_threshold = 2.0;
  const RealT bhattacharyya_threshold = 0.0001;
  const RealT MINIMUM_DISTANCE = 0.1;

  const RealT field_of_view = Radians(15);

  // Conversion between robot position to camera position
  // This function takes the robot's position and orientation and current pan angle
  // Returns corrected position and orientation (from offset of camera including pan angle)
  // All angles in radians
  void Robot_to_Camera( const Point2dC rob_position, const RealT rob_orientation, const RealT pan,
		  Point2dC &cam_pos, RealT &cam_orien );
  void Camera_to_Robot( const Point2dC cam_position, const RealT cam_orientation, const RealT pan,
		  Point2dC &rob_pos, RealT &rob_orien );

#ifndef GUI_POINT_COLOURS
#define GUI_POINT_COLOURS
  const IntT point = 0;
  const IntT point_new = 1;
  const IntT point_updated = 2;
  const IntT point_position = 3;
  const IntT point_navigation = 4;
#endif

// 2 degrees
#ifndef ERROR_ANGLE
#define ERROR_ANGLE 2.0 * RavlConstN::pi / 180.0
#endif

// robot radius in mm
#define ROBOT_RADIUS 250

  struct NextMoveInfo
  {
    Point2dC camPos; // position of new CAMERA position
    RealT theta; // orientation of ROBOT to reach new position (radians)
    RealT view; // viewing direction of CAMERA (radians)
    Point2dC navigationL; // left edge point selected for NVB
    Point2dC navigationR; // right edge point selected for NVB
    RealT expectedImprovement; // expected improvement of area from this position given current information
  };

} // end of namespace HollyN

#endif
