


#--------------------------
# Compiler and flags etc
#--------------------------
CC = cl.exe

LD = lib.exe

INCLUDES =  /I "include\Win32" /I "include" /I "c:/Program Files/Microsoft Visual Studio 8/VC/ATLMFC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/PlatformSDK/include" /I "c:/Program Files/Microsoft Visual Studio 8/SDK/v2.0/include" 

DEFINES = /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2=1" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_SCL_SECURE=0" /D "_UNICODE" /D "UNICODE"


OPTFLAGS = /nologo /c /O2 /Ob1 /EHsc /MD /TP

DEBUGFLAGS = /nologo /c /Ob1 /EHsc /MD /TP

#-----------------------------------------------------------------------------
# OK lets define some of our output directories and define script to make them
#-----------------------------------------------------------------------------
DEBUGOBJDIR = C:\Build/win32/debug/obj/ccmath
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/ccmath
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/atou1.obj $(OPTOBJDIR)/atovm.obj $(OPTOBJDIR)/chouse.obj $(OPTOBJDIR)/chousv.obj $(OPTOBJDIR)/cmattr.obj $(OPTOBJDIR)/cmcpy.obj $(OPTOBJDIR)/cminv.obj $(OPTOBJDIR)/cmmul.obj $(OPTOBJDIR)/cmmult.obj $(OPTOBJDIR)/cmprt.obj $(OPTOBJDIR)/csolv.obj $(OPTOBJDIR)/cvmul.obj $(OPTOBJDIR)/eigen.obj $(OPTOBJDIR)/eigval.obj $(OPTOBJDIR)/evmax.obj $(OPTOBJDIR)/hconj.obj $(OPTOBJDIR)/heigval.obj $(OPTOBJDIR)/heigvec.obj $(OPTOBJDIR)/hevmax.obj $(OPTOBJDIR)/hmgen.obj $(OPTOBJDIR)/house.obj $(OPTOBJDIR)/housev.obj $(OPTOBJDIR)/ldumat.obj $(OPTOBJDIR)/ldvmat.obj $(OPTOBJDIR)/matprt.obj $(OPTOBJDIR)/mattr.obj $(OPTOBJDIR)/mcopy.obj $(OPTOBJDIR)/minv.obj $(OPTOBJDIR)/mmul.obj $(OPTOBJDIR)/ortho.obj $(OPTOBJDIR)/otrma.obj $(OPTOBJDIR)/otrsm.obj $(OPTOBJDIR)/psinv.obj $(OPTOBJDIR)/qrbdi.obj $(OPTOBJDIR)/qrbdu1.obj $(OPTOBJDIR)/qrbdv.obj $(OPTOBJDIR)/qrecvc.obj $(OPTOBJDIR)/qreval.obj $(OPTOBJDIR)/qrevec.obj $(OPTOBJDIR)/rmmult.obj $(OPTOBJDIR)/ruinv.obj $(OPTOBJDIR)/smgen.obj $(OPTOBJDIR)/solvps.obj $(OPTOBJDIR)/solvru.obj $(OPTOBJDIR)/solvtd.obj $(OPTOBJDIR)/sv2u1v.obj $(OPTOBJDIR)/sv2uv.obj $(OPTOBJDIR)/sv2val.obj $(OPTOBJDIR)/svdu1v.obj $(OPTOBJDIR)/svduv.obj $(OPTOBJDIR)/svdval.obj $(OPTOBJDIR)/trncm.obj $(OPTOBJDIR)/trnm.obj $(OPTOBJDIR)/unitary.obj $(OPTOBJDIR)/utrncm.obj $(OPTOBJDIR)/utrnhm.obj $(OPTOBJDIR)/vmul.obj $(OPTOBJDIR)/unfl.obj $(OPTOBJDIR)/lrand.obj $(OPTOBJDIR)/lrana.obj $(OPTOBJDIR)/solv.obj $(OPTOBJDIR)/fft2.obj $(OPTOBJDIR)/fft2_d.obj $(OPTOBJDIR)/fftgc.obj $(OPTOBJDIR)/fftgr.obj $(OPTOBJDIR)/ftuns.obj $(OPTOBJDIR)/pfac.obj $(OPTOBJDIR)/pshuf.obj $(OPTOBJDIR)/pwspec.obj $(OPTOBJDIR)/smoo.obj $(OPTOBJDIR)/chcof.obj $(OPTOBJDIR)/csfit.obj $(OPTOBJDIR)/csplp.obj $(OPTOBJDIR)/evpsq.obj $(OPTOBJDIR)/fitval.obj $(OPTOBJDIR)/gnlsq.obj $(OPTOBJDIR)/plsq.obj $(OPTOBJDIR)/psqcf.obj $(OPTOBJDIR)/qrbdbv.obj $(OPTOBJDIR)/qrvar.obj $(OPTOBJDIR)/sv2lsq.obj $(OPTOBJDIR)/tnsfit.obj $(OPTOBJDIR)/chpade.obj $(OPTOBJDIR)/cspl.obj $(OPTOBJDIR)/dcspl.obj $(OPTOBJDIR)/evpsqv.obj $(OPTOBJDIR)/ftch.obj $(OPTOBJDIR)/lsqsv.obj $(OPTOBJDIR)/pplsq.obj $(OPTOBJDIR)/psqvar.obj $(OPTOBJDIR)/qrlsq.obj $(OPTOBJDIR)/seqlsq.obj $(OPTOBJDIR)/svdlsq.obj $(OPTOBJDIR)/gaml.obj $(OPTOBJDIR)/pctb.obj $(OPTOBJDIR)/pctbn.obj $(OPTOBJDIR)/pctg.obj $(OPTOBJDIR)/pctgn.obj $(OPTOBJDIR)/pctn.obj $(OPTOBJDIR)/qbeta.obj $(OPTOBJDIR)/qbnc.obj $(OPTOBJDIR)/qgama.obj $(OPTOBJDIR)/qgnc.obj $(OPTOBJDIR)/qnorm.obj
	@echo -- making $(OPTLIBDIR)/ccmath.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/ccmath.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/atou1.obj $(DEBUGOBJDIR)/atovm.obj $(DEBUGOBJDIR)/chouse.obj $(DEBUGOBJDIR)/chousv.obj $(DEBUGOBJDIR)/cmattr.obj $(DEBUGOBJDIR)/cmcpy.obj $(DEBUGOBJDIR)/cminv.obj $(DEBUGOBJDIR)/cmmul.obj $(DEBUGOBJDIR)/cmmult.obj $(DEBUGOBJDIR)/cmprt.obj $(DEBUGOBJDIR)/csolv.obj $(DEBUGOBJDIR)/cvmul.obj $(DEBUGOBJDIR)/eigen.obj $(DEBUGOBJDIR)/eigval.obj $(DEBUGOBJDIR)/evmax.obj $(DEBUGOBJDIR)/hconj.obj $(DEBUGOBJDIR)/heigval.obj $(DEBUGOBJDIR)/heigvec.obj $(DEBUGOBJDIR)/hevmax.obj $(DEBUGOBJDIR)/hmgen.obj $(DEBUGOBJDIR)/house.obj $(DEBUGOBJDIR)/housev.obj $(DEBUGOBJDIR)/ldumat.obj $(DEBUGOBJDIR)/ldvmat.obj $(DEBUGOBJDIR)/matprt.obj $(DEBUGOBJDIR)/mattr.obj $(DEBUGOBJDIR)/mcopy.obj $(DEBUGOBJDIR)/minv.obj $(DEBUGOBJDIR)/mmul.obj $(DEBUGOBJDIR)/ortho.obj $(DEBUGOBJDIR)/otrma.obj $(DEBUGOBJDIR)/otrsm.obj $(DEBUGOBJDIR)/psinv.obj $(DEBUGOBJDIR)/qrbdi.obj $(DEBUGOBJDIR)/qrbdu1.obj $(DEBUGOBJDIR)/qrbdv.obj $(DEBUGOBJDIR)/qrecvc.obj $(DEBUGOBJDIR)/qreval.obj $(DEBUGOBJDIR)/qrevec.obj $(DEBUGOBJDIR)/rmmult.obj $(DEBUGOBJDIR)/ruinv.obj $(DEBUGOBJDIR)/smgen.obj $(DEBUGOBJDIR)/solvps.obj $(DEBUGOBJDIR)/solvru.obj $(DEBUGOBJDIR)/solvtd.obj $(DEBUGOBJDIR)/sv2u1v.obj $(DEBUGOBJDIR)/sv2uv.obj $(DEBUGOBJDIR)/sv2val.obj $(DEBUGOBJDIR)/svdu1v.obj $(DEBUGOBJDIR)/svduv.obj $(DEBUGOBJDIR)/svdval.obj $(DEBUGOBJDIR)/trncm.obj $(DEBUGOBJDIR)/trnm.obj $(DEBUGOBJDIR)/unitary.obj $(DEBUGOBJDIR)/utrncm.obj $(DEBUGOBJDIR)/utrnhm.obj $(DEBUGOBJDIR)/vmul.obj $(DEBUGOBJDIR)/unfl.obj $(DEBUGOBJDIR)/lrand.obj $(DEBUGOBJDIR)/lrana.obj $(DEBUGOBJDIR)/solv.obj $(DEBUGOBJDIR)/fft2.obj $(DEBUGOBJDIR)/fft2_d.obj $(DEBUGOBJDIR)/fftgc.obj $(DEBUGOBJDIR)/fftgr.obj $(DEBUGOBJDIR)/ftuns.obj $(DEBUGOBJDIR)/pfac.obj $(DEBUGOBJDIR)/pshuf.obj $(DEBUGOBJDIR)/pwspec.obj $(DEBUGOBJDIR)/smoo.obj $(DEBUGOBJDIR)/chcof.obj $(DEBUGOBJDIR)/csfit.obj $(DEBUGOBJDIR)/csplp.obj $(DEBUGOBJDIR)/evpsq.obj $(DEBUGOBJDIR)/fitval.obj $(DEBUGOBJDIR)/gnlsq.obj $(DEBUGOBJDIR)/plsq.obj $(DEBUGOBJDIR)/psqcf.obj $(DEBUGOBJDIR)/qrbdbv.obj $(DEBUGOBJDIR)/qrvar.obj $(DEBUGOBJDIR)/sv2lsq.obj $(DEBUGOBJDIR)/tnsfit.obj $(DEBUGOBJDIR)/chpade.obj $(DEBUGOBJDIR)/cspl.obj $(DEBUGOBJDIR)/dcspl.obj $(DEBUGOBJDIR)/evpsqv.obj $(DEBUGOBJDIR)/ftch.obj $(DEBUGOBJDIR)/lsqsv.obj $(DEBUGOBJDIR)/pplsq.obj $(DEBUGOBJDIR)/psqvar.obj $(DEBUGOBJDIR)/qrlsq.obj $(DEBUGOBJDIR)/seqlsq.obj $(DEBUGOBJDIR)/svdlsq.obj $(DEBUGOBJDIR)/gaml.obj $(DEBUGOBJDIR)/pctb.obj $(DEBUGOBJDIR)/pctbn.obj $(DEBUGOBJDIR)/pctg.obj $(DEBUGOBJDIR)/pctgn.obj $(DEBUGOBJDIR)/pctn.obj $(DEBUGOBJDIR)/qbeta.obj $(DEBUGOBJDIR)/qbnc.obj $(DEBUGOBJDIR)/qgama.obj $(DEBUGOBJDIR)/qgnc.obj $(DEBUGOBJDIR)/qnorm.obj 
	@echo -- making $(DEBUGLIBDIR)/ccmath.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/ccmath.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for ccmath
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/atou1.obj: .././CCMath/matrix/atou1.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/atou1.obj .././CCMath/matrix/atou1.c

$(DEBUGOBJDIR)/atou1.obj: .././CCMath/matrix/atou1.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/atou1.obj .././CCMath/matrix/atou1.c

$(OPTOBJDIR)/atovm.obj: .././CCMath/matrix/atovm.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/atovm.obj .././CCMath/matrix/atovm.c

$(DEBUGOBJDIR)/atovm.obj: .././CCMath/matrix/atovm.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/atovm.obj .././CCMath/matrix/atovm.c

$(OPTOBJDIR)/chouse.obj: .././CCMath/matrix/chouse.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/chouse.obj .././CCMath/matrix/chouse.c

$(DEBUGOBJDIR)/chouse.obj: .././CCMath/matrix/chouse.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/chouse.obj .././CCMath/matrix/chouse.c

$(OPTOBJDIR)/chousv.obj: .././CCMath/matrix/chousv.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/chousv.obj .././CCMath/matrix/chousv.c

$(DEBUGOBJDIR)/chousv.obj: .././CCMath/matrix/chousv.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/chousv.obj .././CCMath/matrix/chousv.c

$(OPTOBJDIR)/cmattr.obj: .././CCMath/matrix/cmattr.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/cmattr.obj .././CCMath/matrix/cmattr.c

$(DEBUGOBJDIR)/cmattr.obj: .././CCMath/matrix/cmattr.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/cmattr.obj .././CCMath/matrix/cmattr.c

$(OPTOBJDIR)/cmcpy.obj: .././CCMath/matrix/cmcpy.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/cmcpy.obj .././CCMath/matrix/cmcpy.c

$(DEBUGOBJDIR)/cmcpy.obj: .././CCMath/matrix/cmcpy.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/cmcpy.obj .././CCMath/matrix/cmcpy.c

$(OPTOBJDIR)/cminv.obj: .././CCMath/matrix/cminv.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/cminv.obj .././CCMath/matrix/cminv.c

$(DEBUGOBJDIR)/cminv.obj: .././CCMath/matrix/cminv.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/cminv.obj .././CCMath/matrix/cminv.c

$(OPTOBJDIR)/cmmul.obj: .././CCMath/matrix/cmmul.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/cmmul.obj .././CCMath/matrix/cmmul.c

$(DEBUGOBJDIR)/cmmul.obj: .././CCMath/matrix/cmmul.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/cmmul.obj .././CCMath/matrix/cmmul.c

$(OPTOBJDIR)/cmmult.obj: .././CCMath/matrix/cmmult.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/cmmult.obj .././CCMath/matrix/cmmult.c

$(DEBUGOBJDIR)/cmmult.obj: .././CCMath/matrix/cmmult.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/cmmult.obj .././CCMath/matrix/cmmult.c

$(OPTOBJDIR)/cmprt.obj: .././CCMath/matrix/cmprt.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/cmprt.obj .././CCMath/matrix/cmprt.c

$(DEBUGOBJDIR)/cmprt.obj: .././CCMath/matrix/cmprt.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/cmprt.obj .././CCMath/matrix/cmprt.c

$(OPTOBJDIR)/csolv.obj: .././CCMath/matrix/csolv.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/csolv.obj .././CCMath/matrix/csolv.c

$(DEBUGOBJDIR)/csolv.obj: .././CCMath/matrix/csolv.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/csolv.obj .././CCMath/matrix/csolv.c

$(OPTOBJDIR)/cvmul.obj: .././CCMath/matrix/cvmul.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/cvmul.obj .././CCMath/matrix/cvmul.c

$(DEBUGOBJDIR)/cvmul.obj: .././CCMath/matrix/cvmul.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/cvmul.obj .././CCMath/matrix/cvmul.c

$(OPTOBJDIR)/eigen.obj: .././CCMath/matrix/eigen.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/eigen.obj .././CCMath/matrix/eigen.c

$(DEBUGOBJDIR)/eigen.obj: .././CCMath/matrix/eigen.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/eigen.obj .././CCMath/matrix/eigen.c

$(OPTOBJDIR)/eigval.obj: .././CCMath/matrix/eigval.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/eigval.obj .././CCMath/matrix/eigval.c

$(DEBUGOBJDIR)/eigval.obj: .././CCMath/matrix/eigval.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/eigval.obj .././CCMath/matrix/eigval.c

$(OPTOBJDIR)/evmax.obj: .././CCMath/matrix/evmax.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/evmax.obj .././CCMath/matrix/evmax.c

$(DEBUGOBJDIR)/evmax.obj: .././CCMath/matrix/evmax.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/evmax.obj .././CCMath/matrix/evmax.c

$(OPTOBJDIR)/hconj.obj: .././CCMath/matrix/hconj.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/hconj.obj .././CCMath/matrix/hconj.c

$(DEBUGOBJDIR)/hconj.obj: .././CCMath/matrix/hconj.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/hconj.obj .././CCMath/matrix/hconj.c

$(OPTOBJDIR)/heigval.obj: .././CCMath/matrix/heigval.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/heigval.obj .././CCMath/matrix/heigval.c

$(DEBUGOBJDIR)/heigval.obj: .././CCMath/matrix/heigval.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/heigval.obj .././CCMath/matrix/heigval.c

$(OPTOBJDIR)/heigvec.obj: .././CCMath/matrix/heigvec.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/heigvec.obj .././CCMath/matrix/heigvec.c

$(DEBUGOBJDIR)/heigvec.obj: .././CCMath/matrix/heigvec.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/heigvec.obj .././CCMath/matrix/heigvec.c

$(OPTOBJDIR)/hevmax.obj: .././CCMath/matrix/hevmax.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/hevmax.obj .././CCMath/matrix/hevmax.c

$(DEBUGOBJDIR)/hevmax.obj: .././CCMath/matrix/hevmax.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/hevmax.obj .././CCMath/matrix/hevmax.c

$(OPTOBJDIR)/hmgen.obj: .././CCMath/matrix/hmgen.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/hmgen.obj .././CCMath/matrix/hmgen.c

$(DEBUGOBJDIR)/hmgen.obj: .././CCMath/matrix/hmgen.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/hmgen.obj .././CCMath/matrix/hmgen.c

$(OPTOBJDIR)/house.obj: .././CCMath/matrix/house.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/house.obj .././CCMath/matrix/house.c

$(DEBUGOBJDIR)/house.obj: .././CCMath/matrix/house.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/house.obj .././CCMath/matrix/house.c

$(OPTOBJDIR)/housev.obj: .././CCMath/matrix/housev.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/housev.obj .././CCMath/matrix/housev.c

$(DEBUGOBJDIR)/housev.obj: .././CCMath/matrix/housev.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/housev.obj .././CCMath/matrix/housev.c

$(OPTOBJDIR)/ldumat.obj: .././CCMath/matrix/ldumat.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ldumat.obj .././CCMath/matrix/ldumat.c

$(DEBUGOBJDIR)/ldumat.obj: .././CCMath/matrix/ldumat.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ldumat.obj .././CCMath/matrix/ldumat.c

$(OPTOBJDIR)/ldvmat.obj: .././CCMath/matrix/ldvmat.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ldvmat.obj .././CCMath/matrix/ldvmat.c

$(DEBUGOBJDIR)/ldvmat.obj: .././CCMath/matrix/ldvmat.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ldvmat.obj .././CCMath/matrix/ldvmat.c

$(OPTOBJDIR)/matprt.obj: .././CCMath/matrix/matprt.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/matprt.obj .././CCMath/matrix/matprt.c

$(DEBUGOBJDIR)/matprt.obj: .././CCMath/matrix/matprt.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/matprt.obj .././CCMath/matrix/matprt.c

$(OPTOBJDIR)/mattr.obj: .././CCMath/matrix/mattr.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/mattr.obj .././CCMath/matrix/mattr.c

$(DEBUGOBJDIR)/mattr.obj: .././CCMath/matrix/mattr.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/mattr.obj .././CCMath/matrix/mattr.c

$(OPTOBJDIR)/mcopy.obj: .././CCMath/matrix/mcopy.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/mcopy.obj .././CCMath/matrix/mcopy.c

$(DEBUGOBJDIR)/mcopy.obj: .././CCMath/matrix/mcopy.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/mcopy.obj .././CCMath/matrix/mcopy.c

$(OPTOBJDIR)/minv.obj: .././CCMath/matrix/minv.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/minv.obj .././CCMath/matrix/minv.c

$(DEBUGOBJDIR)/minv.obj: .././CCMath/matrix/minv.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/minv.obj .././CCMath/matrix/minv.c

$(OPTOBJDIR)/mmul.obj: .././CCMath/matrix/mmul.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/mmul.obj .././CCMath/matrix/mmul.c

$(DEBUGOBJDIR)/mmul.obj: .././CCMath/matrix/mmul.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/mmul.obj .././CCMath/matrix/mmul.c

$(OPTOBJDIR)/ortho.obj: .././CCMath/matrix/ortho.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ortho.obj .././CCMath/matrix/ortho.c

$(DEBUGOBJDIR)/ortho.obj: .././CCMath/matrix/ortho.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ortho.obj .././CCMath/matrix/ortho.c

$(OPTOBJDIR)/otrma.obj: .././CCMath/matrix/otrma.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/otrma.obj .././CCMath/matrix/otrma.c

$(DEBUGOBJDIR)/otrma.obj: .././CCMath/matrix/otrma.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/otrma.obj .././CCMath/matrix/otrma.c

$(OPTOBJDIR)/otrsm.obj: .././CCMath/matrix/otrsm.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/otrsm.obj .././CCMath/matrix/otrsm.c

$(DEBUGOBJDIR)/otrsm.obj: .././CCMath/matrix/otrsm.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/otrsm.obj .././CCMath/matrix/otrsm.c

$(OPTOBJDIR)/psinv.obj: .././CCMath/matrix/psinv.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/psinv.obj .././CCMath/matrix/psinv.c

$(DEBUGOBJDIR)/psinv.obj: .././CCMath/matrix/psinv.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/psinv.obj .././CCMath/matrix/psinv.c

$(OPTOBJDIR)/qrbdi.obj: .././CCMath/matrix/qrbdi.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/qrbdi.obj .././CCMath/matrix/qrbdi.c

$(DEBUGOBJDIR)/qrbdi.obj: .././CCMath/matrix/qrbdi.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/qrbdi.obj .././CCMath/matrix/qrbdi.c

$(OPTOBJDIR)/qrbdu1.obj: .././CCMath/matrix/qrbdu1.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/qrbdu1.obj .././CCMath/matrix/qrbdu1.c

$(DEBUGOBJDIR)/qrbdu1.obj: .././CCMath/matrix/qrbdu1.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/qrbdu1.obj .././CCMath/matrix/qrbdu1.c

$(OPTOBJDIR)/qrbdv.obj: .././CCMath/matrix/qrbdv.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/qrbdv.obj .././CCMath/matrix/qrbdv.c

$(DEBUGOBJDIR)/qrbdv.obj: .././CCMath/matrix/qrbdv.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/qrbdv.obj .././CCMath/matrix/qrbdv.c

$(OPTOBJDIR)/qrecvc.obj: .././CCMath/matrix/qrecvc.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/qrecvc.obj .././CCMath/matrix/qrecvc.c

$(DEBUGOBJDIR)/qrecvc.obj: .././CCMath/matrix/qrecvc.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/qrecvc.obj .././CCMath/matrix/qrecvc.c

$(OPTOBJDIR)/qreval.obj: .././CCMath/matrix/qreval.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/qreval.obj .././CCMath/matrix/qreval.c

$(DEBUGOBJDIR)/qreval.obj: .././CCMath/matrix/qreval.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/qreval.obj .././CCMath/matrix/qreval.c

$(OPTOBJDIR)/qrevec.obj: .././CCMath/matrix/qrevec.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/qrevec.obj .././CCMath/matrix/qrevec.c

$(DEBUGOBJDIR)/qrevec.obj: .././CCMath/matrix/qrevec.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/qrevec.obj .././CCMath/matrix/qrevec.c

$(OPTOBJDIR)/rmmult.obj: .././CCMath/matrix/rmmult.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/rmmult.obj .././CCMath/matrix/rmmult.c

$(DEBUGOBJDIR)/rmmult.obj: .././CCMath/matrix/rmmult.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/rmmult.obj .././CCMath/matrix/rmmult.c

$(OPTOBJDIR)/ruinv.obj: .././CCMath/matrix/ruinv.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ruinv.obj .././CCMath/matrix/ruinv.c

$(DEBUGOBJDIR)/ruinv.obj: .././CCMath/matrix/ruinv.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ruinv.obj .././CCMath/matrix/ruinv.c

$(OPTOBJDIR)/smgen.obj: .././CCMath/matrix/smgen.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/smgen.obj .././CCMath/matrix/smgen.c

$(DEBUGOBJDIR)/smgen.obj: .././CCMath/matrix/smgen.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/smgen.obj .././CCMath/matrix/smgen.c

$(OPTOBJDIR)/solvps.obj: .././CCMath/matrix/solvps.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/solvps.obj .././CCMath/matrix/solvps.c

$(DEBUGOBJDIR)/solvps.obj: .././CCMath/matrix/solvps.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/solvps.obj .././CCMath/matrix/solvps.c

$(OPTOBJDIR)/solvru.obj: .././CCMath/matrix/solvru.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/solvru.obj .././CCMath/matrix/solvru.c

$(DEBUGOBJDIR)/solvru.obj: .././CCMath/matrix/solvru.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/solvru.obj .././CCMath/matrix/solvru.c

$(OPTOBJDIR)/solvtd.obj: .././CCMath/matrix/solvtd.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/solvtd.obj .././CCMath/matrix/solvtd.c

$(DEBUGOBJDIR)/solvtd.obj: .././CCMath/matrix/solvtd.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/solvtd.obj .././CCMath/matrix/solvtd.c

$(OPTOBJDIR)/sv2u1v.obj: .././CCMath/matrix/sv2u1v.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/sv2u1v.obj .././CCMath/matrix/sv2u1v.c

$(DEBUGOBJDIR)/sv2u1v.obj: .././CCMath/matrix/sv2u1v.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/sv2u1v.obj .././CCMath/matrix/sv2u1v.c

$(OPTOBJDIR)/sv2uv.obj: .././CCMath/matrix/sv2uv.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/sv2uv.obj .././CCMath/matrix/sv2uv.c

$(DEBUGOBJDIR)/sv2uv.obj: .././CCMath/matrix/sv2uv.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/sv2uv.obj .././CCMath/matrix/sv2uv.c

$(OPTOBJDIR)/sv2val.obj: .././CCMath/matrix/sv2val.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/sv2val.obj .././CCMath/matrix/sv2val.c

$(DEBUGOBJDIR)/sv2val.obj: .././CCMath/matrix/sv2val.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/sv2val.obj .././CCMath/matrix/sv2val.c

$(OPTOBJDIR)/svdu1v.obj: .././CCMath/matrix/svdu1v.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/svdu1v.obj .././CCMath/matrix/svdu1v.c

$(DEBUGOBJDIR)/svdu1v.obj: .././CCMath/matrix/svdu1v.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/svdu1v.obj .././CCMath/matrix/svdu1v.c

$(OPTOBJDIR)/svduv.obj: .././CCMath/matrix/svduv.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/svduv.obj .././CCMath/matrix/svduv.c

$(DEBUGOBJDIR)/svduv.obj: .././CCMath/matrix/svduv.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/svduv.obj .././CCMath/matrix/svduv.c

$(OPTOBJDIR)/svdval.obj: .././CCMath/matrix/svdval.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/svdval.obj .././CCMath/matrix/svdval.c

$(DEBUGOBJDIR)/svdval.obj: .././CCMath/matrix/svdval.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/svdval.obj .././CCMath/matrix/svdval.c

$(OPTOBJDIR)/trncm.obj: .././CCMath/matrix/trncm.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/trncm.obj .././CCMath/matrix/trncm.c

$(DEBUGOBJDIR)/trncm.obj: .././CCMath/matrix/trncm.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/trncm.obj .././CCMath/matrix/trncm.c

$(OPTOBJDIR)/trnm.obj: .././CCMath/matrix/trnm.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/trnm.obj .././CCMath/matrix/trnm.c

$(DEBUGOBJDIR)/trnm.obj: .././CCMath/matrix/trnm.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/trnm.obj .././CCMath/matrix/trnm.c

$(OPTOBJDIR)/unitary.obj: .././CCMath/matrix/unitary.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/unitary.obj .././CCMath/matrix/unitary.c

$(DEBUGOBJDIR)/unitary.obj: .././CCMath/matrix/unitary.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/unitary.obj .././CCMath/matrix/unitary.c

$(OPTOBJDIR)/utrncm.obj: .././CCMath/matrix/utrncm.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/utrncm.obj .././CCMath/matrix/utrncm.c

$(DEBUGOBJDIR)/utrncm.obj: .././CCMath/matrix/utrncm.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/utrncm.obj .././CCMath/matrix/utrncm.c

$(OPTOBJDIR)/utrnhm.obj: .././CCMath/matrix/utrnhm.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/utrnhm.obj .././CCMath/matrix/utrnhm.c

$(DEBUGOBJDIR)/utrnhm.obj: .././CCMath/matrix/utrnhm.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/utrnhm.obj .././CCMath/matrix/utrnhm.c

$(OPTOBJDIR)/vmul.obj: .././CCMath/matrix/vmul.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/vmul.obj .././CCMath/matrix/vmul.c

$(DEBUGOBJDIR)/vmul.obj: .././CCMath/matrix/vmul.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/vmul.obj .././CCMath/matrix/vmul.c

$(OPTOBJDIR)/unfl.obj: .././CCMath/matrix/unfl.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/unfl.obj .././CCMath/matrix/unfl.c

$(DEBUGOBJDIR)/unfl.obj: .././CCMath/matrix/unfl.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/unfl.obj .././CCMath/matrix/unfl.c

$(OPTOBJDIR)/lrand.obj: .././CCMath/matrix/lrand.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/lrand.obj .././CCMath/matrix/lrand.c

$(DEBUGOBJDIR)/lrand.obj: .././CCMath/matrix/lrand.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/lrand.obj .././CCMath/matrix/lrand.c

$(OPTOBJDIR)/lrana.obj: .././CCMath/matrix/lrana.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/lrana.obj .././CCMath/matrix/lrana.c

$(DEBUGOBJDIR)/lrana.obj: .././CCMath/matrix/lrana.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/lrana.obj .././CCMath/matrix/lrana.c

$(OPTOBJDIR)/solv.obj: .././CCMath/matrix/solv.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/solv.obj .././CCMath/matrix/solv.c

$(DEBUGOBJDIR)/solv.obj: .././CCMath/matrix/solv.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/solv.obj .././CCMath/matrix/solv.c

$(OPTOBJDIR)/fft2.obj: .././CCMath/fft/fft2.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/fft2.obj .././CCMath/fft/fft2.c

$(DEBUGOBJDIR)/fft2.obj: .././CCMath/fft/fft2.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/fft2.obj .././CCMath/fft/fft2.c

$(OPTOBJDIR)/fft2_d.obj: .././CCMath/fft/fft2_d.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/fft2_d.obj .././CCMath/fft/fft2_d.c

$(DEBUGOBJDIR)/fft2_d.obj: .././CCMath/fft/fft2_d.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/fft2_d.obj .././CCMath/fft/fft2_d.c

$(OPTOBJDIR)/fftgc.obj: .././CCMath/fft/fftgc.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/fftgc.obj .././CCMath/fft/fftgc.c

$(DEBUGOBJDIR)/fftgc.obj: .././CCMath/fft/fftgc.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/fftgc.obj .././CCMath/fft/fftgc.c

$(OPTOBJDIR)/fftgr.obj: .././CCMath/fft/fftgr.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/fftgr.obj .././CCMath/fft/fftgr.c

$(DEBUGOBJDIR)/fftgr.obj: .././CCMath/fft/fftgr.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/fftgr.obj .././CCMath/fft/fftgr.c

$(OPTOBJDIR)/ftuns.obj: .././CCMath/fft/ftuns.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ftuns.obj .././CCMath/fft/ftuns.c

$(DEBUGOBJDIR)/ftuns.obj: .././CCMath/fft/ftuns.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ftuns.obj .././CCMath/fft/ftuns.c

$(OPTOBJDIR)/pfac.obj: .././CCMath/fft/pfac.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/pfac.obj .././CCMath/fft/pfac.c

$(DEBUGOBJDIR)/pfac.obj: .././CCMath/fft/pfac.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/pfac.obj .././CCMath/fft/pfac.c

$(OPTOBJDIR)/pshuf.obj: .././CCMath/fft/pshuf.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/pshuf.obj .././CCMath/fft/pshuf.c

$(DEBUGOBJDIR)/pshuf.obj: .././CCMath/fft/pshuf.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/pshuf.obj .././CCMath/fft/pshuf.c

$(OPTOBJDIR)/pwspec.obj: .././CCMath/fft/pwspec.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/pwspec.obj .././CCMath/fft/pwspec.c

$(DEBUGOBJDIR)/pwspec.obj: .././CCMath/fft/pwspec.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/pwspec.obj .././CCMath/fft/pwspec.c

$(OPTOBJDIR)/smoo.obj: .././CCMath/fft/smoo.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/smoo.obj .././CCMath/fft/smoo.c

$(DEBUGOBJDIR)/smoo.obj: .././CCMath/fft/smoo.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/smoo.obj .././CCMath/fft/smoo.c

$(OPTOBJDIR)/chcof.obj: .././CCMath/cfit/chcof.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/chcof.obj .././CCMath/cfit/chcof.c

$(DEBUGOBJDIR)/chcof.obj: .././CCMath/cfit/chcof.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/chcof.obj .././CCMath/cfit/chcof.c

$(OPTOBJDIR)/csfit.obj: .././CCMath/cfit/csfit.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/csfit.obj .././CCMath/cfit/csfit.c

$(DEBUGOBJDIR)/csfit.obj: .././CCMath/cfit/csfit.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/csfit.obj .././CCMath/cfit/csfit.c

$(OPTOBJDIR)/csplp.obj: .././CCMath/cfit/csplp.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/csplp.obj .././CCMath/cfit/csplp.c

$(DEBUGOBJDIR)/csplp.obj: .././CCMath/cfit/csplp.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/csplp.obj .././CCMath/cfit/csplp.c

$(OPTOBJDIR)/evpsq.obj: .././CCMath/cfit/evpsq.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/evpsq.obj .././CCMath/cfit/evpsq.c

$(DEBUGOBJDIR)/evpsq.obj: .././CCMath/cfit/evpsq.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/evpsq.obj .././CCMath/cfit/evpsq.c

$(OPTOBJDIR)/fitval.obj: .././CCMath/cfit/fitval.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/fitval.obj .././CCMath/cfit/fitval.c

$(DEBUGOBJDIR)/fitval.obj: .././CCMath/cfit/fitval.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/fitval.obj .././CCMath/cfit/fitval.c

$(OPTOBJDIR)/gnlsq.obj: .././CCMath/cfit/gnlsq.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/gnlsq.obj .././CCMath/cfit/gnlsq.c

$(DEBUGOBJDIR)/gnlsq.obj: .././CCMath/cfit/gnlsq.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/gnlsq.obj .././CCMath/cfit/gnlsq.c

$(OPTOBJDIR)/plsq.obj: .././CCMath/cfit/plsq.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/plsq.obj .././CCMath/cfit/plsq.c

$(DEBUGOBJDIR)/plsq.obj: .././CCMath/cfit/plsq.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/plsq.obj .././CCMath/cfit/plsq.c

$(OPTOBJDIR)/psqcf.obj: .././CCMath/cfit/psqcf.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/psqcf.obj .././CCMath/cfit/psqcf.c

$(DEBUGOBJDIR)/psqcf.obj: .././CCMath/cfit/psqcf.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/psqcf.obj .././CCMath/cfit/psqcf.c

$(OPTOBJDIR)/qrbdbv.obj: .././CCMath/cfit/qrbdbv.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/qrbdbv.obj .././CCMath/cfit/qrbdbv.c

$(DEBUGOBJDIR)/qrbdbv.obj: .././CCMath/cfit/qrbdbv.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/qrbdbv.obj .././CCMath/cfit/qrbdbv.c

$(OPTOBJDIR)/qrvar.obj: .././CCMath/cfit/qrvar.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/qrvar.obj .././CCMath/cfit/qrvar.c

$(DEBUGOBJDIR)/qrvar.obj: .././CCMath/cfit/qrvar.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/qrvar.obj .././CCMath/cfit/qrvar.c

$(OPTOBJDIR)/sv2lsq.obj: .././CCMath/cfit/sv2lsq.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/sv2lsq.obj .././CCMath/cfit/sv2lsq.c

$(DEBUGOBJDIR)/sv2lsq.obj: .././CCMath/cfit/sv2lsq.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/sv2lsq.obj .././CCMath/cfit/sv2lsq.c

$(OPTOBJDIR)/tnsfit.obj: .././CCMath/cfit/tnsfit.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/tnsfit.obj .././CCMath/cfit/tnsfit.c

$(DEBUGOBJDIR)/tnsfit.obj: .././CCMath/cfit/tnsfit.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/tnsfit.obj .././CCMath/cfit/tnsfit.c

$(OPTOBJDIR)/chpade.obj: .././CCMath/cfit/chpade.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/chpade.obj .././CCMath/cfit/chpade.c

$(DEBUGOBJDIR)/chpade.obj: .././CCMath/cfit/chpade.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/chpade.obj .././CCMath/cfit/chpade.c

$(OPTOBJDIR)/cspl.obj: .././CCMath/cfit/cspl.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/cspl.obj .././CCMath/cfit/cspl.c

$(DEBUGOBJDIR)/cspl.obj: .././CCMath/cfit/cspl.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/cspl.obj .././CCMath/cfit/cspl.c

$(OPTOBJDIR)/dcspl.obj: .././CCMath/cfit/dcspl.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/dcspl.obj .././CCMath/cfit/dcspl.c

$(DEBUGOBJDIR)/dcspl.obj: .././CCMath/cfit/dcspl.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/dcspl.obj .././CCMath/cfit/dcspl.c

$(OPTOBJDIR)/evpsqv.obj: .././CCMath/cfit/evpsqv.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/evpsqv.obj .././CCMath/cfit/evpsqv.c

$(DEBUGOBJDIR)/evpsqv.obj: .././CCMath/cfit/evpsqv.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/evpsqv.obj .././CCMath/cfit/evpsqv.c

$(OPTOBJDIR)/ftch.obj: .././CCMath/cfit/ftch.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ftch.obj .././CCMath/cfit/ftch.c

$(DEBUGOBJDIR)/ftch.obj: .././CCMath/cfit/ftch.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ftch.obj .././CCMath/cfit/ftch.c

$(OPTOBJDIR)/lsqsv.obj: .././CCMath/cfit/lsqsv.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/lsqsv.obj .././CCMath/cfit/lsqsv.c

$(DEBUGOBJDIR)/lsqsv.obj: .././CCMath/cfit/lsqsv.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/lsqsv.obj .././CCMath/cfit/lsqsv.c

$(OPTOBJDIR)/pplsq.obj: .././CCMath/cfit/pplsq.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/pplsq.obj .././CCMath/cfit/pplsq.c

$(DEBUGOBJDIR)/pplsq.obj: .././CCMath/cfit/pplsq.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/pplsq.obj .././CCMath/cfit/pplsq.c

$(OPTOBJDIR)/psqvar.obj: .././CCMath/cfit/psqvar.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/psqvar.obj .././CCMath/cfit/psqvar.c

$(DEBUGOBJDIR)/psqvar.obj: .././CCMath/cfit/psqvar.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/psqvar.obj .././CCMath/cfit/psqvar.c

$(OPTOBJDIR)/qrlsq.obj: .././CCMath/cfit/qrlsq.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/qrlsq.obj .././CCMath/cfit/qrlsq.c

$(DEBUGOBJDIR)/qrlsq.obj: .././CCMath/cfit/qrlsq.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/qrlsq.obj .././CCMath/cfit/qrlsq.c

$(OPTOBJDIR)/seqlsq.obj: .././CCMath/cfit/seqlsq.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/seqlsq.obj .././CCMath/cfit/seqlsq.c

$(DEBUGOBJDIR)/seqlsq.obj: .././CCMath/cfit/seqlsq.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/seqlsq.obj .././CCMath/cfit/seqlsq.c

$(OPTOBJDIR)/svdlsq.obj: .././CCMath/cfit/svdlsq.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/svdlsq.obj .././CCMath/cfit/svdlsq.c

$(DEBUGOBJDIR)/svdlsq.obj: .././CCMath/cfit/svdlsq.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/svdlsq.obj .././CCMath/cfit/svdlsq.c

$(OPTOBJDIR)/gaml.obj: .././CCMath/statf/gaml.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/gaml.obj .././CCMath/statf/gaml.c

$(DEBUGOBJDIR)/gaml.obj: .././CCMath/statf/gaml.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/gaml.obj .././CCMath/statf/gaml.c

$(OPTOBJDIR)/pctb.obj: .././CCMath/statf/pctb.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/pctb.obj .././CCMath/statf/pctb.c

$(DEBUGOBJDIR)/pctb.obj: .././CCMath/statf/pctb.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/pctb.obj .././CCMath/statf/pctb.c

$(OPTOBJDIR)/pctbn.obj: .././CCMath/statf/pctbn.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/pctbn.obj .././CCMath/statf/pctbn.c

$(DEBUGOBJDIR)/pctbn.obj: .././CCMath/statf/pctbn.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/pctbn.obj .././CCMath/statf/pctbn.c

$(OPTOBJDIR)/pctg.obj: .././CCMath/statf/pctg.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/pctg.obj .././CCMath/statf/pctg.c

$(DEBUGOBJDIR)/pctg.obj: .././CCMath/statf/pctg.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/pctg.obj .././CCMath/statf/pctg.c

$(OPTOBJDIR)/pctgn.obj: .././CCMath/statf/pctgn.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/pctgn.obj .././CCMath/statf/pctgn.c

$(DEBUGOBJDIR)/pctgn.obj: .././CCMath/statf/pctgn.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/pctgn.obj .././CCMath/statf/pctgn.c

$(OPTOBJDIR)/pctn.obj: .././CCMath/statf/pctn.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/pctn.obj .././CCMath/statf/pctn.c

$(DEBUGOBJDIR)/pctn.obj: .././CCMath/statf/pctn.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/pctn.obj .././CCMath/statf/pctn.c

$(OPTOBJDIR)/qbeta.obj: .././CCMath/statf/qbeta.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/qbeta.obj .././CCMath/statf/qbeta.c

$(DEBUGOBJDIR)/qbeta.obj: .././CCMath/statf/qbeta.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/qbeta.obj .././CCMath/statf/qbeta.c

$(OPTOBJDIR)/qbnc.obj: .././CCMath/statf/qbnc.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/qbnc.obj .././CCMath/statf/qbnc.c

$(DEBUGOBJDIR)/qbnc.obj: .././CCMath/statf/qbnc.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/qbnc.obj .././CCMath/statf/qbnc.c

$(OPTOBJDIR)/qgama.obj: .././CCMath/statf/qgama.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/qgama.obj .././CCMath/statf/qgama.c

$(DEBUGOBJDIR)/qgama.obj: .././CCMath/statf/qgama.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/qgama.obj .././CCMath/statf/qgama.c

$(OPTOBJDIR)/qgnc.obj: .././CCMath/statf/qgnc.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/qgnc.obj .././CCMath/statf/qgnc.c

$(DEBUGOBJDIR)/qgnc.obj: .././CCMath/statf/qgnc.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/qgnc.obj .././CCMath/statf/qgnc.c

$(OPTOBJDIR)/qnorm.obj: .././CCMath/statf/qnorm.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/qnorm.obj .././CCMath/statf/qnorm.c

$(DEBUGOBJDIR)/qnorm.obj: .././CCMath/statf/qnorm.c 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/qnorm.obj .././CCMath/statf/qnorm.c


