sudo apt install qemu-system-aarch64 -y
sudo apt install gcc-aarch64-linux-gnu -y
sudo apt install gdb-multiarch -y
mkdir build
mkdir build/auth
mkdir build/boot
mkdir build/crypto
mkdir build/debug
mkdir build/drivers
mkdir build/fs
mkdir build/lib
mkdir build/mm
mkdir build/monitor
mkdir build/ocom
rm -rf deltaV
git clone https://www.github.com/yuvraj1803/deltaV.git
cd deltaV
chmod +x install.sh
./install.sh
