#pragma once

#include <Math/Point4D>
#include <Math/Point3D>

namespace Ouquitoure::Math
{
    template<typename T>
    union Point3Pos4Color
    {
        constexpr static int NUM_ELEMENTS    = Point3D<T>::NUM_ELEMENTS + Point4D<T>::NUM_ELEMENTS;
        constexpr static int POSITION_OFFSET = 0;
        constexpr static int COLOR_OFFSET    = 3;

        struct PosColor
        {
            Point3D<T> pos;
            Point4D<T> color;

            PosColor() = default;
            PosColor( T x, T y, T z, T r, T g, T b, T a )
                : pos( x, y, z )
                , color( r, g, b, a )
            {
            }
        };

        Point3Pos4Color() = default;
        Point3Pos4Color( T x, T y, T z, T r, T g, T b, T a )
            : posColor( x, y, z, r, g, b, a )
        {
        }

        // data buffer

        inline T * data()
        {
            return data;
        }
        inline const T * data() const
        {
            return data;
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

        // Z

        inline T & z() noexcept
        {
            return posColor.pos.z();
        }
        inline const T & z() const noexcept
        {
            return posColor.pos.z();
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
    using Point3p4c = Math::Point3Pos4Color<float>;
}
