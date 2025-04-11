#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	char c;
	FILE *in, *out;
	
	if(argc != 3){
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        exit(1);
    }

	in = fopen(argv[1], "r");
	if(in == NULL){
        printf("Cannot open %s\n", argv[1]);
        exit(1);
    }

	out = fopen(argv[2], "w");
	
	while(fread(&c, sizeof(char), 1, in)==1){
		fwrite(&c, sizeof(char), 1, out);
	}

	fclose(in);
	fclose(out);

	return 0;
}
