#include "bagel/bagel.h"

namespace bagel
{
Bagel::Bagel(int argc, const char *const *argv) {
  argparse::ArgumentParser parser("bagel");

  // Add duration subparser
  argparse::ArgumentParser duration_command("duration");
  duration_command.add_description("Prints duration of bag in seconds");
  duration_command.add_argument("bag")
    .help("Bagfile to process");
  parser.add_subparser(duration_command);

  try {
    parser.parse_args(argc, argv);
  }
  catch (const std::runtime_error& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << parser;
    std::exit(1);
  }

  if(parser.is_subcommand_used("duration")) {
    durationCommand(duration_command.get<std::string>("bag"));
  }

}

void Bagel::durationCommand(const std::string& bag_path) {
  rosbag::Bag bag(bag_path, rosbag::bagmode::Read);

  rosbag::View view(bag);

  ros::Time bag_start_time = view.getBeginTime();
  ros::Time bag_end_time = view.getEndTime();

  std::cout << (bag_end_time - bag_start_time).toSec() << std::endl;
}
} // namespace bagel
