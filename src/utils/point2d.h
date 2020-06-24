#pragma once

namespace Ouquitoure
{
    namespace Math
    {

        template<typename T>
        union Point2D
        {
            constexpr static int NUM_ELEMENTS = 2;

            struct Elements
            {
                T x;
                T y;

                Elements() = default;
                Elements( T x, T y )
                    : x( x )
                    , y( y )
                {
                }
            };

            Point2D() = default;
            Point2D( T x, T y )
                : elements( x, y )
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
                return elements.x;
            }
            inline const T & x() const noexcept
            {
                return elements.x;
            }

            // Y

            inline T & y() noexcept
            {
                return elements.y;
            }
            inline const T & y() const noexcept
            {
                return elements.y;
            }

            Elements elements;
            T        _data[ NUM_ELEMENTS ];
        };

    } // namespace Math

    using Point2D_f = Math::Point2D<float>;

} // namespace Ouquitoure
