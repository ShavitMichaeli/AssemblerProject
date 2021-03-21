/* Assmbler - Maman 14 by Barel Azulai, ID: 206251951 and Shavit Michaeli, ID:205782659 */

#include "header.h"

int main(int argc, char *argv[]) {
	int i;
	createData();
	for (i = 1; i < argc; i++) {
		printf("\nUsing the file: (%s) as the input.\n\n", argv[i]);
		handleFiles(argv[i]);
	}
	return 0;
}
