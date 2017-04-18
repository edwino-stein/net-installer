
#define STRINGIZE2(s) #s
#define STRINGIZE(s) STRINGIZE2(s)

#define VERSION_MAJOR            0
#define VERSION_MINOR            9
#define VERSION_REVISION         3
#define VERSION_BUILD            0

#define VER_COMPANY_NAME_STR "Edwino Stein"
#define VER_FILE_DESCRIPTION_STR "Assistente de instalação do Windows através de um servidor PXE"
#define VER_FILE_VERSION         VERSION_MAJOR, VERSION_MINOR, VERSION_REVISION, VERSION_BUILD
#define VER_FILE_VERSION_STR     STRINGIZE(VERSION_MAJOR)     \
                                    "." STRINGIZE(VERSION_MINOR) \
                                    "." STRINGIZE(VERSION_REVISION) \
                                    "." STRINGIZE(VERSION_BUILD) \

#define VER_FILE_VERSION_SIMPLE_STR     STRINGIZE(VERSION_MAJOR)     \
                                    "." STRINGIZE(VERSION_MINOR) \
                                    "." STRINGIZE(VERSION_REVISION) \

#define VER_PRODUCTNAME_STR      "NetInstaller"
#define VER_PRODUCT_VERSION      VER_FILE_VERSION
#define VER_PRODUCT_VERSION_STR  VER_FILE_VERSION_STR
#define VER_ORIGINAL_FILENAME_STR   VER_PRODUCTNAME_STR ".exe"
#define VER_INTERNAL_NAME_STR    VER_ORIGINAL_FILENAME_STR
#define VER_DEV_YEAR			 "2017"
#define VER_COPYRIGHT_STR        "Copyright (C) 2017"

#ifdef _DEBUG
	#define VER_VER_DEBUG          VS_FF_DEBUG
	#define VER_BUILD_SET_STR	   "d"
#else
	#define VER_VER_DEBUG          0
	#define VER_BUILD_SET_STR	   "r"
#endif

#define VER_FILEOS               VOS_NT_WINDOWS32
#define VER_FILEFLAGS            VER_VER_DEBUG
#define VER_FILETYPE             VFT_APP

#ifdef _M_X64
	#define VER_ARCH_STR "x64"
#else
	#define VER_ARCH_STR "x86"
#endif


