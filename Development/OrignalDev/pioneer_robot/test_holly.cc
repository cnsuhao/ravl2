//! author="Rachel Gartshore"

/*
 * test_holly.cc 
 *
 * Test of all functions of holly, camera, processing and planning operations
 *
 * including:
 * 	motion functions
 * 	image grabbing
 *
 * COMMANDS ARE AS FOLLOWS
 * 	COMMAND	ARGUMENTS	DESCRIPTION
 * 	connect <machine>	machine to connect to, options: "holly" "simulator"
 * 	exit			quit from program
 * 	startcam		start camera
 * 	move	<x>		move by x mm in the current direction
 * 	rotate	<x>		rotate by x degrees (+cw, -ccw)
 * 	pan	<x>		pan to angle x degrees (absolute position)
 * 	grab	<image_file>	grab an image and store in <image_file>
 * 	whereami		get position of robot
 */

#include "Ravl/config.h"
#include "Ravl/Option.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/DP/FileFormatIO.hh"

#include "Ravl/Point2d.hh"
#include "Ravl/Index2d.hh"

#include "Ravl/Array1d.hh"
#include "Ravl/Array1dIter.hh"

#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"	// RGB integer value class
#include "Ravl/Image/RGBValue.hh"	// RGB integer value class
#include "Ravl/Image/ImgIO.hh"		// for InitDPImageIO()
#include "Ravl/DP/FileFormatIO.hh"	// for load / save functions

#include "Ravl/Calls.hh"
#include "Ravl/GUI/Manager.hh"

#include "Robot_Control.hh"
#include "Robot_Position.hh"
#include "GUI_Functions.hh"

#include <iostream>
#include <stdio.h>

using namespace RavlN;
using namespace RavlImageN;
using namespace RavlGUIN;
using namespace HollyN;

Robot_ControlC my_robot;				// the robot
HashC<StringC,CallFunc1C<const StringC&,int> > commands;	// commands hash table

ImageC < ByteRGBValueC > current_image;			// file with current image stored in
Point2dC current_position;
RealT current_heading;
IntT distCommand;
IntT distRotation;
IntT pan;
IntT movenum;

DListC < Robot_PositionC > robot_data;	// storing images and info whilst moving
int num_images;

GUI_FunctionsC viewer;

// Set up command functions
void SetupCommand( const StringC &cmd, int (*func)(const StringC & arg) )
{
  commands[cmd] = CallFunc1C<const StringC&, int>(func,StringC());
}

// Gets command from the input, returns command and argument
int Get_Command( StringC &command, StringC &argument )
{
  StringC str;
  // get string from input until \n character
  readline( cin, str );

  // given a string str to be split into command and argument
  StringC results[2];
  split( str, results, 2, StringC(' ') );

  command = results[0];
  argument = results[1];
  
  return 0;
}


int DoConnect( const StringC &str )
{
  if( my_robot.Robot_Connected() )
    cerr << "We are already connected to holly" << endl;
  else if( my_robot.Start_Robot() < 0 )
    cerr << "Failed to start robot\n";
  else
    cerr << "Connected to the robot\n";

  return 0;
}

int DoDisconnect( const StringC &str )
{
  if( !my_robot.Robot_Connected() )
    cerr << "We aren't connected to the robot" << endl;
  else if( my_robot.Shutdown_Robot() < 0 )
    cerr << "Failed to shutdown robot" << endl;
  else
    cerr << "Successfully disconnected from the robot\n";

  return 0;
}

int DoExit( const StringC &str )
{
  // exit from the robot
  DoDisconnect(str);
  return -1;
}

int DoStartCamera( const StringC &str )
{
  if( !my_robot.Robot_Connected() )
    cerr << "We aren't connected to the robot" << endl;
  // start the camera
  if( my_robot.Start_Camera() < 0 )
    cerr << "Failed to start the camera\n";
  else
    cerr << "Successfully started the camera\n";

  return 0;
}

// Set the maximum translational speed
int DoTSpeed( const StringC &str )
{
  if( !my_robot.Robot_Connected() )
    cerr << "We aren't connected to the robot" << endl;
  else
  {
    if( str.Size() == 0 )
      cerr << "No argument provided" << endl;
    else
    {
      // set maximum velocity
      my_robot.Set_Max_Velocity( str.IntValue() ); 
    }
  }
  return 0;
}

// Set the maximum rotational speed
int DoRSpeed( const StringC &str )
{
  if( !my_robot.Robot_Connected() )
    cerr << "We aren't connected to the robot" << endl;
  else
  {
    if( str.Size() == 0 )
      cerr << "No argument provided" << endl;
    else
    {
      // set maximum velocity
      my_robot.Set_MaxRot_Velocity( str.IntValue() ); 
    }
  }
  return 0;
}

// move by number of mm given in str
int DoMove( const StringC &str )
{
  if( !my_robot.Robot_Connected() )
    cerr << "We aren't connected to the robot" << endl;
  else
  {
    if( str.Size() == 0 )
      cerr << "No argument provided" << endl;
    else
    {
      // pan camera by number of degrees given in str
      cerr << "Going to move robot by " << str.IntValue() << " mm" << endl;
      my_robot.Move_By( str.IntValue() ); 
    }
  }

  return 0;
}

int DoRotateBy( const StringC &str )
{
  // rotate robot by number of degrees given in str
  if( !my_robot.Robot_Connected() )
    cerr << "We aren't connected to the robot" << endl;
  else
  {
    if( str.Size() == 0 )
      cerr << "No argument was entered" << endl;
    else
    {
      // rotate robot by number of degrees given in str
      cout << "Going to rotate robot by " << str.IntValue() << " degrees" << endl;
      my_robot.Rotate_By( str.IntValue() );
    }
  }

  return 0;
}

int DoRotateTo( const StringC &str )
{
  // rotate robot to number of degrees given in str
  if( !my_robot.Robot_Connected() )
    cerr << "We aren't connected to the robot" << endl;
  else
  {
    if( str.Size() == 0 )
      cerr << "No argument was entered" << endl;
    else
    {
      // rotate robot to degrees given in str
      cout << "Going to rotate robot to " << str.IntValue() << " degrees" << endl;
      my_robot.Rotate_To( str.IntValue() );
    }
  }

  return 0;
}


// Stop the robot
int DoStop( const StringC &str )
{
  // stop the robot
  if( !my_robot.Robot_Connected() )
    cerr << "We aren't connected to the robot" << endl;
  else
  {
    my_robot.Stop();
    cerr << "Stopped robot" << endl;
  }

  return 0;
}

int DoPan( const StringC &str )
{
  if( !my_robot.Robot_Connected() )
    cerr << "We aren't connected to the robot" << endl;
  else if( !my_robot.Camera_Connected() )
    cerr << "We aren't connected to the camera" << endl;
  else
  {
    if( str.Size() == 0 )
      cerr << "No argument was entered" << endl;
    else
    {
      cerr << "Argument was entered" << endl;
      // pan camera by number of degrees given in str
      my_robot.Set_Pan( str.IntValue() );
      cerr << "Panned the camera to " << str.IntValue() << " deg" << endl;
    }
  }

  return 0;
}

int DoTilt( const StringC &str )
{
  if( !my_robot.Robot_Connected() )
    cerr << "We aren't connected to the robot" << endl;
  else if( !my_robot.Camera_Connected() )
    cerr << "We aren't connected to the camera" << endl;
  else
  {
    if( str.Size() == 0 )
      cerr << "No argument was entered" << endl;
    else
    {
      cerr << "Argument was entered" << endl;
      // pan camera by number of degrees given in str
      my_robot.Set_Tilt( str.IntValue() );
      cerr << "Tilted the camera to " << str.IntValue() << " deg" << endl;
    }
  }

  return 0;
}

int DoZoom( const StringC &str )
{
  if( !my_robot.Robot_Connected() )
    cerr << "We aren't connected to the robot" << endl;
  else if( !my_robot.Camera_Connected() )
    cerr << "We aren't connected to the camera" << endl;
  else
  {
    if( str.Size() == 0 )
      cerr << "No argument was entered" << endl;
    else
    {
      // zoom camera to value given
      my_robot.Set_Zoom( str.IntValue() );
      cerr << "Zoomed the camera to " << str.IntValue() << endl;
    }
  }

  return 0;
}

int DoTestPan( const StringC  &str )
{
  if( !my_robot.Robot_Connected() )
    cerr << "We aren't connected to the robot" << endl;
  else if( !my_robot.Camera_Connected() )
    cerr << "We aren't connected to the camera" << endl;
  else
  {
    cerr << "Be ready to press a key and hit return when first and second pan have finished" << endl;
    my_robot.Pan_Timing();
  }
  return 0;
}


int DoTestImages( const StringC  &str )
{
  if( !my_robot.Robot_Connected() )
    cerr << "We aren't connected to the robot" << endl;
  else if( !my_robot.Camera_Connected() )
    cerr << "We aren't connected to the camera" << endl;
  else
  {
    my_robot.Image_Timing();
  }
  return 0;
}

int DoMoveGrab( const StringC  &str )
{
  if( !my_robot.Robot_Connected() )
    cerr << "We aren't connected to the robot" << endl;
  else if( !my_robot.Camera_Connected() )
    cerr << "We aren't connected to the camera" << endl;
  else
  {
    // Capture an image, get position
    cerr << "Enter a distance to move: ";
    IntT distance = 0;
    cin >> distance;
    cerr << "\nEnter an angle to move: ";
    IntT angle = 0;
    cin >> angle;
    cerr << "\nEnter pan angle: ";
    IntT pan = 0;
    cin >> pan;
    VectorC newinfo(4);
    ImageC <ByteRGBValueC> new_image;
    my_robot.Move_Grab( distance, angle, pan, newinfo, new_image );
    current_image = new_image;

    viewer.Display_Image( current_image );
    // Add image and position into list
#if 0
    IntT panangle, tilt, zoom;
    my_robot.Where_Camera( panangle, tilt, zoom );
    Robot_PositionC pos1( 0, 0, 0, current_position, current_heading, panangle, current_image );
#endif
    // Add new information into database(!)
    //robot_data += pos1; 
    char next_name[20];
    sprintf( next_name, "image_%03d.ppm", num_images++ );
    Save( next_name, current_image );
  }

  return 0;
}

int DoSave( const StringC  &str )
{
  if( str.Size() == 0 )
    cerr << "No filename argument was entered" << endl;
  else
  {
    // Load the image from file
    if(!Save(str, current_image))
    {
      cerr << "Failed to save the input file." << endl;
    }
  }

  return 0;
}

int DoLoadImage( const StringC  &str )
{
  if( str.Size() == 0 )
    cerr << "No filename argument was entered" << endl;
  else
  {
    // Load the image from file
    if(!Load(str, current_image))
    {
      cerr << "Failed to load the input file." << endl;
      return 0;
    }
    else
    {
      cerr << "Loaded image: " << str << endl;
      cerr << "Please tell me where I am" << endl;
    }
  }
  return 0;
}

int DoWhereRobot( const StringC  &str )
{
  if( !my_robot.Robot_Connected() )
    cerr << "We aren't connected to the robot" << endl;
  else
  {
    cout << "Robot is at : ";
    my_robot.Where( current_position, current_heading );
    int pan, tilt, zoom;
    my_robot.Where_Camera( pan, tilt, zoom );
    cout << "Odometry: " << current_position << "," << current_heading << ", pan: " << pan << endl;
    Point2dC cam_position;
    RealT cam_heading;
    Robot_to_Camera( current_position, current_heading, pan, cam_position, cam_heading );
    cout << "Camera: " << cam_position << "," << cam_heading << endl;
    cout << endl;
  }

  return 0;
}

// move by number of mm given in str
int DoMove_Metre( const StringC  &str )
{
  if( !my_robot.Robot_Connected() )
    cerr << "We aren't connected to the robot" << endl;
  else
  {
    if( str.Size() == 0 )
      cerr << "No argument provided for rotation and line_number" << endl;
    else
    {
      StringC results[3];
      split( str, results, 3, " ");

      int distance = results[0].IntValue();
      int rotation = 0;
      cout << "Enter the rotation: ";
      cin >> rotation;
      cout << "\nthanks...\n";

      cout << "Information you entered: distance: " << distance << "; rotation: "
	      << rotation << endl;

      cerr << "Going to rotate by: " << rotation << endl;
      my_robot.Rotate_To( rotation );
      // While we are still moving, pan the camera back to off central point
      my_robot.Set_Pan( 60 ); // LOOK RIGHT
      while( !my_robot.Not_Rotating() )
      {
	//cout << "The robot is still rotating..." << endl;
	Sleep(0.1); // same as paiPause(100)
      }
      cerr << "Robot should have rotated and panned... going to move now\n";

      // move robot
      my_robot.Move_By( distance ); // move robot by distance
      Sleep( 0.100 );
      int num_images_taken = 0;
      // While we are still moving
      while( !my_robot.Not_Moving() )
      {
        cerr << "Robot is still moving, grab three images" << endl;
	for( int i=0; i<3; i++ )
	{
	  // Capture an image, get position
	  my_robot.Capture( current_image, current_position , current_heading);
	  num_images_taken++;
	  // Add image and position into list
    IntT panangle, tilt, zoom;
    my_robot.Where_Camera( panangle, tilt, zoom );
    Robot_PositionC pos1( 0, 0, 0, current_position, current_heading, panangle, current_image );
	  // Add new information into database(!)
	  robot_data += pos1; 
	}

	// Pan the camera left/right
	int pan_angle = (int)Pow(-1,num_images_taken)*60;
	cout << "Setting pan to: " << pan_angle << endl;
	my_robot.Set_Pan( pan_angle );
	Sleep( 0.500 );
	cerr << "panning the camera" << endl;

      } // end of while robot is still moving
      cerr << "Robot has stopped moving.... returning\n";

    }
  }

  return 0;
}

int Do_Clear_Data( const StringC  &str )
{
  robot_data.Empty();
  return 0;
}

int Do_Save_Data( const StringC &str )
{
  if( str.Size() == 0 )
    cerr << "No filename argument was entered" << endl;
  else
  {
    // For each element in robot_data, save image, write odometry etc
    char basename[50];
    strcpy(basename,str);

    // clear datafile
    char cmd[100];
    strcpy(cmd,"rm ");
    strcat(cmd,basename);
    system(cmd);
    
    cerr << "writing data into <" << basename << '<' << endl;
    char next_name[100];
    int i=0;
    for( DLIterC <Robot_PositionC> it(robot_data); it.IsElm(); it++ )
    { 
      sprintf( next_name, "%s%03d.ppm", basename, i++ );
      it->Save_Image( next_name );
      //it->Write_Data( basename, next_name );
    }
  }
 
  return 0;
}


int DoHelp( const StringC  &str )
{
  // print usage information
  cout << "Command summary: " << endl
	  << "connect\t-Connect to the robot\n"
	  << "disconnect\t\t-disconnect from the robot\n"
	  << "exit\t\t-Quit from program\n"
	  << "startcam\t\t-Start the camera up\n"
	  << "maxtspeed <x>\t\t-set maximum translational velocity to <x>mm/sec\n"
	  << "maxrspeed <x>\t\t-set maximum rotational velocity to <x>deg/sec\n"
	  << "move <x>\t\t-move the robot by <x> mm\n"
	  << "rotateby <x>\t\t-rotate the robot base by <x> degrees\n"
	  << "rotateto <x>\t\t-rotate the robot base to <x> degrees\n"
	  << "stop\t\t-stop the robot\n"
	  << "pan <x>\t\t-pan the camera by <x> degrees (+cw,-ccw)\n"
	  << "tilt <x>\t\t-tilt the camera by <x> degrees (+up,-down)\n"
	  << "zoom <x>\t\t-zoom the camera to <x> value (min - max)\n"
	  << "testpan\t\t-test panning of camera\n"
	  << "testimages\t\t-runs the test image function to work out timing of image grabbing, 20 images\n"
	  << "grab\t\t-Grab an image (requests movement commands first)\n"
	  << "save\t\t-Save the last image\n"
	  << "loadimage <filename>\t\t-Load an image file from <filename>\n"
	  << "whereami\t\t-Prints out current robot position\n"
	  << "move1m <dist> <angle>\t\t-Prints out current robot position\n"
	  << "cleardata\t\t-clears the information we have about the robot's positions & images\n"
	  << "savedata\t\t-saves the information we have about the robot's positions & images into <basefile>\n"
	  << "help\t\t-Prints this usage information\n";

  return 0;
}

// Initialise commands for user
void InitCommands()
{
  SetupCommand("connect", & DoConnect); // <machine> machine to connect to, options: "holly" "simulator"
  SetupCommand("disconnect", DoDisconnect); // <machine> machine to connect to, options: "holly" "simulator"
  SetupCommand("exit", DoExit); // quit from program
  SetupCommand("startcam", DoStartCamera);	// start camera
  SetupCommand("maxtspeed", DoTSpeed); // Set maximum translation velocity to <x> mm/sec
  SetupCommand("maxrspeed", DoRSpeed); // Set maximum rotational velocity to <x> deg/sec
  SetupCommand("move", DoMove); // <x> move by x mm in the current direction
  SetupCommand("rotateby", DoRotateBy); // <x> rotate by x degrees (-cw, +ccw)
  SetupCommand("rotateto", DoRotateTo); // <x> rotate to x degrees (-cw, +ccw)
  SetupCommand("stop", DoStop); // stop robot moving
  SetupCommand("pan", DoPan);	// <x> pan to angle x degrees (absolute position) (+cw, -ccw)
  SetupCommand("tilt", DoTilt);	// <x> pan to angle x degrees (absolute position) (+cw, -ccw)
  SetupCommand("zoom", DoZoom);	// <x> zoom to value
  SetupCommand("testpan", DoTestPan);	// pan camera to 0, pan to -10, pan to +10... get timing
  SetupCommand("testimages", DoTestImages);	// grab images: getting timing
  SetupCommand("grab", DoMoveGrab);	// grab an image
  SetupCommand("save", DoSave);	// grab an image
  SetupCommand("loadimage", DoLoadImage);	// load an image
  SetupCommand("whereami", DoWhereRobot);	// get position of robot
  SetupCommand("move1m", DoMove_Metre); // <x> move by x mm in the current direction
  SetupCommand("cleardata", Do_Clear_Data);	// pan camera to 0, pan to -10, pan to +10... get timing
  SetupCommand("savedata", Do_Save_Data);	// pan camera to 0, pan to -10, pan to +10... get timing
  SetupCommand("help", DoHelp);	// print command list to screen
  num_images = 0;
}

int Execute(const StringC &cmd,StringC &data) {
  CallFunc1C<const StringC&, int> cf = commands[cmd];
  if(!cf.IsValid()) {
    	cerr << "Unknown command '" << cmd << "'\n";
	return 0;
  }
  return cf.Call(data);
}



int main(int argc, char *argv[])
{
  Manager.Execute();
  InitCommands();

  viewer.Start_Window( Index2dC( current_image.Rows(), current_image.Cols() ), Index2dC(10,10) );

  for( int i=0; i<50; i++ ) // while valid commands have been sent
  {
    StringC cmd;
    StringC data;
    cout << "my_robot.Not_Moving(): " << my_robot.Not_Moving()
	    << ", now_rotating?: " << my_robot.Not_Rotating() << endl;

    cout << "--holly---->";
    // get entry from stdin and split into command and string
    Get_Command( cmd, data );

    if( Execute( cmd, data ) < 0 )
    {
      return -1;
    }
    
  }
  cerr << "Kill the manager - your 50 moves are up\n";

  Manager.Wait();
  return 0;
}




