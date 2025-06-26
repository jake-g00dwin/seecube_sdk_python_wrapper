#!/bin/sh
#Author: Jake G
#Date: 2024
#Filename: setup.sh

PKG_MNGR=""
DEBIAN=0
FBSD=0
SYSINSTALL=0
DEV_UTILS="vim tmux fzf git"
PY_VER="python3.10"

install_pkg () {
    PKG=$1
    ICMD=""
    if [ $DEBIAN -eq 1 ]; then
        ICMD="sudo apt install ${PKG}"
    elif [ $FBSD -eq 1 ]; then
        ICMD="sudo pkg install ${PKG}"
    fi

    $ICMD
}

install_dev_utils () {
    ICMD=""
    if [ $DEBIAN -eq 1 ]; then
        ICMD="sudo apt install"
    elif [ $FBSD -eq 1 ]; then
        ICMD="sudo pkg install"
    fi

    for util in $DEV_UTILS
    do
        ${ICMD} ${util}
    done
}


check_os () {
    echo "checking the OS..."
     if [ -f /etc/debian_version ]; then
         echo "debian detected"
        DEBIAN=1
    elif [ -f /etc/freebsd-update.conf ]; then
        echo "FreeBSD detected"
        FBSD=1
    fi  
}


remove_template_examples () {
    echo ""
}


install_needed_dependencies () {
    echo "Installing dependencies..."
    install_pkg "cmake"
    install_pkg "git"
    #install_pkg "clang"
    install_pkg "${PY_VER}"

    # Install python modules/libraries.
    echo "Upgrading python pip module..."
    $PY_VER -m pip -m pip install --upgrade pip
    echo "Installing Python Modules..."
    $PY_VER -m pip install pytest
    $PY_VER -m pip install opencv-python   
}


create_project_symlinks () {
    # Allows the clangd LSP to find it.
    ln -s ./build/compile_commands.json ./compile_commands.json
}


build_cpputest () {
    git submodule add https://github.com/cpputest/cpputest.git
    git sumodule status
    cd ./cpputest/build
    cmake ../
    
    if [ SYSINSTALL -eq 1 ]; then
        make install
    else
        make
    fi
}


# The default setup stuff.
default () {
    remove_template_examples
    install_needed_dependencies
    create_project_symlinks
}

setup() {
    echo "Setting up env"
    check_os
    #install_dev_utils
    install_needed_dependencies 
}

setup
