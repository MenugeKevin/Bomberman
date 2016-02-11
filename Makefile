#Project Name
TARGET=				Bomberman
TARGET_DEBUG=		$(addsuffix _debug, $(TARGET))

#Project Sources
SRCS=					$(shell ls $(SRCS_DIR)/)
SRCS_DIR=			source
SRCS_EXTENTION=	$(firstword $(suffix $(SRCS)))

#Project Object
OBJS=					$(addprefix $(OBJS_DIR)/, $(SRCS:$(SRCS_EXTENTION)=.o))
OBJS_DEBUG=			$(addprefix $(OBJS_DEBUG_DIR)/, $(SRCS:$(SRCS_EXTENTION)=.o))
OBJS_DIR=			object

#Include Directory
INCLUDES=			-I./$(INCLUDES_DIR) -I./LibBomberman_linux_x64/includes/

INCLUDES_DIR=		include

#GCC
ifeq ($(SRCS_EXTENTION), .c)
CC=					gcc
else ifeq ($(SRCS_EXTENTION), .cpp)
CC=					g++
else
$(error  $(SRCS_EXTENTION) unreconized file extention)
endif

LIB_DIR=	         LibBomberman_linux_x64/libs
#Flags
CFLAGS=				-W -Wall -Wextra
LDFLAGS=	         -L$(LIB_DIR) -Wl,-rpath,$(LIB_DIR) -Wl,--no-as-needed -lgdl_gl -lGL -lGLEW -lfbxsdk -lSDL2 -lpthread -ldl -lrt

.PHONY:				all clean fclean re

#all
all:		$(OBJS_DIR) $(TARGET)

debug:	$(OBJS_DEBUG_DIR) $(TARGET_DEBUG)

#Release Rules
$(OBJS_DIR):
	@mkdir $(OBJS_DIR)

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%$(SRCS_EXTENTION)
	$(CC) $(INCLUDES) -c $(CFLAGS) $< -o $@

$(TARGET):	$(OBJS)
	@$(CC) $^ -o $@ $(LDFLAGS)

#Release Clean Rules
clean:
	@rm -rf $(OBJS_DIR)

fclean:	clean
	@rm -f  $(TARGET)

re:		fclean all

# EOF #
