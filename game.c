#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printUsage(const char* programName) {
	printf("usage: %s <width> <height> <density> <steps>\n", programName);
}

int main(int argc, char *argv[]) {
    	if(argc != 5) {
		printUsage(argv[0]);
		return EXIT_FAILURE;
	}
    const int width = atoi(argv[1]);
	const int height = atoi(argv[2]);
	const double density = atof(argv[3]);
	const int steps = atoi(argv[4]);

	printf("width:   %4d\n", width);
	printf("height:  %4d\n", height);
	printf("density: %4.0f%%\n", density * 100);
	printf("steps:   %4d\n", steps);
    srand(time(NULL));

    int **src = malloc(sizeof(int*) * height);
    for (int i = 0; i < height; i++) {
        src[i] = malloc(sizeof(int) * width);
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            src[i][j] = rand() % 100;
              if (src[i][j] >= density*100) {
                src[i][j] = 0;
            } else {
                src[i][j] = 1;
            }
        }
    }


     for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%d ", src[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    int temp = 0;
    int k = 0;
    char str[] = "gol_00000.pbm";
    
    FILE* firstIm;

    firstIm = fopen(str, "wb");

    fprintf(firstIm, "P1\n"); 

    fprintf(firstIm, "%d %d\n", width, height); 
  
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            temp = src[i][j];
  
            fprintf(firstIm, "%d ", temp);
        }
        fprintf(firstIm, "\n");
    }
    fclose(firstIm);
    printf("%s\n", str);

    int con = 8;
    while (k < steps) {
    str[con] += 1;
    int draw = 0;
    int sum = 0;
    

    int **dst = malloc(sizeof(int*) * height);
    for (int i = 0; i < height; i++) {
        dst[i] = malloc(sizeof(int) * width);
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 && j == 0) {
                sum += src[i+1][j+1];
                sum += src[i+1][j];
                sum += src[i][j+1];
            } else if (i == 0 && (j > 0 && j < (width-1))) {
                sum += src[i][j-1];
                sum += src[i][j+1];
                sum += src[i+1][j-1];
                sum += src[i+1][j];
                sum += src[i+1][j+1];
            } else if (i == 0 && j == (width-1)) {
                sum += src[i][j-1];
                sum += src[i+1][j-1];
                sum += src[i+1][j];
            } else if ((i > 0 && i < (height-1)) && j == 0) {
                sum += src[i-1][j];
                sum += src[i+1][j];
                sum += src[i][j+1];
                sum += src[i+1][j+1];
                sum += src[i-1][j+1];
            } else if (i == (height-1) && j == 0) {
                sum += src[i-1][j];
                sum += src[i-1][j+1];
                sum += src[i][j+1];
            } else if (i == (height-1) && (j > 0 && j < (width-1))) {
                sum += src[i][j-1];
                sum += src[i][j+1];
                sum += src[i-1][j-1];
                sum += src[i-1][j];
                sum += src[i-1][j+1];
            } else if (i == (height-1) && j == (width-1)) {
                sum += src[i][j-1];
                sum += src[i-1][j-1];
                sum += src[i-1][j];
            } else if ((i > 0 && i < (height-1)) && j == (width-1)) {
                sum += src[i-1][j];
                sum += src[i+1][j];
                sum += src[i+1][j-1];
                sum += src[i][j-1];
                sum += src[i-1][j-1];
            } else {

            sum += src[i+1][j+1];
            sum += src[i-1][j-1];
            sum += src[i+1][j-1];
            sum += src[i-1][j+1];
            sum += src[i+1][j];
            sum += src[i-1][j];
            sum += src[i][j+1];
            sum += src[i][j-1];
            }
            if (src[i][j] == 0 && sum == 3) {
                dst[i][j] = 1;
            } else if (src[i][j] == 1 && (sum < 2 ||sum > 3)) {
                dst[i][j] = 0;
            } else {
                dst[i][j] = src[i][j];
            }
            sum = 0;
        }
    }

    printf("\n\n");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%d ", dst[i][j]);
        }
        printf("\n");
      }
        
    // Creating Images here-----------------------------------------------------------
     if (str[con] > '9') {
            str[con] = '0';
            str[con-1] += 1;
            if (str[con-1] > '9') {
                str[con-1] = '0';
                str[con-2] += 1;
                if (str[con-2] > '9') {
                    str[con-2] = '0';
                    str[con-3] += 1;
                    if (str[con-3] > '9') {
                        str[con-3] = '0';
                        str[con-4] += 1;
                        if(str[con-4] > '9') {
                            break;
                        }
                    }
                }
            }
        }
        printf("%s\n", str);
        

    FILE* secondarr;

    secondarr = fopen(str, "wb");
  
    fprintf(secondarr, "P1\n"); 
  
    fprintf(secondarr, "%d %d\n", width, height); 
  
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            draw = dst[i][j];
  
            fprintf(secondarr, "%d ", draw);
        }
        fprintf(secondarr, "\n");
    }
    fclose(secondarr);

      for (int i = 0; i < height; i++) {
          for (int j = 0; j < width; j++) {
              src[i][j] = dst[i][j];
          }
      }

      for (int i = 0; i < height; i++) {
          free(dst[i]);
          dst[i] = NULL;
      }
      free(dst);
      k++;

      printf("\n\n");
    }

    for (int i = 0; i < height; i++) {
          free(src[i]);
          src[i] = NULL;
      }
      free(src);
 
  return EXIT_SUCCESS;
    
}