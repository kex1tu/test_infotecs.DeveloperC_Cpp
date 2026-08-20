// Copyright (C) 2026 Grigoriy Mikheyev. All rights reserved.
// Distributed under MIT license or project terms.

#pragma once

#include <optional>
#include <string>
#include <string_view>

#include "log_level.hpp"

namespace app {

/**
 * \brief конфигурация параметров запуска клиентского приложения.
 */
struct AppConfig {
  std::string filepath;
  logger::LogLevel min_level = logger::LogLevel::kDebug;
};

/**
 * \brief разбирает аргументы командной строки и формирует конфигурацию.
 *
 * поддерживаемый формат аргументов:
 * - <log_file> [min_level]
 *
 * \param[in] argc количество аргументов командной строки.
 * \param[in] argv массив указателей на строки аргументов.
 * \return std::optional со структурой AppConfig при корректных параметрах,
 *         или std::nullopt при ошибке синтаксиса или невалидных значениях.
 * \pre argv != nullptr
 */
std::optional<AppConfig> parse_cli_args(int argc,
                                        const char* const* argv) noexcept;

void print_usage(std::string_view program_name) noexcept;

/**
 * \brief разобранный элемент пользовательского ввода из консоли.
 */
struct LogItem {
  logger::LogLevel level;
  std::string message;
};

/**
 * \brief разбирает строку ввода, извлекая опциональный тег [LEVEL] и текст.
 *
 * если строка начинается с тега вида "[INFO] message", уровень извлекается
 * из тега, а остаток строки становится сообщением. в противном случае
 * используется default_level.
 */
LogItem parse_input(
    std::string_view input,
    logger::LogLevel default_level = logger::LogLevel::kDebug) noexcept;

}  // namespace app