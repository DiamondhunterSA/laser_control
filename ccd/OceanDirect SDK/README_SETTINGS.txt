Notes:
--------
1. The python wrapper requires Python-3.9.5 or later. The naming convention of python wrapper function 
   follows closely with the C-API as much as possible. For example, the C-API prefix (odapi/odapi_adv) 
   were removed and the remaining text were used as a python function name.

   OceanDirect is split into two installers:
      * Core - contains all common functions to manipulate the spectrometers. This is the installer 
               that goes to most users.
      * Admin - contains less commonly used and advance functions. This installer is available upon request.

   NOTE: 
   Be sure to use the correct version of Python and OceanDirect installer to avoid bit 
   mismatch. For example, an x64 Python must use an x64 OceanDirect.

2. Windows
   A. Ocean Direct Home variable is automatically created by windows installer.
      OCEANDIRECT_HOME=C:\Program Files\Ocean Insight\OceanDirect-1.34.0
      PYTHONPATH=%OCEANDIRECT_HOME%\python

3. Linux / Mac
   -after copying the rule files, the installer will automatically reload and trigger the rule file. If 
   this doesn't work, use udevadm command to manually reload/trigger rule files. 

   A. libusb-1.0
      This is the minimum version of usb library to be installed in linux.

   B. Rule Files
      The rules file is automatically copied by the installer to the right folder. The installer then reload 
      and trigger the rule file. In the linux ARM environment, you have to copy the rule file yourselves 
      and manually reload/trigger them.

   C. When using Python wrapper, enable these two variables like this:
      PYTHONPATH=/home/user1/OceanDirect-1.34/python
      LD_LIBRARY_PATH=/home/user1/OceanDirect-1.34/python/oceandirect/lib

   D. When using C/C++ functions only, you can define this variable to point to the ./lib folder.
      LD_LIBRARY_PATH=/home/user1/OceanDirect-1.34/lib
 
4. Run sample test program (for linux, be sure to use python3):
     - python3 ./test_get_spectra.py

