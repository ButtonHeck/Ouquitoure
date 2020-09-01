#pragma once

#include "Math/Point2D"
#include "Math/Point4D"

namespace Ouquitoure::Math
{
    template<typename T>
    union Point2Pos4Color
    {
        constexpr static int NUM_ELEMENTS    = Point2D<T>::NUM_ELEMENTS + Point4D<T>::NUM_ELEMENTS;
        constexpr static int POSITION_OFFSET = 0;
        constexpr static int COLOR_OFFSET    = 2;

        struct PosColor
        {
            Point2D<T> pos;
            Point4D<T> color;

            PosColor() = default;
            PosColor( T x, T y, T r, T g, T b, T a )
                : pos( x, y )
                , color( r, g, b, a )
            {
            }
        };

        Point2Pos4Color() = default;
        Point2Pos4Color( T x, T y, T r, T g, T b, T a )
            : posColor( x, y, r, g, b, a )
        {
        }

        // data buffer

        inline T * data()
        {
            return _data;
        }
        inline const T * data() const
        {
            return _data;
        }

        // X

        inline T & x() noexcept
        {
            return posColor.pos.x();
        }
        inline const T & x() const noexcept
        {
            return posColor.pos.x();
        }

        // Y

        inline T & y() noexcept
        {
            return posColor.pos.y();
        }
        inline const T & y() const noexcept
        {
            return posColor.pos.y();
        }

        // Red

        inline T & r() noexcept
        {
            return posColor.color.r();
        }
        inline const T & r() const noexcept
        {
            return posColor.color.r();
        }

        // Green

        inline T & g() noexcept
        {
            return posColor.color.g();
        }
        inline const T & g() const noexcept
        {
            return posColor.color.g();
        }

        // Blue

        inline T & b() noexcept
        {
            return posColor.color.b();
        }
        inline const T & b() const noexcept
        {
            return posColor.color.b();
        }

        // Alpha

        inline T & a() noexcept
        {
            return posColor.color.a();
        }
        inline const T & a() const noexcept
        {
            return posColor.color.a();
        }

        PosColor posColor;
        T        _data[ NUM_ELEMENTS ];
    };

} // namespace Ouquitoure::Math

namespace Ouquitoure
{
    using Point2p4c = Math::Point2Pos4Color<float>;
}
