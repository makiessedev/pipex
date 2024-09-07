#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	int	pipe_fd[2];
	int	p_id;

	if (ac != 5)
	{
		ft_putstr_fd("format: ./pipex infile cmd1 cmd2 outfile\n", 2);
		exit(-1);
	}
	if (pipe(pipe_fd) == -1)
	{
		perror("Error on init pipe!");
		exit(-1);
	}
	p_id = fork();
	if (p_id == -1)
	{
		perror("Error on create child!");
		exit(-1);
	}
	if (p_id)
		exec_on_parent_process(av[1], av[2], pipe_fd, env);
	else
		exec_on_child_process(av[4], av[3], pipe_fd, env);
	return (0);
}
