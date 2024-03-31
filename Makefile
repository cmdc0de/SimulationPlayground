all: 
	make debug

debug:
	#generate make files
	cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -S . -B build/debug 
	make -C build/debug -j$(nproc)

release:
	cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -S . -B build/release
	make -C build/release -ji$(nproc)

reldeb:
	cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo -S . -B build/relwdebug 
	make -C build/relwdebug -j$(nproc)

minsize:
	cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=MinSizeRel -S . -B build/minsize 
	make -C build/minsize -j4

rundebug:
	./build/debug/src/sim-p/sim-p

runrelease:
	./build/release/src/sim-p/sim-p

