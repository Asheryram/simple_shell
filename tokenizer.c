#include "shell.h"


/**
 * clean_to_kens - cleans up tokeniz functions
 * @tokens: the gen_tokend tokens variable
 * @tokens_idx: the index referring to the tokens
 * @data: pointer used to store the data in tokens, only used in this
 * function to free the memory there
 */
void clean_to_kens(tokens_t *tokens, unsigned int tokens_idx, char *data)
{
  unsigned int i;

  tokens->tokensN = tokens_idx;
  token_clasify(tokens);
  del_dups(tokens);

  if (tokens->tokensN)
    {
      if (tokens->tokens[tokens->tokensN - 1].id == TO_KEN_SE_MI_CO_LON)
	tokens->tokensN--;
      for (i = 0; i < tokens->tokensN; i++)
	tokens->tokens[i].str = _str_dupp((char *)tokens->tokens[i].str);
    }
  free(data);
}

/**
 * gen_token - gen_tokens command string
 * @tokens: tokens_t struct containing initial string and array of strings
 * @string: command string
 */
void gen_token(tokens_t *tokens, const char *string)
{
  unsigned int l, string_idx, data_idx, tokens_idx;
  unsigned int skip_next, skip_quote, is_token;
  char *data, symbol;

  l = (_str_length(string) == 0 ? 1 : _str_length(string));
  init_to_kens(tokens, l);
  data = safe_malloc((l * 2 + 1) * sizeof(char));
  string_idx = data_idx = tokens_idx = skip_next = skip_quote = is_token = 0;
  while ((symbol = string[string_idx++]) != '\0' && symbol != '#')
    {
      if (!is_token && _is_t_space(symbol))
	continue;
      if (!is_token && !_is_t_space(symbol) && (symbol != ';'))
	tokens->tokens[tokens_idx++].str = data + data_idx, is_token = 1;
      if (is_token && _is_t_space(symbol) && !skip_next && !skip_quote)
	{
	  data[data_idx++] = '\0', is_token = 0;
	  continue;
	}
      if ((symbol == ';') && !skip_next && !skip_quote)
	{
	  if (is_token)
	    data[data_idx++] = '\0';
	  tokens->tokens[tokens_idx++].str = data + data_idx;
	  data[data_idx++] = ';', data[data_idx++] = '\0', is_token = 0;
	  continue;
	}
      if ((symbol == '\"' || symbol == '\'') && !skip_next)
	{
	  skip_quote = !skip_quote;
	  continue;
	}
      if ((symbol == '\\') && !skip_next)
	{
	  skip_next = 1;
	  continue;
	}
      skip_next = 0, data[data_idx++] = symbol;
    }
  clean_to_kens(tokens, tokens_idx, data);
}

