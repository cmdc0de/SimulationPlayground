all: 
	make debug

debug:
	#generate make files
	cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -S . -B build/debug 
	make -C build/debug -j4

release:
	cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -S . -B build/release
	make -C build/release -j4

reldeb:
	cmake -G "Unix Makefiles" -S . -B build/relwdebug -DCMAKE_BUILD_TYPE=RelWithDebInfo
	make -C build/relwdebug -j4

minsize:
	cmake -G "Unix Makefiles" -S . -B build/minsize -DCMAKE_BUILD_TYPE=MinSizeRel
	make -C build/minsize -j4

rundebug:
	./build/debug/src/sim-p/sim-p

runrelease:
	./build/release/src/sim-p/sim-p

