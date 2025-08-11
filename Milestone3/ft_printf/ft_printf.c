#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

int ft_putstr(char *str);
int ft_putnbr_base(int nbr, int base);


int	ft_printf(const char *message, ...)
{
	va_list	args;
	int i = 0;
	int len = 0;

	va_start(args, message);
	while (message[i])
	{
		if (message[i] == '%' && message[i + 1] != '\0')
		{
			i++;
			if (message[i] == 's')
				len += ft_putstr(va_arg(args, char *));
			if (message[i] == 'd')
				len += ft_putnbr_base(va_arg(args, int), 10);
			if (message[i] == 'x')
				len += ft_putnbr_base(va_arg(args, int), 16);
			if (message[i] == '%')
				len += write(1, "%", 1);
		}
		else
			len += write(1, &message[i], 1);
		i++;
	}
	return (len);
}

int ft_putstr(char *str)
{
	int i = 0;
	int len = 0;

	if (!str)
		str = "(null)";
	while (str[i])
	{
		len += write(1, &str[i], 1);
		i++;
	}
	return (len);
}

int ft_putnbr_base(int nbr, int base)
{
	int len = 0;
	unsigned int tmp_nbr = 0;
	char *hexa = "0123456789abcdef";

	if (nbr < 0 && base == 10)
	{
		tmp_nbr = -nbr;
		len += write(1, "-", 1);
	}
	else
		tmp_nbr = (unsigned int)nbr;
	if (tmp_nbr >= (unsigned int)base)
		len += ft_putnbr_base(tmp_nbr / base, base);
	len += write(1, &hexa[tmp_nbr % base], 1);
	return (len); 
}

// #include <stdio.h>

// int	main(void)
// {
// 	int nbr = 42;
// 	char *str = "Hello world!";
// 	int hexa = 15;

// 	ft_printf("		This is ft_printf:\n");
// 	ft_printf("s: %s\n", str);
// 	ft_printf("d: %d\n", nbr);
// 	ft_printf("x: %x\n", hexa);
// 	write(1, "\n", 1);
// 	printf("	This is printf:\n");
// 	printf("s: %s\n", str);
// 	printf("d: %d\n", nbr);
// 	printf("x: %x\n", hexa);
// 	return (0);
// }
