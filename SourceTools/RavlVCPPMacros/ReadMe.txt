The following macros are available for use with Visual Studio .Net
to install Ravl header files to the target inc\Ravl\ directory.

BuildSelection()
================
Highlight a project and use BuildSelection() to build a Ravl library
without linking dependent projects. The headers for all dependent 
libraries are installed first, dependencies are then switched off and 
the project is built.
Warning: if the build crashes the macro will not reinstate the dependencies!

InstallHeaders()
================
Highlight a project and use InstallHeaders() to install all the headers
for a specific project.

InstallAllHeaders()
================
Use InstallAllHeaders() to install the headers for all Ravl libraries.


These macros are provided to overcome the problem of setting project
dependencies for static libraries. Header installation is performed
in the custom build step for the header files, so to ensure all necessary
headers are installed when building a library all the dependent libraries
have to be built as well. This is automated by setting up project
dependencies. However, this causes the libraries to be linked together,
leading to large libraries and lots of multiply defined symbols. 
One option is to remove all the dependencies from the libraries and 
build them one by one in the correct order. These macros are provided 
so that you can leave the dependency structure in place and build 
without linking in dependent projects.


Notes:

1. To install the macros, place the RavlVCPPMacros directory in 
VisualStudioProjects\VSMacros71. Go to the Tools menu and select
Macros->Load Macro Project and open RavlVCPPMacros\RavlMacroProject.vsmacros

2. To view the macros go to the Tools menu and select Macros->Macros Explorer

3. To bind a macro to a toolbar button right click on the toolbar and select
customize. Go to the commands tab, scroll down to macros and then drag the 
macro you want on the toolbar. You can edit the display options for the macro
button by right clicking on it when the customize window is up.