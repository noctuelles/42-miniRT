/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_lexer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:12:27 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/11 16:59:32 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_LEXER_H
# define MINIRT_LEXER_H

# include "libft.h"
# include <stdint.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdbool.h>

# define STR_AMBIANT_LIGHT    "A"
# define STR_CAMERA           "C"
# define STR_LIGHT            "L"
# define STR_COMMA            ","
# define STR_NEWLINE          "\n"
# define STR_TAB              "\t"
# define STR_SPACE            " "
# define STR_SPHERE           "sp"
# define STR_PLAN             "pl"
# define STR_CYLINDER         "cl"
# define STR_CONE             "cn"

# define STR_ERROR                  "Error\n"
# define STR_INVALID_FILE_EXTENSION "invalid file extension"
# define STR_ERROR_FILE_READ        "an error occured during file reading"
# define STR_EMPTY_FILE             "empty or invalid file."
# define STR_INVALID_SYNTAX         "invalid syntax"

# define STR_TOO_MUCH_AMLIGHT       "minirt: line %u: ambiant light cannot be \
declared more than once.\n"
# define STR_TOO_MUCH_CAMERA        "minirt: line %u: camera cannot be \
declared more than once.\n"
# define STR_TOO_MUCH_LIGHT         "minirt: line %u: light cannot be \
declared more than once.\n"
# define STR_NO_CAMERA              "no camera declared in the scene"
# define STR_NO_AMBIANT_LIGHT       "no ambient light declared"

# define STR_FILE_EXTENSION         ".rt"

# define STR_FUNCTION_READ          "read"
# define STR_FUNCTION_OPEN          "open"
# define STR_FUNCTION_MALLOC        "malloc"

typedef enum e_token_type
{
	T_CAMERA,
	T_AMBIANT_LIGHT,
	T_LIGHT,
	T_SPHERE,
	T_CYLINDER,
	T_CONE,
	T_PLAN,
	T_NEWLINE,
	T_VALUE,
	T_COMMA,
	T_BREAK,
	T_NULL
}				t_token_type;

typedef struct e_token
{
	t_token_type	type;
	size_t			len;
	char			*value;
}				t_token;

typedef enum e_lexer_errcode
{
	E_LEX_TOO_MUCH_AMLIGHT,
	E_LEX_TOO_MUCH_CAMERA,
	E_LEX_TOO_MUCH_LIGHT,
	E_LEX_MALLOC
}			t_lexer_errcode;

typedef struct e_lexer
{
	char				**file_content;
	t_list				*list_tkns;
	t_token				tkn;
	const char			*line;
	const char			*prev;
	unsigned int		declared_ambiant_light;
	unsigned int		declared_camera;
	unsigned int		declared_light;
	size_t				line_nbr;
	t_lexer_errcode		errcode;
}				t_lexer;

/*
 *	lexer.c
 */

t_list	*lex_from_file(const char *filename);

/* file.c */

char	**read_file(const char *filename);

/* file_utils.c */

size_t	get_file_nbr_lines(int fd);
char	*readline(int fd, char **line);

/* io_utils.c */

void	*print_error(const char *error_msg);
void	*print_error_function(const char *function);
void	*print_error_line_nbr(const char *error_msg, size_t line_nbr);
void	print_warning(const char *message);

/* tokens.c */

t_token	set_token(char *str, t_token_type type);
t_token	*new_token(char *str, size_t len, t_token_type type);
void	free_token(void *token);

/* lexer_utils.c */

void	*add_known_token_to_list(t_lexer *lexer);
t_token	search_known_token(const char *str);
t_token	*add_token_to_list(t_lexer *lexer, char *value, size_t len,
			t_token_type type);
bool	analysis_syntax(t_list	*tkns);
void	remove_break_tokens(t_list **tkns);

/* lexer_utils2.c */

bool	check_valid_lexing(t_lexer *lexer);

t_list	*lex_from_file(const char *filename);

#endif
