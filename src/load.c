/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:00:22 by jsaarine          #+#    #+#             */
/*   Updated: 2022/08/28 15:28:59 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	handle_args(int argc, char **argv, t_context *ctx)
{
	int	fd;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			exit(1);
	}
	else
	{
		 // FIX ? ft_putstr("Usage: ./RTv1 <scene>\n");
		exit(1);
	}
	close(fd);
	return (1);
}

static void	free_array(void **array)
{
	void	**temp;

	temp = *array;
	while (*temp)
		ft_memdel(temp++);
	free(*array);
	*array = NULL;
}

static void	process_line( char ***words, t_vec *linevec)
{
	// LOOP OVER WORDS HERE
	ft_atoi(*(*words));
	vec_push(linevec, p);
	(*words)++;
}

int	load_map(int fd, t_context *ctx)
{
	char	*line;
	char	**words;
	char	**temp;
	t_vec	linevec;

	vec_new(&ctx->scene, BUFF_SIZE * 2, sizeof(t_vec));
	while (get_next_line(fd, &line))
	{
		vec_new(&linevec, ft_strlen(line) / 2 + 1, sizeof(t_point));
		words = ft_strsplit(line, ' ');
		temp = words;
		process_line(&words, &linevec);
		if (linevec.len > 0)
			vec_push(&ctx->scene, &linevec);
		free_array((void *)&temp);
		ft_strdel(&line);
	}
	return (1);
}
