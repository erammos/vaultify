
#wget https://apt.llvm.org/llvm.sh
#chmod +x llvm.sh
#sudo ./llvm.sh 18 all
#sudo rm llvm.sh
#sudo ln -sf $(which clang-18) /usr/bin/clang
#sudo ln -sf $(which clangd-18) /usr/bin/clangd
#sudo ln -sf $(which clang++-18) /usr/bin/clang++

export CC=clang
export CXX=clang++
