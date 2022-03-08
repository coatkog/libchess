#pragma once

#include "libchess/internal/macros.h"

#include "spdlog/async_logger.h"
#include "spdlog/common.h"
#include "spdlog/pattern_formatter.h"
#include "spdlog/spdlog.h"

namespace libchess {

class Log {
  public:
    Log();

    DISABLE_COPY_AND_MOVE(Log);

    ~Log();

    static const std::unique_ptr<Log> &instance();

    // TODO: Fix formatting (looks like in inherits it from spdlog)
    template<typename... Args>
    void trace(Args &&...args) const {
        m_logger->trace(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void debug(Args &&...args) const {
        m_logger->debug(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void info(Args &&...args) const {
        m_logger->info(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void warn(Args &&...args) const {
        m_logger->warn(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void error(Args &&...args) const {
        m_logger->error(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void critical(Args &&...args) const {
        m_logger->critical(std::forward<Args>(args)...);
    }

  private:
    static constexpr spdlog::level::level_enum kDefaultLogLevel = spdlog::level::trace;
    static constexpr std::size_t kThreadPoolQueueSize = 8192;

    static std::unique_ptr<Log> m_instance;
    static std::once_flag m_init_flag;

    std::shared_ptr<spdlog::async_logger> m_logger;
};

template<typename... Args>
constexpr void trace(Args &&...args) {
    Log::instance()->trace(std::forward<Args>(args)...);
}

template<typename... Args>
constexpr void debug(Args &&...args) {
    Log::instance()->debug(std::forward<Args>(args)...);
}

template<typename... Args>
constexpr void info(Args &&...args) {
    Log::instance()->info(std::forward<Args>(args)...);
}

template<typename... Args>
constexpr void warn(Args &&...args) {
    Log::instance()->warn(std::forward<Args>(args)...);
}

template<typename... Args>
constexpr void error(Args &&...args) {
    Log::instance()->error(std::forward<Args>(args)...);
}

template<typename... Args>
constexpr void crit(Args &&...args) {
    Log::instance()->critical(std::forward<Args>(args)...);
}

class LogLevelFormatter : public spdlog::custom_flag_formatter {
  public:
    void format(const spdlog::details::log_msg &msg,
                const std::tm &tm_time,
                spdlog::memory_buf_t &dest) override;

    std::unique_ptr<spdlog::custom_flag_formatter> clone() const override;

  private:
    static const std::array<spdlog::string_view_t, 7> kLogLevelNames;
};

} // namespace libchess
