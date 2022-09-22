/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:00:22 by jsaarine          #+#    #+#             */
/*   Updated: 2022/09/22 14:44:10 by jsaarine         ###   ########.fr       */
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
	if (!words || !(*words) || !(**words) || !(***words))
		return ;
	**words = ft_strtrim(**words);
	if (ft_strncmp(**words, "loc", 3) == 0)
	{
		ctx->obj.loc = read_triple(ctx, *words);
		printf("?? %f %f %f\n", ctx->obj.loc.x, ctx->obj.loc.y, ctx->obj.loc.z);
	}
	if (ft_strncmp(**words, "rot", 3) == 0)
		ctx->obj.rot = vec3_unit(read_triple(ctx, *words));
	if (ft_strncmp(**words, "coi", 3) == 0)
		ctx->cam.coi = read_triple(ctx, *words);
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

static void	parse_line(t_context *ctx)
{
	if (ctx->parse_state == NOTHING && **ctx->temp == '{')
		check_type(ctx->temp, ctx);
	else if (**ctx->temp == '}')
	{
		if (ctx->obj.type == CAMERA)
			set_camera(ctx);
		ctx->parse_state = NOTHING;
		if (vec_push(&ctx->scene, &ctx->obj) == -1)
			exit (1);
	}
	else if (ctx->parse_state == PROCESSING)
		process_line(ctx, &ctx->words);
}

int	load_scene(int fd, t_context *ctx)
{
	if (!(vec_new(&ctx->scene, BUFF_SIZE * 2, sizeof(t_object))))
		exit(1);
	ctx->gnl = 1;
	while (ctx->gnl == 1)
	{
		ctx->gnl = get_next_line(fd, &ctx->line);
		if (ctx->gnl <= 0)
			break ;
		ctx->words = ft_strsplit(ctx->line, ' ');
		ctx->temp = ctx->words;
		if (*ctx->temp)
			parse_line(ctx);
		free_array((void *)&ctx->temp);
		ft_strdel(&ctx->line);
	}
	if (ctx->gnl != 0)
		return (0);
	return (1);
}
