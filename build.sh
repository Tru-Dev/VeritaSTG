
./get_deps.sh

if [ ! -d build ]; then mkdir build; fi

cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-linux -GNinja

cmake --build .
