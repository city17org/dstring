/*
 * Copyright (c) 2019 Sean Davies <sean@city17.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <err.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEFLEN		16
#define ERRLIMIT	1000
#define MINLEN		8
#define MAXLEN		64
#define MAXNUM		1000

static void		genstr(char *, int);
static int		chkstr(const char *);
static void		chkerr(const char *);
static void		usage(void) __attribute__ ((noreturn));

extern char		*__progname;
static const char	set[] = "abcdefghijklmnopqrstuvwxyz"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"0123456789"
				"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

int
main(int argc, char *argv[])
{
	int		 ch;
	int		 i;
	int		 lflag = DEFLEN;
	int		 nflag = 1;
	char		 s[MAXLEN + 1];
	const char	*errstr;

#ifdef __OpenBSD__
	if (pledge("stdio", NULL) == -1)
		err(1, "pledge");
#endif

	while ((ch = getopt(argc, argv, "l:n:")) != -1)
		switch (ch) {
		case 'l':
			lflag = strtonum(optarg, MINLEN, MAXLEN, &errstr);
			chkerr(errstr);
			break;
		case 'n':
			nflag = strtonum(optarg, 1, MAXNUM, &errstr);
			chkerr(errstr);
			break;
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc)
		usage();

	for (i = 0; i < nflag; i++) {
		do
			genstr(s, lflag);
		while (chkstr(s));
		(void)printf("%s\n", s);
	}
	return 0;
}

static void
genstr(char *s, int l)
{
	size_t	b = strlen(set);
	int	i;

	for (i = 0; i < l; i++)
		s[i] = set[arc4random_uniform(b)];
	s[i] = '\0';
}

static int
chkstr(const char *s)
{
	size_t		i;
	static int	c = 0;
	int		d = 0; /* digit */
	int		l = 0; /* lowercase */
	int		u = 0; /* uppercase */
	int		x = 0; /* special */

	if (++c >= ERRLIMIT)
		errx(1, "failed to create string");
	for (i = 0; i < strlen(s); i++) {
		if (isdigit(s[i]))
			d = 1;
		else if (islower(s[i]))
			l = 1;
		else if (isupper(s[i]))
			u = 1;
		else
			x = 1;
	}
	if (d && l && u && x) {
		c = 0;
		return 0;
	}
	return 1;
}

static void
chkerr(const char *s)
{
	if (s != NULL) {
		(void)fprintf(stderr, "%s: %s: %s\n",
		    __progname, optarg, s);
		usage();
	}
}

static void
usage(void)
{
	(void)fprintf(stderr, "usage: %s [-l length] [-n number]\n",
	    __progname);
	exit(1);
}
