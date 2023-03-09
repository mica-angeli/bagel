#ifndef BAGEL_BAGEL_H
#define BAGEL_BAGEL_H

#include <string>
#include <iostream>
#include <argparse/argparse.hpp>
#include <rosbag/bag.h>
#include <rosbag/view.h>

namespace bagel {
class Bagel {
public:
  Bagel(int argc, const char *const *argv);

private:
  void durationCommand(const std::string& bag_path);
}; // class Bagel
} // namespace bagel

#endif
