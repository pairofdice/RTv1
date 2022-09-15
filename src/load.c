/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:00:22 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/15 19:28:31 by jsaarine         ###   ########.fr       */
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

static void	process_line(t_context *ctx, char ***words/* , t_vec *obj_vec */)
{
	int			i;

	i = 0;
	if (!words || !(*words) || !(**words) || !(***words))
		return ;
	**words = ft_strtrim(**words);
	if (ft_strncmp(**words, "loc", 3) == 0)
	{
		ctx->obj.loc = read_triple(ctx, *words);
		printf("?? %f %f %f\n", ctx->obj.loc.x, ctx->obj.loc.y, ctx->obj.loc.z);
	}
	if (ft_strncmp(**words, "rot", 3) == 0)
	{
		
		ctx->obj.rot = read_triple(ctx, *words);
		ctx->obj.rot = vec3_unit(ctx->obj.rot);
	}
	if (ft_strncmp(**words, "color", 5) == 0)
		ctx->obj.color = read_triple(ctx, *words);
		printf("\n %f %f %f  \n", ctx->obj.color.x, ctx->obj.color.y , ctx->obj.color.z);
	if (ft_strncmp(**words, "size", 4) == 0)
	{
		(*words)++;
		printf("%s", **words);
		ctx->obj.size = ft_atof(**words);
		printf(" - %f", ctx->obj.size);
	}
}

int	load_scene(int fd, t_context *ctx)
{
	char	*line;
	char	**words;
	char	**temp;
	//t_vec	obj_vec;

	printf("...\n");
	vec_new(&ctx->scene, BUFF_SIZE * 2, sizeof(t_object));
	while (get_next_line(fd, &line))
	{
		words = ft_strsplit(line, ' ');
		temp = words;
		if (*temp)
		{
			if (ctx->parse_state == NOTHING && **temp == '{')
			{
				ctx->parse_state = PROCESSING;
				check_type(temp, ctx);
				//vec_new(&obj_vec, ft_strlen(line) / 2 + 1, sizeof(t_object));
			}
			else if (**temp == '}')
			{
				// printf("Hello\n");
				ctx->parse_state = NOTHING;
				//push_obj(ctx);
				vec_push(&ctx->scene, &ctx->obj);
			}
			else if (ctx->parse_state == PROCESSING)
			{
				process_line(ctx, &words/* , &obj_vec  */);
			}
		}
		free_array((void *)&temp);
		ft_strdel(&line);
	}
	return (1);
}
