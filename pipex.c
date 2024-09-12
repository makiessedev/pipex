#include "pipex.h"

static char	*get_bin_path(char **cmds, char **env);
static void	free_mat(char **mat);

void	exec_on_child_process(char *file, char *cmd, int p_fd[2], char **env)
{
	char	**cmds;
	char	*exec_path;
	int		fd;

	cmds = ft_split(cmd, ' ');
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("infile error");
		free_mat(cmds);
		exit(1);
	}
	dup2(p_fd[1], 1);
	dup2(fd, 0);
	close(p_fd[0]);
	exec_path = get_bin_path(cmds, env);
	if (execve(exec_path, cmds, env) == -1)
	{
		perror("Error on exec command!");
		free_mat(cmds);
		free(exec_path);
		exit(1);;
	}
}

void	exec_on_parent_process(char *file, char *cmd, int p_fd[2], char **env)
{
	char	**cmds;
	char	*exec_path;
	int		fd;

	cmds = ft_split(cmd, ' ');
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("outfile error");
		free_mat(cmds);
		exit(1);
	}
	dup2(p_fd[0], 0);
	dup2(fd, 1);
	close(p_fd[1]);
	exec_path = get_bin_path(cmds, env);
	if (execve(exec_path, cmds, env) == -1)
	{
		perror("Error on exec command!");
		free_mat(cmds);
		free(exec_path);
		exit(1);
	}
}

static char	*get_bin_path(char **cmds, char **env)
{
	char	**path;
	char	**paths;
	char	*bin_path;
	char	*err_msg;
	char	*executable;
	int		i;

	i = -1;
	while (env[++i] != NULL)
	{
		path = ft_split(env[i], '=');
		if (ft_strncmp(path[0], "PATH", ft_strlen("PATH")) == 0)
		{
			paths = ft_split(path[1], ':');
			i = -1;
			while (paths[++i])
			{
				bin_path = ft_strjoin(paths[i], "/");
				executable = ft_strjoin(bin_path, cmds[0]);
				if (access(executable, X_OK) == 0)
				{
					free_mat(paths);
					free_mat(path);
					free(bin_path);
					return (executable);
				}
				free(executable);
				free(bin_path);
			}
			err_msg = ft_strjoin(cmds[0], ": command not found!");
			ft_putstr_fd(err_msg, 2);
			free(err_msg);
			free_mat(paths);
			free_mat(path);
			free_mat(cmds);
			exit(1);
		}
		free_mat(path);
	}
	exit(1);
}

static void	free_mat(char **mat)
{
	int	i;

	i = -1;
	while(mat[++i])
		free(mat[i]);
	free(mat);
}
