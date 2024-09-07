#ifndef PIPEX_H
# define PIPEX_H
# include "./libft/libft.h"
# include <fcntl.h>

void	exec_on_parent_process(char *file, char *cmd, int p_fd[2], char **env);
void	exec_on_child_process(char *file, char *cmd, int p_fd[2], char **env);
#endif
