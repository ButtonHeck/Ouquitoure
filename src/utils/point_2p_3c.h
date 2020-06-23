#pragma once

#include <QVector2D>
#include <QVector3D>

namespace Ouquitoure
{
    namespace Utils
    {
        union Point2Pos3Color
        {
            constexpr static int POSITION_OFFSET = 0;
            constexpr static int COLOR_OFFSET    = 2;

            struct PosColor
            {
                // position
                float x;
                float y;
                // color
                float r;
                float g;
                float b;

                PosColor() = default;
                PosColor( float x, float y, float r, float g, float b )
                    : x( x )
                    , y( y )
                    , r( r )
                    , g( g )
                    , b( b )
                {
                }
            };

            Point2Pos3Color() = default;
            Point2Pos3Color( float x, float y, float r, float g, float b )
                : posColor( x, y, r, g, b )
            {
            }
            Point2Pos3Color( QVector2D && position, QVector3D && color )
                : posColor( position.x(), position.y(), color.x(), color.y(), color.z() )
            {
            }

            inline float * data()
            {
                return _data;
            }

            inline float & x() noexcept
            {
                return posColor.x;
            }
            inline const float & x() const noexcept
            {
                return posColor.x;
            }

            inline float & y() noexcept
            {
                return posColor.y;
            }
            inline const float & y() const noexcept
            {
                return posColor.y;
            }

            inline float & r() noexcept
            {
                return posColor.r;
            }
            inline const float & r() const noexcept
            {
                return posColor.r;
            }

            inline float & g() noexcept
            {
                return posColor.g;
            }
            inline const float & g() const noexcept
            {
                return posColor.g;
            }

            inline float & b() noexcept
            {
                return posColor.b;
            }
            inline const float & b() const noexcept
            {
                return posColor.b;
            }

            PosColor posColor;
            float    _data[ 5 ];
        };

    } // namespace Utils

    using Point2p3c = Utils::Point2Pos3Color;

} // namespace Ouquitoure
