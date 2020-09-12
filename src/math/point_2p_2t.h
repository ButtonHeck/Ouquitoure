#pragma once

#include "Math/Point2D"

namespace Ouquitoure::Math
{
    template<typename T>
    union Point2Pos2TexCoords
    {
        constexpr static int NUM_ELEMENTS     = Point2D<T>::NUM_ELEMENTS * 2;
        constexpr static int POSITION_OFFSET  = 0;
        constexpr static int TEXCOORDS_OFFSET = 2;

        struct PosTexCoords
        {
            Point2D<T> pos;
            Point2D<T> texCoords;

            PosTexCoords() = default;
            PosTexCoords( T x, T y, T s, T t )
                : pos( x, y )
                , texCoords( s, t )
            {
            }
        };

        Point2Pos2TexCoords() = default;
        Point2Pos2TexCoords( T x, T y, T s, T t )
            : posTexCoords( x, y, s, t )
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
    using Point2p2t = Math::Point2Pos2TexCoords<float>;
}
