# This file is part of QMake, Quick Make System 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU General 
# Public License (GPL). See the gpl.licence file for details or
# see http://www.gnu.org/copyleft/gpl.html
# file-header-ends-here
# Common RCS stuff
#! rcsid="$Id: rcs.mk 5747 2006-07-19 07:57:14Z craftit $"
#! file="Ravl/QMake/rcs.mk"

##########################################################
# Prevent rcs from checking out internal makefiles.

ifndef NOCHECKOUT

$(MAKEHOME)/% :: $(MAKEHOME)/RCS/%,v
	@true

$(MAKEHOME)/defs/% :: $(MAKEHOME)/defs/RCS/%,v
	@true

# Normal checkout.

% :: RCS/%,v
	@echo "--- co $(@F)"
	$(SHOWIT)if [ -w $@ ] ; then \
	  echo "WARNING: RCS file newer than source file. "; \
	  touch -c $@; \
	else \
	  co -q $@; \
	  exit 0; \
	fi

$(QCWD)/% :: $(QCWD)/RCS/%,v
	@echo "--- co $(@F)"
	$(SHOWIT)if [ -w $@ ] ; then \
	  echo "WARNING: RCS file newer than source file. "; \
	  touch -c $@; \
	else \
	  co -q $@; \
	  exit 0;\
	fi

else

% :: RCS/%,v

$(QCWD)/% :: $(QCWD)/RCS/%,v

endif
