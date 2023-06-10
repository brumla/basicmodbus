Juni 2023: Works with Qt 6.5.1
May 2023: Upgraded to Qt 6.5
November 2021: Project moved to Qt 6.2 and it is no longer compatible with Qt 5.x.

# Basic MODBUS communication tool
This is simple tool used for writting and reading data connected via MODBUS to local COMx: port. The usage is pretty simple:

1. Start the tool
1. Setup the ports in the _Communication section_, only available ports are shown there
1. Enter the input data as hexadecimal numbers
  1. Address: 1 byte (2 digits)
  1. Function: 1 byte (2 digits)
  1. Start address 2 bytes (4 digits)
  1. Data separated by new line, no empty lines are allowed yet
1. Press _Send data_ button (in toolbar)

CRC is calculated automatically, the RTU transfer mode is currently supported. ASCII transfer mode is planed for the future.

# Licence
This tool is licenced under LPGPL 3 with one exception---the code contains the CRC calculation from the document http://www.delta.com.tw/product/em/drive/ac_motor/download/manual/DELTA_IA-MDS_VFD-EL_UM_EN_20140522.pdf, the licence of the code is unknown. 

**If you are author of this code, please contact me, if the licence is not compatible with the LGPL3!**

