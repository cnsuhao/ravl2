#!/usr/bin/perl -w
# AutoBuild.pl

use strict;

my $cfgfile = $ARGV[0];
my %config;

# Parse config file info $config
open(FILE, $cfgfile) || die "Failed to read config file $cfgfile\n";
while (<FILE>) {
  if(/^([^#]*)(#.*|\s*)$/) {
    $_ = $1;
  }
  next if(/^\s*$/) ;
  /^\s*((\s*[^\s]+)*)\s*$/;
  my($key, $val) = split(/\s+/, $1, 2);
  chomp($val);
  $config{$key} = $val;
  die "Error on line $.:\n$@\n" if ($@);
}
close(FILE);

# Load variables from $config
my $PACKAGENAME = $config{PACKAGENAME};
my $PACKAGES = $config{PACKAGES} ? $config{PACKAGES} : $config{PACKAGENAME};
my $BUILDDIRECTORY = $config{BUILDDIRECTORY};
my $BUILDTREES = $config{BUILDTREES};

# Get buildinfo file
my $BUILDINFOFILE = "$BUILDDIRECTORY/trees/.buildinfo_$PACKAGENAME";

# Get tree number
my $TREENO = 0;

# find out the username, first check environment, then try whoami
my $USERNAME ;
if ($ENV{USER} ) 
     { $USERNAME = $ENV{USER} ;}
else
     { $USERNAME = `whoami` ; }

# Mail Error function
# A function to mail the error to a user
sub MailError () {
  # Get function args
  my($body) = @_;
  # Get config options
  my $SENDMAIL = $config{SENDMAIL};
  my $MAILTO = $config{MAILTO};
  my $SUBJECT = $config{SUBJECT};
  # Send mail
  open(SENDMAIL, "|$SENDMAIL $MAILTO") or print "\nCannot open $SENDMAIL: $!\n";
  print SENDMAIL "Subject: $SUBJECT\n\n" ;
  print SENDMAIL "$body \n" ;
  close SENDMAIL ;
}

# build function - runs and logs results of a build command
sub Build () {
  # Get function args
  my($command, $logfile, $friendlyname) = @_;
  # Get config options
  my $MAILLOGS = $config{MAILLOGS};
  # run commands
  print "Starting $friendlyname\n";
  if (system("$command > $logfile 2>&1") != 0) {
# failure!
    my $message = "$friendlyname failed - tree $TREENO";
    # alert user
    print "$message \n" ;
    # send a mail
    if ($MAILLOGS == 1) {
      # Read logfile
      require Fcntl;
      open(FILE,$logfile);
      undef $/;
      my $file = <FILE>;
      close(FILE);
      # Append logfile to message
      $message .= "\n\nLog:\n\n" . $file;
    }
    & MailError ($message) ;
    # Stop the build process
    exit;
  }
}

sub ChDir () {
  # Get function args
  my($dir) = @_;
  # Change directory
  if(!chdir($dir)) {
    my $message="ERROR - Failed to change to directory $dir\n";
    & MailError ($message) ;
    die ($message) ;
  }
}

sub MkDir () {
  # Get function args
  my($dir) = @_;
  # Create directory
  if(!-d $dir) {
    if (! mkdir($dir, 0755)) {
      my $message = "ERROR - Failed to create directory '$dir' ";
      & MailError ($message) ;
      die ($message) ;
    }
  }
}

sub Checkout () {
  # How many retries?
  my $retries = 7;
  my $delay = 100;
  my $ok = 0;
  # Get function args
  my($pkg) = @_;
  # Get config params
  my $CVSROOT = $config{CVSROOT};
  # Checkout source
  do {    
    if ($retries != 7) {
      sleep $delay;
    }
    print "checking out...";
    if (system("cvs -z3 -d$CVSROOT co $pkg") == 0) {
      $ok = 1;
    } 
    $retries--;
  } while (!$ok && $retries > 0);
  if (!$ok) {
    my $message = "ERROR - Failed to check out package(s) $pkg";
    & MailError ($message) ;
    die ($message) ;
  }
}

# Select new build tree, and clear it out

print "Selecting build tree. \n";

if(!-d "$BUILDDIRECTORY/trees") {
  mkdir "$BUILDDIRECTORY/trees" ,0755 ;
}
if(!-e "$BUILDINFOFILE") {
  system("echo 1 > $BUILDINFOFILE");
}

if (open BUILDINFO,"< $BUILDINFOFILE") {
  $_ = <BUILDINFO>;
  chomp ;
  $TREENO = $_;
  close BUILDINFO;
} else {
  my $message = "Failed to find tree number" ;
  & MailError ($message) ;
  die ($message) ;
}

print " Using tree $TREENO. \n";
& MkDir("$BUILDDIRECTORY/trees/$PACKAGENAME.$TREENO");

print "Recreating build area \n";

my $SRCTREE = "$BUILDDIRECTORY/trees/$PACKAGENAME.$TREENO/src";
system("rm -rf $SRCTREE");
& MkDir($SRCTREE);
print "Src =$SRCTREE\n";

my $BUILDTREE = "$BUILDDIRECTORY/trees/$PACKAGENAME.$TREENO/build";
system("rm -rf $BUILDTREE");
& MkDir($BUILDTREE);
print "Build =$BUILDTREE\n";

# Check out source tree.
print "Checking out source tree.\n";
& ChDir($SRCTREE);
& Checkout($PACKAGES);

# Check out extra packages
if ($config{EXTRAPKG}) {
  & ChDir("$SRCTREE/$PACKAGENAME");
  & Checkout($config{EXTRAPKG});
}

# Create defs.mk file
if ($config{PACKAGES}) {
  open(MAKEFILE, ">$SRCTREE/defs.mk");
  print MAKEFILE "# Temporary QMake Makefile\n";
  print MAKEFILE "NESTED = ";
  my @subdirs = split(/ /, $PACKAGES);
  my $dir;
  foreach $dir (@subdirs) {
    print MAKEFILE "$dir.r "
  }
  print MAKEFILE "\n";
  close(MAKEFILE);
}

# Set temporary file location
if ($config{TEMPDIR}) {
  & MkDir($config{TEMPDIR});
  $ENV{DEFAULTTMP} = $config{TEMPDIR};
}

# Clean out temporary files
print ("\nPre Cleaning temporary files :$config{TEMPDIR}/$USERNAME/qm$BUILDTREE \n") ;
system("rm -rf $config{TEMPDIR}/$USERNAME/qm$BUILDTREE");

# If an install script exists, do full install
if(-e "$SRCTREE/$PACKAGENAME/install") {
  # Install
  my $command = "$SRCTREE/$PACKAGENAME/install $BUILDTREE auto";
  if ($config{RAVLCONFIG}) {
    $command .= " $config{RAVLCONFIG}";
  }
  & Build($command,"$BUILDTREE/install.log","install");
  # Test  
  & Build("gmake -f $BUILDTREE/share/RAVL/QMake/QMake.mk PROJECT_OUT=$BUILDTREE test","$BUILDTREE/test.log","test");
}
# Otherwise do a buildall
else {
  # Build
  & Build("gmake -f $config{RAVL_LOCATION}/share/RAVL/QMake/QMake.mk PROJECT_OUT=$BUILDTREE buildall","$BUILDTREE/install.log","build");
  # Test
  & Build("gmake -f $config{RAVL_LOCATION}/share/RAVL/QMake/QMake.mk PROJECT_OUT=$BUILDTREE test","$BUILDTREE/test.log","test");
}

if ($config{CLEANTEMP}) {
  print ("\nCleaning temporary files :$config{TEMPDIR}/$USERNAME/qm$BUILDTREE \n") ;
  system("rm -rf $config{TEMPDIR}/$USERNAME/qm$BUILDTREE");
}

# it worked ok
print "Clean compile, replacing symlinks. \n";

# Update new tree number
$TREENO++;
if($TREENO > $BUILDTREES) {
  $TREENO = 1;
}
unless(open BUILDFILEINFO,"> $BUILDINFOFILE") {
  my $message="Can't open buildinfo file. \n";
  & MailError($message) ;
  die ($message) ;
}
print BUILDFILEINFO "$TREENO\n";
close BUILDFILEINFO;

# Symlink new version as default.
my $SYMNAME = "$BUILDDIRECTORY/$PACKAGENAME" ;
if(-e $SYMNAME) {
  unlink $SYMNAME;
}
symlink $BUILDTREE, $SYMNAME;

my $message = "Build completed successfully " ;
if ($config{MAILONSUCCESS} == 1) {
  & MailError ($message);
}
