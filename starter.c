#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#include <EXTERN.h>
#include <perl.h>

/* perl_parse prefix-parameters */
static const char *prefix[] = {
	"kephra", "-Ikre/site", "-Ikre/lib", "src\\kephra.pl", NULL
};

/* in starter_xsi.c */
EXTERN_C void xs_init(pTHX);

static PerlInterpreter *my_perl;

int
main(int argc, char **argv, char **env)
{
	int cParams = (sizeof(prefix)/sizeof(*prefix))-1 + argc-1;
	const char **params, **para;

	char *path, *p;

	PERL_SYS_INIT3(&argc, &argv, &env);

	/* fix working directory */
	/* NOTE: this works since the last component will always be kephra.exe,
	 * otherwise use _splitpath_s
	 */
	if (!(path = strdup(argv[0]))) {
		fprintf(stderr, "strdup: OOM\n");
		goto leave;
	}
	if ((p = strrchr(path, '\\'))) {
		*p = '\0';
		if (chdir(path)) {
			perror("chdir");
			goto leave;
		}
	}
	free(path);

	params = para = malloc(sizeof(const char *) * cParams);
	if (!params) {
		fprintf(stderr, "strdup: OOM\n");
		goto leave;
	}

	/* copy prefix parameters */
	for (const char **av = prefix; *av; av++)
		*para++ = *av;

	/* copy kephra.exe parameters */
	for (int c = argc - 1; c; c--)
		*para++ = *++argv;

	my_perl = perl_alloc();
	perl_construct(my_perl);

	PL_exit_flags |= PERL_EXIT_DESTRUCT_END;

	perl_parse(my_perl, xs_init, cParams, (char **)params, NULL);
	perl_run(my_perl);

	perl_destruct(my_perl);
	perl_free(my_perl);

	free(params);

leave:
	PERL_SYS_TERM();
}
