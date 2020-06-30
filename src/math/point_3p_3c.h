#pragma once

#include <Math/Point3D>

namespace Ouquitoure
{
    namespace Math
    {

        template<typename T>
        union Point3Pos3Color
        {
            constexpr static int NUM_ELEMENTS    = Point3D<T>::NUM_ELEMENTS * 2;
            constexpr static int POSITION_OFFSET = 0;
            constexpr static int COLOR_OFFSET    = 3;

            struct PosColor
            {
                Point3D<T> pos;
                Point3D<T> color;

                PosColor() = default;
                PosColor( T x, T y, T z, T r, T g, T b )
                    : pos( x, y, z )
                    , color( r, g, b )
                {
                }
            };

            Point3Pos3Color() = default;
            Point3Pos3Color( T x, T y, T z, T r, T g, T b )
                : posColor( x, y, z, r, g, b )
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

            PosColor posColor;
            T        _data[ NUM_ELEMENTS ];
        };

    } // namespace Math

    using Point3p3c = Math::Point3Pos3Color<float>;

} // namespace Ouquitoure
