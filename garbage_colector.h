#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include <stdlib.h>

typedef struct s_gc_node
{
	void				*ptr;
	struct s_gc_node	*next;
}	t_gc_node;

typedef struct s_gc
{
	t_gc_node	*head;
}	t_gc;

t_gc	*gc_init(void);
void	*gc_malloc(t_gc *gc, size_t size);
void	gc_free_all(t_gc *gc);
void	gc_remove_ptr(t_gc *gc, void *ptr);

#endif