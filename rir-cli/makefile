NAME=rir

CC=clang
CSTD=c23
LDFLAGS=./../rir-backend/rir-backend.a ./../third-party/STC/build/Linux_gcc/libstc.a

include ./../mk/make-exe.mk

$(NAME): ../rir-backend/librir-backend.a

../rir-backend/librir-backend.a:
	make -C ../rir-backend