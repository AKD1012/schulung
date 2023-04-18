.PHONY: all clean

all:
	$(MAKE) -C 01_vector 
	$(MAKE) -C 02_maps

clean:
	$(MAKE) -C 01_vector clean
	$(MAKE) -C 02_maps clean
