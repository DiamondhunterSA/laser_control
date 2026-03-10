TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS BELOW HERE

# Use typed rset structure (see 3.16.1 release notes)
USR_CPPFLAGS += -DUSE_TYPED_RSET

# xxxRecord.h will be created from xxxRecord.dbd
DBDINC += xxxRecord

# Install xxxSupport.dbd into <top>/dbd
DBD += xxxSupport.dbd

# Build an IOC support library
LIBRARY_IOC += vcmdSupport

# Compile and add code to the support library
vcmdSupport_SRCS += xxxRecord.c
vcmdSupport_SRCS += devXxxSoft.c

# Link locally-provided code into the support library,
# rather than directly into the IOC application, that
# causes problems on Windows DLL builds
vcmdSupport_SRCS += dbSubExample.c
vcmdSupport_SRCS += devvcmdVersion.c
vcmdSupport_SRCS += vcmdHello.c
vcmdSupport_SRCS += initTrace.c

vcmdSupport_LIBS += $(EPICS_BASE_IOC_LIBS)

# Auto-generate a header file containing a version string.
# Version comes from the VCS if available, else date+time.
GENVERSION = vcmdVersion.h
# Macro name
GENVERSIONMACRO = vcmdVERSION

# Build the IOC application
PROD_IOC = vcmd

# vcmd.dbd will be created and installed
DBD += vcmd.dbd

# vcmd.dbd will include these files:
vcmd_DBD += base.dbd
vcmd_DBD += xxxSupport.dbd
vcmd_DBD += dbSubExample.dbd
vcmd_DBD += devvcmdVersion.dbd
vcmd_DBD += vcmdHello.dbd
vcmd_DBD += initTrace.dbd
vcmd_DBD += asyn.dbd
vcmd_DBD += drvAsynIPPort.dbd
vcmd_DBD += drvAsynSerialPort.dbd
vcmd_DBD += calc.dbd
vcmd_DBD += stream-scalcout.dbd
vcmd_DBD += stream.dbd
vcmd_DBD += as.dbd
vcmd_DBD += asSupport.dbd

# vcmd_registerRecordDeviceDriver.cpp derives from vcmd.dbd
vcmd_SRCS += vcmd_registerRecordDeviceDriver.cpp

# Build the main IOC entry point where needed
vcmd_SRCS_DEFAULT += vcmdMain.cpp
vcmd_SRCS_vxWorks += -nil-

# Link in the code from our support library
vcmd_LIBS += vcmdSupport
vcmd_LIBS += asyn
vcmd_LIBS += calc
vcmd_LIBS += autosave
vcmd_LIBS += stream
# To build SNL programs, SNCSEQ must be defined
# in the <top>/configure/RELEASE file
ifneq ($(SNCSEQ),)
    # Build sncExample into vcmdSupport
    sncExample_SNCFLAGS += +r
    vcmd_DBD += sncExample.dbd
    # A .stt sequence program is *not* pre-processed:
    vcmdSupport_SRCS += sncExample.stt
    vcmdSupport_LIBS += seq pv
    vcmd_LIBS += seq pv

    # Build sncProgram as a standalone program
    PROD_HOST += sncProgram
    sncProgram_SNCFLAGS += +m
    # A .st sequence program *is* pre-processed:
    sncProgram_SRCS += sncProgram.st
    sncProgram_LIBS += seq pv
    sncProgram_LIBS += $(EPICS_BASE_HOST_LIBS)
endif

# Link QSRV (pvAccess Server) if available
ifdef EPICS_QSRV_MAJOR_VERSION
    vcmd_LIBS += qsrv
    vcmd_LIBS += $(EPICS_BASE_PVA_CORE_LIBS)
    vcmd_DBD += PVAServerRegister.dbd
    vcmd_DBD += qsrv.dbd
endif

# Finally link IOC to the EPICS Base libraries
vcmd_LIBS += $(EPICS_BASE_IOC_LIBS)

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD EXTRA GNUMAKE RULES BELOW HERE

# Explicit dependency needed for generated header file
devvcmdVersion$(DEP): $(COMMON_DIR)/$(GENVERSION)
