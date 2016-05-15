/*
 * Fucking bug in interpreter getting me pissed, so hack on to the hacky
 * compiler
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BF_BUF_SIZE 30000

void
cgen(FILE *f);


int
main(int argc, char* argv[])
{
	FILE *f;

	if (argc != 2) {
		printf("Usage: %s <script>\n", argv[0]);
		exit(1);
	}

	f = fopen(argv[1], "r");

	if (!f) {
		perror(argv[1]);
		exit(1);
	}

	cgen(f);

	fclose(f);
	return 0;
}

void
printInit(FILE *w)
{
	fprintf(w, "/*\n * File generated by bfc\n * */\n");
	fprintf(w, "#include <stdio.h>\n\n");
	fprintf(w, "#define BUFF_SIZE 30000\n\n");
	fprintf(w, "int\nmain(void)\n{\n");
	fprintf(w, "\tchar array[BUFF_SIZE] = {0};\n");
	fprintf(w, "\tchar *ptr = array;\n");
}

void
printEnd(FILE *w)
{
	fprintf(w, "\treturn 0;\n");
	fprintf(w, "}\n");
}

void
identline(int c, FILE *w){
	int i;

	for (i = 0; i < c; i++)
		fputc('\t', w);
}

void
cgen(FILE *f)
{
	FILE *w;
	int t = 1;
	int c;

	w = fopen("a.c", "w");

	if (!w) {
		perror("Fucking no space for write file");
		exit(1);
	}

	printInit(w);

	while ((c = fgetc(f)) != EOF) {
		switch(c) {
		case '>': 
			identline(t, w);
			fprintf(w, "++ptr;\n");
			break;
		case '<':
			identline(t, w);
			fprintf(w, "--ptr;\n");
			break;
		case '+': 
			identline(t, w);
			fprintf(w, "++*ptr;\n");
			break;
		case '-':
			identline(t, w);
			fprintf(w, "--*ptr;\n");
			break;
		case '.': 
			identline(t, w);
			fprintf(w, "putchar(*ptr);\n");
			break;
		case ',':
			identline(t, w);
			fprintf(w, "*ptr =  getchar();\n");
			break;
		case '[':
			identline(t, w);
			fprintf(w, "while(*ptr) {\n");
			t++;
			break;
		case ']':
			t--;
			identline(t, w);
			fprintf(w, "}\n");
			break;

		}
	}

	printEnd(w);
	fclose(w);

}



