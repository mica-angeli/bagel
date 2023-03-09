#include "bagel/bagel.h"

namespace bagel
{

static std::string humanSize(uint64_t bytes)
{
	const std::vector<std::string> suffixes = {"B", "KB", "MB", "GB", "TB"};

  int i = 0;
  double dbl_bytes = bytes;
  
  if(bytes > 1024) {
    while((bytes / 1024) > 0 and i < suffixes.size() - 1) {
      dbl_bytes = bytes / 1024.0;
      i++;
      bytes /= 1024;
    }
  }

  std::stringstream ss;
  ss << std::fixed << std::setprecision(2) << dbl_bytes << " " << suffixes[i];
  return ss.str();
}

Bagel::Bagel(int argc, const char *const *argv) {
  argparse::ArgumentParser parser("bagel");

  // Add duration subparser
  argparse::ArgumentParser info_command("info");
  info_command.add_description("Prints bag info");
  info_command.add_argument("bag")
    .help("Bagfile to process");
  parser.add_subparser(info_command);

  // Add play subparser
  argparse::ArgumentParser play_command("play");
  play_command.add_description("Plays back bag");
  play_command.add_argument("bag")
    .help("Bagfile to play");
  parser.add_subparser(play_command);

  try {
    parser.parse_args(argc, argv);
  }
  catch (const std::runtime_error& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << parser;
    std::exit(1);
  }

  if(parser.is_subcommand_used("info")) {
    infoCommand(info_command.get<std::string>("bag"));
  } else if(parser.is_subcommand_used("play")) {
    playCommand(play_command.get<std::string>("bag"));
  }

}

void Bagel::infoCommand(const std::string& bag_path) {
  rosbag::Bag bag(bag_path, rosbag::bagmode::Read);
  rosbag::View view(bag);

  const double version = static_cast<double>(bag.getMajorVersion()) + static_cast<double>(bag.getMinorVersion()) * 0.1;
  const double duration = (view.getEndTime() - view.getBeginTime()).toSec();
  const uint64_t size = bag.getSize();

  std::cout << std::fixed << std::setprecision(1) << "version:  " << version << std::endl;
  std::cout << std::fixed << std::setprecision(2) << "duration: " << duration << std::endl;
  std::cout << "size:     " << humanSize(size) << std::endl;
}

void Bagel::playCommand(const std::string& bag_path) {
  rosbag::PlayerOptions options;
  options.bags.push_back(bag_path);

  ros::init(ros::VP_string(), "bagel", ros::init_options::AnonymousName);
  rosbag::Player player(options);

  try {
    player.publish();
  } catch (const std::runtime_error& err) {
    std::cerr << err.what() << std::endl;
    std::exit(1);
  }
}

} // namespace bagel
