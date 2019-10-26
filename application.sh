#!/bin/bash

declare -A osInfo;
osInfo[/etc/debian_version]="sudo apt-get install "
#osInfo[/etc/alpine-release]="sudo apk"
#osInfo[/etc/centos-release]="sudo yum"
#osInfo[/etc/fedora-release]="sudo dnf"
osInfo[/etc/arch-release]="sudo pacman -S "

dependencies="check"
# check the Linux distro
for f in ${!osInfo[@]}
do
    if [[ -f ${f} ]]; then
        package_manager=${osInfo[$f]}
    fi
done

# install all dependencies if necessary
for command in ${dependencies}
do
    if ! type checkmk > /dev/null 2>&1; then
        eval "${package_manager} ${command}";
    fi
done


FILE_IN=${argc}[1]
FILE_OUT=${argc}[2]
test -d build || mkdir build
cd build
cmake -G"Unix Makefiles" ..
make
cd ../bin/
chmod u+x main
