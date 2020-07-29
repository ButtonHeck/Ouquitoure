#pragma once

namespace Ouquitoure
{
    namespace Math
    {

        template<typename T>
        /**
         * @brief point union with two components
         */
        union Point2D
        {
            constexpr static int NUM_ELEMENTS = 2;

            struct Elements
            {
                union
                {
                    T x;
                    T r;
                    T s;
                };
                union
                {
                    T y;
                    T g;
                    T t;
                };

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

            // Red

            inline T & r() noexcept
            {
                return elements.r;
            }
            inline const T & r() const noexcept
            {
                return elements.r;
            }

            // Green

            inline T & g() noexcept
            {
                return elements.g;
            }
            inline const T & g() const noexcept
            {
                return elements.g;
            }

            // S

            inline T & s() noexcept
            {
                return elements.s;
            }
            inline const T & s() const noexcept
            {
                return elements.s;
            }

            // T

            inline T & t() noexcept
            {
                return elements.t;
            }
            inline const T & t() const noexcept
            {
                return elements.t;
            }

            Elements elements;
            T        _data[ NUM_ELEMENTS ];
        };

    } // namespace Math

    using Point2D_f = Math::Point2D<float>;

} // namespace Ouquitoure
