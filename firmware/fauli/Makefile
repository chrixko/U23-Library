# Target file name.
TARGET = fauli

# List C source files here.
CCSOURCES = Game.c bilder.c Entity.c Player.c Animation.c Vector.c Camera.c Weapon.c Bullet.c Ui.c Healthbar.c Storyboard.c Scene.c LabScene.c Fonts.c 

# Additional local static libs to link against
LIBS = gaming stm32f4xx fatfs sdcard graphics

# Folder for object files
OBJDIR = obj

# Folder for sourcecode
SRCDIR = src

# Additional defines
DEFINES := -DRGB8Pixels

-include $(ROOT)/build/firmware.mak
