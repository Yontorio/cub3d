#include "stdfcts.h"

static int	overflow(long result, int sign)
{
	if (sign == 1 && result > (long)INT_MAX)
		return (1);
	if (sign == -1 && result > (long)INT_MIN)
		return (1);
	return (0);
}

int	ft_atoi(char *s)
{
	long	result;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	result = 0;
	if (!s)
		return (-1);
	i += skip_spaces(s, i);
	if (s[i] == '-' || s[i] == '+')
		if (s[i++] == '-')
			sign = -1;
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + (s[i++] - '0');
		if (overflow(result, sign))
			return (-1);
	}
	return ((int)(result * sign));
}