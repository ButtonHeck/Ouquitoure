#pragma once

#include <QVector2D>
#include <QVector3D>

namespace Ouquitoure
{
    namespace Utils
    {
        struct Point2Pos3Color
        {
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
            union Point
            {
                Point() = default;
                Point( float x, float y, float r, float g, float b )
                    : posColor( x, y, r, g, b )
                {
                }
                PosColor posColor;
                float    _data[ 5 ];
            } point;

            Point2Pos3Color() = default;
            Point2Pos3Color( float x, float y, float r, float g, float b )
                : point( x, y, r, g, b )
            {
            }
            Point2Pos3Color( QVector2D && position, QVector3D && color )
                : point( position.x(), position.y(), color.x(), color.y(), color.z() )
            {
            }

            inline float * data()
            {
                return point._data;
            }
        };

    } // namespace Utils

    using Point2p3c = Utils::Point2Pos3Color;

} // namespace Ouquitoure
