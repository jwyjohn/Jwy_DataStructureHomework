/*** Start of inlined file: bsorttree.h ***/
#ifndef _BSORTTREE_H__
#define _BSORTTREE_H__

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <map>
#include <assert.h>

using namespace std;

typedef struct avl_tree_node
{
	int data = 0;
	int height = 0;
	avl_tree_node *left = nullptr;
	avl_tree_node *right = nullptr;

} avl_tree;

avl_tree *root;

int clear_tree(avl_tree *t);
int get_balance(avl_tree *t);
int get_height(avl_tree *t);
int get_height_s(avl_tree *t);

int clear_tree(avl_tree *t)
{
	if (t->left != nullptr)
	{
		clear_tree(t->left);
	};
	if (t->right != nullptr)
	{
		clear_tree(t->right);
	};
	delete t;
	return 0;
};

int print_tree_lvr(avl_tree *t)
{
	if (t->left != nullptr)
	{
		print_tree_lvr(t->left);
	};
	if (t->data != 0)
		// cout << " " << t->data << "[" << get_balance(t) << "," << get_height(t) << "," << get_height_s(t) << "]";
		cout << " " << t->data;
	if (t->right != nullptr)
	{
		print_tree_lvr(t->right);
	};
	return 0;
};

int print_tree_vlr(avl_tree *t)
{
	if (t->data != 0)
		// cout << " " << t->data << "[" << get_balance(t) << "," << get_height(t) << "," << get_height_s(t) << "]";
		cout << " " << t->data;
	if (t->left != nullptr)
	{
		print_tree_vlr(t->left);
	};

	if (t->right != nullptr)
	{
		print_tree_vlr(t->right);
	};
	return 0;
};

int print_tree_lrv(avl_tree *t)
{
	if (t->left != nullptr)
	{
		print_tree_lrv(t->left);
	};

	if (t->right != nullptr)
	{
		print_tree_lrv(t->right);
	};
	if (t->data != 0)
		// cout << " " << t->data << "[" << get_balance(t) << "," << get_height(t) << "," << get_height_s(t) << "]";
		cout << " " << t->data;
	return 0;
};

int get_height(avl_tree *t)
{
	if (t == nullptr)
		return 0;
	return max(get_height(t->left), get_height(t->right)) + 1;
};

int get_height_s(avl_tree *t)
{
	if (t == nullptr)
		return 0;
	return max(get_height_s(t->left), get_height_s(t->right)) + 1;
};

// int get_height(avl_tree *t)
// {
// 	if (t == nullptr)
// 		return 0;
// 	if (t->lazy == true)
// 		return t->height;
// 	else
// 	{
// 		t->height = max(get_height_s(t->left), get_height_s(t->right)) + 1;
// 		// t->height = max(get_height(t->left), get_height(t->right)) + 1;
// 		t->lazy = true;
// 	}
// 	return t->height;
// };

int get_balance(avl_tree *t)
{
	if (t == nullptr)
		return 0;
	return get_height(t->right) - get_height(t->left);
	// return get_height_s(t->right) - get_height_s(t->left);
};

avl_tree *rotate_left(avl_tree *t)
{
	avl_tree *root;
	root = t->right;
	t->right = t->right->left;
	root->left = t;
	return root;
};

avl_tree *rotate_right(avl_tree *t)
{
	avl_tree *root;
	root = t->left;
	t->left = t->left->right;
	root->right = t;
	return root;
};

avl_tree *adjust_tree_RR(avl_tree *t)
{
	return rotate_right(t);
};

avl_tree *adjust_tree_LL(avl_tree *t)
{
	return rotate_left(t);
};

avl_tree *adjust_tree_LR(avl_tree *t)
{
	avl_tree *root;
	t->left = rotate_left(t->left);
	root = rotate_right(t);
	return root;
};

avl_tree *adjust_tree_RL(avl_tree *t)
{
	avl_tree *root;
	t->right = rotate_right(t->right);
	root = rotate_left(t);
	return root;
};

int balance_node(avl_tree *&t)
{
	int bf = get_balance(t);
	if (bf > 1)
	{
		if (get_balance(t->right) > 0)
		{
			t = adjust_tree_LL(t);
		}
		else
		{
			t = adjust_tree_RL(t);
		};
	};
	if (bf < -1)
	{
		if (get_balance(t->left) < 0)
		{
			t = adjust_tree_RR(t);
		}
		else
		{
			t = adjust_tree_LR(t);
		};
	};
	return 0;
};

avl_tree *find_val(avl_tree *t, int val)
{
	if (val == t->data)
		return t;
	if (val < t->data)
	{
		if (t->left == nullptr)
			return t;
		else
			return find_val(t->left, val);
	};
	if (val > t->data)
	{
		if (t->right == nullptr)
			return t;
		else
			return find_val(t->right, val);
	};
	return nullptr;
};

int val_is_in(avl_tree *t, int val)
{
	if (val == t->data)
	{
		// cout << "Im Here. " << t->data << " " << val << endl;
		return 1;
	};

	if (val < t->data)
	{
		if (t->left == nullptr)
			return 0;
		else
			return val_is_in(t->left, val);
	};
	if (val > t->data)
	{
		if (t->right == nullptr)
			return 0;
		else
			return val_is_in(t->right, val);
	};
	return 0;
};

int insert_val(avl_tree *&t, int val)
{
	if (t->data == val)
	{
		// cout << "Value exists!" << endl;
		return 1;
	}
	else
	{
		if (val < t->data)
		{
			if (t->left == nullptr)
			{
				avl_tree_node *ins = new avl_tree_node;
				ins->data = val;
				t->left = ins;
			}
			else
			{
				insert_val(t->left, val);
			}
		};
		if (val > t->data)
		{
			if (t->right == nullptr)
			{
				avl_tree_node *ins = new avl_tree_node;
				ins->data = val;
				t->right = ins;
			}
			else
			{
				insert_val(t->right, val);
			}
		};
	};
	balance_node(t);
	return 0;
};

int remove_val(avl_tree *&t, int val)
{
	if (t->data == val)
	{
		if (t->left == nullptr && t->right == nullptr)
		{
			avl_tree *to_del = t;
			t = nullptr;
			delete to_del;
			return 0;
		}
		else if (t->left != nullptr && t->right == nullptr)
		{
			avl_tree *to_del = t;
			t = t->left;
			delete to_del;
			return 0;
		}
		else if (t->right != nullptr && t->left == nullptr)
		{
			avl_tree *to_del = t;
			t = t->right;
			delete to_del;
			return 0;
		}
		else if (t->left != nullptr && t->right != nullptr)
		{
			avl_tree *left_max = t->left, *pre_max = nullptr;
			while (left_max->right != nullptr)
			{
				pre_max = left_max;
				left_max = left_max->right;
			}
			t->data = left_max->data;
			if (left_max == t->left)
			{
				t->left = left_max->left;
			}
			else
			{
				pre_max->right = left_max->left;
			};
			delete left_max;
			return 0;
		};
	}
	else
	{
		if (val < t->data)
		{
			if (t->left == nullptr)
			{
				// cout<<"Value not found!"<<endl;
				return 1;
			}
			else
			{
				remove_val(t->left, val);
			}
		};
		if (val > t->data)
		{
			if (t->right == nullptr)
			{
				// cout<<"Value not found!"<<endl;
				return 1;
			}
			else
			{
				remove_val(t->right, val);
			}
		};
	};
	balance_node(t);
	return 0;
};
#endif

/*** End of inlined file: bsorttree.h ***/

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



/* For the C++ support. */
#ifdef __cplusplus
}
#endif
/*** End of inlined file: libcmdf.h ***/

/*** Start of inlined file: main.cpp ***/
#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>
#include <stack>

#define _CRT_SECURE_NO_WARNINGS
#define LIBCMDF_IMPL

using namespace std;

#define PROG_INTRO "                 ___  ______                      \n                /\\_ \\/\\__  _\\                     \n   __     __  __\\//\\ \\/_/\\ \\/ _ __    __     __   \n /'__`\\  /\\ \\/\\ \\ \\ \\ \\ \\ \\ \\/\\`'__\\/'__`\\ /'__`\\ \n/\\ \\L\\.\\_\\ \\ \\_/ | \\_\\ \\_\\ \\ \\ \\ \\//\\  __//\\  __/ \n\\ \\__/.\\_\\\\ \\___/  /\\____\\\\ \\_\\ \\_\\\\ \\____\\ \\____\\\n \\/__/\\/_/ \\/__/   \\/____/ \\/_/\\/_/ \\/____/\\/____/\n                                                  \n                                                  \n\n - Free Software by 1951510 JiangWenyuan \nNov 2021\n==================================================\n! This is a program to operate an AVL Tree.\n! Input command 'add 19 7 6 4 ...' to add values to tree.\n! Input command 'lvr', 'lvr' or to expolre the tree.\n! Input command 'find 19 7 6 3...' to search value in the tree.\n! Use 'rm 9 7 5 3...' to remove value in tree.\n! Use 'init' to clear and init tree WITH CAUTION.\n"
#define INIT_HELP "Initialize the binary sort tree.\n"
#define VLR_HELP "Print the tree in ROOT LEFT RIGHT order.\n"
#define LVR_HELP "Print the tree in LEFT ROOT RIGHT order.\n"
#define LRV_HELP "Print the tree in LEFT RIGHT ROOT order.\n"
#define ADD_HELP "Add value to graph. Format \"add N\"\n"
#define FIND_HELP "Add edge to graph. Format \"find N\"\n"
#define REMOVE_HELP "Remove value from tree. Format \"rm N\"\n "

static CMDF_RETURN init_tree(cmdf_arglist *arglist)
{
	clear_tree(root);
	root = new avl_tree;
	cout << " [Success] Binary Sort Tree cleared and initialized." << endl;
	return CMDF_OK;
};

static CMDF_RETURN vlr(cmdf_arglist *arglist)
{
	if (root->left == nullptr && root->right == nullptr)
	{
		cout << " [Error] Tree is empty. Use 'add N' to add some nodes." << endl;
		return CMDF_OK;
	};
	cout << " [VLR] " << endl;
	print_tree_vlr(root);
	cout << endl;
	return CMDF_OK;
};

static CMDF_RETURN lvr(cmdf_arglist *arglist)
{
	if (root->left == nullptr && root->right == nullptr)
	{
		cout << " [Error] Tree is empty. Use 'add N' to add some nodes." << endl;
		return CMDF_OK;
	};
	cout << " [LVR] " << endl;
	print_tree_lvr(root);
	cout << endl;
	return CMDF_OK;
};

static CMDF_RETURN lrv(cmdf_arglist *arglist)
{
	if (root->left == nullptr && root->right == nullptr)
	{
		cout << " [Error] Tree is empty. Use 'add N' to add some nodes." << endl;
		return CMDF_OK;
	};
	cout << " [LRV] " << endl;
	print_tree_lrv(root);
	cout << endl;
	return CMDF_OK;
};

bool isNumber(const string &str)
{
	for (char const &c : str)
	{
		if (std::isdigit(c) == 0)
			return false;
	}
	return true;
}

static CMDF_RETURN add_node(cmdf_arglist *arglist)
{
	if (!arglist)
	{
		cout << " [Sytax Error] No arguments provided!\n [Tip] Please provide node name like \"add 5 7 4 1 ... 10\"" << endl;
		return CMDF_OK;
	};
	for (int i = 0; i < arglist->count; i++)
	{
		if (!isNumber(arglist->args[i]))
		{
			cout << " [Error] Value " << arglist->args[i] << " is not nubmer." << endl;
		}
		else if (stoi(arglist->args[i]) <= 0)
		{
			cout << " [Error] Value " << arglist->args[i] << " should be an int and >0." << endl;
		}
		else
		{
			if (val_is_in(root, stoi(arglist->args[i])) == 1)
			{
				cout << " [Error] Value " << arglist->args[i] << " is alerady in tree." << endl;
			}
			else
			{
				insert_val(root, stoi(arglist->args[i]));
				cout << " [Success] Value " << arglist->args[i] << " added." << endl;
			};
		};
	};
	return CMDF_OK;
};

static CMDF_RETURN find_node(cmdf_arglist *arglist)
{
	if (!arglist)
	{
		cout << " [Sytax Error] No arguments provided!\n [Tip] Please provide node name like \"find 5 7 4 1 ... 10\"" << endl;
		return CMDF_OK;
	};
	for (int i = 0; i < arglist->count; i++)
	{
		if (!isNumber(arglist->args[i]))
		{
			cout << " [Error] Value " << arglist->args[i] << " is not nubmer." << endl;
		}
		else if (stoi(arglist->args[i]) <= 0)
		{
			cout << " [Error] Value " << arglist->args[i] << " should be an int and >0." << endl;
		}
		else
		{
			if (val_is_in(root, stoi(arglist->args[i])) == 1)
			{
				cout << " [Success] Value " << arglist->args[i] << " is in tree." << endl;
			}
			else
			{
				cout << " [Error] Value " << arglist->args[i] << " is not in tree." << endl;
			};
		};
	};
	return CMDF_OK;
};

static CMDF_RETURN rm_node(cmdf_arglist *arglist)
{
	if (!arglist)
	{
		cout << " [Sytax Error] No arguments provided!\n [Tip] Please provide node name like \"rm 5 7 4 1 ... 10\"" << endl;
		return CMDF_OK;
	};
	for (int i = 0; i < arglist->count; i++)
	{
		if (!isNumber(arglist->args[i]))
		{
			cout << " [Error] Value " << arglist->args[i] << " is not nubmer." << endl;
		}
		else if (stoi(arglist->args[i]) <= 0)
		{
			cout << " [Error] Value " << arglist->args[i] << " should be an int and >0." << endl;
		}
		else
		{
			if (val_is_in(root, stoi(arglist->args[i])) == 1)

			{
				remove_val(root, stoi(arglist->args[i]));
				cout << " [Success] Value " << arglist->args[i] << " is removed." << endl;
			}
			else
			{
				cout << " [Error] Value " << arglist->args[i] << " is not in tree." << endl;
			};
		};
	};
	return CMDF_OK;
};

int main()
{
	root = new avl_tree;
	cmdf_init("network> ", PROG_INTRO, NULL, NULL, 0, 1);

	/* Register our custom commands */
	cmdf_register_command(init_tree, "init", INIT_HELP);
	cmdf_register_command(find_node, "find", FIND_HELP);
	cmdf_register_command(add_node, "add", ADD_HELP);
	cmdf_register_command(rm_node, "rm", REMOVE_HELP);
	cmdf_register_command(vlr, "vlr", VLR_HELP);
	cmdf_register_command(lvr, "lvr", LVR_HELP);
	cmdf_register_command(lrv, "lrv", LRV_HELP);

	cmdf_commandloop();
	return 0;
	return 0;
}
/*** End of inlined file: main.cpp ***/
