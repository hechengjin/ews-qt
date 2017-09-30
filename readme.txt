mkdir build
cd build
CMAKE_PREFIX_PATH=xxxx/KDSoap/build/KDSoap cmake ..
make
KDSoapClient/KDSoapValue.h: 没有那个文件或目录
修改CMakeLists.txt文件增加KDSoap的头文件路径即可(通过include_directories添加)
编译完成后会生成 libews-qt5.so.0.0.0 文件