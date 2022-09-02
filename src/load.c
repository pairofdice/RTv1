/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:00:22 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/02 20:18:00 by jsaarine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RTv1.h"

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
		ft_putstr("Usage: ./RTv1 <scene>\n");
		exit(1);
	}
	load_scene(fd, ctx);
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

static void	process_object(char **words)
{
	while (*words != 0)
	{
		printf("- %s\n", *words);
		words++;
	}
	printf("Object has been processed\n");
}

static void	process_light()
{
	printf("Light has been processed\n");
}

/* static void	process_line( char ***words, t_vec *linevec)
{
	t_object	obj;
	int			i;

	i = 0;
	// LOOP OVER WORDS HERE
	if (ft_strcmp(**words, "light"))
		process_light();
	else if (ft_strcmp(**words, "object"))
		process_object();	
	//ft_atoi(*(*words));
	vec_push(linevec, &obj);
	(*words)++;
}
 */
int	load_scene(int fd, t_context *ctx)
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
		printf("%s\n", *temp);
		if (*temp)
		{
			if (ft_strncmp(*temp, "light", 5) == 0)
				process_light();
			else if (ft_strncmp(*words, "object", 6) == 0)
				process_object(temp);
			
		}

		// process_line(&words, &linevec);
		if (linevec.len > 0)
			vec_push(&ctx->scene, &linevec);
		free_array((void *)&temp);
		ft_strdel(&line);
	}
	return (1);
}
