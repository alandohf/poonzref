# This is a gnumake makefile. 

#
# Location of UDB instance.  Change as appropriate.
#
INSTHOME = /export/home/${DB2INSTANCE}

#
# Wrapper library definitions.  Change these as appropriate
#

# Object files that make up the sample wrapper
UNFENCED_WRAPPER_OBJ_FILES = sample_wrapper.o \
                             sample_server.o \
                             sample_user.o \
                             sample_nickname.o \
                             sample_utilities.o

FENCED_WRAPPER_OBJ_FILES   = sample_connection.o \
                             sample_operation.o \
                             sample_fenced_wrapper.o \
                             sample_fenced_server.o \
                             sample_fenced_nickname.o \
                             sample_utilities.o

# Name of wrapper library to be created. Change name as appropriate
WRAPPER_ARCHIVE_NAME          = libsample

# These macros shouldn't be changed
WRAPPER_ARCHIVE_LIB          = $(WRAPPER_ARCHIVE_NAME).$(SHARED_LIB_EXT)
FENCED_WRAPPER_ARCHIVE_LIB   = $(WRAPPER_ARCHIVE_NAME)F.$(SHARED_LIB_EXT)
UNFENCED_WRAPPER_ARCHIVE_LIB = $(WRAPPER_ARCHIVE_NAME)U.$(SHARED_LIB_EXT)

# 
# Tools and Macros. These are platform specific.
# The following is for SunOS
#
# NOTE:
#    1. To build the sample wrapper in a 32bit enabled DB2 instance, set the variable
#       32_BIT to 1. For exmaple: 32_BIT = 1
#    2. To build a wrapper with 32 bit bridging support in a 64bit enabled DB2 instance,
#       set the variable 32_BIT_BRIDGING to 1. For example: 32_BIT_BRIDGING = 1
#

SHARED_LIB_EXT               = so
CCC = CC
CCC_LIB = CC

ifdef 32_BIT
32_BIT_UNFENCED = 1
32_BIT_FENCED = 1
endif

ifdef 32_BIT_BRIDGING
32_BIT_FENCED = 1
endif

#
# UDB definitions.  These should not need to be changed.
#

# Location of the DB2 UDB 64 bit libraries
UDB_LIB64_DIR = ${INSTHOME}/sqllib/lib64

# Location of the DB2 UDB 32 bit libraries
UDB_LIB32_DIR = ${INSTHOME}/sqllib/lib32

# Location of the wrapper include files and public include files
UDB_INCLUDE_DIR = ${INSTHOME}/sqllib/include

all: ${UNFENCED_WRAPPER_ARCHIVE_LIB}  ${FENCED_WRAPPER_ARCHIVE_LIB}  move

# compile and link the unfenced wrapper code

ifdef 32_BIT_UNFENCED
COPTS_64 =
LDFLAGS_64 =
UNFENCED_LIB_DIR = ${UDB_LIB32_DIR}
else
ifeq ("$(ARCH)","i386")
COPTS_64 = -xarch=amd64
LDFLAGS_64 = -xarch=amd64
else
COPTS_64 = -xarch=v9 
LDFLAGS_64 = -xarch=v9 
endif
UNFENCED_LIB_DIR = ${UDB_LIB64_DIR}
endif

COPTS = -mt -xs -KPIC -w -DSQLUNIX -DSQLSUN $(COPTS_64) -g
LDFLAGS =  -lpthread -lm -lc -lCrun $(LDFLAGS_64)

$(UNFENCED_WRAPPER_ARCHIVE_LIB): $(UNFENCED_WRAPPER_OBJ_FILES)
	$(CCC_LIB) \
                -G -i \
                -eUnfencedWrapper_Hook \
                $(filter %.o, $^) \
                $(LDFLAGS) \
                -o $@
        

# compile and link the fenced wrapper code

ifdef 32_BIT_FENCED
COPTS_64 =
LDFLAGS_64 =
FENCED_LIB_DIR = ${UDB_LIB32_DIR}
else 
ifeq ("$(ARCH)","i386")
COPTS_64 = -xarch=amd64
LDFLAGS_64 = -xarch=amd64
else
COPTS_64 = -xarch=v9
LDFLAGS_64 = -xarch=v9 
endif
FENCED_LIB_DIR = ${UDB_LIB64_DIR}
endif

COPTS = -mt -xs -KPIC -w -DSQLUNIX -DSQLSUN $(COPTS_64) -g
LDFLAGS =  -lpthread -lm -lc -lCrun $(LDFLAGS_64)

${FENCED_WRAPPER_ARCHIVE_LIB}: ${FENCED_WRAPPER_OBJ_FILES} ${UDB_EXPORTS}
	${CCC_LIB} \
                -G -i \
                -eFencedWrapper_Hook \
                $(filter %.o, $^) \
                $(LDFLAGS) \
                -o $@
        
move:
	 -rm -f ${UNFENCED_LIB_DIR}/${UNFENCED_WRAPPER_ARCHIVE_LIB}
	 -rm -f ${FENCED_LIB_DIR}/${FENCED_WRAPPER_ARCHIVE_LIB}
	 cp ${UNFENCED_WRAPPER_ARCHIVE_LIB} ${UNFENCED_LIB_DIR}    
	 cp ${FENCED_WRAPPER_ARCHIVE_LIB} ${FENCED_LIB_DIR}    
	 cp ${UNENCED_LIB_DIR}/libdb2sqqgtop.$(SHARED_LIB_EXT) ${UNFENCED_LIB_DIR}/$(WRAPPER_ARCHIVE_LIB)

#
# Pattern rules
#
%.o : %.C 
	${CCC} ${COPTS} ${UDB_FLAGS} -I${UDB_INCLUDE_DIR} -c $<

#
# Useful targets
#
depend: $(wildcard *.u)
	-cat $^ /dev/null | egrep -v "/usr/" > $@

clean:
	rm -f *.o *.u *.map depend ${UNFENCED_WRAPPER_ARCHIVE_LIB}  ${FENCED_WRAPPER_ARCHIVE_LIB}

include depend
