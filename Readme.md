



Authentication library V34
PalmSecure™ SDK V02.
“PalmSecure Sensor V2” and “PalmSecure-F Pro".
Authentication library V34 Professional Edition.
Microsoft® Visual Studio® 2019.


Prerequisites
---------------
Windows (x64) ：Microsoft® C/C++ Optimizing Compiler Version
19.28.29914 for x64 (Build Tools for Visual Studio 2019)
Linux(x64)：gcc 4.8.5 (Included in CentOS 7.9)

(1) Install the Sensor driver.
(2) Install the Authentication library and set the operational environment setting
file “PvAPI.INI”.
(3) Confirm firmware version level of the Sensor unit and update the firmware if
necessary.
(4) Set your application key.
Define your “application key” printed in the “License Agreement”


Building the App code
----------------------
windows

cl BioAPI_sample_C_Verify.c /D WIN32 /I .\include /link .\lib\F3BC4BIO.lib
cl BioAPI_sample_C_Identify.c /D WIN32 /I .\include /link .\lib\F3BC4BIO.lib

linux
gcc BioAPI_sample_C_Verify.c -DUNIX -I./Inc -L./LM -lf3bc4bio
gcc BioAPI_sample_C_Identify.c -DUNIX -I./Inc -L./LM -lf3bc4bio



Running the Built Program
--------------------------
Confirm that the Sensor is connected, and then run the built program by
double-clicking it or command-line input.
The C Sample source is programmed to do the following processes.
•
BioAPI_sample_C_Verify
(1) Calling “BioAPI_Enroll” 1 time. (Note)
Note) If enrollment data file “BIRData.dat” exists in the current folder, this
process is skipped.
(2) Calling “BioAPI_Verify” 1 time.
(3) Calling “BioAPI_Capture” 1 time.
(4) Calling “BioAPI_VerifyMatch” 1 time.
*Output files of the program
BioAPI_sample_C_Verify stores enrollment data “BIRData.dat”, capture data “BIRCapData.dat”, and silhouette image data
“silhouette.bmp” in the current folder.
Delete these files yourself as necessary.

BioAPI_sample_C_Identify
(1) Calling “BioAPI_Enroll” 2 times.
(2) Calling “BioAPI_Identify” 1 time.
(3) Calling “BioAPI_Capture” 1 time.
(4) Calling “BioAPI_IdentifyMatch” 1 time.
★Output data of the program
BioAPI_sample_C_Identify stores enrollment data and capture data on the memory.
The data is automatically deleted when you close the program.
Note that error information is output when an error occurred in the Authentication library.


Random tests
---------------
/usr/bin/gcc -o BioAPI_sample_C_Verify BioAPI_sample_C_Verify.o -L ./LM -Wl,-rpath -Wl,./ -lf3bc4bio -lf3bc4com -lf3bc4bsp -lf3bc4cap -lf3bc4mat

/usr/bin/gcc -c -g -Wall -DUNIX -I ./ -I ./Inc -I /usr/bin/ BioAPI_sample_C_Identify_HTTP_API.c

/usr/bin/gcc -o BioAPI_sample_C_Identify_HTTP_API BioAPI_sample_C_Identify.o -L ./LM -Wl,-rpath -Wl,./ -lf3bc4bio -lf3bc4com -lf3bc4bsp -lf3bc4cap -lf3bc4mat


/usr/bin/gcc -o BioAPI_sample_C_Verify.o BioAPI_sample_C_Verify.c -L ./LM -Wl,-rpath -Wl,./ -lf3bc4bio -lf3bc4com -lf3bc4bsp -lf3bc4cap -lf3bc4mat


gcc -c BioAPI_sample_C_Verify.c -o BioAPI_sample_C_Verify.o

gcc -c BioAPI_sample_C_Verify.c -o BioAPI_sample_C_Verify.o

gcc -c BioAPI_sample_C_Identify.c -o BioAPI_sample_C_Identify.o

gcc -c BioAPI_sample_C_Identify_HTTP_API.c -o BioAPI_sample_C_Identify_HTTP_API.o && 

/usr/bin/gcc -o BioAPI_sample_C_Identify_HTTP_API BioAPI_sample_C_Identify.o -L ./LM -Wl,-rpath -Wl,./ -lf3bc4bio -lf3bc4com -lf3bc4bsp -lf3bc4cap -lf3bc4mat



http://localhost:8000/api/identify

---------------------

More NOtes
-----------------------
Stand-alone
configuration


License
--------------
Version of Authentication library
･ Edition of Authentication library
(Professional Edition/Enterprise Edition)
･ In case of V33 Professional Edition, the type of license
(Developer/Distribution)
･ In case of Enterprise Edition or V33 Professional Edition Developer
license, OS type


License for Professional Edition   Target hardware:(stand-alone or client in the client-server configuration)
License for Enterprise Edition    Target hardware
(server in the client-server configuration)


Required environment for the license file
The license file is valid only if the following matches with the target hardware.
･ The version and edition of the Authentication library
･ The OS type (in case of Enterprise Edition or Authentication library
V33 Professional Edition Developer license)



gcc BioAPI_sample_C_Identify.c -DUNIX -I./Inc -L./LM -lf3bc4bio


*************
If you have only the source file (BioAPI_sample_C_Identify_HTTP_API.c), you would typically first compile it into an object file using a command like:


/usr/bin/gcc -c BioAPI_sample_C_Identify_HTTP_API.c -o BioAPI_sample_C_Identify.o
And then you can use the original linking command you provided to create the executable.
This command assumes that the source code file (BioAPI_sample_C_Identify_HTTP_API.c) has already been compiled into an object file (BioAPI_sample_C_Identify.o)

/usr/bin/gcc -o BioAPI_sample_C_Identify_HTTP_API BioAPI_sample_C_Identify.o -L ./LM -Wl,-rpath -Wl,./ -lf3bc4bio -lf3bc4com -lf3bc4bsp -lf3bc4cap -lf3bc4mat



original identify
-----------
/usr/bin/gcc -c BioAPI_sample_C_Identify.c -o BioAPI_sample_C_Identify.o

/usr/bin/gcc -o BioAPI_sample_C_Identify BioAPI_sample_C_Identify.o -L ./LM -Wl,-rpath -Wl,./ -lf3bc4bio -lf3bc4com -lf3bc4bsp -lf3bc4cap -lf3bc4mat



/usr/bin/gcc -o BioAPI_sample_C_Identify_HTTP_API BioAPI_sample_C_Identify.o -L ./LM -Wl,-rpath -Wl,./ -lf3bc4bio -lf3bc4com -lf3bc4bsp -lf3bc4cap -lf3bc4mat


errors: nov 28
-------------------
When compile file.c I error: expected ')' before '*' token

Because the system memory.h is shadowing your memory.h, causing the #include to succeed without declaring your types. Several possible fixes:

Rename your file -- probably for the best in any case, to reduce potential confusion.
Include your file via a prefix subdirectory (e.g., #include <myproj/memory.h>).
Move your file into the same directory as the source file, allowing the #include precedence rules for filenames wrapped in " to take effect.
Ensure that your C pre-processor include path options place your project header path prior to the system header paths.


Working makefile:
-----------------------
Check Library Existence:

Make sure that the required shared libraries (libf3bc4bio.so, libf3bc4com.so, etc.) are present in the ./LM directory.
Check Library Directory:

Verify that the -L ./LM option correctly points to the directory containing the shared libraries.
Check Runtime Path:

Ensure that -Wl,-rpath -Wl,./ correctly sets the runtime path. This tells the dynamic linker where to find the shared libraries when the executable is run.
Run ldd Command:

After compiling your program, you can use the ldd command to check the shared library dependencies and their paths. For example:
bash
ldd BioAPI_sample_C_Identify
This command will show you which libraries your executable is linked against and where they are expected to be found.
Full Compilation and Linking Command:

If you still encounter issues, consider printing the full compilation and linking commands generated by make. This can help you inspect the actual commands being executed.
Check Library Loading at Runtime:

When running your executable, ensure that the ./LM directory is part of the system's library search path. You can modify the LD_LIBRARY_PATH environment variable for testing:
bash

export LD_LIBRARY_PATH=./LM:$LD_LIBRARY_PATH
./BioAPI_sample_C_Identify
This ensures that the dynamic linker looks in the ./LM directory for the required shared libraries.
Check File Permissions:

Verify that the user running the executable has the necessary permissions to read the shared libraries in the ./LM directory.


./BioAPI_sample_C_Identify
--
PvAPI_ApAuthenticate
--
BioAPI_ModuleLoad
--
BioAPI_ModuleAttach
 ErrorLevel  = 0x02
 ErrorCode   = 0x01
 ErrorDetail = 0x02010002
 ErrorInfo1 = 0x00000000
 ErrorInfo2 = 0x10010015
 ErrorInfo3[0] = 0x00006021
 ErrorInfo3[1] = 0x00000000
 ErrorInfo3[2] = 0x00000000
 ErrorInfo3[3] = 0x00000000


----
Error indicates sensor related erro
Install sensr driver by going into its source and running 
Edit the 
To find the path to your kernel source directory, you can follow these steps:

Check Kernel Header Installation:
First, check if your system has the kernel headers installed. The kernel headers provide the necessary files for building kernel modules.

On Debian/Ubuntu-based systems, you can install the kernel headers with the following command:


sudo apt-get install linux-headers-$(uname -r)
make

edit makefile
----------
KERNDIR := /lib/modules/$(shell uname -r)/build

-----------
sudo make
make[1]: Entering directory '/usr/src/linux-headers-6.2.0-39-generic'
  SYNC    include/config/auto.conf.cmd
  HOSTCC  scripts/basic/fixdep
  HOSTCC  scripts/kconfig/conf.o
  HOSTCC  scripts/kconfig/confdata.o
  HOSTCC  scripts/kconfig/expr.o
  LEX     scripts/kconfig/lexer.lex.c
/bin/sh: 1: flex: not found
make[3]: *** [scripts/Makefile.host:9: scripts/kconfig/lexer.lex.c] Error 127
make[2]: *** [Makefile:711: syncconfig] Error 2
Makefile:789: include/config/auto.conf.cmd: No such file or directory
make[1]: *** [Makefile:812: include/config/auto.conf.cmd] Error 2
make[1]: *** [include/config/auto.conf.cmd] Deleting file 'include/generated/rustc_cfg'
make[1]: *** [include/config/auto.conf.cmd] Deleting file 'include/generated/autoconf.h'
make[1]: Leaving directory '/usr/src/linux-headers-6.2.0-39-generic'
make: *** [Makefile:29: all] Error 2



install glibc
----
$ sudo apt install glibc-source -y


copy
palmsecure.rules to “/etc/udev/rules.d



----------------------------------
restarting
--------------------
urce$ ./BioAPI_sample_C_Identify 
--
PvAPI_ApAuthenticate
--
BioAPI_ModuleLoad
 ErrorLevel  = 0x03
 ErrorCode   = 0x04
 ErrorDetail = 0x03040002
 ErrorInfo1 = 0x00000000
 ErrorInfo2 = 0x10260000
 ErrorInfo3[0] = 0x0000A002
 ErrorInfo3[1] = 0x00010001
 ErrorInfo3[2] = 0x00000000
 ErrorInfo3[3] = 0x00000000
law@lawpc:~/Documents/authentication/fujitsu/BIO_HTTP_API_C/source$ export LD_LIBRARY_PATH=./LM:$LD_LIBRARY_PATH
law@lawpc:~/Documents/authentication/fujitsu/BIO_HTTP_API_C/source$ ./BioAPI_sample_C_Identify 
--
PvAPI_ApAuthenticate
--
BioAPI_ModuleLoad
--
BioAPI_ModuleAttach
--
BioAPI_SetGUICallbacks
--
PvAPI_SetProfile
--
BioAPI_Enroll(No.1)
-MessageCB: PvAPI_NOTIFY_CAP_GUID_START[0x02030021]
 Capturing Start. (1/2)
-MessageCB: PvAPI_NOTIFY_CAP_GUID_NO_HANDS
 Place your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_MOVING
 Stop moving your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_LESSINFO
 Unclench your hand and place correctly.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_MOVING
 Stop moving your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_LESSINFO
 Unclench your hand and place correctly.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_NO_HANDS
 Place your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_MOVING
 Stop moving your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_LESSINFO
 Unclench your hand and place correctly.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_MOVING
 Stop moving your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_LESSINFO
 Unclench your hand and place correctly.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_NO_HANDS
 Place your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_MOVING
 Stop moving your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_LESSINFO
 Unclench your hand and place correctly.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_MOVING
 Stop moving your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_CAPTURING
 Now capturing.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_START[0x02030022]
 Capturing Start. (2/2)
-MessageCB: PvAPI_NOTIFY_CAP_GUID_BADIMAGE
 Move your hand away from the sensor.
-MessageCB: State: Silhouette
-MessageCB: PvAPI_NOTIFY_CAP_GUID_NO_HANDS
 Place your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_MOVING
 Stop moving your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_CAPTURING
 Now capturing.
 Enroll done.
--
BioAPI_GetBIRFromHandle
--
BioAPI_FreeBIRHandle
--
BioAPI_Enroll(No.2)
-MessageCB: PvAPI_NOTIFY_CAP_GUID_START[0x02030021]
 Capturing Start. (1/2)
-MessageCB: PvAPI_NOTIFY_CAP_GUID_CAPTURING
 Now capturing.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_NO_HANDS
 Place your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_MOVING
 Stop moving your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_LESSINFO
 Unclench your hand and place correctly.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_MOVING
 Stop moving your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_CAPTURING
 Now capturing.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_START[0x02030022]
 Capturing Start. (2/2)
-MessageCB: PvAPI_NOTIFY_CAP_GUID_BADIMAGE
 Move your hand away from the sensor.
-MessageCB: State: Silhouette
-MessageCB: PvAPI_NOTIFY_CAP_GUID_NO_HANDS
 Place your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_MOVING
 Stop moving your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_ROLL_RIGHT
 Lay your hand flat.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_LESSINFO
 Unclench your hand and place correctly.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_MOVING
 Stop moving your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_CAPTURING
 Now capturing.
 Enroll done.
--
BioAPI_GetBIRFromHandle
--
BioAPI_FreeBIRHandle
--
BioAPI_Identify
-MessageCB: PvAPI_NOTIFY_CAP_GUID_START[0x02030011]
 Capturing Start. (1/1)
-MessageCB: PvAPI_NOTIFY_CAP_GUID_CAPTURING
 Now capturing.
-MessageCB: State: Silhouette
-MessageCB: PvAPI_NOTIFY_CAP_GUID_PHASE_END
 Now authenticating.
--
BioAPI_Identify Result: Number of Candidate: 2
Candidate01 Enroll-No.01 Score:10000
Candidate02 Enroll-No.02 Score:10000
--
BioAPI_Capture
-MessageCB: PvAPI_NOTIFY_CAP_GUID_START[0x02030011]
 Capturing Start. (1/1)
-MessageCB: PvAPI_NOTIFY_CAP_GUID_CAPTURING
 Now capturing.
-MessageCB: State: Silhouette
 Capture done.
--
BioAPI_GetBIRFromHandle
--
BioAPI_FreeBIRHandle
--
BioAPI_IdentifyMatch
-MessageCB: PvAPI_NOTIFY_CAP_GUID_START[0x02030011]
 Capturing Start. (1/1)
-MessageCB: PvAPI_NOTIFY_CAP_GUID_PHASE_END
 Now authenticating.
--
BioAPI_IdentifyMatch Result: Number of Candidate: 2
Candidate01 Enroll-No.01 Score:10000
Candidate02 Enroll-No.02 Score:10000
--
BioAPI_ModuleDetach
--
BioAPI_ModuleUnload

---------------------------
./BioAPI_sample_C_Identify 
--
PvAPI_ApAuthenticate
--
BioAPI_ModuleLoad
--
BioAPI_ModuleAttach
--
BioAPI_SetGUICallbacks
--
PvAPI_SetProfile
--
BioAPI_Enroll(No.1)
-MessageCB: PvAPI_NOTIFY_CAP_GUID_START[0x02030021]
 Capturing Start. (1/2)
-MessageCB: PvAPI_NOTIFY_CAP_GUID_NO_HANDS
 Place your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_LESSINFO
 Unclench your hand and place correctly.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_MOVING
 Stop moving your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_CAPTURING
 Now capturing.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_START[0x02030022]
 Capturing Start. (2/2)
-MessageCB: PvAPI_NOTIFY_CAP_GUID_BADIMAGE
 Move your hand away from the sensor.
-MessageCB: State: Silhouette
-MessageCB: PvAPI_NOTIFY_CAP_GUID_NO_HANDS
 Place your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_ROUND
 Lay your hand flat.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_LESSINFO
 Unclench your hand and place correctly.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_MOVING
 Stop moving your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_CAPTURING
 Now capturing.
 Enroll done.
--
BioAPI_GetBIRFromHandle
--
BioAPI_FreeBIRHandle
--
BioAPI_Enroll(No.2)
-MessageCB: PvAPI_NOTIFY_CAP_GUID_START[0x02030021]
 Capturing Start. (1/2)
-MessageCB: PvAPI_NOTIFY_CAP_GUID_CAPTURING
 Now capturing.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_START[0x02030022]
 Capturing Start. (2/2)
-MessageCB: PvAPI_NOTIFY_CAP_GUID_BADIMAGE
 Move your hand away from the sensor.
-MessageCB: State: Silhouette
-MessageCB: PvAPI_NOTIFY_CAP_GUID_NO_HANDS
 Place your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_ROUND
 Lay your hand flat.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_LESSINFO
 Unclench your hand and place correctly.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_MOVING
 Stop moving your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_CAPTURING
 Now capturing.
 Enroll done.
--
BioAPI_GetBIRFromHandle
--
BioAPI_FreeBIRHandle
--
BioAPI_Identify
-MessageCB: PvAPI_NOTIFY_CAP_GUID_START[0x02030011]
 Capturing Start. (1/1)
-MessageCB: PvAPI_NOTIFY_CAP_GUID_CAPTURING
 Now capturing.
-MessageCB: State: Silhouette
-MessageCB: PvAPI_NOTIFY_CAP_GUID_PHASE_END
 Now authenticating.
--
BioAPI_Identify Result: Number of Candidate: 2
Candidate01 Enroll-No.01 Score:10000
Candidate02 Enroll-No.02 Score:10000
--
BioAPI_Capture
-MessageCB: PvAPI_NOTIFY_CAP_GUID_START[0x02030011]
 Capturing Start. (1/1)
-MessageCB: PvAPI_NOTIFY_CAP_GUID_CAPTURING
 Now capturing.
-MessageCB: State: Silhouette
 Capture done.
--
BioAPI_GetBIRFromHandle
--
BioAPI_FreeBIRHandle
--
BioAPI_IdentifyMatch
-MessageCB: PvAPI_NOTIFY_CAP_GUID_START[0x02030011]
 Capturing Start. (1/1)
-MessageCB: PvAPI_NOTIFY_CAP_GUID_PHASE_END
 Now authenticating.
--
BioAPI_IdentifyMatch Result: Number of Candidate: 2
Candidate01 Enroll-No.01 Score:10000
Candidate02 Enroll-No.02 Score:10000
--
BioAPI_ModuleDetach
--
BioAPI_ModuleUnload


-------------------------

VERIFY
----
ource$ ./BioAPI_sample_C_Verify 
--
PvAPI_ApAuthenticate
--
BioAPI_ModuleLoad
--
BioAPI_ModuleAttach
--
BioAPI_SetGUICallbacks
--
BioAPI_Enroll
-MessageCB: PvAPI_NOTIFY_CAP_GUID_START[0x02030021]
 Capturing Start. (1/2)
-MessageCB: PvAPI_NOTIFY_CAP_GUID_NO_HANDS
 Place your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_MOVING
 Stop moving your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_LESSINFO
 Unclench your hand and place correctly.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_MOVING
 Stop moving your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_CAPTURING
 Now capturing.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_NO_HANDS
 Place your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_MOVING
 Stop moving your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_LESSINFO
 Unclench your hand and place correctly.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_MOVING
 Stop moving your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_CAPTURING
 Now capturing.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_START[0x02030022]
 Capturing Start. (2/2)
-MessageCB: PvAPI_NOTIFY_CAP_GUID_BADIMAGE
 Move your hand away from the sensor.
-MessageCB: State: Silhouette
-MessageCB: PvAPI_NOTIFY_CAP_GUID_NO_HANDS
 Place your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_MOVING
 Stop moving your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_LESSINFO
 Unclench your hand and place correctly.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_MOVING
 Stop moving your hand.
-MessageCB: PvAPI_NOTIFY_CAP_GUID_CAPTURING
 Now capturing.
 BioAPI_Enroll done.
--
BioAPI_GetBIRFromHandle
--
BioAPI_FreeBIRHandle
--
 FILE: BIRData.dat (DataSize=7105)
--
BioAPI_Verify
-MessageCB: PvAPI_NOTIFY_CAP_GUID_START[0x02030011]
 Capturing Start. (1/1)
-MessageCB: PvAPI_NOTIFY_CAP_GUID_CAPTURING
 Now capturing.
-MessageCB: State: Silhouette
-MessageCB: PvAPI_NOTIFY_CAP_GUID_PHASE_END
 Now authenticating.
--
BioAPI_Verify Result: Auth-OK
--
BioAPI_Capture
-MessageCB: PvAPI_NOTIFY_CAP_GUID_START[0x02030011]
 Capturing Start. (1/1)
-MessageCB: PvAPI_NOTIFY_CAP_GUID_CAPTURING
 Now capturing.
-MessageCB: State: Silhouette
 Capture done.
--
BioAPI_GetBIRFromHandle
--
BioAPI_FreeBIRHandle
--
 FILE: BIRCapData.dat (DataSize=9939)
--
BioAPI_VerifyMatch
-MessageCB: PvAPI_NOTIFY_CAP_GUID_START[0x02030011]
 Capturing Start. (1/1)
-MessageCB: PvAPI_NOTIFY_CAP_GUID_PHASE_END
 Now authenticating.
--
BioAPI_VerifyMatch Result: Auth-OK
--
BioAPI_ModuleDetach
--
BioAPI_ModuleUnload