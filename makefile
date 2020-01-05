all: TransitSim tests

check-style:
	cd src; make check-style

check-style-cse:
	cd src; make check-style-cse

TransitSim:
	cd src; make -j

capture_transit_sim:
	cd src; make capture_transit_sim -j

vis_sim:
	cd src; make vis_sim -j

config_sim:
	cd src; make config_sim -j

tests:
	cd tests; make -j

clean:
	rm -rf build

clobber: clean
	cd ../external/googletest; make clean
