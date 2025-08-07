#include <libc.h>


typedef struct s_map
{
	int		is_valid;
	char	grid;
}	t_map;

typedef struct g_map
{
	char	grid;
	int		is_valid;
}	t_gap;

int main(void)
{
    printf("%lu\n", sizeof(t_map));
    printf("%lu\n", sizeof(t_gap));
}