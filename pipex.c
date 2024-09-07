#include "pipex.h"

static char	*get_bin_path(char *cmd, char **env);

void	exec_on_parent_process(int fd, char **cmds, int p_fd[2], char **env)
{
	dup2(p_fd[1], 1);
	dup2(fd, 0);
	close(p_fd[0]);
	if (execve(get_bin_path(cmds[0], env), cmds, env) == -1)
		perror("Error on exec command!");
}

void	exec_on_child_process(int fd, char **cmds, int p_fd[2], char **env)
{
	dup2(p_fd[0], 0);
	dup2(fd, 1);
	close(p_fd[1]);
	if (execve(get_bin_path(cmds[0], env), cmds, env) == -1)
		perror("Error on exec command!");
}

static char	*get_bin_path(char *cmd, char **env)
{
	int	i;
	char	**path;
	char	*err_msg;
	i = -1;

	while (env[++i])
	{
		path = ft_split(env[i], '=');
		if (ft_strncmp(path[0], "PATH", ft_strlen("PATH")) == 0)
		{
			path = ft_split(path[1], ':');
			i = -1;
			while (path[++i])
			{
				path[i] = ft_strjoin(path[i], ft_strjoin("/", cmd));
				if (access(path[i], X_OK) == 0)
					return (path[i]);
			}
			err_msg = ft_strjoin(cmd, ": command not found!");
			ft_putstr_fd(err_msg, 2);
			exit(-1);
		}
	}
	exit(-1);
}
