NAME = minirt.a
NAME_BONUS = minirt_bonus.a	
EXEC = miniRT
EXEC_BONUS = miniRT_bonus
HDRS = includes/mandatory/minirt.h
HDRS_BONUS = includes/bonus/minirt_bonus.h
OBJ = obj
OBJDIR = obj/mandatory
OBJDIR_BONUS = obj/bonus
SRCDIR = srcs/mandatory
SRCDIR_BONUS = srcs/bonus
HDRDIR = includes/mandatory
HDRDIR_BONUS = includes/bonus
FILEC =	main.c\
		ft_atof.c \
		Parsing/pars_obj.c \
		Parsing/pars2.c \
		Parsing/parsing.c \
		Parsing/pars.c \
		Raytracing/hit.c \
		Raytracing/intersection.c \
		Raytracing/intersection2.c \
		Raytracing/ray.c \
		Raytracing/render.c \
		Raytracing/shading.c \
		Raytracing/utils_ray.c \
		error.c \
		exit.c \
		free.c \
		init.c \
		utils_vec.c \
		utils.c 

FILEC_BONUS = main_bonus.c\
		ft_atof_bonus.c \
		Parsing/pars_obj_bonus.c \
		Parsing/pars2_bonus.c \
		Parsing/parsing_bonus.c \
		Parsing/pars_bonus.c \
		Raytracing/hit_bonus.c \
		Raytracing/hit2_bonus.c \
		Raytracing/damier.c \
		Raytracing/intersection_bonus.c \
		Raytracing/intersection2_bonus.c \
		Raytracing/ray_bonus.c \
		Raytracing/render_bonus.c \
		Raytracing/shading_bonus.c \
		Raytracing/utils_ray_bonus.c \
		Raytracing/phong.c \
		error_bonus.c \
		exit_bonus.c \
		free_bonus.c \
		init_bonus.c \
		utils_vec_bonus.c \
		utils_bonus.c \
		Parsing/pars_mode_bonus.c \
		Parsing/load_img_bonus.c \
		Parsing/load_img2_bonus.c \
		Parsing/load_img3_bonus.c \
		Raytracing/texture_bonus.c \
		Raytracing/texture2_bonus.c
		
OBJS = $(patsubst %.c, $(OBJDIR)/%.o, $(FILEC))
OBJS_BONUS = $(patsubst %.c, $(OBJDIR_BONUS)/%.o, $(FILEC_BONUS))
SRCS = $(addprefix	$(SRCDIR),	$(FILEC))
SRCS_BONUS = $(addprefix	$(SRCDIR_BONUS),	$(FILEC_BONUS))
LDIR = libft
LIBR = $(LDIR)/libft.a
MDIR = mlx_linux
MNAME = libmlx_Linux.a
MLIB = $(MDIR)/$(MNAME)
FLAGS = -Wall -Werror -Wextra -g
FLAGM = -L$(MDIR) -l:$(MNAME) -I$(MDIR) -lXext -lX11 -lm -lz
CC = cc
AR = ar -rcs
MAKEFLAGS += --no-print-directory

all:		init_dirs	$(NAME)	$(EXEC)

bonus:		init_dirs_bonus	$(NAME_BONUS)	$(EXEC_BONUS)

$(NAME):	$(OBJS)	$(LIBR) $(MLIB)	$(HDRS)
			@$(AR) $(NAME) $(OBJS)	

$(NAME_BONUS):	$(OBJS_BONUS)	$(LIBR) $(MLIB)	$(HDRS_BONUS)
			@$(AR) $(NAME_BONUS) $(OBJS_BONUS)	

# Compilation des fichiers .o dans obj/
$(OBJDIR_BONUS)/%.o: $(SRCDIR_BONUS)/%.c | $(OBJDIR_BONUS)
	@$(CC) $(FLAGS) -I$(HDRDIR_BONUS) -I$(LDIR) -I$(MDIR) -O3 -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) $(FLAGS) -I$(HDRDIR) -I$(LDIR) -I$(MDIR) -O3 -c $< -o $@
# Création du dossier obj/ si nécessaire
init_dirs:
				@mkdir -p $(OBJ)
				@mkdir -p $(OBJDIR)
				@mkdir -p $(OBJDIR)/Parsing
				@mkdir -p $(OBJDIR)/Raytracing

init_dirs_bonus:
				@mkdir -p $(OBJ)
				@mkdir -p $(OBJDIR_BONUS)
				@mkdir -p $(OBJDIR_BONUS)/Parsing
				@mkdir -p $(OBJDIR_BONUS)/Raytracing		
			
$(LIBR):		
				@[ -d $(LDIR) ] && $(MAKE) -C $(LDIR) all
				@echo "Libft compiled."

$(MLIB):
				@[ -d $(MDIR) ] && $(MAKE) -C $(MDIR) all
				@echo "mlx library compiled."

$(EXEC):		$(OBJS) $(LIBR) $(MLIB) $(HDRS)
				@$(CC) $(FLAGS) $(OBJS) $(MLIB) $(LIBR) -I$(HDRDIR) -o $(EXEC) $(FLAGM)
				@echo "Mandatory compilation completed, exec $(EXEC) ready."

$(EXEC_BONUS):	$(OBJS_BONUS) $(LIBR) $(MLIB) $(HDRS_BONUS)
				@$(CC) $(FLAGS) $(OBJS_BONUS) $(MLIB) $(LIBR) -I$(HDRDIR_BONUS) -o $(EXEC_BONUS) $(FLAGM)
				@echo "Bonus compilation completed, exec $(EXEC_BONUS) ready."

clean:		
			@rm -rf	$(OBJS)
			@rm -rf $(OBJDIR)
			@rm -rf	$(OBJS_BONUS)
			@rm -rf $(OBJDIR_BONUS)
			@$(MAKE) -C $(LDIR) clean
			@echo "Make clean command (mandatory + bonus) executed."

fclean:		clean
			@$(MAKE) -C $(LDIR) fclean
			@rm -rf $(NAME) $(EXEC)	
			@rm -rf $(NAME_BONUS) $(EXEC_BONUS)	
			@echo "Make fclean command (mandatory + bonus) executed."

re:			fclean all

re_bonus:	fclean bonus

.PHONY:		all clean fclean re
