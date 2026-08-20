// Copyright (C) 2026 Grigoriy Mikheyev. All rights reserved.
// Distributed under MIT license or project terms.

#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <string_view>

namespace logger {

/**
 * \brief уровни важности сообщений логирования.
 */
enum class [[nodiscard]] LogLevel : uint8_t {
  kDebug = 0,
  kInfo = 1,
  kWarning = 2,
  kError = 3,
  kUnknown = 4,  ///< неопределенный или неподдерживаемый уровень.
};

/**
 * \brief возвращает строковое представление уровня логирования.
 *
 * \param[in] level уровень логирования.
 * \return строковый литерал с названием уровня ("DEBUG", "INFO", "WARNING",
 * "ERROR", "UNKNOWN").
 */
[[nodiscard]] constexpr std::string_view log_level_to_string(
    LogLevel level) noexcept {
  switch (level) {
    case LogLevel::kDebug:
      return "DEBUG";
    case LogLevel::kInfo:
      return "INFO";
    case LogLevel::kWarning:
      return "WARNING";
    case LogLevel::kError:
      return "ERROR";
    default:
      return "UNKNOWN";
  }
}

namespace helpers {

constexpr char to_upper_ascii(char c) noexcept {
  return (c >= 'a' && c <= 'z') ? static_cast<char>(c - ('a' - 'A')) : c;
}

constexpr bool is_equal(std::string_view a, std::string_view b) noexcept {
  if (a.size() != b.size()) {
    return false;
  }
  for (std::size_t i = 0; i < a.size(); ++i) {
    if (to_upper_ascii(a[i]) != to_upper_ascii(b[i])) {
      return false;
    }
  }
  return true;
}

}  // namespace helpers

/**
 * \brief выполняет регистронезависимый разбор строки в уровень логирования.
 * \return std::optional с LogLevel при успешном разборе, или std::nullopt если
 * строка не распознана.
 */
[[nodiscard]] constexpr std::optional<LogLevel> parse_log_level(
    std::string_view str) noexcept {
  if (helpers::is_equal(str, "DEBUG")) {
    return LogLevel::kDebug;
  }
  if (helpers::is_equal(str, "INFO")) {
    return LogLevel::kInfo;
  }
  if (helpers::is_equal(str, "WARNING")) {
    return LogLevel::kWarning;
  }
  if (helpers::is_equal(str, "ERROR")) {
    return LogLevel::kError;
  }
  if (helpers::is_equal(str, "UNKNOWN")) {
    return LogLevel::kUnknown;
  }
  return std::nullopt;
}

}  // namespace logger