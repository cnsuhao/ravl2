#!/usr/bin/perl
# qlibs.pl
#
#
# This program works out the libraries needed to compile RAVL/RAVL programs.
# author: Kieron Messer
# date:   3 April 2001

use Getopt::Long;

$QMAKE_INSTALL_DIR = "/vol/vssp/local/beta";
$BASE_INSTALL_DIR = "$QMAKE_INSTALL_DIR/../../..";

$opts = $#ARGV;
#--------- Options  ---------------------------------------------------
$res = GetOptions('w:s', 'p:s', 'hf:s', 'i:s', 'use:s', 'prog:s', 'd', 'v');


#--------- Usage   ----------------------------------------------------
if ($res!=1)
{
  print"\n" if ($res != 1);
  print"usage:\n";
  print" qlibs.pl\n";
  print"  -w              Working directory\n";
  print"  -p              Local Project Out directory\n";
  print"  -hf             Hints file to use\n";
  print"  -use            Output libraries used in current libraries\n";
  print"  -prog           Output Libraries used in the current executable\n";
  print"  -d              Output definitions suitable for a .def file\n";
  print"  -v              Verbose\n";

  exit(-1);
}

# First lets sort out the Lib Hints File
if(!defined($opt_hf)) {
  $libhints = "$BASE_INSTALL_DIR/lib/RAVL/libdep";
} else {
  if(-f $opt_hf) {
    $libhints = $opt_hf;
  } else {
    print "Error no such file exists for libhints: $opt_hf\n";
    exit(-1);
  }
}

# Next lets sort out the global project out
$glob_proj = "$BASE_INSTALL_DIR/include";

# Next we can sort out the local project out
if(!defined($opt_p)) {
  $loc_proj = "$ENV{'PROJECT_OUT'}/include";
} else {
  if(-d $opt_p) {
    $loc_proj = "$opt_p/include";
  } else {
#    print "Error no such directory exists for local project out: $opt_p\n";
    exit(-1);
  }
}

# Next we can sort out the working directory
if(!defined($opt_w)) {
  $work_dir = ".";
} else {
  if(-d $opt_w) {
    $work_dir = $opt_w
  } else {
    print "Error no such directory exists for working dir: $opt_w\n";
    exit(-1);
  }
}

# If in verbose mode then print out soe useful information
if(defined($opt_v)) {
  print "Working Directory: $work_dir\n";
  print "Global Project Out: $glob_proj\n";
  print "Local  Project Out: $loc_proj\n";
  print "Lib Hints File being used: $libhints\n";
}


# now lets load the lib hints file
%hints = LoadLibHints();

# We need to find USESLIBS from HEADERS and SOURCES tags in defs.mk
@SOURCES = findindefs($work_dir, "defs.mk", "SOURCES");
@HEADERS = findindefs($work_dir, "defs.mk", "HEADERS");

for $file (@SOURCES) {
  $extrauseslibs .= $extrauseslibs . " " . getUseslibs($file);
}

push(@HEADERS, @SOURCES);

for $file (@HEADERS) {
  @incs = getInclude($work_dir, $file);
  for $include (@incs) {
    if($lut{$include} != 1) {
      $lut{$include} = 1;
    }
  }
}

$Libs = getLibs(keys %lut);
$Libs .= $Libs . " " . $extrauseslibs;
@words = split(' ', $Libs);
@words = sort @words;

for $f (@words) {
  $useslibs = "$useslibs $f" if(($useslibs =~ m/$f/s)==0);
}


# We need to find PROGLIBS from MAINS
@MAINS = findindefs("$work_dir", "defs.mk", "MAINS");
@EXAMPLES = findindefs("$work_dir", "defs.mk", "EXAMPLES");
push(@MAINS, @EXAMPLES);
@TESTEXES = findindefs("$work_dir", "defs.mk", "TESTEXES");
push(@MAINS, @TESTEXES);

for $file (@MAINS) {
#  print "opening file: $file\n";
  @incs = getInclude($work_dir, $file);
  $tmpprog = getUseslibs($file);
  $proguseslibs .= $proguseslibs . " " . $tmpprog;
  for $include (@incs) {
    if($lup{$include} != 1) {
      $lup{$include} = 1;
    }
  }
}


$Libs = getLibs(keys %lup);
$Libs .= $Libs . " " . $proguseslibs;
@words = split(' ', $Libs);
@words = sort @words;

for $f (@words) {
  $proglibs = "$proglibs $f" if((($proglibs =~ m/$f/s)==0) && ((($useslibs =~ m/$f/s)==0)));
}

# need to take out PLIB
$plib = getPLIB("$work_dir/defs.mk");
$useslibs =~ s/$plib//g;

# now we can print format the results according to the options specified
if(!defined($opt_d)) {
  $useslibs = "USESLIBS= $useslibs";
  $proglibs = "PROGLIBS= $proglibs";
} else {
    $u = " ";
    $p = " ";

    for $l (split(' ', $useslibs)) {
	$u = $u." $l.def";
    }
    $useslibs = $u;

    for $l (split(' ', $proglibs)) {
	$p = $p." $l.def";
    }
    $proglibs = $p;
}


if(defined($opt_use)) {
  print "$useslibs\n";
} elsif(defined($opt_prog)) {
  print "$proglibs\n";
} else{
  print "$useslibs\n";
  print "$proglibs\n";
}


#------------------------------------------------
# SUBROUTINES
#------------------------------------------------

#-------------------------------------------------
# getInclude(workingDir, file)
#
# routine which goes thru all lines in a file and
# searches for all the includes

sub getInclude {
  $wd = $_[0];
  $file = $_[1];
  open FILE, "$wd/$file" or die "can not open: $_[0]";
  local @lines = <FILE>;
  close FILE;
  chomp @lines;

  for $line (@lines) {
    if($line =~ m/include/g) {
      ($q1, $ins) = ($line =~ /([\"<])([a-z\/A-Z.0-9]+)/);
      #print "$q1 $ins\n";
      push (@inc, $ins);
    }
  }

  return @inc;
}


#-------------------------------------------------
# getLibs(list of headers)
#
# this routine looks through the headers in the local
# project out and the RAVL project out
sub getLibs {
  local $lib;
  local $inc;

  for $inc (@_) {

    # first look in lib hints hash
    if($hints{$inc} ne "") {
      $libs .= "$hints{$inc} ";
    }
    # else look in local PROJECT_OUT
    elsif(-f "$loc_proj/$inc") {
      #print "found locally: $inc\n";
      $lib = getLib("$loc_proj/$inc");
      $libs .= "$lib " if($lib ne "");
    }
    # else look in RAVL installation
    elsif(-f "$glob_proj/$inc") {
      #print "found globally: $inc\n";
      $lib = getLib("$glob_proj/$inc");
      $libs .= "$lib " if($lib ne "");
    }
    # can not find but we do not produce an error
    else {
      #print "$inc not found\n";
    }
  }

  return $libs;
}

#-------------------------------------------------
# getLib(name of header)
#
# this routine looks through a file for the //! lib=
# and returns the first one it finds
sub getLib {
  local $lib;
  local $line;
  local $lines;

  open FILE, $_[0] or die "can not open: $_[0]";
  local @lines = <FILE>;
  close FILE;
  chomp @lines;
  $beg = "//!";
  for $line (@lines) {
    if($line =~ m/$beg/g) {
      if(($line =~ m/lib/g)) {
	($pre, $lib) = split('=', $line);
	#print "found lib: $lib\n";
	return $lib;
      }
    }
  }
}

#-------------------------------------------------
# getUseslibs(name of source file)
#
# this routine looks through a file for the //! useslibs=
# and returns the first one it finds
sub getUseslibs {
  local $lib;
  local $line;
  local $lines;

  open FILE, $_[0] or die "can not open: $_[0]";
  local @lines = <FILE>;
  close FILE;
  chomp @lines;
  $beg = "//!";
  for $line (@lines) {
    if($line =~ m/$beg/g) {
      if(($line =~ m/useslibs/g)) {
	($pre, $lib) = split('=', $line);
	if(($lib =~ m/\"(.*)\"/g)) {
	  $lib = $1;
	}
	#print "found lib: $lib\n";
	return $lib;
      }
    }
  }
}

#-------------------------------------------------
# LoadLibHints(name of lib hints file)
#
# Loads the libhints file into a global hash
sub LoadLibHints {
  local $line;
  local @lines;
  local @lib;

  open FILE, $libhints or return;
  local @lines = <FILE>;
  close FILE;
  chomp @lines;
  $h = "#";
  for $line (@lines) {

    if(!(($line =~ m/$h/g)>0)) {

      ($lib, @rest) = split(' ', $line);
      for $r (@rest) {
	$hsh{$r} = $lib;
      }
    }
  }
  return %hsh;
}

#-------------------------------------------------
# findindefs(working dir, filename, tag)
#
# this searches thru a defs.mk file and returns the line
# according to the tag
sub findindefs {

  $wd = $_[0];
  $filename = "$wd/$_[1]";
  open DEFS, $filename or die "can not open: $_[0]/$_[1]";
  local @defs = <DEFS>;
  close DEFS;
  chomp @defs;

  local $FIND=$_[2];  # FILES can be split over multiple lines
  $FILES="";
  local $read=0;
  local $c = '\\\\';

  for $line (@defs) {

    split (" ", $line);
    if($_[0] =~ s/\A$FIND//g) {
      $read=1;
    }

    if($read==1) {

      $files = join(" ", @_);
      $files =~ s/=//g; # get rid of annoying equals
      $files =~ s/$c//g; # get rid of annoying \ at end of lines
      @file = split(' ', $files);

      foreach $src (@file) {

	if ((-f "$wd/$src") || ($FIND eq "PACKAGE")) {
	  $FILES .="$src ";  # append directory onto string
	} else { # assume we've reached end of FILES section
	  $read=0;
	  last;
	}
      }
    }

  }

  return split(' ', $FILES);
}

#-------------------------------------------------
# getPLIB(filename)
#
# returns the PLIB tag in defs.mk file
sub getPLIB {
  local $file = $_[0];
  local $line, @tag, @defs;

  open DEFS, $file or die "can not open: $file";
  @defs = <DEFS>;
  close DEFS;
  chomp @defs;

  for $line (@defs) {
    @tag = split ((' '), $line);
    $line = join("", @tag);
    if($line =~ s/\APLIB//g) {
      $line =~ s/=//g; # get rid of annoying equals
      return $line;
      last;
    }
  }
}
