// Robot_Control.hh

//! author="Rachel Gartshore"

/*
 * Interface to holly and to holly's camera
 */

#ifndef ROBOT_CONTROL__HH
#define ROBOT_CONTROL__HH

#include "Ravl/config.h"
#include "Ravl/StdMath.hh"
#include "Ravl/StdConst.hh"
#include "Ravl/IntC.hh"

#include "Ravl/Point2d.hh"
#include "Ravl/Vector.hh"
#include "Ravl/DList.hh"
#include "Ravl/Stack.hh"
#include "Ravl/StackIter.hh"

#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Image/ImgIO.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/DP/FileFormatIO.hh"

#include "Ravl/OS/Date.hh"

#include "Aria.h"

#include "My_Definitions.hh"

#include <iostream>
#include <fstream>

using namespace RavlN;
using namespace RavlImageN;

namespace HollyN
{
  const RealT start_pan = 60;

  class Robot_ControlC
  {
	
	  public:
		  Robot_ControlC();
		  ~Robot_ControlC();
		  RealT Power(); // returns amount of power left - return 0!!
		  IntT Robot_Connected(); // returns if we are connected to robot
		  IntT Camera_Connected();
		  IntT Not_Moving();
		  IntT Not_Rotating();

		  // connect to the robot and camera
		  IntT Start_Robot();
		  IntT Start_Camera();
		  IntT Shutdown_Robot();
		  IntT Stop_Camera();

		  IntT Move_Grab( RealT distance, RealT angle, RealT pan,
				  VectorC &info_gathered, ImageC <ByteRGBValueC> &image );
		  // Pan, Rotate, Move distance, grab images at distanceX intervals
		  IntT Move_GrabX( RealT distance, RealT angle, RealT pan, RealT distanceX,
				  DListC<VectorC> &info_gathered,
				  DListC<ImageT> &images );
		  IntT Go( RealT distance, RealT angle );
		  IntT Stop(); // stop robot from moving
		  IntT Rotate_To( RealT angle ); // rotate to angle degrees
		  IntT Rotate_By( RealT angle ); // rotate by angle degrees
		  IntT Move_By( RealT distance ); // move by distance mm

		  // set maximum velocity in mm/sec
		  IntT Set_Max_Velocity( RealT vel );
		  // set rotational velocity in degrees/sec
		  IntT Set_MaxRot_Velocity( RealT vel );

		  // basic capture function
		  IntT Capture( Point2dC &position, RealT &angle );
		  IntT Capture( ImageC <ByteRGBValueC> &new_image,
				  Point2dC &image_position ,RealT &image_heading);

		  // Grab an image, save it to image_file, write odometry to info_file
		  IntT Capture( const char *image_file, const char *info_file );

		  // Grab an image, store as new_image, save in image_file, write odometry to info_file
		  IntT Capture( ImageC <ByteRGBValueC> &new_image,
				  const char *image_file, const char *info_file );
		  IntT Where( Point2dC &position, RealT &orientation );
		  IntT Where();
		  IntT Where_Camera( RealT &pan, RealT &tilt, RealT &zoom );
		  IntT Where_Camera();
		  RealT GetPan();

		  // set odometry data
		  IntT Set_Position( Point2dC position, RealT orientation );

		  // Move camera
		  IntT Set_Pan( RealT pan );
		  IntT Set_Tilt( RealT tilt );
		  IntT Set_Zoom( RealT zoom );
		  IntT Set_PT( RealT pan, RealT tilt );

		  IntT Image_Timing();
		  IntT Pan_Timing();


	  private:
		  ArRobot my_robot;
		  ArSerialConnection serConn;
		  ArPose position;
		  RealT pan_angle;

		  ArPTZ *my_camera;

		  //IntT Safe_Move ( IntT distance ); // moves distance(mm) checking if it is safe
		  //IntT Min_Sonar_Distance( IntT low, IntT high ); // returns closest sonar range

		  DPIPortC< ImageC < ByteRGBValueC > > input; 	// image input
		  ImageC < ByteRGBValueC >	current_image;	// image that is currently being grabbed

		  IntT camconnected;
  };


} // end of namespace HollyN

#endif
