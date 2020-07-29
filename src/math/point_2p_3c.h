#pragma once

#include "Math/Point2D"
#include "Math/Point3D"

#include <QVector2D>
#include <QVector3D>

namespace Ouquitoure
{
    namespace Math
    {

        template<typename T>
        /**
         * @brief vertex union with 2 position and 3 color components
         */
        union Point2Pos3Color
        {
            constexpr static int NUM_ELEMENTS    = Point2D<T>::NUM_ELEMENTS + Point3D<T>::NUM_ELEMENTS;
            constexpr static int POSITION_OFFSET = 0;
            constexpr static int COLOR_OFFSET    = 2;

            struct PosColor
            {
                Point2D<T> pos;
                Point3D<T> color;

                PosColor() = default;
                PosColor( T x, T y, T r, T g, T b )
                    : pos( x, y )
                    , color( r, g, b )
                {
                }
            };

            Point2Pos3Color() = default;
            Point2Pos3Color( T x, T y, T r, T g, T b )
                : posColor( x, y, r, g, b )
            {
            }
            Point2Pos3Color( QVector2D && position, QVector3D && color )
                : posColor( position.x(), position.y(), color.x(), color.y(), color.z() )
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

            PosColor posColor;
            T        _data[ NUM_ELEMENTS ];
        };

    } // namespace Math

    using Point2p3c = Math::Point2Pos3Color<float>;

} // namespace Ouquitoure
