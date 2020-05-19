DIR_FONTS = ./obj/oled/Fonts
DIR_OLED = ./obj/oled
DIR_SENSE = ./obj/sense
DIR_OBJ = ./obj
DIR_BIN = ./bin
DIR_TARGET = ../

OBJ_C = $(wildcard ${DIR_SENSE}/*.c ${DIR_OLED}/*.c ${DIR_FONTS}/*.c ${DIR_OBJ}/*.c)
OBJ_O = $(patsubst %.c,${DIR_BIN}/%.o,$(notdir ${OBJ_C}))

TARGET = ../obcyastronom
#BIN_TARGET = ${DIR_BIN}/${TARGET}

CC = gcc

DEBUG = -g -O0 -Wall
CFLAGS += $(DEBUG)

USELIB = USE_WIRINGPI_LIB
# USELIB = USE_WIRINGPI_LIB
# USELIB = USE_DEV_LIB
DEBUG = -D $(USELIB)
ifeq ($(USELIB), USE_BCM2835_LIB)
    LIB = -lbcm2835 -lm 
else ifeq ($(USELIB), USE_WIRINGPI_LIB)
    LIB = -lwiringPi -lm -lpthread
else 
    LIB = -lm 
endif

${DIR_BIN}/%.o : $(DIR_SENSE)/%.c
	$(CC) $(CFLAGS) -c  $< -o $@ $(LIB)

${DIR_BIN}/%.o:$(DIR_OLED)/%.c
	$(CC) $(CFLAGS) -c  $< -o $@ $(LIB)
	
${DIR_BIN}/%.o:$(DIR_FONTS)/%.c
	$(CC) $(CFLAGS) -c  $< -o $@ 	
	
${TARGET}:${OBJ_O}
	$(CC) $(CFLAGS) $(OBJ_O) -o ./$@ $(LIB)

${DIR_BIN}/%.o : $(DIR_OBJ)/%.c
	$(CC) $(CFLAGS) -c  $< -o $@ $(LIB)


clean :
	$(RM) $(DIR_BIN)/*.*
