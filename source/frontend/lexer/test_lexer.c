#include "minishell.h"

void	test_lexer(t_shell *shell)
{
	t_list	*cur;
	t_token	*token_node;

	ft_lexer(shell);

	cur = shell->token_list;
	printf("**************\n");
	while (cur)
	{
		token_node = (t_token *) cur->content;
		printf("\ndata: %s\n", token_node->data);
		printf("type: %i / %s\n", token_node->type, ft_get_token_type_str(token_node->type));
		cur = cur->next;
	}
	printf("\n**************\n");
	ft_lstclear(&shell->token_list, free);
}
