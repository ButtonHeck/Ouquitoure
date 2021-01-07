#pragma once

#include "Math/Point2D"
#include "Math/Point3D"

namespace Ouquitoure::Math
{
    template<typename T>
    union Point3Pos2TexCoords
    {
        constexpr static int NUM_ELEMENTS     = Point2D<T>::NUM_ELEMENTS + Point3D<T>::NUM_ELEMENTS;
        constexpr static int POSITION_OFFSET  = 0;
        constexpr static int TEXCOORDS_OFFSET = 3;

        struct PosTexCoords
        {
            Point3D<T> pos;
            Point2D<T> texCoords;

            PosTexCoords() = default;
            PosTexCoords( T x, T y, T z, T s, T t )
                : pos( x, y, z )
                , texCoords( s, t )
            {
            }
        };

        Point3Pos2TexCoords() = default;
        Point3Pos2TexCoords( T x, T y, T z, T s, T t )
            : posTexCoords( x, y, z, s, t )
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
            return posTexCoords.pos.x();
        }
        inline const T & x() const noexcept
        {
            return posTexCoords.pos.x();
        }

        // Y

        inline T & y() noexcept
        {
            return posTexCoords.pos.y();
        }
        inline const T & y() const noexcept
        {
            return posTexCoords.pos.y();
        }

        // Z

        inline T & z() noexcept
        {
            return posTexCoords.pos.z();
        }
        inline const T & z() const noexcept
        {
            return posTexCoords.pos.z();
        }

        // S

        inline T & s() noexcept
        {
            return posTexCoords.texCoords.s();
        }
        inline const T & s() const noexcept
        {
            return posTexCoords.texCoords.s();
        }

        // T
        inline T & t() noexcept
        {
            return posTexCoords.texCoords.s();
        }
        inline const T & t() const noexcept
        {
            return posTexCoords.texCoords.t();
        }

        PosTexCoords posTexCoords;
        T            _data[ NUM_ELEMENTS ];
    };
} // namespace Ouquitoure::Math

namespace Ouquitoure
{
    using Point3p2t = Math::Point3Pos2TexCoords<float>;
}
