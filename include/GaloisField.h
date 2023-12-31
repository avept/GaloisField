#pragma once

#include <bitset>
#include <string_view>
#include <string>

class GaloisField
{
    // magic constants
    inline static constexpr int64_t fieldDimension = 293;
    inline static constexpr int64_t extendedDimension = fieldDimension * 2;
    using FieldElement = std::bitset<fieldDimension>;

public:
    GaloisField() = default;
    GaloisField(const std::string_view& element);
    GaloisField(const FieldElement& bits);

    GaloisField operator+(const GaloisField& rhs) const;
    GaloisField operator*(const GaloisField& rhs) const;
    GaloisField& operator =(const GaloisField& rhs) = default;

    GaloisField power(const GaloisField& degree) const;

    static GaloisField square(const GaloisField& element);
    static GaloisField trace(const GaloisField& element);
    static GaloisField inverse(const GaloisField& element);

    friend std::ostream& operator <<(std::ostream& out, const GaloisField& rhs);

private:
    // functions
    std::bitset<extendedDimension> module(const std::bitset<extendedDimension>& element) const;
    std::bitset<extendedDimension> extendElementDimension(const std::bitset<fieldDimension>& element) const; // expand to 293 * 2
    std::bitset<fieldDimension> reduceElementDimension(const std::bitset<extendedDimension>& element) const; // reduce backward to 293

    // members
    FieldElement m_data;
};