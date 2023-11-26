#ifndef OPERATOR_HELPER
#define OPERATOR_HELPER

#include <functional>
#include <cmath>

using RFunction = std::function<float(float x, float y)>;

namespace euler
{
    static RFunction or_f(RFunction &&first, RFunction &&second)
    {
        return [first, second](float x, float y)
        {
            const float f = first(x, y);
            const float r = second(x, y);
            return f + r + std::sqrt(f*f + r*r);
        };
    }

    static RFunction and_f(RFunction &&first, RFunction &&second)
    {
        return [first, second](float x, float y)
        {
            const float f = first(x, y);
            const float r = second(x, y);
            return f + r - std::sqrt(f*f + r*r);
        };
    }
}

#endif //OPERATOR_HELPER
