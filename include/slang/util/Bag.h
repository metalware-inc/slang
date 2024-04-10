//------------------------------------------------------------------------------
//! @file Bag.h
//! @brief General container of arbitrary objects, keyed by type
//
// SPDX-FileCopyrightText: Michael Popoloski
// SPDX-License-Identifier: MIT
//------------------------------------------------------------------------------
#pragma once

#include <any>
#include <unordered_map>
#include <string>

namespace slang {

/// Bag - A general container of arbitrary objects.
///
/// The Bag container is a collection of various type-erased objects that can
/// be looked up by their original type. This is useful for things like passing
/// around a collection of various options to different subsystems without needing
/// to have cross dependencies between them.
class SLANG_EXPORT Bag {
public:
    Bag() = default;

    template<typename... Args>
    Bag(Args&&... items) {
        (..., set(std::forward<Args>(items)));
    }

    template<typename T>
    void set(const T& item) {
        items[typeKey<T>()] = item;
    }

    template<typename T>
    void set(T&& item) {
        items[typeKey<T>()] = std::forward<T>(item);
    }

    template<typename T>
    const T* get() const {
        auto it = items.find(typeKey<T>());
        if (it == items.end())
            return nullptr;
        return std::any_cast<T>(&it->second);
    }

    template<typename T>
    T& insertOrGet() {
        auto& item = items[typeKey<T>()];
        if (!item.has_value())
            item.template emplace<T>();
        return *std::any_cast<T>(&item);
    }

    template<typename T>
    T getOrDefault() const {
        const T* result = get<T>();
        if (result)
            return *result;
        return T();
    }

private:
    std::unordered_map<std::string, std::any> items;

    template<typename T>
    std::string typeKey() const {
        return typeid(T).name(); // or another unique string for each type
    }
};

} // namespace slang

