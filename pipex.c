#include "pipex.h"

void	exec_on_parent_process(int fd, char *cmd, int p_fd[2], char **env)
{
	dup2(p_fd[1], 1);
	dup2(fd, 0);
	close(p_fd[0]);
	system(cmd);
}

void	exec_on_child_process(int fd, char *cmd, int p_fd[2], char **env)
{
	dup2(p_fd[0], 0);
	dup2(fd, 1);
	close(p_fd[1]);
	system(cmd);
}
