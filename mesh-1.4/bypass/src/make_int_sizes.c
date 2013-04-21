/*
Bypass
Copyright (C) 1999-2001 Douglas Thain
http://www.cs.wisc.edu/condor/bypass
This program is released under a BSD License.
See the file COPYING for details.
*/

#include <stdlib.h>
#include <stdio.h>

char *findtype( int size )
{
	if(size==8*sizeof(char)) {
		return "char";
	} else if(size==8*sizeof(short)) {
		return "short";
	} else if(size==8*sizeof(int)) {
		return "int";
	} else if(size==8*sizeof(long)) {
		return "long";
	#ifdef __GNUC__
	} else if(size==8*sizeof(long long)) {
		return "long long";
	#endif
	} else {
		return "unknown";
	}
}


int main( int argc, char *argv[] )
{
	printf("/* This file is automatically generated. */\n");
	printf("#ifndef INT_SIZES_H\n");
	printf("#define INT_SIZES_H\n");
	printf("\n");
	printf("#define INT8_T %s\n",findtype(8));
	printf("#define INT16_T %s\n",findtype(16));
	printf("#define INT32_T %s\n",findtype(32));
	printf("#define INT64_T %s\n",findtype(64));
	printf("\n");
	printf("#define UINT8_T unsigned %s\n",findtype(8));
	printf("#define UINT16_T unsigned %s\n",findtype(16));
	printf("#define UINT32_T unsigned %s\n",findtype(32));
	printf("#define UINT64_T unsigned %s\n",findtype(64));
	printf("\n");
	printf("#endif\n");
	return 0;
}
