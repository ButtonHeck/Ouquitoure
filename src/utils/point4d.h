#pragma once

namespace Ouquitoure
{
    namespace Math
    {

        template<typename T>
        union Point4D
        {
            constexpr static int NUM_ELEMENTS = 4;

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
                union
                {
                    T z;
                    T b;
                    T p;
                };
                union
                {
                    T w;
                    T a;
                    T q;
                };

                Elements() = default;
                Elements( T x, T y, T z, T w )
                    : x( x )
                    , y( y )
                    , z( z )
                    , w( w )
                {
                }
            };

            Point4D() = default;
            Point4D( T x, T y, T z, T w )
                : elements( x, y, z, w )
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

            // Z

            inline T & z() noexcept
            {
                return elements.z;
            }
            inline const T & z() const noexcept
            {
                return elements.z;
            }

            // W

            inline T & w() noexcept
            {
                return elements.w;
            }
            inline const T & w() const noexcept
            {
                return elements.w;
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

            // Blue

            inline T & b() noexcept
            {
                return elements.b;
            }
            inline const T & b() const noexcept
            {
                return elements.b;
            }

            // Alpha

            inline T & a() noexcept
            {
                return elements.a;
            }
            inline const T & a() const noexcept
            {
                return elements.a;
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

            // P

            inline T & p() noexcept
            {
                return elements.p;
            }
            inline const T & p() const noexcept
            {
                return elements.p;
            }

            // Q

            inline T & q() noexcept
            {
                return elements.q;
            }
            inline const T & q() const noexcept
            {
                return elements.q;
            }

            Elements elements;
            T        _data[ NUM_ELEMENTS ];
        };

    } // namespace Math

    using Point4D_f = Math::Point4D<float>;

} // namespace Ouquitoure
