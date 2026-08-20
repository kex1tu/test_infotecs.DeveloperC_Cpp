// Copyright (C) 2026 Grigoriy Mikheyev. All rights reserved.
// Distributed under MIT license or project terms.
#include "utilities.hpp"

#include <cstddef>
#include <iostream>

namespace app {

std::optional<AppConfig> parse_cli_args(int argc,
                                        const char* const* argv) noexcept {
  if (argv == nullptr) {
    return std::nullopt;
  }
  if (argc < 2 || argc > 3) {
    return std::nullopt;
  }
  for (int i = 0; i < argc; ++i) {
    if (argv[i] == nullptr) {
      return std::nullopt;
    }
  }

  AppConfig config;
  config.filepath = argv[1];
  if (config.filepath.empty()) {
    return std::nullopt;
  }

  if (argc == 3) {
    const auto parsed_level = logger::parse_log_level(argv[2]);
    if (!parsed_level) {
      return std::nullopt;
    }
    config.min_level = *parsed_level;
  }

  return config;
}

void print_usage(std::string_view program_name) noexcept {
  std::cout << "Usage:\n"
            << "  " << program_name
            << " <log_file> [level: DEBUG|INFO|WARNING|ERROR]\n";
}

LogItem parse_input(std::string_view input,
                    logger::LogLevel default_level) noexcept {
  const std::size_t start = input.find_first_not_of(" \t");
  if (start == std::string_view::npos) {
    return {default_level, ""};
  }
  input.remove_prefix(start);
  if (input.front() != '[') {
    return {default_level, std::string(input)};
  }
  const std::size_t close_bracket = input.find(']');
  if (close_bracket == std::string_view::npos) {
    return {default_level, std::string(input)};
  }
  const std::string_view level_str = input.substr(1, close_bracket - 1);
  const auto parsed_level = logger::parse_log_level(level_str);
  if (!parsed_level) {
    return {default_level, std::string(input)};
  }

  std::string_view msg = input.substr(close_bracket + 1);
  const std::size_t msg_start = msg.find_first_not_of(" \t");
  if (msg_start != std::string_view::npos) {
    msg.remove_prefix(msg_start);
  } else {
    msg = {};
  }

  return {*parsed_level, std::string(msg)};
}

}  // namespace app
