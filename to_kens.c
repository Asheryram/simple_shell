#include "shell.h"


/**
 * re_di_rec_tion - checks if token id is a redirection
 * @token_id: tokenid
 *
 * Return: 1 if yes , 0 if no
 */
int re_di_rec_tion(int token_id)
{
  return (token_id == TO_KEN_RE_WRITE || token_id == TO_KEN_AP_PEND ||
	  token_id == TO_KEN_CAT);
}

/**
 * del_tokens - freeing tokens
 * @tokens: tokens_t struct with tokens
 * Return: 0
 */
int del_tokens(tokens_t *tokens)
{
  unsigned int i;

  for (i = 0; i < tokens->tokensN; i++)
    free(tokens->tokens[i].str);

  free(tokens->tokens);
  tokens->tokens = NULL;
  tokens->tokensN = 0;

  return (0);
}

/**
 * del_dups - deletes duplicate semi-colons from data
 * @tokens: tokens_t struct
 */
void del_dups(tokens_t *tokens)
{
  unsigned int i, tokens_to_move;

  for (i = 0; i + 1 < tokens->tokensN;)
    {
      if ((tokens->tokens[i].id == tokens->tokens[i + 1].id) &&
	  (tokens->tokens[i].id == TO_KEN_SE_MI_CO_LON))
	{
	  tokens_to_move = tokens->tokensN - i - 1;
	  _chg_mem_loc(tokens->tokens + i, tokens->tokens + i + 1,
		   tokens_to_move * sizeof(token_t));

	  tokens->tokensN--;
	}
      else
	{
	  i++;
	}
    }
}

/**
 * token_clasify - classifies the tokens
 * @tokens: tokens_t struct
 */
void token_clasify(tokens_t *tokens)
{
  unsigned int i;
  int j;

  token_types token_names[] = {
			       { TO_KEN_SE_MI_CO_LON,  ";",  "semicolon",  1 },
			       { TO_KEN_BACK_GROUND, "&",  "background", 1 },
			       { TO_KEN_AND,        "&&", "and",        2 },
			       { TO_KEN_OR,         "||", "or",         2 },
			       { TO_KEN_PIPE ,       "|",  "pipe",       3 },
			       { TO_KEN_RE_WRITE,    ">",  "rewrite",    4 },
			       { TO_KEN_AP_PEND,     ">>", "append",     4 },
			       { TO_KEN_CAT,        "<",  "cat",        4 },
			       { 9, '\0', '\0', 9}
  };

  for (i = 0; i < tokens->tokensN; i++)
    {
      tokens->tokens[i].id = TO_KEN_STRING;

      for (j = 0; token_names[j].token_id != 9; j++)
	{
	  if (_strg_com_pare(token_names[j].token_str, tokens->tokens[i].str) == 0)
	    {
	      tokens->tokens[i].id = token_names[j].token_id;
	      tokens->tokens[i].prec = token_names[j].precedence;
	      break;
	    }
	}
    }
}



/**
 * init_to_kens - initializes token struct
 * @tokens: tokens struct to initialize
 * @length: length to malloc for
 */
void init_to_kens(tokens_t *tokens, int length)
{
  tokens->tokens = safe_malloc(length * sizeof(token_t));

  /* Initialize the rest of the structure */
  tokens->tokensN = 0;
}