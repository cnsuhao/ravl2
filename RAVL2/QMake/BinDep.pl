#!/usr/bin/perl

@searchDirs = ('/usr/lib64', '/usr/lib', '/lib' );
@ignoreLibs = {"m","c"};
@useLibs = {"c"};
%targLibs;
$verbose=0;

sub checkLib {
  my $libName = $_[0] . $_[1];
  if(exists $targLibs{$libName}) {
    print "$libName ";
    return 1;
  }
  if(-r $libName) {
    print "$libName ";
    return 1;
  }
  return 0;
}

# Search all known paths for the libraries.

sub findlib {
  my $libNameA = "/lib" . $_[0] . ".a";
  my $libNameSO = "/lib" . $_[0] . ".so";

  if(exists $ignoreLibs{$libName}) {
    return ;
  }
  if($verbose) {
    print stderr "Searching for lib$_[0].so or .a \n";
  }
  foreach(@searchDirs) {
    if(checkLib($_,$libNameSO)) {
      return ;
    }
    if(checkLib($_,$libNameA)) {
      return ;
    }
  }
  print stderr  "\nWarning: Unable to find library '$_[0]'\n";
}

sub PrintHelp {
  print "BinDep 1.2\n Some help: \n";
  print "  bindep [options] objectfiles \n";
  print "Options: \n";
  print "  -T(library name)  Specify a library that will be created soon. \n";
  print "  -L(directory)     Directory to seach for libraries. \n";
  print "  -l(library stem)  Stem of library name use in executable. \n";
  print "  -P(string)        Pass on string to stdout. \n";
  print "  -v                Verbose mode. \n";
  print " -I... -o... -O...  Are ingored. \n";
  exit ;
}

sub main {
  # Collect all directories to search.
  
  foreach (@ARGV) {
    if(/\A-L([^ ]*)/) {
      push searchDirs, $1 ;
      next ;
    }
    if(/\A-R([^ ]*)/) {
      push searchDirs, $1 ;
      next ;
    }
    if(/\A-n32/) {  # Irix new 32 bit mode ?
      push searchDirs, "/usr/lib32" ;
      next ;
    }
    if(/\A-64/) {  # Irix 64 bit mode ?
      push searchDirs, "/usr/lib64" ;
      next ;
    }
    if(/\A-v/) { # Verbose
      $verbose=1;
      next ;
    }
    if(/\A-h/) {  # Reqest for help.
      PrintHelp;
    }
  }

  if($verbose) {
    print stderr "Searching directories  '@searchDirs' \n";
  }
  
  # Go through libraries.
  
  foreach (@ARGV) {
    if(/\A-P(.*)/) { # Just pass on string.
      print $1 . " ";
      next ;
    }
    if(/\A-l([^ ]*)/) {
      findlib($1);
      next ;
    }
    if(/\A-T([^ ]*)/) {
      $targLibs{$1} = 1;
      next ;
    }
    if(/\A-64/ || /\A-n32/) { # Ignore these.
      next;
    }
    if(/\A-[WRLuIOvVgrpB][^ ]*/ )  { # Ignore these.
      next ;
    }
    if(/\A[^-][^ ]*/) { # Ingore direct dependancy on object files
      next ;
    }
    print stderr "Unknown argument $_\n ";
  }

  print "\n";
}

main();
