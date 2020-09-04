#include <Utils/RGBGuiPalettes>

namespace Ouquitoure
{
    RGBGuiPalettes::RGBGuiPalettes()
        : labels( { "R", "G", "B", "?" } )
    {
        QPalette redPalette;
        redPalette.setColor( QPalette::WindowText, Qt::red );
        QPalette greenPalette;
        greenPalette.setColor( QPalette::WindowText, Qt::darkGreen );
        QPalette bluePalette;
        bluePalette.setColor( QPalette::WindowText, Qt::blue );
        palettes[ 0 ] = redPalette;
        palettes[ 1 ] = greenPalette;
        palettes[ 2 ] = bluePalette;
        palettes[ 3 ] = QPalette();
    }

    const QPalette & RGBGuiPalettes::getPalette( size_t index ) const noexcept
    {
        return ( index < NUM_ELEMENTS && index >= 0 ? palettes[ index ] : palettes[ 3 ] );
    }

    const QPalette & RGBGuiPalettes::getPalette( Qt::GlobalColor color ) const noexcept
    {
        if( color == Qt::red )
        {
            return palettes[ 0 ];
        }
        else if( color == Qt::green )
        {
            return palettes[ 1 ];
        }
        else if( color == Qt::blue )
        {
            return palettes[ 2 ];
        }
        else
        {
            return palettes[ 3 ];
        }
    }

    const QString & RGBGuiPalettes::getLabel( size_t index ) const noexcept
    {
        return ( index < NUM_ELEMENTS && index >= 0 ? labels[ index ] : labels[ 3 ] );
    }

    const QString & RGBGuiPalettes::getLabel( Qt::GlobalColor color ) const noexcept
    {
        if( color == Qt::red )
        {
            return labels[ 0 ];
        }
        else if( color == Qt::green )
        {
            return labels[ 1 ];
        }
        else if( color == Qt::blue )
        {
            return labels[ 2 ];
        }
        else
        {
            return labels[ 3 ];
        }
    }

} // namespace Ouquitoure
