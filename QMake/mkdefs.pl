#!/usr/bin/perl

# Author: Kieron Messer
# Date  : August 2000

require 'getopt.pl';

if($#ARGV==-1) {
    print "\n\tmkdefs.pl -i dir\n";
    print "\nscript that creates a defs.mk file in dir (and subdirs of dir).\n";
    exit(-1);
}
Getopt('i');

mkdefs("$opt_i");


# subroutines
####################################################################
sub cfile {
  local @exts = split(('\.'), $_[0]);
  local $cext="c cc cpp cxx"; # allowable c or c++ extensions 
  $n=($cext =~ s/$exts[-1]//g);
  return 1 if($n>0);
  return 0;
}

sub hfile {
  local @exts = split(('\.'), $_[0]);
  local $cext="h hh"; # allowable header file extensions
  $n=($cext =~ s/$exts[-1]//g);
  return 1 if($n>0);
  return 0;
}

sub ehtfile {
  local @exts = split(('\.'), $_[0]);
  local $cext="eht"; # allowable documentation extensions
  $n=($cext =~ s/$exts[-1]//g);
  return 1 if($n>0);
  return 0;
}

sub cmain {
  open CFILE, $_[0] or die "can not open: $_[0]";
  local @lines = <CFILE>;
  close CFILE;
  chomp @lines;
  local $line;
  local $main = "main";                  # had to do it this way as I had trouble
  local $Ravl = "RAVL\_ENTRY\_POINT";    # with unmatched bracket in regexp??
  local $n=0;

  foreach $line (@lines) {

    $n=($line =~ m/$main/g);
    return 1 if($n>0);
    
    $n=($line =~ m/$Ravl/g);
    return 1 if($n>0);

  }
  
  return 0;
}


sub mkdefs {

  print "Making defs.mk for $_[0]\n"; 
  local $pth = $_[0];
  opendir DIR, $pth;
  local @files = readdir DIR;
  close DIR;
  
  local $SOURCES="";
  local $HEADERS="";
  local $MAINS="";
  local $EHT="";
  local $NESTED="";
  local $dirs="";
  local $dir;

  foreach $file (@files) {
    
    local $pfile = "$pth/$file";

    # is it a file
    if(-f $pfile) {
      
      # C or C++ file
      if(cfile($file)) {
	
	# MAINS
	if(cmain($pfile)) {
	  $MAINS .= "$file ";
	} 
	# SOURCES
	else {
	  $SOURCES .= "$file ";
	}
      } 
      
      # Header file
      elsif(hfile($file)) {
	$HEADERS .="$file ";
      } 
      
      # EHT fiel
      elsif(ehtfile($file)) {
	$EHT .= "$file ";
      }
      
    } 

    # is it a directory
    elsif(-d $pfile) {
      $NESTED .= "$file\.r " if(($pfile ne "$pth/.") && ($pfile ne "$pth/..") && ($pfile ne "$pth/RCS"));
      $dirs .= "$pfile " if(($pfile ne "$pth/.") && ($pfile ne "$pth/..") && ($pfile ne "$pth/RCS")); 
    }
  
  }


  # have we got any dirs
 
  foreach $dir(split(' ', $dirs)) {
    mkdefs($dir);
  }

  # get lib name from dir
  split('/', $pth);
  $PLIB = $_[-1];
  
  # write DEFS.MK file
  open DEFS, ">$pth/defs.mk" or die "can not open: $pth/defs.mk";  
  print DEFS "# Automatically generated make file\n\n";
  print DEFS "NESTED = $NESTED\n\n";
  print DEFS "SOURCES = $SOURCES\n\n";
  print DEFS "HEADERS = $HEADERS\n\n";
  print DEFS "MAINS = $MAINS\n\n";
  print DEFS "EHT = $EHT\n\n";
  print DEFS "PLIB = $PLIB\n\n" if($SOURCES ne "");
  close DEFS;


}







