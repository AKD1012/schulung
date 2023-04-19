.PHONY: all clean

all:
	$(MAKE) -C 01_vector 
	$(MAKE) -C 02_maps
	$(MAKE) -C 03_maps_advanced

clean:
	$(MAKE) -C 01_vector clean
	$(MAKE) -C 02_maps clean
	$(MAKE) -C 03_maps_advanced clean
