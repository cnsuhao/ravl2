// Robot_Control.cc

//! author="Rachel Gartshore"

#include "Robot_Control.hh"

namespace HollyN
{

Robot_ControlC::Robot_ControlC()
{
  camconnected = 0; // flag that the camera is not yet connected
}

Robot_ControlC::~Robot_ControlC()
{
  if( my_robot.isConnected() )
    Shutdown_Robot();
}

RealT Robot_ControlC::Power()
{
  return (RealT)my_robot.getBatteryVoltage();
}

IntT Robot_ControlC::Robot_Connected()
{
  return my_robot.isConnected();
}

IntT Robot_ControlC::Camera_Connected()
{ 
  return camconnected;
}

IntT Robot_ControlC::Not_Moving()
{
  IntT ret = my_robot.isMoveDone(100);
  return ret;
}

IntT Robot_ControlC::Not_Rotating()
{
  IntT ret = my_robot.isHeadingDone(10);
  return ret;
}

IntT Robot_ControlC::Start_Robot()
{
  my_robot.lock();
  if( my_robot.isConnected() ) // if we are already connected to the robot
  {
    my_robot.unlock();
    cerr << "We are already connected to the robot\n";
  }
  else
  {
    my_robot.unlock();
    // mandotary init
    Aria::init();

    //serConn.setPort("/dev/ttyS0");
    serConn.setPort();
    my_robot.setDeviceConnection(&serConn);
    if( !my_robot.blockingConnect() )
    {
      cerr << "Could not connect to robot... Exiting" << endl;
      Aria::shutdown();
      return -1;
    }
    my_robot.runAsync(false);
    cout << "We are now connected to holly" << endl;

    // set maximum rotation and translation
    my_robot.lock();
    my_robot.setAbsoluteMaxTransVel(80); 
    my_robot.setAbsoluteMaxRotVel(25); 

    // Enable motors and disable sonars
    my_robot.enableMotors();
    my_robot.comInt(ArCommands::SONAR, 0);
    my_robot.unlock();
    cerr << "Motors should now be enabled" << endl;
  }
  my_robot.unlock();

  return 0;
}


IntT Robot_ControlC::Stop_Camera()
{
  if( camconnected )
  {
    // disconnect from frame grabber
    input.Invalidate();
    delete my_camera;
  }
  return 0;
}

IntT Robot_ControlC::Start_Camera()
{
  my_robot.lock();
  if( my_robot.isConnected() && !camconnected )
  {
    my_robot.unlock();
    cerr << "Trying to start up the camera" << endl;
    // Initialise the camera
    my_camera = new ArSonyPTZ(&my_robot);
    Sleep(0.1); 
    
    // BooleanT OpenISequence(DPISPortC<DataT> & ip,const StringC & fn,
    // const StringC & fileformat = "",BooleanT verbose = FALSE )
    if( !OpenISequence( input, "@V4LH:/dev/video0#1", "", (bool)true ) )
    {
      cerr << "Failed to open the frame grabber" << endl;
      return -1;
    } 
  
    // we are successfully connected
    camconnected = 1; // flag that the camera is successfully connected

    // Set up the camera variables
    Set_Pan(0);
    Set_Tilt(0);
    Set_Zoom(32); 
    Sleep(2);
    
    cout << "Grabbing five images into file test.ppm" << endl;
    for(IntT i=0; i<5; i++) // grab some images to be discarded (clear the buffer)
      current_image = input.Get();

    if( !Save("test.ppm",current_image, "", (bool)true) )
      cerr << "Didn't save anything" << endl;
  
  } // end of if is connected
  my_robot.unlock();
 
  return 0;

}


IntT Robot_ControlC::Shutdown_Robot()
{
  my_robot.lock();
  my_robot.disconnect();	/* bye, bye */
  my_robot.unlock();
  Stop_Camera();
  cout << endl << "Thanks for playing with me!" << endl;
  return 0;
}

// *************************** movement commands **************************

// argument should be from 0to359
IntT Robot_ControlC::Rotate_To( RealT angle ) // rotate by angle degrees
{
  my_robot.lock();
  my_robot.setHeading( (int)floor(angle) );
  my_robot.unlock();
  return 0;
}
// Rotation ccw is positive, cw negative
// argument should be from -180 to 180
IntT Robot_ControlC::Rotate_By( RealT angle ) // rotate by angle degrees
{
  // Rotate robot to desired heading
  my_robot.lock();
  my_robot.setDeltaHeading( (int)Degrees(angle) );
  my_robot.unlock();
  ArTime start;
  start.setToNow();
  while(1)
  {
    my_robot.lock();
    if( my_robot.isHeadingDone(2) )
    {
      cerr << "Finished turn\n";
      my_robot.unlock();
      break;
    }
    if( start.mSecSince() > 10000 )
    {
      cerr << "Turn timed out\n";
      my_robot.unlock();
      break;
    }
    my_robot.unlock();
    ArUtil::sleep(100);
  }
  return 0;
}
IntT Robot_ControlC::Move_By( RealT distance ) // move by distance mm
{
  my_robot.lock();
  my_robot.move( (IntT)floor(distance) );
  my_robot.unlock();
  return 0;
}
IntT Robot_ControlC::Set_Max_Velocity( RealT vel )
{
  my_robot.lock();
  my_robot.setAbsoluteMaxTransVel((int)floor(vel)); 
  my_robot.unlock();
  return 0;
}

// set rotational velocity in degrees/sec
IntT Robot_ControlC::Set_MaxRot_Velocity( RealT vel )
{
  my_robot.lock();
  my_robot.setAbsoluteMaxRotVel((int)floor(vel)); 
  my_robot.unlock();
  return 0;
}

// Move distance(mm) at angle(radians)
IntT Robot_ControlC::Go(RealT distance, RealT angle)
{
  cout << "Going to rotate by " << angle 
	  << " degrees and then move " << distance << "mm" << endl;
  my_robot.lock();
  my_robot.setHeading( Degrees(angle) );
  // wait until we're within 10 degrees before moving on
  while( !my_robot.isHeadingDone(10) )
    Sleep(0.1);
  my_robot.unlock();


  my_robot.lock();
  my_robot.move( (int)floor(distance) );
  while ( !my_robot.isMoveDone(100) ) 
    Sleep(0.1); // wait until we're within 10cm before moving on
  my_robot.unlock();

  return 0;
}

IntT Robot_ControlC::Stop()
{
  // stop robot
  my_robot.lock();
  my_robot.stop();
  my_robot.unlock();
  return 0;
}

// Capture routine - grabs image and stores position when image was taken
// Stores the grabbed image into new_image, and camera's position and heading
//IntT Robot_ControlC::Capture( ImageC <ByteRGBValueC> &new_image, Point2dC &position, float &heading )
IntT Robot_ControlC::Capture( Point2dC &camera_position, RealT &camera_angle )
{
  if( camconnected )
  {
    //current_image = input.Get();
    my_robot.lock();
    position = my_robot.getPose();
    my_robot.unlock();
    pan_angle = Radians(my_camera->getPan());

    Point2dC rob_pos( position.getX(), position.getY() );
    RealT rob_angle = Radians(position.getTh());

    // Get position of the camera
    Robot_to_Camera( rob_pos, rob_angle, pan_angle,
		    camera_position, camera_angle );

    return 0;
  }
  else
    cerr << "We aren't connected to the camera" << endl;

  return -1;
}

// Capture an image & store camera_position and camera_angle
IntT Robot_ControlC::Capture( ImageC <ByteRGBValueC> &new_image,
		Point2dC &camera_position ,RealT &camera_angle)
{
  if( camconnected )
  {
    ImageC <ByteRGBValueC> image = input.Get();

    my_robot.lock();
    position = my_robot.getPose();
    my_robot.unlock();
    pan_angle = Radians(my_camera->getPan());

    Point2dC rob_pos( position.getX(), position.getY() );
    RealT rob_angle = Radians(position.getTh());

    // Get position of the camera
    Robot_to_Camera( rob_pos, rob_angle, pan_angle,
		    camera_position, camera_angle ); 
    new_image = image;
    current_image = image;
  }
  else
  {
    cerr << "We aren't connected to the camera" << endl;
    return -1;
  }

  //if( Capture( camera_position, camera_heading ) < 0 )
    //return -1;
  return 0;
}

// Capture an image & save in image_file, write camera data (odometry + offset) into info_file
IntT Robot_ControlC::Capture( const char *image_file, const char *info_file )
{
  // Capture an image
  Point2dC camera_position;
  RealT camera_angle;
  if( Capture( camera_position, camera_angle ) < 0 )
    return -1;
  
  // Save the image_file
  Save( image_file, current_image );

  // Write the camera information
  ofstream info_out( info_file, ios::app );
  if( !info_out )
    cerr << "Couldn't open <" << info_file << '>' << endl;
  else
  {
    info_out << image_file << "\t" << camera_position.X() << "\t" << camera_position.Y()
	    << "\t" << camera_angle << endl;
    info_out.close();
  }

  return 0;
}

// Capture an image to new_image, save in image_file, write camera data (odometry + offset) into info_file
IntT Robot_ControlC::Capture( ImageC <ByteRGBValueC> &new_image,
		const char *image_file, const char *info_file )
{ 
  if( Capture( image_file, info_file ) < 0 )
    return -1;

  // assign current_image to new_image
  new_image = current_image;

  return 0;

}

// return the current position
IntT Robot_ControlC::Where( Point2dC &robot_position, RealT &robot_orientation )
{
  my_robot.lock();
  if( my_robot.isConnected() ) // if we are connected to the robot
  {
    position = my_robot.getPose();
    my_robot.unlock();
    robot_position = Point2dC( position.getX(), position.getY() );
    robot_orientation = Radians(my_robot.getTh());
  }
  else
    cerr << "We aren't connected to the robot" << endl;
  my_robot.unlock();

  return 0;
}

// get the current position
IntT Robot_ControlC::Where()
{
  my_robot.lock();
  if( my_robot.isConnected() ) // if we are connected to the robot
  {
    position = my_robot.getPose();
    my_robot.unlock();
  }
  else
    cerr << "We aren't connected to the robot" << endl;
  my_robot.unlock();

  return 0;
}

// return the position of the camera
IntT Robot_ControlC::Where_Camera( RealT &pan, RealT &tilt, RealT &zoom )
{
  my_robot.lock();
  if( my_robot.isConnected() ) // if we are connected to the robot
  {
    my_robot.unlock();
    pan = Radians(my_camera->getPan());
    tilt = Radians(my_camera->getTilt());
    zoom = Radians(my_camera->getZoom());
  }
  else
    cerr << "We aren't connected to the robot" << endl;
  my_robot.unlock();
    
  return 0;
}

// print out the position of the camera
IntT Robot_ControlC::Where_Camera()
{
  my_robot.lock();
  if( my_robot.isConnected() ) // if we are connected to the robot
  {
    my_robot.unlock();
    pan_angle = Radians(my_camera->getPan());
  }
  else
    cerr << "We aren't connected to the robot" << endl;
  my_robot.unlock();

  return 0;
}

// set the odometry information
IntT Robot_ControlC::Set_Position( Point2dC position, RealT orientation )
{
  my_robot.lock();
  my_robot.moveTo( ArPose(position.X(), position.Y(), Degrees(orientation)) );
  my_robot.unlock();
  return 0;
}

/*
IntT Robot_ControlC::Safe_Move( IntT distance )
{
  IntT mindist = Min_Sonar_Distance(2,5);
  if (mindist <= 700 && mindist > 200) // if the mindist to obstacle is within 20-70cm
    paiStopRobot();
  else
    paiMoveRobot (distance);
  paiPause(400);
  do
  {
    IntT mindist = Min_Sonar_Distance(2,5);
    if (mindist <= 700 && mindist > 200) // if the mindist to obstacle is within 20-70cm
    {
      paiStopRobot();
      cout << endl << "There's something in my way!" << endl;
    }
    paiPause(90);
  } while (paiRobotStatus() == paiSTATUSMOVING);

  return 0;
}

IntT Robot_ControlC::Min_Sonar_Distance( IntT low, IntT high )
{
  IntT i;
  IntT closest = 5000;
  for (i=low; i <= high; i++)
    if (paiSonarRange(i) < closest)
      closest = paiSonarRange(i);
  return closest;
}
*/


IntT Robot_ControlC::Set_Pan( RealT pan )
{
  // pan to an absolute position
  my_camera->pan((int)floor(pan));
  Sleep(0.1);
  return 0;
}

IntT Robot_ControlC::Set_Tilt( RealT tilt )
{
  // tilt to an absolute position
  my_camera->tilt((int)floor(tilt));
  Sleep(0.1);
  return 0;
}

IntT Robot_ControlC::Set_Zoom( RealT zoom )
{
  // zoom to an absolute zoom
  cerr << "Maximum zoom: " << my_camera->getMaxZoom() << endl;
  cerr << "Minimum zoom: " << my_camera->getMinZoom() << endl;
  my_camera->zoom((int)floor(zoom));
  Sleep(0.1);
  return 0;
}

IntT Robot_ControlC::Set_PT( RealT pan, RealT tilt )
{
  // set pan and tilt
  my_camera->panTilt((int)floor(pan),(int)floor(tilt));
  Sleep(0.1);
  return 0;
}

IntT Robot_ControlC::Image_Timing()
{
  my_robot.lock();
  if( !my_robot.isConnected() || !camconnected )
  {
    my_robot.unlock();
    cerr << "Trying to grab images from the camera, but not connected" << endl;
    return -1;
  }
  my_robot.unlock();

  // Initialise time - for current time
  DateC time((bool)true );
  // want to grab a number of images, printing out timing of the images
  for( IntT i=0; i<20; i++ )
  {
    time.SetToNow();
    double before = time.Double();
    //current_image = input.Get();
    time.SetToNow();
    double after = time.Double();
    double diff = after - before;
    cout << "\t\tdiff: " << diff << endl;
    //Sleep(1);
  }

  return 0;
}

IntT Robot_ControlC::Pan_Timing()
{
  my_robot.lock();
  if( !my_robot.isConnected() || !camconnected )
  {
    my_robot.unlock();
    cerr << "Trying to grab images from the camera, but not connected" << endl;
    return -1;
  }
  my_robot.unlock();

  my_camera->pan(0);
  Sleep(2);

  char ch;
  // Initialise time - for current time
  DateC time((bool)true );
  // want to grab a number of images, printing out timing of the images
  time.SetToNow();
  double before = time.Double();
  my_camera->pan(-90);
  time.SetToNow();
  double after = time.Double();
  cerr << "Enter a character; when finished panning hit return: ";
  cin >> ch;
  time.SetToNow();
  double later = time.Double();
  double diff = after - before;
  cout << "\t\tsend command to return from command: " << diff
	  << ", send command to hit return: " << later - before << endl;
  Sleep(1);

  time.SetToNow();
  before = time.Double();
  my_camera->pan(90);
  time.SetToNow();
  after = time.Double();
  cerr << "Enter a character; when finished panning hit return: ";
  cin >> ch;
  time.SetToNow();
  later = time.Double();
  diff = after - before;
  cout << "\t\tsend command to return from command: " << diff
	  << ", send command to hit return: " << later - before << endl;
  Sleep(1);
  return 0;
}

// Pan Camera, Rotate and move robot
// Grab images at x mm intervals
IntT Robot_ControlC::Move_GrabX( RealT distance, RealT angle, RealT pan, RealT distanceX,
		DListC<VectorC> &info_gathered, DListC<ImageT> &images )
{
  my_robot.lock();
  if( !my_robot.isConnected() || !camconnected )
  {
    my_robot.unlock();
    cerr << "Trying to grab images from the camera, but not connected" << endl;
    return -1;
  }
  // pan the camera - no way of checking we've done it, so call function first
  my_camera->pan((int)floor(pan)); Sleep(1);
  pan_angle = Radians(my_camera->getPan());

  position = my_robot.getPose();
  my_robot.unlock();
  Point2dC prev_pos(position.getX(),position.getY());
  RealT prev_rot = Radians(position.getTh());

  info_gathered.Empty();
  images.Empty();

  ArTime start;

  // Rotate robot to desired heading
  my_robot.lock();
  my_robot.setDeltaHeading( (int)Degrees(angle) );
  my_robot.unlock();
  start.setToNow();
  while(1)
  {
    my_robot.lock();
    if( my_robot.isHeadingDone(2) )
    {
      cerr << "Finished turn\n";
      my_robot.unlock();
      break;
    }
    if( start.mSecSince() > 10000 )
    {
      cerr << "Turn timed out\n";
      my_robot.unlock();
      break;
    }
    my_robot.unlock();
    ArUtil::sleep(100);
  }

  Sleep(2); // to make sure the camera has stopped moving

  ImageC<ByteRGBValueC> newimage;

  // We have now rotated and panned the robot/camera - get initial image
  // Grab an image and store position of robot
  pan_angle = Radians(my_camera->getPan());

  // Get the first image before we start to move
  newimage = input.Get(); 
  my_robot.lock();
  position = my_robot.getPose();
  my_robot.unlock();
  
  VectorC newinfo1(4);
  // Store the image
  images.InsLast(newimage);
  // The information we require is the delta movements
  newinfo1[0] = position.getX() - prev_pos.X();
  newinfo1[1] = position.getY() - prev_pos.Y();
  newinfo1[2] = Radians(position.getTh()) - prev_rot;
  newinfo1[3] = pan_angle;
  info_gathered.InsLast(newinfo1); 
  cerr << "Info Gathered: " << newinfo1 << endl;

  // Calculate the average distance we travel between images - just as a test
  // We don't want to get this first one, as it should be 0 and will mess up the average!
  StackC<RealT> travellingTotal;
  cerr << "Distance travelled before first image: " << sqrt(Sqr(newinfo1[0])+Sqr(newinfo1[1])) << endl;
  
  // Store the new position into previous for next time
  prev_pos = Point2dC(position.getX(),position.getY());
  prev_rot = Radians(position.getTh());

  start.setToNow();
  // Now start to move the robot
  my_robot.lock();
  my_robot.move( distance );
  my_robot.unlock();

  IntT count = 1;
  IntT max_count = Abs(distance / distanceX);
  cerr << "We should be grabbing: " << max_count << " images\n";
  while(1)
  {
    VectorC newinfo(4);
    // Check to see if we have finished moving
    my_robot.lock();
    // Check we haven't stalled
    if( start.mSecSince() > 20000 )
    { // mSecSince - milli-seconds since started
      cerr << "Distance timed out\n";
      my_robot.unlock();
      break;
    }
    my_robot.unlock();

    my_robot.lock();
    if( my_robot.isMoveDone(Abs(distance)-count*distanceX+1) )
    {
      my_robot.unlock();
      count++;
      if( count >= max_count ) // >= just in case!
      {
	cerr << "Finished complete distance\n";
	break;
      }

      my_robot.lock();
      ArPose position_before = my_robot.getPose();
      my_robot.unlock(); 
      
      //RealT before = start.mSecSince();
      // grab an image
      newimage = input.Get(); 
      
      // Get the pose of the robot - have to wait for frame to come from camera
      // so position of robot is closer to the finish of the input.Get()
      my_robot.lock();
      position = my_robot.getPose();
      my_robot.unlock(); 
      //RealT after = start.mSecSince();

      Point2dC pos1(position_before.getX(), position_before.getY());
      Point2dC pos2(position.getX(), position.getY()); 
      //cerr << "Time to get image;pos: " << after - before
	      //<< "\tDistance: " << pos1.EuclidDistance(pos2)
	      //<< "The position: " << position.getX() << "," << position.getY() << endl;
    
      // Store the image
      images.InsLast(newimage);
      // The information we require is the delta movements
      newinfo[0] = position.getX() - prev_pos.X();
      newinfo[1] = position.getY() - prev_pos.Y();
      newinfo[2] = Radians(position.getTh()) - prev_rot;
      newinfo[3] = pan_angle;
      info_gathered.InsLast(newinfo); 
      cerr << "Info Gathered: " << newinfo << endl;
      //cerr << "Distance travelled between images: " << sqrt(Sqr(newinfo[0])+Sqr(newinfo[1])) << endl;
      travellingTotal.Push(sqrt(Sqr(newinfo[0])+Sqr(newinfo[1])));
    
      // Store the new position into previous for next time
      prev_pos = Point2dC(position.getX(),position.getY());
      prev_rot = Radians(position.getTh()); 
      
    }
    else
      my_robot.unlock();
    ArUtil::sleep(40);
  }

  // Calculate the average distance travelled between images grabbed
  IntT i = 0;
  RealT mean = 0;
  RealT sd = 0;
  for( StackIterC <RealT> it(travellingTotal); it; it++ )
  {
    i++;
    mean += *it;
  }
  if( i>0 )
  {
    mean /= i;
    for( StackIterC <RealT> it(travellingTotal); it; it++ )
      sd += Sqr( mean - *it );
    sd /= i;
    sd = sqrt(Abs(sd));
  }
  cerr << "Average distance travelled between images: " << mean << ", sd: " << sd << endl;

  // flush the buffer to get the last four images we grabbed
  // buffer size=5
  VectorC newinfo(0,0,0,0);
  for( IntT i=0; i<4; i++ )
  {
    newimage = input.Get();
    images.InsLast(newimage); // flush buffer to get images grabbed
    images.PopFirst(); // and remove the first ones which were the old ones from last time!
  }

  return 0;
}

RealT Robot_ControlC::GetPan()
{
  pan_angle = Radians(my_camera->getPan());
  return pan_angle;
}

// Pan camera, rotate and move robot - then grab an image when stationary
IntT Robot_ControlC::Move_Grab( RealT distance, RealT angle, RealT pan, VectorC &info_gathered, ImageC <ByteRGBValueC> &image )
{
  my_robot.lock();
  if( !my_robot.isConnected() || !camconnected )
  {
    my_robot.unlock();
    cerr << "Trying to grab images from the camera, but not connected" << endl;
    return -1;
  }
  position = my_robot.getPose();
  my_robot.unlock();
  Point2dC prev_pos(position.getX(),position.getY());
  RealT prev_rot = Radians(position.getTh());

  ArTime start;

  // pan the camera - no way of checking we've done it, so call function first
  my_camera->pan((int)floor(pan));
  Sleep(1);

  // Rotate robot to desired heading
  my_robot.lock();
  //my_robot.setHeading( angle );
  my_robot.setDeltaHeading( (int)Degrees(angle) );
  my_robot.unlock();
  start.setToNow();
  while(1)
  {
    my_robot.lock();
    if( my_robot.isHeadingDone(5) )
    {
      cerr << "Finished turn\n";
      my_robot.unlock();
      break;
    }
    if( start.mSecSince() > 5000 )
    {
      cerr << "Turn timed out\n";
      my_robot.unlock();
      break;
    }
    my_robot.unlock();
    ArUtil::sleep(100);
  }

  // Move the robot
  my_robot.lock();
  my_robot.move( distance );
  my_robot.unlock();
  while(1)
  {
    my_robot.lock();
    if( my_robot.isMoveDone() )
    {
      cerr << "Finished distance\n";
      my_robot.unlock();
      break;
    }
    if( start.mSecSince() > 10000 )
    {
      cerr << "Distance timed out\n";
      my_robot.unlock();
      break;
    }
    my_robot.unlock();
    ArUtil::sleep(50);
  }

  Point2dC camera_position;
  //RealT camera_angle = 0.0;

  my_robot.lock();
  position = my_robot.getPose();
  my_robot.unlock();
  pan_angle = Radians(my_camera->getPan());

  // The information we require is the delta movements
  info_gathered[0] = position.getX() - prev_pos.X();
  info_gathered[1] = position.getY() - prev_pos.Y();
  info_gathered[2] = Radians(position.getTh()) - prev_rot;
  info_gathered[3] = pan_angle;

  // Grab an image and store position of robot
  // grab three images to ensure we have a new image - buffer size of 3 images
  Sleep(1); // - just to make sure we've stopped moving
  for( IntT i=0; i<3; i++ )
    current_image = input.Get();
  image = current_image;

  return 0;
}



} // end of namespace HollyN
