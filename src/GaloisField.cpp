#include "GaloisField.h"
#include <iostream>

GaloisField::GaloisField(const std::string_view& element)
{
    if(element.size() > GaloisField::fieldDimension)
    {
        std::cout << "The available length is exceeded!" << std::endl;
    }

    for(std::size_t i = 0; i < element.size(); ++i)
    {
        m_data[element.size() - i - 1] = (element[i] == '1');
    }
}

GaloisField::GaloisField(const FieldElement& bits) : m_data(bits)
{
    // 
}

GaloisField GaloisField::operator+(const GaloisField& rhs) const
{
    return m_data ^ rhs.m_data;
}

GaloisField GaloisField::operator*(const GaloisField& rhs) const
{
    std::bitset<GaloisField::extendedDimension> result;

    std::bitset<GaloisField::extendedDimension> leftPoly = extendElementDimension(m_data);
    std::bitset<GaloisField::extendedDimension> rightPoly = extendElementDimension(rhs.m_data);

    int64_t shift = 0;
    while (shift < GaloisField::extendedDimension)
    {
        if (rightPoly.test(shift))
        {
            result ^= (leftPoly << shift);
        }
        shift++;
    }

    auto modResult = module(result);

    return reduceElementDimension(modResult);
}

GaloisField GaloisField::power(const GaloisField& degree) const
{
    GaloisField result("1");

    std::int64_t i = GaloisField::fieldDimension - 1;
    for(std::int64_t i = GaloisField::fieldDimension - 1; i >= 0; --i)
    {
        result = degree.m_data[i] ? (result * *this) : result;
        if(i != 0)
            result = square(result);
    }

    return result;
}

GaloisField GaloisField::square(const GaloisField &element)
{
    std::bitset<GaloisField::extendedDimension> result;

    for (std::size_t i = 0; i < GaloisField::fieldDimension; ++i) 
    {
        if (element.m_data.test(i)) {
            result.set(i * 2);
        }
    }

    auto modResult = element.module(result);
    return element.reduceElementDimension(modResult);
}

GaloisField GaloisField::trace(const GaloisField& element)
{
    auto result = element;
    auto currentSquare = element;
    std::size_t i = 1;
    
    do
    {
        currentSquare = square(currentSquare);
        result.m_data ^= currentSquare.m_data;
        i++;
    } while (i < GaloisField::fieldDimension);

    return result;
}

GaloisField GaloisField::inverse(const GaloisField& element)
{
    GaloisField result("1");
    std::size_t i = 1;

    while (i < GaloisField::fieldDimension)
    {
        result = result * element;
        result = element.square(result);
        ++i;
    }

    return result;
}

std::bitset<GaloisField::extendedDimension> GaloisField::module(const std::bitset<GaloisField::extendedDimension>& element) const
{
    std::bitset<GaloisField::extendedDimension> fieldGenerator = std::bitset<GaloisField::extendedDimension>(1)         |
                                                                 (std::bitset<GaloisField::extendedDimension>(1) << 1)  |
                                                                 (std::bitset<GaloisField::extendedDimension>(1) << 6)  |
                                                                 (std::bitset<extendedDimension>(1) << 11)              |
                                                                 (std::bitset<extendedDimension>(1) << GaloisField::fieldDimension);

    std::bitset<GaloisField::extendedDimension> result(element);
    for (std::size_t i = GaloisField::extendedDimension - 1; i >= GaloisField::fieldDimension; --i) 
    {
        if (result.test(i))
            result ^= fieldGenerator << (i - GaloisField::fieldDimension);
    }

    return result;
}

std::bitset<GaloisField::extendedDimension> GaloisField::extendElementDimension(const std::bitset<GaloisField::fieldDimension>& element) const
{
    return std::bitset<GaloisField::extendedDimension>(element.to_string());
}

std::bitset<GaloisField::fieldDimension> GaloisField::reduceElementDimension(const std::bitset<GaloisField::extendedDimension> &element) const
{
    return std::bitset<GaloisField::fieldDimension>(element.to_string().substr(GaloisField::fieldDimension));
}

std::ostream& operator<<(std::ostream& out, const GaloisField& rhs)
{
    const auto bits = rhs.m_data.to_string();
    const auto firstDigit = bits.find('1');

    if(firstDigit != std::string::npos)
    {
        out << bits.substr(firstDigit);
        return out;
    }

    out << "0";
    return out;
}
