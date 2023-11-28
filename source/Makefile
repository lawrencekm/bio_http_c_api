CROSS := /usr/bin/

ifneq ($(CROSS),)
CROSS_PREFIX := $(CROSS)
endif

CC = $(CROSS_PREFIX)gcc
CFLAGS = -c -g -Wall -DUNIX \
         -I ./ -I ./Inc \
         -I /usr/bin/
LDFLAGS = -L ./LM -Wl,-rpath -Wl,./
LDLIBS = -lf3bc4bio -lf3bc4com -lf3bc4bsp -lf3bc4cap -lf3bc4mat -lmongoose
IDENTIFY = BioAPI_sample_C_Identify
VERIFY = BioAPI_sample_C_Verify
BIOHTTPAPI = BioAPI_HTTP_API

all: $(BIOHTTPAPI) $(IDENTIFY) $(VERIFY)

$(BIOHTTPAPI): $(BIOHTTPAPI).o
	$(CC) -o $(BIOHTTPAPI) $(BIOHTTPAPI).o $(LDFLAGS) $(LDLIBS)
$(BIOHTTPAPI).o : $(BIOHTTPAPI).c
	$(CC) $(CFLAGS) $(BIOHTTPAPI).c

$(VERIFY): $(VERIFY).o
	$(CC) -o $(VERIFY) $(VERIFY).o $(LDFLAGS) $(LDLIBS)

$(VERIFY).o : $(VERIFY).c
	$(CC) $(CFLAGS) $(VERIFY).c

$(IDENTIFY): $(IDENTIFY).o
	$(CC) -o $(IDENTIFY) $(IDENTIFY).o $(LDFLAGS) $(LDLIBS)

$(IDENTIFY).o : $(IDENTIFY).c
	$(CC) $(CFLAGS) $(IDENTIFY).c



clean:
	$(RM) *~ *.o $(BIOHTTPAPI) $(IDENTIFY) $(VERIFY)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

