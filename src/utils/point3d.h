#pragma once

namespace Ouquitoure
{
    namespace Math
    {

        template<typename T>
        union Point3D
        {
            constexpr static int NUM_ELEMENTS = 3;

            struct Elements
            {
                union
                {
                    T x;
                    T r;
                };
                union
                {
                    T y;
                    T g;
                };
                union
                {
                    T z;
                    T b;
                };

                Elements() = default;
                Elements( T x, T y, T z )
                    : x( x )
                    , y( y )
                    , z( z )
                {
                }
            };

            Point3D() = default;
            Point3D( T x, T y, T z )
                : elements( x, y, z )
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

            Elements elements;
            T        _data[ NUM_ELEMENTS ];
        };

    } // namespace Math

    using Point3D_f = Math::Point3D<float>;

} // namespace Ouquitoure
