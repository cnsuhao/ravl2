// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2004, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlNet
//! file="Ravl/OS/Network/testSocket.cc"

#include "Ravl/Option.hh"
#include "Ravl/Threads/LaunchThread.hh"
#include "Ravl/OS/Socket.hh"
#include "Ravl/Stream.hh"
#include "Ravl/OS/Date.hh"
#include "Ravl/Random.hh"
#include "Ravl/Threads/Semaphore.hh"
#include "Ravl/Threads/Mutex.hh"

//#include <signal.h>

using namespace RavlN;

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x) 
#endif

StringC address;
bool buffer;
int g_totalSize = 100000;
bool testFreeze = false;
SemaphoreC serverReady(0);
SemaphoreC serverCanClose(0);
int timeout = 1;
volatile bool error = false;
MutexC g_consoleMutex;	//Only one thread can write to the console at the same time

void WriteToConsole(StringC strMsg)
{
	MutexLockC consoleLock(g_consoleMutex);
	cerr << strMsg;
}

bool TransmitThread() 
{
	//Open a connection to the server
	WriteToConsole("Opening server socket\n");
	SocketC acceptSocket;
    SocketC serverSocket(address,true);
  if(!serverSocket.IsOpen()) 
  {
    error = true;
    return true;
  }
  //Semaphore
  serverReady.Post(); 
  acceptSocket = serverSocket.Listen();
  acceptSocket.SetNonBlocking(true);
  acceptSocket.SetWriteTimeout(timeout);

  //acceptSocket.ConnectedHost();
  //acceptSocket.ConnectedPort();

  WriteToConsole("Transmit starting. \n");
  for(int i = 0;i < g_totalSize && ! error;) 
  {
	  //Construct three int arrays
    int a[257],b[257],c[257];

	//Initialise the first b1s elements of int array, a
    int b1s = Round(Random1() * 255) + 1;
    for(int k = 0;k < b1s;k++)
	{
      a[k] = i++;
	}

	//Initialise the first b2s elements of int array, b
    int b2s = Round(Random1() * 255) + 1;
    for(int k = 0;k < b2s;k++)
	{
      b[k] = i++;
	}
	//Initialise the first b3 elements of int array, c
    int b3s = Round(Random1() * 255) + 1;
    for(int k = 0;k < b3s;k++)
	{
      c[k] = i++;
	}
	//Initialise the buffers and lengths that we're about to transmit
    char *bufs[3];
    int lens[3];
    bufs[0] = (char *) a;
    lens[0] = sizeof(int) * b1s;
    bufs[1] = (char *) b;
    lens[1] = sizeof(int) * b2s;
    bufs[2] = (char *) c;
    lens[2] = sizeof(int) * b3s;

	//Sum up the total length of all the buffers
    int total = lens[0] + lens[1] + lens[2];

	//Write the buffers and get back the number of bytes written
    int n = acceptSocket.WriteV((const char **) bufs,lens,3);
		
    if(n != total) 
	{
		char strError[256];
		sprintf(strError, "Num bytes: array1: %i, array2: %i, array3: %i \n", lens[0], lens[1], lens[2]);
		WriteToConsole(strError);
		sprintf(strError, "WriteV(), ERROR: Data size(bytes)=%i num bytes written=%i \n", total, n);
		WriteToConsole(strError);
		error = true;
      break;
    }
    //if(Random1() < 0.3)
    // Sleep(0.1);
  }
  WriteToConsole("Transmit done. \n");
 // RavlN::Sleep(5);
 // Sleep((DWORD) 5000);
  //Prevent this thread from finishing before the client
  serverCanClose.Wait();  
  return 0;
}

int RecieveThread() 
{
	//Open a client socket
	WriteToConsole("Opening client socket\n");
  SocketC clientSocket(address,false);
  
  //Check that the socket is open
  int n = 10;
  while(!clientSocket.IsOpen() && n-- > 0) 
  {
    WriteToConsole("RecieveThread(), Failed to open socket. Retrying. \n");
    Sleep(0.02);
    clientSocket = SocketC(address,false);
  }

  if(!clientSocket.IsOpen()) 
  {
    error = true;
    return __LINE__;
  }
  //Wait for a signal that the server is ready
  serverReady.Wait(); 
  clientSocket.SetNonBlocking(true);
  bool error = false;
  for(int i = 0;i < g_totalSize && !error;) 
  {
	  //Create three new arrays of equal size
    int a[257],b[257],c[257];

	//Generate numbers representing the number of bytes to read into each array
    int b1s = Round(Random1() * 256) + 1;
    int b2s = Round(Random1() * 256) + 1;
    int b3s = Round(Random1() * 256) + 1;

	//Initialise the buffers and lengths
    char *bufs[3];
    int lens[3];
    bufs[0] = (char *) a;
    lens[0] = sizeof(int) * b1s;
    bufs[1] = (char *) b;
    lens[1] = sizeof(int) * b2s;
	
    int total = lens[0] + lens[1];
    
	//Test the timeout function
	clientSocket.SetWriteTimeout(timeout);
	//Read the data into the buffer
	int n = clientSocket.ReadV(bufs,lens,2);
    if(n < total) 
	{
		char strError[256];
		sprintf(strError, "Error ReadV(), Total=%i n=%i i=%i\n", total, n, i);
		WriteToConsole(strError);
	}
      if(i > (g_totalSize - 256)) // Just end of stream ?
	  {
		  WriteToConsole("End of stream\n");
		  serverCanClose.Post();
		  return 0;
	  }
      if(n != total) 
	  {
		  WriteToConsole("Number of bytes read is incorrect\n");
		error = true;
		break;
      }

	  //Check that the data hasn't been corrupted
	  bool bDataIntegrityError = false;
		for(int k = 0;k < b1s;k++)
		{
			if(a[k] != i++) 
			{ 
				bDataIntegrityError = true; 
			}
		}

		for(int k = 0;k < b2s;k++)
		{
			if(b[k] != i++) 
			{ 
				bDataIntegrityError = true; 
			}
		}

		if(bDataIntegrityError)
		{
			WriteToConsole("Data integrity error 1\n");
		    error = true; 
			break; 
		}

		total = sizeof(int) * b3s;
		n = clientSocket.Read((char *) c,total);
		if(n < total) 
		{
			ONDEBUG(cerr << "Read(), Total=" << total << " n=" << n << " i=" << i << "\n");
		}
		if(i > (g_totalSize - 64)) // Just end of stream ?
		{
			WriteToConsole("End of stream\n");
			serverCanClose.Post();
			return 0;
		}
    
		for(int k = 0;k < b3s;k++)
		{
			if(c[k] != i++) 
			{ 
				WriteToConsole("Data integrity error 2\n");
				error = true; 
				break; 
			}
		}
		//cerr << "." << flush;
		if(Random1() < 0.4)
		{
			Sleep(0.1);
		}
		if(testFreeze)
		{
			break;
		}
  }

  if(testFreeze) 
  {
    WriteToConsole("Freezing reader thread. \n");
    while(testFreeze)
	{
		RavlN::Sleep(10000);
	}
  }
  
  if(error) 
  {
    WriteToConsole("Test failed. \n");
	serverCanClose.Post();
    return __LINE__;
  }
  WriteToConsole("Recieve done. \n");
  serverCanClose.Post();
  return 0;
}



int main(int nargs,char **argv)
{
  OptionC opts(nargs,argv);
  address = opts.String("h","localhost:20248","Network address to use. ");
  buffer = opts.Boolean("b",false,"Buffer. ");
  g_totalSize = opts.Int("s",10000,"Test size. ");
  testFreeze = opts.Boolean("f",false,"Test reader freeze. ");
  timeout = opts.Int("to",30,"Set write timeout. ");;
  opts.Check();
  
	  LaunchThread(&TransmitThread);
	  if(RecieveThread() != 0)
	  {
		StringC strTemp;
		cin >> strTemp;
		return 1;
	  }
	  if(error) 
	  {
		WriteToConsole("Test failed. \n");
		StringC strTemp;
		cin >> strTemp;
		return 1;
	  }

  WriteToConsole("Test succeeded\n");
  StringC strTemp;
  cin >> strTemp;
  return 0;
}
