#include <iostream>
#include <argparse/argparse.hpp>
#include <rosbag/bag.h>
#include <rosbag/view.h>

int main(int argc, char *argv[]) {
  argparse::ArgumentParser parser("bagel");

  parser.add_argument("bag")
    .help("Bagfile to process");

  try {
    parser.parse_args(argc, argv);
  }
  catch (const std::runtime_error& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << parser;
    std::exit(1);
  }

  std::cout << parser.get<std::string>("bag") << std::endl;

  rosbag::Bag bag;

  const auto bag_path = parser.get<std::string>("bag");
  bag.open(bag_path, rosbag::bagmode::Read);

  rosbag::View view(bag);

  ros::Time bag_start_time = view.getBeginTime();
  ros::Time bag_end_time = view.getEndTime();

  std::cout << "ROS bag time: " << (bag_end_time - bag_start_time).toSec() << " (s)" << std::endl;
  bag.close();
  return 0;
}
