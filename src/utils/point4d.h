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

            inline T & x()
            {
                return elements.x;
            }
            inline const T & x() const
            {
                return elements.x;
            }

            // Y

            inline T & y()
            {
                return elements.y;
            }
            inline const T & y() const
            {
                return elements.y;
            }

            // Z

            inline T & z()
            {
                return elements.z;
            }
            inline const T & z() const
            {
                return elements.z;
            }

            // W

            inline T & w()
            {
                return elements.w;
            }
            inline const T & w() const
            {
                return elements.w;
            }

            // Red

            inline T & r()
            {
                return elements.r;
            }
            inline const T & r() const
            {
                return elements.r;
            }

            // Green

            inline T & g()
            {
                return elements.g;
            }
            inline const T & g() const
            {
                return elements.g;
            }

            // Blue

            inline T & b()
            {
                return elements.b;
            }
            inline const T & b() const
            {
                return elements.b;
            }

            // Alpha

            inline T & a()
            {
                return elements.a;
            }
            inline const T & a() const
            {
                return elements.a;
            }

            // S

            inline T & s()
            {
                return elements.s;
            }
            inline const T & s() const
            {
                return elements.s;
            }

            // T

            inline T & t()
            {
                return elements.t;
            }
            inline const T & t() const
            {
                return elements.t;
            }

            // P

            inline T & p()
            {
                return elements.p;
            }
            inline const T & p() const
            {
                return elements.p;
            }

            // Q

            inline T & q()
            {
                return elements.q;
            }
            inline const T & q() const
            {
                return elements.q;
            }

            Elements elements;
            T        _data[ NUM_ELEMENTS ];
        };

    } // namespace Math

    using Point4D_f = Math::Point4D<float>;

} // namespace Ouquitoure
