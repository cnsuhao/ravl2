//! author="Rachel Gartshore"

#include "My_Definitions.hh"

namespace HollyN
{

  // Receive angles in radians - return angle in radians
  void Robot_to_Camera( const Point2dC rob_pos, const RealT rob_theta, const RealT pan,
		  Point2dC &cam_pos, RealT &cam_orien )
  {
    AngleC cam_rot(rob_theta-pan);
    cam_orien = cam_rot.Value();
#if debugpos
    cerr << "Rotation of camera: " << rob_theta << " - " << pan << " = " << cam_orien << endl;
#endif

    RealT x_val = rob_pos.X() + cam_offset*cos(rob_theta) + lens_offset*cos(cam_orien);
    RealT y_val = rob_pos.Y() + cam_offset*sin(rob_theta) + lens_offset*sin(cam_orien);

    cam_pos = Point2dC( x_val, y_val );
#if debugpos
    cerr << "Position of Camera: " << cam_pos << endl;
#endif
  }

  // Receive angles in radians - return angle in radians
  void Camera_to_Robot( const Point2dC cam_pos, const RealT cam_orien, const RealT pan,
		  Point2dC &rob_pos, RealT &rob_theta )
  {
    AngleC rob_rot(cam_orien + pan);
    rob_theta = rob_rot.Value();

#if debugpos
    cerr << "Rotation of robot: " << cam_orien << " + " << pan << " = " << rob_theta << endl;
#endif

    RealT x_val = cam_pos.X() - cam_offset*cos(rob_theta) - lens_offset*cos(cam_orien);
    RealT y_val = cam_pos.Y() - cam_offset*sin(rob_theta) - lens_offset*sin(cam_orien);

    rob_pos = Point2dC( x_val, y_val );
#if debugpos
    cerr << "Robot Position: " << rob_pos << endl;
#endif
  }

}
