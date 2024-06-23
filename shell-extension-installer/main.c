#include <stdio.h>
#include <khopanwin32.h>
#include <ShlObj_core.h>
#include "installer.h"

// {E761549A-5209-4183-88CA-D587FCD89393}
EXTERN_GUID(CLSID_SIMPLE_SHELL_EXTENSION, 0xE761549A, 0x5209, 0x4183, 0x88, 0xCA, 0xD5, 0x87, 0xFC, 0xD8, 0x93, 0x93);

int main(int argc, char** argv) {
	if(!RegisterInProcessServer()) {
		return 1;
	}

	if(!RegisterContextMenuHandler()) {
		return 1;
	}

	SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);
	printf("Installation finished\n");
	return 0;
}
