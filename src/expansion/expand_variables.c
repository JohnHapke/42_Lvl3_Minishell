//added this file so git would recognize this directory

#include "../../include/minishell.h"

char	*ft_insert_str(char *str, char *insert, size_t where)
{
	char	*ret;

	if (where > (ft_strlen(str) + ft_strlen(str)))
	ret = ft_calloc(ft_strlen(str) + ft_strlen(insert), sizeof(char));
	ft_memcpy(ret, str, where);
	ft_memcpy(&ret[where], insert, ft_strlen(insert));
	ft_memcpy(&ret[ft_strlen(insert) + where], &str[where], ft_strlen(&str[where]));
	return (ret);
}
