#pragma once

#define DISABLE_COPY(ClassName) \
    ClassName(const ClassName&) = delete; \
    ClassName& operator=(const ClassName&) = delete;

#define DISABLE_MOVE(ClassName) \
    ClassName(ClassName&&) = delete; \
    ClassName& operator=(ClassName&&) = delete;

#define DISABLE_COPY_AND_MOVE(ClassName) \
    DISABLE_COPY(ClassName) \
    DISABLE_MOVE(ClassName)
