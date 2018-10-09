===============================================================================
HW v4.8.2 for Windows 9x - Windows 10 (RC), Server 2003-2014 (32/64 bit)
Copyright (c) 1996-2015 Marvin Test Solutions Inc.
All Rights Reserved.
ATEasy is a registered trademark of Marvin Test Solutions Inc.
===============================================================================
The HW package - Hardware Access Driver, is used by all 
MTS instrument drivers and ATEasy. It provide access to the PC 
resources (memory, IO ports, DMA etc.), PCI/PXI configuration and more. 
The HW package includes libraries used to program and create instrument 
drivers for PC/PCI/PXI based instruments. A PXI/PCI Explorer utility to 
configure and display PXI/PC based systems is also included. 
The utility includes a VISA configuration utility for PXI and PXI 
express instruments (similar to NI-MAX) and support for MTS chassis  
and controllers

This text file contains installation notes for this
release as well as additional technical notes.

The following topics are covered:

    1. HW Files.
    2. Installation Notes.
    3. Licensing.
    4. Known problems
    5. Changes
    6. Technical support
    7. Trademark Notes

1. HW Files
===============================================================================
HwSetup.exe - Setup for HW.

HwTest.exe - A program to test the HW driver and to read/write
    to I/O ports, memory and to display PCI resources.

Hw.sys - Windows 2000-7 (32 bit) kernel mode device driver provides access
    to I/O ports, memory and PCI resources, installed to the
    Windows System Drivers directory.
Hw64.sys - Windows XP-7 (64 bit) kernel mode device driver provides access
    to I/O ports, memory and PCI resources, installed to the
    Windows System Drivers directory.

HwDevice.sys - Windows 2000-7 (32 bit) kernel mode device driver for HW.INF
    boards, installed to the Windows System\Drivers directory.
HwDevice64.sys - Windows XP-7 (64 bit) kernel mode device driver for HW.INF
    boards, installed to the Windows System\Drivers directory.

HwPxiExpress.dll - Provides information to MTS Chassis, 
    Controller and Peripheral PXIe devices, installed to the 
    Windows System directory.

HwPxiExpress64.dll - Provides information to MTS Chassis, 
    Controller and Peripheral PXIe devices, installed to the 
    Windows System directory.
	
Hw.vxd - Windows 9x/Me virtual device driver provides access
    for memory and PCI resources, installed to the
    Windows System directory.

HwCIns16.dll - Windows 9x/Me Class Installer for HW.
HwCIns32.dll - Windows 2K-7, 32 bit, Class Installer for HwDevice.sys
HwCIns64.dll - Windows XP-7, 64 bit, Class Installer for HwDevice64.sys

HwVdd.dll - VDD for 16 app running on Windows 2K-7, 32 bit, installed
    to the Windows System directory.

Hw.inf - Driver information files for MTS's PXI/PCI boards.
    Installed to the HW and Windows System\INF directory.
Hw.cat - Signed catalog file. Installed to the HW directory.

HwPciExplorer64.cpl - Windows 2K-7, 32 bit, PXI/PCI Explorer - Windows
    Control Panel applet to display the current PXI/PCI devices and to
    assign slot numbers	to device resources. Slots numbers are required
    to identify	a PCI/PXI board when using MTS board driver. 
    Installed to the Windows System directory.
HwPciExplorer64.cpl - Windows XP-7, 64 bit, PXI/PCI Explorer - Windows
    Control Panel applet to display the current PXI/PCI devices and to
    assign slot numbers	to device resources. Slots numbers are required
    to identify	a PCI/PXI board when using MTS board driver. 
    Installed to the Windows System directory.

Hw.dll - 32 bit DLL to support external application programming 
    using the hw.h. Installed to the Windows System folder.
Hw64.dll - 64 bit DLL to support external application programming 
    using the hw.h. Installed to the Windows System folder.

Hw.c -  File to include in your C/C++ project provides access to the
    HW.SYS/VXD drivers.
Hw.h -  Include file to include in your C/C++ project provides
    functions prototypes to Hw.c files
HwIoCtl.h - File used by Hw.h/c.

GX7000.ini ,
GX7100.ini ,
GX7200.ini ,
GX7300.ini ,
GX7600.ini ,
GX7910.ini ,
GX7920.ini ,
GX7922.ini ,
GX7924.ini ,
GX7924.ini ,
GX7927.ini ,
GX7932.ini ,
GX7934.ini -
    PXI configuration files for MTS Chassis and Controllers.
    Used by PXI explorer or NI-MAX to configure PXISYS.ini, PXISysE.ini 

ReadMe.txt - This file.

2. Installation Notes
===============================================================================
The HW driver is installed by the MTS product you purchased. It
is shared between ATEasy and MTS board drivers.

If you are using the HW with a PCI board and HW was not installed it
is recommended to first install the board driver and then install the
board. That way the Plug and Play operating system will find the driver
without requiring you to search for a driver setup information file
(HW.INF). I

If you installed the PXI board before installing this driver Windows
New Hardware Found Wizard may prompt you to locate the driver
information file (HW.INF). At that point, you may select the HW.INF
file from the product setup directory and follow the instruction on
the screen.

Under Windows 2K-8.x, the kernel mode device driver service, HW.SYS or
HW64.sys must be installed and started before your product
can be used. Before installing the kernel mode driver, you must
be logged on as a user with administrator privileges.

The Setup program normally installs the kernel mode driver and starts
it automatically. However, if the current user is not logged-in
as an administrator, the kernel mode driver installation fails.

This section explains how to install the kernel mode driver manually
when the Setup program FAILS to do so.

To manually install the HW, perform the following:

1.	Log in with administrator privileges (Windows 2K-8.x only).

2.	Open a Command prompt window.

3.	Change to the installation destination directory by using the CD
	command. For example:

		CD \Program Files\Marvin Test Solutions\HW

4.	At the command prompt, type the following command:

		HWSETUP install start

	or if WIN16 support is required (when running ATEasy 2.x under
	NT/2000, 32 bit Windows only):

		HWSETUP -vdd install start


	If the current working directory is different from the directory where
	the HW folder resides, you may specify your own custom path.
	For example:

		HWSETUP install=a: start

Under Windows 2K-7 the Setup program installs the driver as a service.
The service can be started or stopped from the Windows NT control
panel Devices applet.
The -vdd switch can be removed from the command if support for 16-bit
drivers are not required (only the 32-bit DLLs will be used in this case).

Additional HWSETUP.EXE command line options are available.
To display these options, type HWSETUP without command line options.

3. Licensing
===============================================================================
The Setup program HWSETUP.EXE, the device driver HW.SYS, HW.VXD, 
HW64.SYS, HW.DLL, HW64.DLL and HWVDD.DLL files may be distributed 
royalty free provided it is provided with a MTS product you have
purchased.

4. Known problems
===============================================================================
- PCI devices share the same I/O port address or memory resources
  on Computers running Microsoft Windows NT 4.0.
  Cause:   The Windows NT Hardware Abstraction Layer (HAL) HAL assigned an
           I/O port address or memory resource a PCI device that overlaps
           with an existing PCI device therefore causing a PCI resource conflict
           on your system. Under normal operation, the system BIOS is responsible
           for setting the PCI device resource requirements. When Windows NT loads,
           the Windows NT HAL sometimes moves the PCI device resources. PCI devices
           are dynamically configurable. However, the Windows NT HAL sometimes
           assigns overlapping I/O port addresses or memory resources for the PCI
           devices.
  Solution: Adding to the BOOT.INI file the /PCILOCK switch forces the Windows NT HAL
           to use the PCI device resources aloocatred by the system BIOS. After
           modifying the BOOT.INI file the system must be rebooted.
  Example: The following is a typical Boot.INI file with the /PCILOCK switch

             [boot loader]
             timeout=3
             [operating systems]
             multi(0)disk(0)rdisk(0)partition(1)\WINNT="Windows NT Workstation
             Version 4.00"/PCILOCK
             multi(0)disk(0)rdisk(0)partition(1)\WINNT="Windows NT Workstation

             Version 4.00 [VGA mode]" /basevideo /sos /PCILOCK

5. Changes
===============================================================================
HW v4.8.2, June 24, 2015
- Signed driver with dual certificates (SHA1, SHA256) to support older Windows
  (fixed).
- PCI/PXI Explorer:
  - Rename PXI Settings page to VISA.
  - Add a checbox to disable using VISA device driver for Marvin Test Solutions
    devices. Check the checkbox in case VISA device driver are not working, 
    changing the value of the checkbox requires restart. After restart
    VISA device driver will be removed from Marvin Test devices and HW will be
    used instead. Checking the checkbox will reassign Marvin Test devices
    to use VISA. By default VISA is used if installed in your system. This will
    allow you to see the Marvin Test devices in VISA (in addition to HW).
- Setup mistakenly prompts for restart at the end (fixed).

HW v4.8.1, May 21, 2015
- HwGetVersion() returns empty string and 0 value with 64 bit DLL (fixed).
- PXI Explorer does not work when using MXI-Express (e.g. NI-8360) 
  with Express chassis (e.g. GX7200/GX7600).
- Setup. Remove VDD installation (for 16-bit applications) from 64 bit 
  Windows (not supported).
- Setup. Delete/Uninstall will not remove all files (fixed).
- Updated Code Sign Certificate from Geotest to Marvin Test Solutions, Inc.
- Added support for Windows 10 (tested with pre-release).
  
HW v4.8.0, November 24, 2014
- BSOD when shutting down Windows when using interrupt functions (fixed).
- 4.7.3 setup not installing/uninstalling the version correctly (fixed)
- Direct support for ATEasy USB educational board, no longer requires 
  local administrator privileges after installation when plugging the USBTMC 
  device. Does not act as a filter driver for USBTMC anymore.
- Support for PXI-2 Software Specifications Rev 2.4
- HW.INF: Support for NI-VISA Interrupts for GX1649, GX6192, GX6256
- PXI Explorer - New tab "PXI System Settings" used to display and set the 
  default VISA provider and default trigger manager. Setting the default 
  provider to Marvin Test Solutions to prevent NI-VISA erasing the PXISYS.INI 
  file on computer start.
- Known Issues
  - On Computers that have NI-VISA v14.x. After the computer starts, device 
    manager will show warning icon next to each MTS device (error code 39, 
    failed to load NiViPciKw Service"). As result MTS devices will not operate 
    correctly and sometimes will not have resources (memory) assigned to them. 
    This issue can be fixed by uninstalling NI-VISA, Restart, and then 
    reinstalling NI-VISA. Or by setting the Default VISA provider to Non-
    NI using the new PXI Explorer.

HW v4.7.3, September 25, 2014
- Add support for GX6192.
- Add 64 bit support for express chassis.
- VISA resource string returned from HwPciGetSlotVisaResource() not 
  compatible with all instruments (fixed).
- Instrument resources not allocated properly after installing NI-VISA v14.0
  (fixed). If your system have instruments or chassis  that cannot be 
  initialized:
  - Install HW 4.7.3
  - Open the Windows Device Manager
  - Locate MTS devices and for each, right click and select Uninstall
  - Restart
  After restart, all MTS boards/chassis will work as expected.

HW v4.7.2, February 5, 2013
- Add support for GX6256 and GX3108.

HW v4.7.1, October 16, 2013
- Multiple MXI cards will not show devices properly in PXI Explorer (fixed).
- Wrong ATEasy.usr format error when installing HW before ATEasy (fixed).
- 64-bit PXI Explorer will not locate the PXIISA INI file correctly (fixed).

HW v4.7.0a, September 26, 2013
- Unable to install HW device driver because of driver not signed (fixed).

HW v4.7.0, August 12, 2013
- GX7300/GX7000 Chassis INI files contains the wrong local bus
  information for slot 14 (LocalBusRight).
- Support for USBTMC filter installation.
- Support for Windows 8 x64 machine (PCI/PXI devices device driver
  and resources were empty).
- Updated company name from Geotest to Marvin Test Solution:
  - Program Files\Geotest is copied to Program Files\
    "Marvin Test Solutions" folder.
  - Program Files\Geotest is now a symbolic link to 
    Program Files\Marvin Test Solutions for compatibility.
  - Start Menu\Programs\Geotest is copied to Start Menu\Programs\
    Marvin Test Solutions folder.
  - Start Menu\Programs\Geotest is a symbolic link to Start Menu\
    Programs\Marvin Test Solutions folder. Geotest has a hidden 
    attribute.
  - Registry entries for HKEY_LOCAL_MACHINE\SOFTWARE[\Wow6432Node]
    \Geotest is copied to \Marvin Test Solutions, \Geotest is now a
    symbolic link to \Marvin Test Solutions for compatibility.
  - Registry entries for HKEY_CURRENT_USER\SOFTWARE
    \Geotest is copied to \Marvin Test Solutions, \Geotest is now a
    symbolic link to \Marvin Test Solutions for compatibility.
- Fix issues relate to Windows 7/8 security updates that prevents 
  from non elevated Marvin Test applications to write to registry 
  and Program Files folders.
- Documentation and copyright information is updated to reflect the 
  new company name.  

HW v4.6.3, Mar, 2013
- Reset privliges of Geotest folder under Program Files to allow 
  R/W.
- Under x64 Windows, USBTMC devices use the wrong device driver 
  (HwDevice.sys instead of HWDevice64.sys).
- PXI Explorer shows a PXI Express Settings section for none PXIe
  slots.
  
HW v4.6.2, Feb, 2013
- Support for GX7800 Chassis.
- Increased USB devices transmition size instead of breaking to 
  multiple packets (fixed).
- HwScanForHardwareChanges generate a 4KB memory leak (fixed).
- PXI Explorer - PXI Express folder is displayed for non-express 
  slots (fixed).

HW v4.6.1, Dec, 2012
- Fix issue with PXI Explorer on Windows 7. 

HW v4.6, Nov, 2012
- Support for GX7200 chassis.
- PCI/PXI Explorer (64 bit) did not start (fixed).
- Support for Windows 8.

HW v4.5, Nov, 2011
- New functions for PCI interrupts.
- Support for MSI based interrupts.

HW v4.40, Sep, 2011
- New functions to Get/Set PCI Configuration Space.
- Revise support for PXI Express controllers.
- New support for GX7927 controller.

HW v4.30, May, 2011
- New support for PCI devices with interrupts.
- Fixed. HW.DLL will not load under Windows 9x.
- Add Gx3700 PXI and Gx3700e PXIe to HW.INF.
- Add GX3500 interrupts information to HW.INF.
- Reset security setting for PXISYS.ini and PXIESYS.ini during setup
  to allow updates for non-administrators when files are protected.
- Change HW service startup type from automatic to system to allow ATEasy
  or other program to use the HW at startup.

HW v4.02a, March, 2011
- Fixed. Remove security restrictions from PXISYS.ini and PXISYSe.INI 
  to allow non-administrators setup.
- Fixed. HW.INF file had missing cards for 64 bit Windows. 
- Fixed. PXI Explorer. Add message box to display an error when writing
  INI file fails.

HW v4.02, Jan, 2011
- Fixed. USB devices not working after app restart.
- Fixed. First time installation of MTS device from Windows INF folder
  (remove installation section in HW.INF under Windows\INF).
- Fixed. Legacy Slot numbers are not handled properly for Hybrid slot.
- Fixed. Device Manager under Win64 will not show proper Icons.

HW v4.01, April, 2010
- Fix Windows 7 64 bit issue causes Windows to crashes on HW load.

HW v4.00b, March, 2010
- Revise PXI Explorer and Class installer icons

HW v4.00a, March, 2010
- Revise HWVDD.DLL to fix support for 16 bit applications
- Revise setup to fix error "Failed to load DLL : sfc" at the end of setup 
  when running on 64 bit windows

HW v4, Feb, 2010
- New support for 64 bit applications running on 64 bit Windows XP, 
  2003, VISTA, 2008 and 7
- New support for 32 bit applications running on 64 bit Windows such 
  as ATEasy and MTS drivers 
- New support for GX1120, GX2065, GX3500, GX5294, GX5295, GX5961, GX5964

HW v3.3, July, 2009
- New support for GX7944 controller for the GX7600 chassis

HW v3.2, Sep, 2008
- New functions HwPciGetAliasChassisSlot and HwPciGetAliaChassisSlot
  
HW v3.1, June, 2008
- New support for USB devices (mainly used by ATEasy)
- New Command for Copy resources text to the clipboard
- Scan For New Hardware command will now perform Reset
- When PXI explorer detect changes from last scan it will prompt
  asking to save the changes.

HW v3.00, April, 2008
- Fully compliance to the PXI-2/PXIe-6 specification. 
- Programming support of MTS devices/instruments using HW or NI-VISA
  (NI-VISA require newer MTS drivers).
- Compatible with MTS drivers and NI-VISA (v4.3 or prior).
- When installed, configures NI-VISA to disable automatic creation of 
  PXISYS.INI feature. This feature prevents loosing of PXI legacy slot 
  numbering used by MTS drivers.
- Support for PXIe devices and configuration.
- Support for MTS Chassis and Controllers.
- New/revised user interface for PXI/PCI explorer including:
      - Automatic configuration for PXISYS.ini and PXIeSys.ini (used by VISA
        and HW) for MTS chassis (GX7000, GX7100, GX7300 and GX7600), 
        controllers (GX7900, GX7910, GX7920, GX7922, GX7924, GX7930, GX7932,
        GX7934 and GX7940), and PXI expanders (GX7990)  and NI-MXI-3/4. 
      - Display PCI/cPCI/PXI/PXIe Chassis, Bridges, Buses, Slots and Devices
      - Support for alias address for instruments.
      - Display slot icons similar to the slots labels displayed on the PXI
        and PXIe chassis. 
      - Display devices resources.
      - Display PXI/PXIe slots settings.
      - Support for Legacy Slots and numbering for MTS drivers for
        compatibility.
      - Display VISA resources and test VISA connectivity.
      - Detect and display changes when start and display * at the caption if
        changes are found.
      - Prompts the user to save changes if PXISYS.INI or PXIeSYS.INI on close.
- Updated HW.INF to support new MTS PXI/e instruments.
- New/Revised setup.

Version 2.14d (Jan, 2007)
- New HW.INF to support new PXI instruments

Version 2.14a (June, 2006)
- New PXISYS INI files for GX7300.
- Compiled with Visual Studio 2005 

Version 2.14 (Jan, 2005)
- New PXISYS INI files for GX7100/GX7100 and GX7900/GX7910 controllers.

Version 2.13 (Oct, 2004)
- Modified INI files for GX7100
- Modified INF file with new PXI products
- Increase the maximum number of PCI devices to 256
- Fix PXI/PCI Explorer under NT did not display the device description properly
- Update Device Description, Vendor Names for NT
- Improve sort slots to work above 100 slots

Version 2.12 (May, 2002)
- Added new boards to INF file
- Added support to GX7100

Version 2.11 (December, 3 2002)
- Fixed a problem where the PCI explorer and board Initialization will enter to
  infinite loop on computer with device with function #7 usually on newer DELL
  computers). 

Version 2.10 (April 2002)
- Add a way to rescan the PCI bus in the PCI explorer
- Bug fix in PciExplorer that caused the same board resources in two devices
 under XP/2000

Version 2.01 (June 2001)
- Bug fix in _outms, _outmsw and _outmsdw functions when writing buffers
  greater then 64K.
- Bug fix in PciExplorer that caused the board description not to be
  properly displayed.

6. Technical support
===============================================================================
Visit our web site at http://www.MarvinTest.com for more information
about MTS's products and support options. Our web site contains
sections describing: Support options, Application notes, Download 
area for downloading patches, example, patches and new or revised
instrument drivers.

To submit a support issue including suggestion, bug report or 
question please use the following link:

	http://www.MarvinTest.com/magic

In addition, you can the MTS technical support line.
This service is available for registered users between 9:00 AM 
and 5:00 PM Pacific Standard Time.

    Phone : (949) 263-2222

7. Trademark Notes
===============================================================================
- ATEasy is a Registered trademark of Marvin Test Solutions, Inc.
- MTS, Geotest (prior company name), are Marvin Test Solution, Inc, 
- Visual Studio, Windows are a registered trademark of Microsoft Corp.
===============================================================================
