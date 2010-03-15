/**
 * Copyright 2010 Victor Zamanian
 */

/**
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void usage(void);
void chartobinf(unsigned char, FILE*);

int main(int argc, char **argv)
{
  int c;

  if (argc < 2)
    {
      usage();
      exit(EXIT_FAILURE);
    }
  else
    {
      /* set last newline to null byte */
      char * end = &argv[argc-1][strlen(argv[argc-1])];
      if (*end == '\n')
        *end = '\0';
    }

  if ((c = getopt(argc, argv, "b:t:")) != -1)
    {
      switch (c)
        {
        case 'b':
          {
            int i = optind - 1;
            while (i < argc)
              {
                int n = strlen(argv[i]);
                int j = 0;
                while (j < n) {
                  chartobinf(argv[i][j], stdout);
                  putchar(' ');
                  j++;
                }
                i++;
              }
          }
          putchar('\n');
          break;
        case 't':
          {
            char *endptr = NULL;
            int i = optind - 1;
            while (i < argc)
              {
                printf("%c", (int) strtol(argv[i], &endptr, 2));
                i++;
              }
            putchar('\n');
            if (*endptr != '\0')
              {
                fprintf(stderr, "Could not process some binary numbers.\n"
                        "Please verify input is only ones and zeros.\n");
                exit(EXIT_FAILURE);
              }
          }
          break;
        }
    }

  if (optind == 1)
    {
      fputs("One flag must be given!\n", stderr);
      usage();
      exit(EXIT_FAILURE);
    }
 
  exit(EXIT_SUCCESS);
}

void chartobinf(unsigned char c, FILE* out)
{
  size_t n = 8*sizeof(unsigned char);
  while (n-- > 0)
    fputs(((c >> n) & 1) ? "1" : "0", out);
}

void usage(void)
{
  fputs("Usage:\n"
        "\t-b to get output in binary numbers.\n"
        "\t-t to convert from binary to text.\n", stderr);
}
