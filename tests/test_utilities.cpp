// Copyright (C) 2026 Grigoriy Mikheyev. All rights reserved.
// Distributed under MIT license or project terms.

// NOLINTBEGIN

#include <string>
#include <vector>

#include "tests.hpp"
#include "utilities.hpp"

namespace {

std::optional<app::AppConfig> run_parse_cli(
    const std::vector<std::string>& args) noexcept {
  std::vector<const char*> argv;
  argv.reserve(args.size());
  for (const auto& arg : args) {
    argv.push_back(arg.c_str());
  }
  return app::parse_cli_args(static_cast<int>(argv.size()), argv.data());
}

}  // namespace

bool test_1() {
  auto res = run_parse_cli({"./app", "app.log"});
  ASSERT_TRUE(res.has_value());
  ASSERT_EQ(res->filepath, "app.log");
  ASSERT_EQ(res->min_level, logger::LogLevel::kDebug);

  return true;
}

bool test_2() {
  auto res_info = run_parse_cli({"./app", "app.log", "INFO"});
  ASSERT_TRUE(res_info.has_value());
  ASSERT_EQ(res_info->filepath, "app.log");
  ASSERT_EQ(res_info->min_level, logger::LogLevel::kInfo);

  auto res_error = run_parse_cli({"./app", "test.log", "ERROR"});
  ASSERT_TRUE(res_error.has_value());
  ASSERT_EQ(res_error->filepath, "test.log");
  ASSERT_EQ(res_error->min_level, logger::LogLevel::kError);

  auto res_warn = run_parse_cli({"./app", "test.log", "warning"});
  ASSERT_TRUE(res_warn.has_value());
  ASSERT_EQ(res_warn->filepath, "test.log");
  ASSERT_EQ(res_warn->min_level, logger::LogLevel::kWarning);

  auto res_dbg = run_parse_cli({"./app", "test.log", "Debug"});
  ASSERT_TRUE(res_dbg.has_value());
  ASSERT_EQ(res_dbg->filepath, "test.log");
  ASSERT_EQ(res_dbg->min_level, logger::LogLevel::kDebug);

  return true;
}

bool test_3() {
  auto res_no_args = run_parse_cli({"./app"});
  ASSERT_TRUE(!res_no_args.has_value());

  auto res_empty_path = run_parse_cli({"./app", ""});
  ASSERT_TRUE(!res_empty_path.has_value());

  auto res_invalid_level = run_parse_cli({"./app", "app.log", "INVALID_LEVEL"});
  ASSERT_TRUE(!res_invalid_level.has_value());

  auto res_too_many = run_parse_cli({"./app", "app.log", "INFO", "extra_arg"});
  ASSERT_TRUE(!res_too_many.has_value());

  return true;
}

bool test_4() {
  auto item1 = app::parse_input("[INFO] User logged in");
  ASSERT_EQ(item1.level, logger::LogLevel::kInfo);
  ASSERT_EQ(item1.message, "User logged in");

  auto item2 = app::parse_input("[ERROR] Connection failed");
  ASSERT_EQ(item2.level, logger::LogLevel::kError);
  ASSERT_EQ(item2.message, "Connection failed");

  return true;
}

bool test_5() {
  auto item1 = app::parse_input("[dEbUG] msg");
  ASSERT_EQ(item1.level, logger::LogLevel::kDebug);
  ASSERT_EQ(item1.message, "msg");

  auto item2 = app::parse_input("[wArNiNg] msg");
  ASSERT_EQ(item2.level, logger::LogLevel::kWarning);
  ASSERT_EQ(item2.message, "msg");

  return true;
}

bool test_6() {
  auto item = app::parse_input("   [INFO]   hello world");
  ASSERT_EQ(item.level, logger::LogLevel::kInfo);
  ASSERT_EQ(item.message, "hello world");

  return true;
}

bool test_7() {
  auto item1 = app::parse_input("Regular text message");
  ASSERT_EQ(item1.level, logger::LogLevel::kDebug);
  ASSERT_EQ(item1.message, "Regular text message");

  auto item2 =
      app::parse_input("Regular text message", logger::LogLevel::kWarning);
  ASSERT_EQ(item2.level, logger::LogLevel::kWarning);
  ASSERT_EQ(item2.message, "Regular text message");

  return true;
}

bool test_8() {
  auto item = app::parse_input("[CUSTOM] text");
  ASSERT_EQ(item.level, logger::LogLevel::kDebug);
  ASSERT_EQ(item.message, "[CUSTOM] text");

  return true;
}

bool test_9() {
  auto item_empty = app::parse_input("");
  ASSERT_TRUE(item_empty.message.empty());

  auto item_spaces = app::parse_input("   \t  ");
  ASSERT_TRUE(item_spaces.message.empty());

  return true;
}

bool test_10() {
  auto item1 = app::parse_input("[INFO message");
  ASSERT_EQ(item1.level, logger::LogLevel::kDebug);
  ASSERT_EQ(item1.message, "[INFO message");

  auto item2 = app::parse_input("INFO] message");
  ASSERT_EQ(item2.level, logger::LogLevel::kDebug);
  ASSERT_EQ(item2.message, "INFO] message");

  return true;
}

int main() {
  int passed = 0;
  int total = 0;

  std::cout << "Тесты utilities \n";
  std::cout << "==========================================\n";
  RUN_TEST(test_1);
  RUN_TEST(test_2);
  RUN_TEST(test_3);
  RUN_TEST(test_4);
  RUN_TEST(test_5);
  RUN_TEST(test_6);
  RUN_TEST(test_7);
  RUN_TEST(test_8);
  RUN_TEST(test_9);
  RUN_TEST(test_10);

  std::cout << "==========================================\n";
  std::cout << "Итого: " << passed << " из " << total << " тестов пройдено.\n";

  return (passed == total) ? 0 : 1;
}

// NOLINTEND