#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define START "#include <stdio.h>\n#include <string.h>\n" \
	"int main(){char buf[3000],*ptr=buf;memset(buf,0,sizeof(buf));"
#define FORW "ptr++;"
#define BACKW "ptr--;"
#define SUM "(*ptr)++;"
#define SUB "(*ptr)--;"
#define READ "*ptr=getchar();"
#define PUTC "putchar(*ptr);"
#define WRITEDR(d) fwrite(d, 1, strlen(d), o)
#define WHILE "while(*ptr){"
#define RET "return 0;"
#define ENDBLOCK "}"

void parse(const char *in, const char *out) {

	FILE *i, *o = fopen(out, "w");

	if ((i = fopen(in, "r")) == NULL) {

		perror(in);

		exit(1);

	}

	WRITEDR(START);

	size_t forOpened = 0;

	for (int ch; (ch = fgetc(i)) != EOF; ) {

		switch (ch) {

			case '>':
				WRITEDR(FORW);
				break;

			case '<':
				WRITEDR(BACKW);
				break;

			case '+':
				WRITEDR(SUM);
				break;

			case '-':
				WRITEDR(SUB);
				break;

			case ',':
				WRITEDR(READ);
				break;

			case '.':
				WRITEDR(PUTC);
				break;

			case '[':
				WRITEDR(WHILE);
				forOpened++;
				break;

			case ']':
				WRITEDR(ENDBLOCK);
				forOpened--;

		}

	}

	if (forOpened > 0) {

		fprintf(stderr, "Unexpected end of file, output file will be broken.\n");

	} else {

		WRITEDR(RET);

		WRITEDR(ENDBLOCK);

	}

	fclose(i);
	fclose(o);

}

int main(int argc, char * const argv[]) {

	if (argc == 1) {

		fprintf(stderr, "Invalid usage. Should be %s source.bf [output]\n", *argv);

		return 1;

	}

	parse(argv[1], argc > 2 ? argv[2] : "out.c");

}
