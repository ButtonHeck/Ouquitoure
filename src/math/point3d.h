#pragma once

namespace Ouquitoure::Math
{
    template<typename T>
    /**
     * @brief point union with three components
     */
    union Point3D
    {
        constexpr static int NUM_ELEMENTS = 3;

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
        inline T & p() const noexcept
        {
            return elements.p;
        }

        Elements elements;
        T        _data[ NUM_ELEMENTS ];
    };

} // namespace Ouquitoure::Math

namespace Ouquitoure
{
    using Point3D_f = Math::Point3D<float>;
}
