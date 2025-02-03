#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <sstream>

#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"   // support for loading levels from the environment variable
#include "spdlog/fmt/ostr.h"

#include "pugixml.hpp"

void sigHandle(int arg) {
  if ((arg == SIGTERM) || (arg == SIGINT)) {
    std::cout << "sig handle .. " << std::endl;
  }
   std::cout << "sig handle .. " << std::endl;
}

int main (int argc, char* argv[]) {
  pid_t pid;
  if (argc > 1) {
    if (daemon(0, 0) < 0) {
          perror("daemon");
          return 1;
      }
  }

  signal(SIGTERM,sigHandle);
  signal(SIGINT,sigHandle);
  signal(SIGKILL,sigHandle);
  unlink("/home/tan/workCode/third/OK/projectInogence/cplus/1.txt");

  FILE * f = fopen("2.txt", "r");
  fscanf(f, "%d", &pid);
  std::cout << "pid " << static_cast<int>(pid) << std::endl;

  std::stringstream ss;
  ss << "/proc/" << getpid();
  if (access(ss.str().c_str(), 0) == -1) {
    perror("access");
  }
  spdlog::info("This an info message with custom format");

  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_string("<node attr='value'><child>text<child></node>");
  if (result)
  {
      std::cout << "XML [" <<  "] parsed without errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n\n";
  }
  else
  {
      std::cout << "XML [" << "] parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
  }


  kill(getpid(),SIGHUP);
  while(1) {
    std::cout << "running ..." << std::endl;
    sleep (1);
  }
  return 0;
}