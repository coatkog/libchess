#include "libchess/internal/log.h"

#include "spdlog/async.h"
#include "spdlog/common.h"
#include "spdlog/details/fmt_helper.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

#include <iostream>
#include <memory>

namespace libchess {

std::unique_ptr<Log> Log::m_instance;
std::once_flag Log::m_init_flag;

Log::Log() {
    spdlog::init_thread_pool(kThreadPoolQueueSize, 1);

    auto formatter = std::make_unique<spdlog::pattern_formatter>();
    formatter->add_flag<LogLevelFormatter>('|').set_pattern("[%Y-%m-%d %H:%M:%S.%F] [%^%|%$] %v");

    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    sinks.back()->set_formatter(std::move(formatter));

    m_logger = std::make_shared<spdlog::async_logger>("libchess",
                                                      sinks.begin(),
                                                      sinks.end(),
                                                      spdlog::thread_pool(),
                                                      spdlog::async_overflow_policy::block);
    spdlog::register_logger(m_logger);

    m_logger->set_level(kDefaultLogLevel);
    m_logger->flush_on(kDefaultLogLevel);
}

Log::~Log() {
    spdlog::shutdown();
}

const std::unique_ptr<Log> &Log::instance() {
    std::call_once(m_init_flag, []() {
        m_instance = std::make_unique<Log>();
    });
    return Log::m_instance;
}

const std::array<spdlog::string_view_t, 7> LogLevelFormatter::kLogLevelNames = {
    spdlog::string_view_t("trace", 5), spdlog::string_view_t("debug", 5),
    spdlog::string_view_t("info ", 5), spdlog::string_view_t("warn ", 5),
    spdlog::string_view_t("error", 5), spdlog::string_view_t("crit ", 5),
    spdlog::string_view_t("off  ", 5),
};

void LogLevelFormatter::format(const spdlog::details::log_msg &msg,
                               const std::tm & /*tm_time*/,
                               spdlog::memory_buf_t &dest) {
    spdlog::details::fmt_helper::append_string_view(kLogLevelNames[msg.level], dest);
}

std::unique_ptr<spdlog::custom_flag_formatter> LogLevelFormatter::clone() const {
    return spdlog::details::make_unique<LogLevelFormatter>();
}

}
