/**
 * @file main.cpp
 * @author JwyJohn (1951510@tongji.edu.cn)
 * @brief 将头文件和源码文件合并为一个文件，用于Windows下编译。
 * ! 务必使用支持C++11标准的编译器，仅保证在g++ 10.2.0 (GCC) 下编译通过。
 * ! main.cpp的内容从1098行开始
 * @version 0.1
 * @date 2021-12-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */



















/**
 * @file main_header.h
 * @author JwyJohn (1951510@tongji.edu.cn)
 * @brief 头文件和Console库的合并
 * ! 务必使用支持C++11标准的编译器，仅保证在g++ 10.2.0 (GCC) 下编译通过。
 * @version 0.1
 * @date 2021-12-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/*** Start of inlined file: kmp.h ***/
#ifndef _KMP_H__
#define _KMP_H__

#include <bits/stdc++.h>

using namespace std;

class kmp_text
{
	/**
	 * @brief 支持KMP的字符串类及其实现
	 * 
	 */

	string raw_text;

public:
	kmp_text(string t) : raw_text(t){};
	vector<int> prefixFunction(string s)
	{
		/**
		 * @brief KMP中前缀函数的实现
		 * 
		 */
		int n = (int)s.length();
		vector<int> pi(n);
		for (int i = 1; i < n; i++)
		{
			int j = pi[i - 1];
			while (j > 0 && s[i] != s[j])
				j = pi[j - 1];
			if (s[i] == s[j])
				j++;
			pi[i] = j;
		}
		return pi;
	};
	pair<int, vector<int>> countWord(string s)
	{
		/**
		 * @brief 利用前缀和函数进行查找和统计
		 * 
		 */
		int n = (int)s.length();
		int ans = 0;
		int j = 0;
		pair<int, vector<int>> res;
		string pattern = s + '\0';
		pattern += raw_text;
		cout << pattern << endl;
		vector<int> v = prefixFunction(pattern);
		vector<int> pos;
		for (auto u : v)
		{
			j++;
			if (u == n)
			{
				ans++;
				pos.push_back(j-s.length()+1);
			};
		};
		res.first = ans;
		res.second = pos;
		return res;
	}
};

#endif

/*** End of inlined file: kmp.h ***/

/*** Start of inlined file: libcmdf.h ***/
#ifndef LIBCMDF_H_INCLUDE
#define LIBCMDF_H_INCLUDE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <signal.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <termios.h>
#include <sys/ioctl.h>
#endif

/* Configuration */
#ifndef CMDF_MAX_COMMANDS
#define CMDF_MAX_COMMANDS 24
#endif

#ifndef CMDF_TAB_TO_SPACES
#define CMDF_TAB_TO_SPACES 8
#endif

/* Max sub process count */
#ifndef CMDF_MAX_SUBPROCESSES
#define CMDF_MAX_SUBPROCESSES 4
#endif

#ifdef _WIN32
#define CMDF_PPRINT_RIGHT_OFFSET 2
#else
#define CMDF_PPRINT_RIGHT_OFFSET 1
#endif

/* GNU Readline support (Unix/Linux only) */
#ifdef _WIN32
#ifdef CMDF_READLINE_SUPPORT
#undef CMDF_READLINE_SUPPORT
#endif
#else
#ifdef CMDF_READLINE_SUPPORT
#include <readline/readline.h>
#include <readline/history.h>
#endif
#endif

/* fgets()-like function to use for input handling */
#ifndef CMDF_FGETS
#define CMDF_FGETS fgets
#endif

/* malloc()-like function to use for memory allocations */
#ifndef CMDF_MALLOC
#define CMDF_MALLOC malloc
#endif

/* free()-like function to use for memory freeing */
#ifndef CMDF_FREE
#define CMDF_FREE free
#endif

/* Maximum input buffer length */
#ifndef CMDF_MAX_INPUT_BUFFER_LENGTH
#define CMDF_MAX_INPUT_BUFFER_LENGTH 256
#endif

/* STDIN and STDOUT */
#ifndef CMDF_STDIN
#define CMDF_STDIN stdin
#endif

#ifndef CMDF_STDOUT
#define CMDF_STDOUT stdout
#endif

/* =================================================================================== */

/* Error codes (for CMDF_RETURN) */
#define CMDF_OK 1
#define CMDF_ERROR_TOO_MANY_COMMANDS -1
#define CMDF_ERROR_TOO_MANY_ARGS -2
#define CMDF_ERROR_UNKNOWN_COMMAND -3
#define CMDF_ERROR_ARGUMENT_ERROR -4
#define CMDF_ERROR_OUT_OF_MEMORY -5

/* Max processes count reached */
#define CMDF_ERROR_OUT_OF_PROCESS_STACK -6

/* =================================================================================== */

/* For the C++ support */
#ifdef __cplusplus
extern "C"
{
#endif

	/* cmdf_windowsize struct */
	struct cmdf_windowsize
	{
#ifdef _WIN32
		SHORT h, w;
#else
	unsigned short h, w;
#endif
	};

	/* libcmdf command list and arglist */
	typedef struct cmdf___arglist_s
	{
		char **args;  /* NULL-terminated string list */
		size_t count; /* Argument list count */
	} cmdf_arglist;

	/* Command callback typedef */
	typedef int CMDF_RETURN;
	typedef CMDF_RETURN (*cmdf_command_callback)(cmdf_arglist *arglist);

	/* Utility Functions */
	char *cmdf__strdup(const char *src);
	void cmdf__trim(char *src);
	void cmdf__print_title(const char *title, char ruler);
	void cmdf__pprint(size_t loffset, const char *const strtoprint);
	void cmdf__print_command_list();

	/* Init/Free functions */
	void cmdf_init(const char *prompt, const char *intro, const char *doc_header,
				   const char *undoc_header, char ruler, int use_default_exit);
#define cmdf_init_quick() cmdf_init(NULL, NULL, NULL, NULL, 0, 1)
#define cmdf_quit ;

	/* Public interface functions */
	void cmdf_commandloop(void);

	/* Getters */
	const char *cmdf_get_prompt(void);
	const char *cmdf_get_intro(void);
	const char *cmdf_get_doc_header(void);
	const char *cmdf_get_undoc_header(void);
	char cmdf_get_ruler(void);
	int cmdf_get_command_count(void);

	/* Setters */
	void cmdf_set_prompt(const char *new_prompt);
	void cmdf_set_intro(const char *new_intro);
	void cmdf_set_doc_header(const char *new_doc_header);
	void cmdf_set_undoc_header(const char *new_undoc_header);

	/* Argument Parsing */
	cmdf_arglist *cmdf_parse_arguments(char *argline);
	void cmdf_free_arglist(cmdf_arglist *arglist);

	/* Adding/Removing Command Entries */
	CMDF_RETURN cmdf_register_command(cmdf_command_callback callback, const char *cmdname,
									  const char *help);

	/* Default callbacks */
	CMDF_RETURN cmdf__default_do_help(cmdf_arglist *arglist);
	CMDF_RETURN cmdf__default_do_command(const char *cmdname, cmdf_arglist *arglist);
	CMDF_RETURN cmdf__default_do_emptyline(cmdf_arglist *arglist /* Unused */);
	CMDF_RETURN cmdf__default_do_exit(cmdf_arglist *arglist /* Unused */);
	CMDF_RETURN cmdf__default_do_noop(cmdf_arglist *arglist /* Unused */);
	void cmdf__default_commandloop(void);

/* Utility Functions */
#ifdef _WIN32
	struct cmdf_windowsize cmdf_get_window_size_win(void);
#define cmdf_get_window_size cmdf_get_window_size_win
#else
struct cmdf_windowsize cmdf_get_window_size_unix(void);
#define cmdf_get_window_size cmdf_get_window_size_unix
#endif

/* ReadLine-related functions and callbackes.
 * Compiled only if readline is enabled */
#ifdef CMDF_READLINE_SUPPORT
	char **cmdf__command_name_completion(const char *text, int start, int end);
	char *cmdf__command_name_iter(const char *text, int state);
#endif

#endif /* LIBCMDF_H_INCLUDE */

	/*
 * ======================================================================================
 * IMPLEMENTATION
 * ======================================================================================
 */

	/* Defaults */
	static const char *cmdf__default_prompt = "(libcmdf) ";
	static const char *cmdf__default_intro = "";
	static const char *cmdf__default_doc_header = "Documented Commands:";
	static const char *cmdf__default_undoc_header = "Undocumented Commands:";
	static const char cmdf__default_ruler = '=';

	/* libcmdf settings */
	struct cmdf__settings_s
	{
		/* Properties */
		const char *prompt, *intro, *doc_header, *undoc_header;
		char ruler;

		/* Counters */
		int undoc_cmds, doc_cmds, entry_count;

		/* Index in cmdf__entries array from which commands would be active */
		int entry_start;

		/* Flags */
		int exit_flag;

		/* Callback pointers */
		cmdf_command_callback do_emptyline;
		CMDF_RETURN(*do_command)
		(const char *, cmdf_arglist *);
	};

	/* libcmdf settings stack */
	static struct cmdf__settings_stack_s
	{
		struct cmdf__settings_s stack[CMDF_MAX_SUBPROCESSES];
		size_t size;
		struct cmdf__settings_s *top; /* actual settings for currect process */
	} cmdf__settings_stack = {0};

	static struct cmdf__entry_s
	{
		const char *cmdname;			/* Command name */
		const char *help;				/* Help */
		cmdf_command_callback callback; /* Command callback */
	} cmdf__entries[(CMDF_MAX_COMMANDS + 1) * CMDF_MAX_SUBPROCESSES];

	/* Utility Functions */
	char *cmdf__strdup(const char *src)
	{
		char *dst = (char *)(CMDF_MALLOC(sizeof(char) * (strlen(src) + 1))); /* src + '\0' */
		if (!dst)
			return NULL;

		return strcpy(dst, src);
	}

	void cmdf__trim(char *src)
	{
		char *begin = src, *end, *newline;
		size_t end_location;

		/* Check for empty string */
		if (strlen(src) == 1 && (src[0] == '\n' || src[0] == '\0'))
		{
			src[0] = '\0';
			return;
		}

		/* Replace newline */
		newline = strrchr(src, '\n');
		if (newline)
			*newline = '\0';

		/* Replace spaces and re-align the string */
		while (isspace((int)*begin))
			begin++;

		if (src != begin)
		{
			end_location = strlen(begin);
			memmove(src, begin, strlen(begin) + 1);
			memset(begin + end_location, '\0', sizeof(char) * strlen(begin - end_location));
		}

		/* Replaces spaces at the end of the string */
		end = strrchr(src, '\0');

		/* Check if we haven't reached the end of the string.
	 * Because if we did, we have nothing else to do. */
		if (src == end)
			return;
		else
			end--;

		if (isspace((int)*end))
		{
			do
			{
				*end = '\0';
				end--;
			} while (isspace((int)*end));
		}
	}

	void cmdf__print_title(const char *title, char ruler)
	{
		size_t i = 0;

		fprintf(CMDF_STDOUT, "\n%s\n", title);

		for (i = 0; i < strlen(title) + 1; i++)
			putc(ruler, CMDF_STDOUT);

		putc('\n', CMDF_STDOUT);
	}

	/*
 * Print a string from the current line, down to the next line if needed,
 * which is padded with loffset characters.
 * The function takes the input string and prints it word by word - if a word can not
 * be printed on the line without being concatenated, it is printed on the next line.
 */
	void cmdf__pprint(size_t loffset, const char *const strtoprint)
	{
		const struct cmdf_windowsize winsize = cmdf_get_window_size();
		size_t total_printed = loffset, i, wordlen;
		char *strbuff = cmdf__strdup(strtoprint), *wordptr;

		/* If we couldn't allocate a buffer, print regularly, exit. */
		if (!strbuff)
		{
			fprintf(CMDF_STDOUT, "\n%s\n", strtoprint);
			return;
		}

		/* Begin splitting by words */
		wordptr = strtok(strbuff, " \t\n");
		while (wordptr)
		{
			/* Check if we can print this word. */
			wordlen = strlen(wordptr);
			if (total_printed + (wordlen + 1) > (size_t)(winsize.w - CMDF_PPRINT_RIGHT_OFFSET))
			{
				/* Go to the next line and print the word there. */
				/* Print newline and loffset spaces */
				fputc('\n', CMDF_STDOUT);
				for (i = 0; i < loffset; i++)
					fputc(' ', CMDF_STDOUT);

				total_printed = loffset;
			}

			/* Print the word */
			fprintf(CMDF_STDOUT, "%s ", wordptr);
			total_printed += wordlen + 1; /* strlen(word) + space */

			/* Get the next word */
			wordptr = strtok(NULL, " \t\n");
		}

		/* Put newline */
		fputc('\n', CMDF_STDOUT);

		/* Free the string */
		CMDF_FREE(strbuff);
	}

	void cmdf__print_command_list(void)
	{
		int i, printed;
		const struct cmdf_windowsize winsize = cmdf_get_window_size();

		/* Print documented commands */
		cmdf__print_title(cmdf__settings_stack.top->doc_header, cmdf__settings_stack.top->ruler);
		for (i = cmdf__settings_stack.top->entry_start, printed = 0; i < cmdf__settings_stack.top->entry_start + cmdf__settings_stack.top->entry_count; i++)
		{
			if (cmdf__entries[i].help)
			{
				/* Check if we need to break into the next line. */
				if (printed + strlen(cmdf__entries[i].cmdname) + 1 >= winsize.w)
				{
					printed = 0;
					fputc('\n', CMDF_STDOUT);
				}

				/* Print command */
				printed += fprintf(CMDF_STDOUT, "%s ", cmdf__entries[i].cmdname);
			}
		}

		/* Newline */
		fputc('\n', CMDF_STDOUT);

		/* Print undocumented commands, if any */
		if (cmdf__settings_stack.top->undoc_cmds > 0)
		{
			cmdf__print_title(cmdf__settings_stack.top->undoc_header, cmdf__settings_stack.top->ruler);
			for (i = cmdf__settings_stack.top->entry_start, printed = 0; i < cmdf__settings_stack.top->entry_start + cmdf__settings_stack.top->entry_count; i++)
			{
				if (!cmdf__entries[i].help)
				{
					/* Check if we need to break into the next line. */
					if (printed + strlen(cmdf__entries[i].cmdname) + 1 >= winsize.w)
					{
						printed = 0;
						fputc('\n', CMDF_STDOUT);
					}

					/* Print command */
					printed += fprintf(CMDF_STDOUT, "%s ", cmdf__entries[i].cmdname);
				}
			}

			/* Print newline */
			fputc('\n', CMDF_STDOUT);
		}
	}

	/* Init/Free functions */
	void cmdf_init(const char *prompt, const char *intro, const char *doc_header,
				   const char *undoc_header, char ruler, int use_default_exit)
	{
		/* Create new settings to push them to stack */
		struct cmdf__settings_s settings;
		memset((void *)&settings, 0, sizeof(struct cmdf__settings_s));
		/* Set properties */
		settings.prompt = prompt ? prompt : cmdf__default_prompt;
		settings.intro = intro ? intro : cmdf__default_intro;
		settings.doc_header = doc_header ? doc_header : cmdf__default_doc_header;
		settings.undoc_header = undoc_header ? undoc_header : cmdf__default_undoc_header;
		settings.ruler = ruler ? ruler : cmdf__default_ruler;
		settings.doc_cmds = settings.undoc_cmds = settings.entry_count = 0;

		/* If not first - look for actual entry_start index */
		if (cmdf__settings_stack.top != NULL)
			settings.entry_start = cmdf__settings_stack.top->entry_start + cmdf__settings_stack.top->entry_count;

		/* Set command callbacks */
		settings.do_command = cmdf__default_do_command;
		settings.do_emptyline = cmdf__default_do_emptyline;

		/* Push value to the stack */
		if (cmdf__settings_stack.size < CMDF_MAX_SUBPROCESSES)
		{
			cmdf__settings_stack.stack[cmdf__settings_stack.size] = settings;
			cmdf__settings_stack.top = cmdf__settings_stack.stack + cmdf__settings_stack.size;
			cmdf__settings_stack.size++;
		}
		else
		{
			printf("max subprocesses count reached!\n");
			exit(CMDF_ERROR_OUT_OF_PROCESS_STACK); /* maybe handle error somehow */
		}

		/* Register help callback */
		cmdf_register_command(cmdf__default_do_help, "help", "Get information on a command"
															 " or list commands.");

		/* Register exit callback, if required */
		if (use_default_exit)
			cmdf_register_command(cmdf__default_do_exit, "exit", "Quit the application");

#ifdef CMDF_READLINE_SUPPORT
		/* Set completion function */
		rl_attempted_completion_function = cmdf__command_name_completion;
#endif
	}

	/* Public interface functions */
	void cmdf_commandloop(void)
	{
		cmdf__default_commandloop();
	}

	/* Getters */
	const char *cmdf_get_prompt(void)
	{
		return cmdf__settings_stack.top->prompt;
	}

	const char *cmdf_get_intro(void)
	{
		return cmdf__settings_stack.top->intro;
	}

	const char *cmdf_get_doc_header(void)
	{
		return cmdf__settings_stack.top->doc_header;
	}

	const char *cmdf_get_undoc_header(void)
	{
		return cmdf__settings_stack.top->undoc_header;
	}

	char cmdf_get_ruler(void)
	{
		return cmdf__settings_stack.top->ruler;
	}

	int cmdf_get_command_count(void)
	{
		return cmdf__settings_stack.top->entry_count;
	}

	/* Setters */
	void cmdf_set_prompt(const char *new_prompt)
	{
		cmdf__settings_stack.top->prompt = new_prompt ? new_prompt : cmdf__default_prompt;
	}

	void cmdf_set_intro(const char *new_intro)
	{
		cmdf__settings_stack.top->intro = new_intro ? new_intro : cmdf__default_intro;
	}

	void cmdf_set_doc_header(const char *new_doc_header)
	{
		cmdf__settings_stack.top->doc_header = new_doc_header ? new_doc_header : cmdf__default_doc_header;
	}

	void cmdf_set_undoc_header(const char *new_undoc_header)
	{
		cmdf__settings_stack.top->undoc_header = new_undoc_header ? new_undoc_header : cmdf__default_undoc_header;
	}

	/* Argument Parsing */
	cmdf_arglist *cmdf_parse_arguments(char *argline)
	{
		cmdf_arglist *arglist = NULL;
		size_t i;
		char *strptr, *startptr;
		enum states
		{
			NONE,
			IN_WORD,
			IN_QUOTES
		} state = NONE;

		/* Check if there are any arguments */
		if (!argline)
			return NULL;

		/* Allocate argument list */
		arglist = (cmdf_arglist *)(CMDF_MALLOC(sizeof(cmdf_arglist)));
		if (!arglist)
			return NULL;

		arglist->count = 0;

		/* First pass on the arguments line - use the state machine to determine how many
	 * argument do we have. */
		for (strptr = startptr = argline, i = 0; *strptr; strptr++)
		{
			switch (state)
			{
			case NONE:
				/*
				 * Space = Don't care.
				 * Quotes = a quoted argument begins.
				 * Anything else = Inside a word.
				 */
				if (isspace((int)*strptr))
					continue;
				else if (*strptr == '\"')
					state = IN_QUOTES;
				else
					state = IN_WORD;

				break;
			case IN_QUOTES:
				/*
				 * Space = Don't care, since we're inside quotes.
				 * Quotes = Quotes have ended, so count++
				 * Anything else = Don't care, since we're inside quotes.
				 */
				if (isspace((int)*strptr))
					continue;
				else if (*strptr == '\"')
				{
					state = NONE;
					arglist->count++;

					break;
				}
				else
					continue;
			case IN_WORD:
				/*
				 * Space = A word just terminated, so count++
				 * Quotes = Ignore - quote is part of the word
				 * Anything else = Still in word
				 */
				if (isspace((int)*strptr))
				{
					state = NONE;
					arglist->count++;

					break;
				}
				else if (*strptr == '\"')
					continue;
				else
					continue;
			}
		}

		/* Handle last argument counting, if any */
		if (state != NONE)
			arglist->count++;

		/* Now we can allocate the argument list */
		arglist->args = (char **)(CMDF_MALLOC(sizeof(char *) * (arglist->count + 1))); /* + NULL */
		if (!arglist->args)
		{
			CMDF_FREE(arglist);
			return NULL;
		}

		/* Populate argument list */
		state = NONE;
		for (strptr = startptr = argline, i = 0; *strptr; strptr++)
		{
			switch (state)
			{
			case NONE:
				/* Space = No word yet.
				 * Quotes = Quotes started, so ignore everything inbetween.
				 * Else = Probably a word. */
				if (isspace((int)*strptr))
					continue;
				else if (*strptr == '\"')
				{
					state = IN_QUOTES;
					startptr = strptr + 1;
				}
				else
				{
					state = IN_WORD;
					startptr = strptr;
				}

				break;
			case IN_QUOTES:
				/* Space = Ignore it, iterate futher.
				 * Quotes = End quotes, so put the entire quoted part as an argument.
				 * Else = Whatever is between the quotes */
				if (*strptr == '\"')
				{
					*strptr = '\0';
					arglist->args[i++] = cmdf__strdup(startptr);
					state = NONE;
				}

				break;
			case IN_WORD:
				/* Space = End of word, so parse it.
				 * Quote = Some quote inside of a word. We treat it is a word.
				 * Else = Still a word. */
				if (isspace((int)*strptr))
				{
					*strptr = '\0';
					arglist->args[i++] = cmdf__strdup(startptr);
					state = NONE;
				}

				break;
			}
		}

		/* Get the last argument, if any. */
		if (state != NONE && i < arglist->count)
			arglist->args[i++] = cmdf__strdup(startptr);

		/* Set up null terminator in the argument list */
		arglist->args[i] = NULL;

		/* Done. */
		return arglist;
	}

	void cmdf_free_arglist(cmdf_arglist *arglist)
	{
		size_t i;

		/* Check if any argument list was provided. */
		if (arglist)
		{
			/* Free every argument */
			for (i = 0; i < arglist->count - 1; i++)
				CMDF_FREE(arglist->args[i]);

			/* Free args */
			CMDF_FREE(arglist->args);
		}

		/* Free arglist */
		CMDF_FREE(arglist);
	}

	/* Adding/Removing Command Entries */
	CMDF_RETURN cmdf_register_command(cmdf_command_callback callback, const char *cmdname,
									  const char *help)
	{
		int new_index;

		/* Increate entry count, first checking if we can add more */
		if (cmdf__settings_stack.top->entry_count == CMDF_MAX_COMMANDS)
			return CMDF_ERROR_TOO_MANY_COMMANDS;

		/* Initialize new entry */
		new_index = cmdf__settings_stack.top->entry_start + cmdf__settings_stack.top->entry_count;
		cmdf__entries[new_index].callback = callback;
		cmdf__entries[new_index].cmdname = cmdname;
		cmdf__entries[new_index].help = help;

		cmdf__settings_stack.top->entry_count++;

		/* Check doc */
		if (help)
			cmdf__settings_stack.top->doc_cmds++;
		else
			cmdf__settings_stack.top->undoc_cmds++;

		return CMDF_OK;
	}

	/* Default callbacks */
	CMDF_RETURN cmdf__default_do_help(cmdf_arglist *arglist)
	{
		int i;
		size_t offset;

		/* If no arguments provided, print all help listing.
	 * Otherwise, print documentation on specified command. */
		if (arglist)
		{
			if (arglist->count == 1)
			{
				for (i = cmdf__settings_stack.top->entry_start; i < cmdf__settings_stack.top->entry_start + cmdf__settings_stack.top->entry_count; i++)
				{
					if (strcmp(arglist->args[0], cmdf__entries[i].cmdname) == 0)
					{
						/* Print help, if any */
						if (cmdf__entries[i].help)
						{
							offset = fprintf(CMDF_STDOUT, "%s   ", cmdf__entries[i].cmdname);
							cmdf__pprint(offset, cmdf__entries[i].help);
						}
						else
							printf("\n(No documentation)\n");

						return CMDF_OK;
					}
				}

				/* If we reached this, means that the command was not found */
				fprintf(CMDF_STDOUT, "Command '%s' was not found.\n", arglist->args[0]);
				return CMDF_ERROR_UNKNOWN_COMMAND;
			}
			else
			{
				fprintf(CMDF_STDOUT, "Too many arguments for the 'help' command!\n");
				return CMDF_ERROR_TOO_MANY_ARGS;
			}
		}
		else
			cmdf__print_command_list();

		/* Print newline */
		fputc('\n', CMDF_STDOUT);

		return CMDF_OK;
	}

	CMDF_RETURN cmdf__default_do_emptyline(cmdf_arglist *arglist /* Unusued */)
	{
		return CMDF_OK;
	}

	CMDF_RETURN cmdf__default_do_exit(cmdf_arglist *arglist /* Unused */)
	{
		cmdf__settings_stack.top->exit_flag = 1;

		return CMDF_OK;
	}

	CMDF_RETURN cmdf__default_do_noop(cmdf_arglist *arglist /* Unused */)
	{
		return CMDF_OK;
	}

	CMDF_RETURN cmdf__default_do_command(const char *cmdname, cmdf_arglist *arglist)
	{
		int i;

		/* Iterate through the commands list. Find and execute the appropriate command */
		for (i = cmdf__settings_stack.top->entry_start; i < cmdf__settings_stack.top->entry_start + cmdf__settings_stack.top->entry_count; i++)
			if (strcmp(cmdname, cmdf__entries[i].cmdname) == 0)
				return cmdf__entries[i].callback(arglist);

		return CMDF_ERROR_UNKNOWN_COMMAND;
	}

	void cmdf__default_commandloop(void)
	{
#ifndef CMDF_READLINE_SUPPORT
		char inputbuff[CMDF_MAX_INPUT_BUFFER_LENGTH];
#else
	char *inputbuff;
#endif

		char *cmdptr, *argsptr, *spcptr;
		cmdf_arglist *cmd_args;
		int retflag;

		/* Print intro, if any. */
		if (cmdf__settings_stack.top->intro)
			printf("\n%s\n\n", cmdf__settings_stack.top->intro);

		while (!cmdf__settings_stack.top->exit_flag)
		{
/* Print prompt and get input */
#ifndef CMDF_READLINE_SUPPORT
			fprintf(CMDF_STDOUT, "%s", cmdf__settings_stack.top->prompt);
			fgets(inputbuff, sizeof(char) * CMDF_MAX_INPUT_BUFFER_LENGTH, CMDF_STDIN);

			/* Check for EOF */
			if (feof(CMDF_STDIN))
			{
				cmdf__settings_stack.top->exit_flag = 1;
				continue;
			}

#else
		inputbuff = readline(cmdf__settings_stack.top->prompt);

		/* EOF, or failure to allocate a buffer. Means we probably need to exit. */
		if (!inputbuff)
		{
			cmdf__settings_stack.top->exit_flag = 1;
			continue;
		}
#endif

			/* Trim string */
			cmdf__trim(inputbuff);

			/* If input is empty, call do_emptyline command. */
			if (inputbuff[0] == '\0')
			{
				cmdf__settings_stack.top->do_emptyline(NULL);
				continue;
			}

			/* If we've reached this, then line has something in it.
		 * If readline is enabled, save this to history. */
#ifdef CMDF_READLINE_SUPPORT
			add_history(inputbuff);
#endif

			/* Split by first space.
		 * This should be the command, followed by arguments. */
			if ((spcptr = strchr(inputbuff, ' ')))
			{
				*spcptr = '\0';

				cmdptr = inputbuff;
				argsptr = spcptr + 1;
			}
			else
			{
				cmdptr = inputbuff;
				argsptr = NULL;
			}

			/* Parse arguments */
			cmd_args = cmdf_parse_arguments(argsptr);

			/* Execute command. */
			retflag = cmdf__settings_stack.top->do_command(cmdptr, cmd_args);
			switch (retflag)
			{
			case CMDF_ERROR_UNKNOWN_COMMAND:
				fprintf(CMDF_STDOUT, "Unknown command '%s'.\n", cmdptr);
				break;
			}

			/* Free arguments */
			cmdf_free_arglist(cmd_args);

#ifdef CMDF_READLINE_SUPPORT
			/* Free buffer */
			free(inputbuff);
#endif
		}

		/* Pop out settings from settings stack */
		cmdf__settings_stack.size--;
		cmdf__settings_stack.top--;
	}

/* Utility Functions */
#ifdef _WIN32
	struct cmdf_windowsize cmdf_get_window_size_win(void)
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		struct cmdf_windowsize winsize = {0, 0};

		/* If this fails, return the zeroed structure as-is */
		if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi) == 0)
			return winsize;

		winsize.w = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		winsize.h = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

		return winsize;
	}
#else
struct cmdf_windowsize cmdf_get_window_size_unix(void)
{
	struct cmdf_windowsize cm_winsize;
	struct winsize ws;
	int stdin_fd = fileno(CMDF_STDIN);

	memset(&cm_winsize, 0, sizeof(struct cmdf_windowsize));

	/* if this ioctl() fails, return the zeroed struct as-is */
	if (ioctl(stdin_fd, TIOCGWINSZ, &ws) == -1)
		return cm_winsize;

	cm_winsize.w = ws.ws_col;
	cm_winsize.h = ws.ws_row;

	return cm_winsize;
}

#endif

/* readline-related utilities */
#ifdef CMDF_READLINE_SUPPORT

	char **cmdf__command_name_completion(const char *text, int start, int end)
	{
		char **matches = NULL;

		rl_attempted_completion_over = 1;
		matches = rl_completion_matches(text, cmdf__command_name_iter);

		return matches;
	}

	char *cmdf__command_name_iter(const char *text, int state)
	{
		static int list_index;
		static size_t len;
		char *name = NULL;

		if (!state)
		{
			list_index = cmdf__settings_stack.top->entry_start;
			len = strlen(text);
		}

		/* Compare all entries */
		for (; list_index < cmdf__settings_stack.top->entry_start + cmdf__settings_stack.top->entry_count; list_index++)
			if (strncmp(cmdf__entries[list_index].cmdname, text, len) == 0)
				name = cmdf__strdup(cmdf__entries[list_index].cmdname);

		return name;
	}

#endif

/*** End of inlined file: libcmdf.h ***/

/* For the C++ support. */
#ifdef __cplusplus
}
#endif

/**
 * @file main.cpp
 * @author JwyJohn (1951510@tongji.edu.cn)
 * @brief 函数的具体实现和主程序
 * ! 务必使用支持C++11标准的编译器，仅保证在g++ 10.2.0 (GCC) 下编译通过。
 * @version 0.1
 * @date 2021-12-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#define _CRT_SECURE_NO_WARNINGS
#define LIBCMDF_IMPL

using namespace std;

/**
 * @brief 显示输出的内容以及命令的帮助。
 * 
 */

#define PROG_INTRO " __  __           ____    \n/\\ \\/\\ \\  /'\\_/`\\/\\  _`\\  \n\\ \\ \\/'/'/\\      \\ \\ \\L\\ \\\n \\ \\ , < \\ \\ \\__\\ \\ \\ ,__/\n  \\ \\ \\\\`\\\\ \\ \\_/\\ \\ \\ \\/ \n   \\ \\_\\ \\_\\ \\_\\\\ \\_\\ \\_\\ \n    \\/_/\\/_/\\/_/ \\/_/\\/_/ \n                          \n                          \n\n - Free Software by 1951510 JiangWenyuan \nNov 2021\n==========================\n! This is a program to find substring in a file.\n! Can also create, read, append a file.\n! Input command 'c mytext.txt' to create mytext.txt.\n! Input command 'r mytext.txt' to read from mytext.txt.\n! Input command 'a mytext.txt' to append content to mytext.txt.\n! Input command 's' to show loaded text.\n! Input command 'f substr' to serach substr in loaded text.\n! Use 'c mytext.txt' WITH CAUTION because it can overwrite existing file.\n"
#define NEW_HELP "Create a new file and enter text into it. Format 'c mytext.txt'\n"
#define FIND_HELP "Find a substring in the loaded file. Format 'f substr'\n"
#define CAT_HELP "Show loaded file.\n"
#define READ_HELP "Read text from a file. Format 'r mytext.txt'\n"
#define APPEND_HELP "Append text to a file. Format 'a mytext.txt'\n"
using namespace std;

// 一些全局变量，用于暂存读入或要写入的文件

string filename;
string contents;

static CMDF_RETURN read_filename(cmdf_arglist *arglist)
{
	/**
	 * @brief 处理用户输入，读文件
	 * 
	 */

	if (!arglist)
	{
		cout << " [Sytax Error] No file name provided!\n [Tip] Please provide file name like \"r mytext.txt\"" << endl;
		return CMDF_OK;
	};
	if (arglist->count != 1)
	{
		cout << " [Sytax Error] Please provide file name like \"r mytext.txt\"" << endl;
		return CMDF_OK;
	};
	filename = arglist->args[0];
	FILE *fp = fopen(arglist->args[0], "r");
	char ch;
	if (fp == NULL)
	{
		cout << " [Error] Unable to open file: " << filename << endl;
		return CMDF_OK;
	}
	else
	{
		cout << " [Done] Loaded file: " << filename << endl;
	};
	while ((ch = fgetc(fp)) != EOF)
	{
		contents += ch;
	};
	fclose(fp);
	return CMDF_OK;
};

static CMDF_RETURN show_file(cmdf_arglist *arglist)
{
	/**
	 * @brief 显示文件暂存区内容
	 * 
	 */
	cout << " [" << filename << "] :" << endl;
	cout << contents << endl;
	cout << endl;
	return CMDF_OK;
};

static CMDF_RETURN create_file(cmdf_arglist *arglist)
{
	/**
	 * @brief 由用户输入创建文件
	 * 
	 */
	if (!arglist)
	{
		cout << " [Sytax Error] No file name provided!\n [Tip] Please provide file name like \"c mytext.txt\"" << endl;
		return CMDF_OK;
	};
	if (arglist->count != 1)
	{
		cout << " [Sytax Error] Please provide file name like \"c mytext.txt\"" << endl;
		return CMDF_OK;
	};
	filename = arglist->args[0];
	FILE *fp = fopen(arglist->args[0], "w");
	char ch;
	if (fp == NULL)
	{
		cout << " [Error] Unable to create file: " << filename << endl;
		return CMDF_OK;
	}
	else
	{
		cout << " [Done] Created file: " << filename << endl;
		cout << " [Tip] Input your file here (Crtl+D to end)" << endl;
	};
	contents.clear();
	while ((ch = getchar()) != EOF)
	{
		fputc(ch, fp);
		contents += ch;
	};
	fclose(fp);
	clearerr(CMDF_STDIN);
	return CMDF_OK;
};

static CMDF_RETURN append_file(cmdf_arglist *arglist)
{
	/**
	 * @brief 对现有文件进行追加
	 * 
	 */
	if (!arglist)
	{
		cout << " [Sytax Error] No file name provided!\n [Tip] Please provide file name like \"c mytext.txt\"" << endl;
		return CMDF_OK;
	};
	if (arglist->count != 1)
	{
		cout << " [Sytax Error] Please provide file name like \"c mytext.txt\"" << endl;
		return CMDF_OK;
	};
	filename = arglist->args[0];
	contents.clear();
	FILE *fp1 = fopen(arglist->args[0], "r");
	char ch;
	if (fp1 == NULL)
	{
		cout << " [Error] Unable to open file: " << filename << endl;
		return CMDF_OK;
	}
	else
	{
		cout << " [Done] Loaded file: " << filename << endl;
	};
	while ((ch = fgetc(fp1)) != EOF)
	{
		contents += ch;
	};
	fclose(fp1);
	ch = 0;
	FILE *fp2 = fopen(arglist->args[0], "a");
	if (fp2 == NULL)
	{
		cout << " [Error] Unable to append file: " << filename << endl;
		return CMDF_OK;
	}
	else
	{
		cout << " [Tip] Input your text to append here (Crtl+D to end)" << endl;
	};
	while ((ch = getchar()) != EOF)
	{
		fputc(ch, fp2);
		contents += ch;
	};
	fclose(fp2);
	clearerr(CMDF_STDIN);
	return CMDF_OK;
};

static CMDF_RETURN find_str(cmdf_arglist *arglist)
{
	/**
	 * @brief 查找字符串功能
	 * 
	 */
	if (!arglist)
	{
		cout << " [Sytax Error] No file name provided!\n [Tip] Please provide file name like \"f somestr\"" << endl;
		return CMDF_OK;
	};
	if (arglist->count != 1)
	{
		cout << " [Sytax Error] Please provide file name like \"f somestr\"" << endl;
		return CMDF_OK;
	};
	if (contents == "")
	{
		cout << " [Error] No contents in memory. Please read, write or append a file." << endl;
		return CMDF_OK;
	};
	kmp_text tmp(contents);
	pair<int, vector<int>> res = tmp.countWord(arglist->args[0]);
	cout << " [Number of substr] " << res.first << endl;
	cout << " [Pos of substr] ";
	for (auto u : res.second)
	{
		cout << u << ", ";
	};
	cout << endl;
	return CMDF_OK;
};

int main()
{
	cmdf_init("keyword> ", PROG_INTRO, NULL, NULL, 0, 1);

	/* Register our custom commands */
	cmdf_register_command(read_filename, "r", READ_HELP);
	cmdf_register_command(show_file, "s", CAT_HELP);
	cmdf_register_command(create_file, "c", NEW_HELP);
	cmdf_register_command(append_file, "a", APPEND_HELP);
	cmdf_register_command(find_str, "f", FIND_HELP);

	cmdf_commandloop();
	return 0;
}
