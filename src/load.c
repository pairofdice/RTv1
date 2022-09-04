/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:00:22 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/04 19:21:20 by jsaarine         ###   ########.fr       */
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

void	check_type(char *str, t_context *ctx) 
{
	if (ft_strcmp(str, "light") == 0)
		ctx->parse_obj.type = LIGHT;
	else if (ft_strcmp(str, "cone") == 0)
		ctx->parse_obj.type = CONE;
	else if (ft_strcmp(str, "plane") == 0)
		ctx->parse_obj.type = PLANE;
	else if (ft_strcmp(str, "cylinder") == 0)
		ctx->parse_obj.type = CYLINDER;
	else if (ft_strcmp(str, "sphere") == 0)
		ctx->parse_obj.type = SPHERE;

}

 static void	process_line(t_context *ctx, char ***words, t_vec *obj_vec)
{
	t_object	obj;
	int			i;

	i = 0;
	if (ctx->parse_state == PROCESSING && ctx->parse_obj.type == NOTHING)
	{
		// figure out what we're processing and set state
		(*words)++;
		printf("Processing: -%s-", **words);
		check_type(**words, ctx);
		printf("Type id: %d\n", ctx->parse_obj.type);
		return ;
	}
	if (ft_strcmp(**words, "light"))
		process_light();
	else if (ft_strcmp(**words, "object"))
		process_object(*words);
	//ft_atoi(*(*words));
	vec_push(obj_vec, &obj);
	//(*words)++;
}

int	load_scene(int fd, t_context *ctx)
{
	char	*line;
	char	**words;
	char	**temp;
	t_vec	obj_vec;

	vec_new(&ctx->scene, BUFF_SIZE * 2, sizeof(t_vec));
	while (get_next_line(fd, &line))
	{
		words = ft_strsplit(line, ' ');
		temp = words;
		if (*temp)
		{
			if (ctx->parse_state == NOTHING && **temp == '{')
			{
				ctx->parse_state = PROCESSING;
				vec_new(&obj_vec, ft_strlen(line) / 2 + 1, sizeof(t_object));
			}
			else if (**temp == '}')
				ctx->parse_state = NOTHING;
			if (ctx->parse_state == PROCESSING)
				process_line(ctx, &words, &obj_vec);
		}
		if (obj_vec.len > 0)
			vec_push(&ctx->scene, &obj_vec);
		free_array((void *)&temp);
		ft_strdel(&line);
	}
	return (1);
}
