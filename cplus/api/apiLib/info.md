## 创建了build.sh  用于编译

编译dbus-cxx

  g++ quickstart_server_0.cpp  -I/usr/local/include/dbus-cxx-2.0 -I/usr/include/sigc++-3.0 -I/usr/lib/x86_64-linux-gnu/sigc++-3.0/include  -ldbus-cxx

  g++ quickstart_client_0.cpp  -I/usr/local/include/dbus-cxx-2.0  -I/usr/include/sigc++-3.0  -I/usr/lib/x86_64-linux-gnu/sigc++-3.0/include -ldbus-cxx
