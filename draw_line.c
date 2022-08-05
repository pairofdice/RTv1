typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	double	c;
}	t_point;

typedef struct s_deltas
{
	double	x;
	double	y;
	double	z;
	double	r;
	double	g;
	double	b;
}	t_deltas;

typedef struct s_line
{
	t_point	a;
	t_point	b;
}	t_line;

static void	set_points(t_point *p, t_deltas *deltas, t_line *line)
{
	*p = line->a;
	line->a.x = (int)line->a.x;
	line->a.y = (int)line->a.y;
	line->b.x = (int)line->b.x;
	line->b.y = (int)line->b.y;
	deltas->x = line->b.x - line->a.x;
	deltas->y = line->b.y - line->a.y;


}

t_line	line_new(double a_x, double a_y, double b_x, double b_y)
{
	t_line line;
	t_point a;
	t_point b;
	a.x = a_x;
	a.y = a_y;
	b.x = b_x;
	b.y = b_y;
	line.a = a;
	line.b = b;
	return (line);
}


void	draw_line(t_line *line)
{
	t_deltas	deltas;
	t_point		p;
	int			steps;
	t_point		color;

	deltas->x = line->b.x - line->a.x;
	deltas->y = line->b.y - line->a.y;
	if (ft_abs(deltas.x) >= ft_abs(deltas.y))
		steps = ft_abs(deltas.x);
	else
		steps = ft_abs(deltas.y);
	deltas.x /= steps;
	deltas.y /= steps;

		while (steps >= 0)
		{
			img_pixel_put(&ctx->fb, p.x, p.y,0xFFFFFFFF);
			p.x += deltas.x;
			p.y += deltas.y;
			steps--;
		}

}
