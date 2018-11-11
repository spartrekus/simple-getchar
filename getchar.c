#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

/* Use this variable to remember original terminal attributes. */

struct termios saved_attributes;

void reset_input_mode (void)
{
  tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes);
}

void set_input_mode (void)
{
  struct termios tattr;

  /* Make sure stdin is a terminal. */
  if (!isatty (STDIN_FILENO))
    {
      fprintf (stderr, "Not a terminal.\n");
      exit (EXIT_FAILURE);
    }

  /* Save the terminal attributes so we can restore them later. */
  tcgetattr (STDIN_FILENO, &saved_attributes);
  atexit (reset_input_mode);

  /* Set the funny terminal modes. */
  tcgetattr (STDIN_FILENO, &tattr);
  tattr.c_lflag &= ~(ICANON | ECHO);	/* Clear ICANON and ECHO. */

  tattr.c_cc[VMIN] = 1;
  tattr.c_cc[VTIME] = 0;
  tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
}

int main (int argc, char **argv)
{
	char c;

	printf("Par défaut, dans un terminal, les caractères ne sont lus par un programme qu'après l'appui sur la touche Entrée.\n");
	printf("%s est un exemple de programme qui lit les caractères un par un dans un terminal\n", argv[0]);
	printf("Vous pouvez essayer ci-dessous, et terminer en appuyant sur les touches \"Control D\" \n");
	set_input_mode ();

	while (1)
	{
		read (STDIN_FILENO, &c, 1);
		if (c == '\004')		/* C-d */
			break;
		else
		{
			putchar (c);
			fflush (stdout);
		}
	}
	return EXIT_SUCCESS;
}
