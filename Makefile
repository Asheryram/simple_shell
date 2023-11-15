CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic
LIBS=
EXENAME=hsh

CFILES=\
	aliasi.c\
	aliasii.c\
	inventory.c\
	builtin_i.c\
	builtin_ii.c\
	memm.c\
	parseri.c\
	parserii.c\
	str_funcsiii.c\
	token_izer.c\
	to_kens.c\
	procesor.c\
	print.c
	link_pa_th.c\
	pipe_line.c\
	parse_tree.c\
	cust_stdlib.c\
	str_funcsi.c\
	str_funcsii.c\
	cede.c\
	envi.c\
	envii.c\
	exe.c\
	fi_le_io.c\
	freeee.c\
	get_line.c\
	hel_per1.c\
	hel_per2.c\
	his_tory.c\
	

GLOBAL_HEADERS=\
	shell.h

# Make goals
all: $(GLOBAL_HEADERS) $(CFILES) main.c
	$(CC) $(CFLAGS) $(CFILES) main.c -o $(EXENAME) $(LIBS)

debug: $(GLOBAL_HEADERS) $(CFILES) main.c
	$(CC) $(CFLAGS) $(CFILES) main.c -o $(EXENAME) $(LIBS) -g

clean:
	rm -f $(EXENAME)
