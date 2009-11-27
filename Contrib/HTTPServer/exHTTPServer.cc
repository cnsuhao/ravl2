// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////////////////
//! rcsid = "$Id: exHTTPServer.cc 5602 2006-06-19 09:14:19Z craftit $"
//! lib = RavlEHS
//! author = "Warren Moore"

#include "Ravl/Option.hh"
#include "Ravl/OS/Date.hh"
#include "Ravl/HTTPServer.hh"

using namespace RavlN;

bool OnHandle(HTTPRequestC &request, HTTPResponseC &response, HTTPResponseCodeT &retcode)
{
  // Create the response
  StringC text("<html>\n<head>\n<title>\nRavl HTTPServer\n</title>\n</head>\n<body>\n<h1>\nRavl HTTPServer\n</h2>\n");
  text += StringC("<table border='1'>\n<tr><td>\nRequest URI\n</td><td>\n");
  text += request.URI();
  text += StringC("</td></tr>\n</table></body>\n</html>");
  
  // Set the response
  response.SetText(text);
  
  // Set the return code
  retcode = EHTTPResponseCode_200_Ok;
  
  return true;
}

bool OnHandleChild(HTTPRequestC &request, HTTPResponseC &response, HTTPResponseCodeT &retcode)
{
  // Create the response
  StringC text("<html>\n<head>\n<title>\nRavl Child HTTPServer\n</title>\n</head>\n<body>\n<h1>\nRavl Child HTTPServer\n</h2>\n");
  text += StringC("<table border='1'>\n<tr><td>\nRequest URI\n</td><td>\n");
  text += request.URI();
  text += StringC("</td></tr>\n</table></body>\n</html>");
  
  // Set the response
  response.SetText(text);
  
  // Set the return code
  retcode = EHTTPResponseCode_200_Ok;
  
  return true;
}


int main(int argc, char **argv)
{
  // Process the options
  OptionC opt(argc, argv);
  IntT port = opt.Int("port", 8080, "Port.");
  opt.Check();
  
  // Construct the server
  cerr << "Starting server on port " << port << "." << endl;
  HTTPServerC server(port);
  Connect(server.SigHandle(), &OnHandle);
  Connect(server.SigHandlePath("child"), &OnHandleChild);
  
  // Start the server
  bool ret = server.Start();

  // Keep the app running
  while (1)
  {
    Sleep(1);
  }

  // Stop the server
  server.Stop();
  cerr << "Server stopped." << endl;
  
  return (ret ? 0 : 1);
}

