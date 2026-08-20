// Copyright (C) 2026 Grigoriy Mikheyev. All rights reserved.
// Distributed under MIT license or project terms.

#pragma once

#include <memory>
#include <string>
#include <utility>

#include "file_sink.hpp"
#include "log_level.hpp"
#include "logger.hpp"
#include "logger_error.hpp"

namespace logger {

/**
 * \brief создает и инициализирует логгер для записи в файл.
 *
 * Examples:
 * \code
 * auto [err, log] = logger::make_file_logger("app.log", LogLevel::kInfo);
 * if (err == LoggerError::kSuccess) {
 *   log->log_message(LogLevel::kInfo, "App started");
 * }
 * \endcode
 *
 * \param[in] filename путь к файлу лога.
 * \param[in] min_level минимальный уровень логирования.
 * \return пара, содержащая код ошибки и уникальный указатель на Logger.
 */
inline std::pair<LoggerError, std::unique_ptr<Logger>> make_file_logger(
    const std::string& filename,
    LogLevel min_level = LogLevel::kDebug) noexcept {
  try {
    auto sink = std::make_unique<FileSink>();
    const LoggerError err = sink->open(filename);
    if (err != LoggerError::kSuccess) {
      return {err, nullptr};
    }

    auto log = std::make_unique<Logger>(std::move(sink), min_level);
    return {LoggerError::kSuccess, std::move(log)};
  } catch (...) {
    return {LoggerError::kSinkError, nullptr};
  }
}

/**
 * \brief создает логгер с произвольной пользовательской реализацией ISink.
 *
 * \param[in] sink уникальный указатель на предварительно открытый ISink.
 * \param[in] min_level минимальный уровень логирования.
 * \return пара, содержащая код ошибки и уникальный указатель на Logger.
 */
inline std::pair<LoggerError, std::unique_ptr<Logger>> make_custom_logger(
    std::unique_ptr<ISink> sink,
    LogLevel min_level = LogLevel::kDebug) noexcept {
  try {
    if (!sink || !sink->is_open()) {
      return {LoggerError::kInvalidArgument, nullptr};
    }

    auto log = std::make_unique<Logger>(std::move(sink), min_level);
    return {LoggerError::kSuccess, std::move(log)};
  } catch (...) {
    return {LoggerError::kSinkError, nullptr};
  }
}

}  // namespace logger
