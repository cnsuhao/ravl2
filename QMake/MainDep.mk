# This file is part of QMake, Quick Make System 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU General 
# Public License (GPL). See the gpl.licence file for details or
# see http://www.gnu.org/copyleft/gpl.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/QMake/MainDep.mk"

# Make with dependancies.

.PRECIOUS : %.def 
ifndef MAKEHOME
 MAKEHOME=.
endif
include $(MAKEHOME)/Main.mk

-include $(TARG_DEPEND)

-include $(TARG_HDRFLAG)

