comp	:=	c++ -std=c++98 -Wall -Werror -Wextra

src	:=	test.cc
name	:=	a.out
all	:	$(name)

$(name)	:	$(src)
		@ $(comp) $^ -o $@
		@ ./$(name)
		@ make f

f	:
		rm -rf $(name)

run	:	re
re	:	f all
