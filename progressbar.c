#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

/**
 * RESERVED_SPACE is the space taken by fixed chars 
 * 4 chars for the current second + '[' + ']' + '\r'
 */
#define RESERVED_SPACE 7

void fullscreen_bar(int length) {
	/* Getting window information (we're interested by the columns) */
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	/* t is the available space for the inner bar */
	int t = w.ws_col-RESERVED_SPACE;
	/* For each second in length */
	for(int i=1; i<=length; i++) {
		/* Printing the current second */
		printf("%3d ",i);
		/* Beginning of the bar */
		putchar('[');
		/* progression is the time progression applied to the bar length */
		int progression = i*t/length;
		/* For each character in the inner bar */
		for(int j=0; j<t; j++) {
			if(j < progression)				{ putchar('='); }
			else if(j == progression)	{ putchar('>'); }
			else											{ putchar(' '); } 
		}
		/* End of the bar */
		putchar(']');
		/* Outputs the bar (workaround to output a line without using \n) */
		fflush(stdout);
		/* Initiating the cursor at the beginning of the line */
		putchar('\r');
		sleep(1);
	}
}

void align_right_bar(int length, int bar) {
	/* Getting window information (we're interested by the columns) */
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	/* t is the available space for the inner bar */
	int t = w.ws_col-bar-RESERVED_SPACE;
	/* For each second in length */
	for(int i=1; i<=length; i++) {
		/* Printing the current second */
		printf("%3d ",i);
		/* Printing spaces from beginning of the line until beginning of the bar = right alignment */
		for(int k=0; k<t; k++) { putchar(' '); }
		/* Beginning of the bar */
		putchar('[');
		/* progression is the time progression applied to the bar length */
		int progression = i*bar/length;
		/* For each character in the inner bar */
		for(int j=0; j<bar; j++) {
			if(j<i*bar/length) 				{ putchar('='); }
			else if(j==i*bar/length)	{ putchar('>'); }
			else 											{ putchar(' '); }
		}
		/* End of the bar */
		putchar(']');
		/* Outputs the bar (workaround to output a line without using \n) */
		fflush(stdout);
		/* Initiating the cursor at the beginning of the line */
		putchar('\r');
		sleep(1);
	}
}

void main(int argc, const char** argv) {
	if(argc == 3 && atoi(argv[1]) == 0) { /* Fullscreen bar */
		fullscreen_bar(atoi(argv[2]));
	}
	else if(argc == 4 && atoi(argv[1]) == 1) { /* Align right bar */
		align_right_bar(atoi(argv[2]), atoi(argv[3]));
	}
	else { /* Prints usage */
		printf("Usage : %s <mode> <time> [bar length]\n", argv[0]);
		printf("\tmode can be\n");
		printf("\t\t0 : fullscreen bar (no bar length to provide)\n");
		printf("\t\t1 : align right bar (bar length to provide)\n");

		exit(1);
	}
}
