#include "./libft/libft.h"
#include <stdio.h>
#include <fcntl.h>

#ifndef pipex
# define pipex
#endif

void	exec_on_parent_process(int fd, char *cmd, int p_fd[2], char **env);
void	exec_on_child_process(int fd, char *cmd, int p_fd[2], char **env);
