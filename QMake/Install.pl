$NEWHOME = $ARGV[0];
open(infile,$ARGV[1]);
open(outfile,">$ARGV[2]");
while(<infile>) {
  if(/[ ]*MAKEHOME[ ]*=[ ]*[^ ]*/) {
    print outfile " MAKEHOME\=$NEWHOME\n" ;
  } else {
    if(/[ ]*setenv[ ]+QMAKE_INSTALL[ ]*[^ ]*/) {
      print outfile "setenv QMAKE_INSTALL $NEWHOME\n" ;
    } elsif(/[ ]*\$QMAKE_INSTALL_DIR[ ]+\=[ ]*[^ ]*/) {
      print outfile "\$QMAKE_INSTALL_DIR = \"$NEWHOME\" ;\n" ;
    } else {
      print outfile "$_" ;
    }
  }
}
($a1,$a2,$mode,$nlink,$uid,$gid,$rdev,$size,$atime,$mtime,$ctime,$blksize,$blocks)= stat($ARGV[1]);
chmod $mode,$ARGV[2] ;
