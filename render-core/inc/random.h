#pragma once

#include <random>
#include <algorithm>

#include <export.h>

class RENDER_API rng
{
public:
    template <typename type>
    static inline type generate_random_number(const type min, const type max) { return generate_random_number_internal(min, max, std::is_integral<type>()); }

    template <typename T>
    static inline void shuffle_array(std::vector<T> &arr) { std::shuffle(arr.begin(), arr.end(), m_mt_generator); }

private:
    template <typename type>
    static inline type generate_random_number_internal(const type min, const type max, std::true_type)
    {
        auto distribution = std::uniform_int_distribution<type>(min, max);
        return distribution(m_mt_generator);
    }

    template <typename type>
    static inline type generate_random_number_internal(const type min, const type max, std::false_type)
    {
        auto distribution = std::uniform_real_distribution<type>(min, max);
        return distribution(m_mt_generator);
    }

private:
    static std::mt19937 m_mt_generator;
};
