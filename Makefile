all: 
	make debug

debug_generate:
	cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -S . -B build/debug 

debug: 
	make -C build/debug -j$(nproc)

release_generate:
	cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -S . -B build/release

release:
	make -C build/release -ji$(nproc)

reldeb_generate:
	cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo -S . -B build/relwdebug 

reldeb:
	make -C build/relwdebug -j$(nproc)

minsize_generate:
	cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=MinSizeRel -S . -B build/minsize 
minsize:
	make -C build/minsize -j$(nproc)

rundebug:
	./build/debug/src/sim-p/sim-p

runrelease:
	./build/release/src/sim-p/sim-p

