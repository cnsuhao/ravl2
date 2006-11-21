
Some quick notes on building RAVL on windows:

Prerequisites:

RAVL Requires Visual Studio 2005, with Visual C++ to compile.


I'd recommend tortoisesvn for dealing with subversion repositories on windows, its very nice! 

  http://tortoisesvn.tigris.org/


1) You'll need to checkout the following to a directory on your hard drive.   I use C:\src\Ravl


https://svn.sourceforge.net/svnroot/ravl/main/Ravl


2) To compile the RAVL you need a few libraries lucky they've been put together into one package 'Glade for Windows'

Can be found at: http://gladewin32.sourceforge.net/

Download the latest package called: 'Gtk+/Win32 Development Environment'

Install it to: C:\GTKWIN32  (this isn't the default install location, but its where the project files are configured to look)

3) You should be able to open Visual Studio, then open the solution file in     C:\src\Ravl\MSVC\Ravl.sln

Then select,  'Build Solution' in the usual way.  

The libraries are built to: C:/Build

You can build executables by including the appropriate project file's from C:\src\Ravl\MSVC\Mains, C:\src\Ravl\MSVC\Examples, or C:\src\Ravl\MSVC\Tests.   You will have to set the library dependancies manually, A list of the direct dependancies can be found in the defs.mk files in the same directory as the source for the executable. 


If you want to build a seperate project using RAVL you'll have to add two include paths.  C:\src\Ravl\MSVC\include\Win32 and C:\src\Ravl\MSVC\include, in that order.
