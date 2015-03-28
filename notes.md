Potential restructuring
=======================
- Currently there is one main.c for each protocol, which means it is weird to make a project containing more than one protocol.
- If we convert each main() into reset/setup/run/etc. sections, we can make a new main() in the project directory and either manually specify the sections to setup or automatically determine this based on the enabled protocols.
    - Hasu is not very interested in merging a major restructuring, so we will go with a main() in each project which can be manually setup using some building block functions.
- Existing main() sections
	- iwrap
		- MCU setup
		- disable VUSB
		- initialize iwrap pins and serial port
		- keyboard init
		- set driver to iwrap
		- init & call iwrap
		- main loop
		    - sleeping code, with unclear TODO comments
	- lufa
	    - MCU setup
		- USB initialization
		- keyboard init
		- set driver to lufa
		- sleep led...?
		- main loop

iWRAP 5 support
===============
- Rather than try too hard to make the current iWRAP 5 code work, where it is tightly locked down to hardware, we can start from scratch.
- Using the LUFA USBtoSerial project as a base, we can recreate Hasu’s manual serial mux command mode, then add in the rest of the keyboard functionality.
- Hasu’s code uses hardware serial for computer control and software serial for iWRAP communication.
- I want to use the hardware serial for iWRAP communication and a virtual serial port over USB for computer control.
- Hardware and software drivers seem to exist in protocol sections already, just need to add LUFA virtual USB to the mix so they are configurable.
- Serial port drivers will need to be changed to allow more than one to be active at a time, similar to the host_driver.h setup.
    - The current functionality can likely be maintained as well so we don’t need to change a bunch of old projects.
