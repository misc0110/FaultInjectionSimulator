VICTIMSRCS = $(wildcard demos/victim*.c)
VICTIMPROGS = $(patsubst %.c,%,$(VICTIMSRCS))

all: simulator $(VICTIMPROGS)

simulator: simulator.c
	gcc simulator.c -o simulator


%: %.c
	$(CC) $(CFLAGS) -I./ -static -o $@ $<

clean:
	rm -f simulator $(VICTIMPROGS)
