#include "pipex.h"
#include <stdio.h>

int	main(int ac, char **av, char **env)
{
	if (ac == 5)
	{
		int	fd_file1;
		int	fd_file2;
		char	**cmd1;
		char	**cmd2;
		int	pipe_fd[2];
		int	p_id;

		fd_file1 = open(av[1], O_RDONLY);
		fd_file2 = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		cmd1 = ft_split(av[2], ' ');
		cmd2 = ft_split(av[3], ' ');

		if (fd_file1 == -1 || fd_file2 == -1)
		{
			perror("infile | outfile error");
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
			exec_on_parent_process(fd_file1, cmd1, pipe_fd, env);
		else
			exec_on_child_process(fd_file2, cmd2, pipe_fd, env);
	}
	else
		ft_putstr_fd("format: ./pipex infile cmd1 cmd2 outfile\n", 2);
}
