#pragma once

#include <QPalette>
#include <QVector>
#include <array>

namespace Ouquitoure
{

    /**
     * @brief Palette storage with preset palette and according labels,
     * mostly be used in widgets for labels coloring
     */
    class RGBGuiPalettes
    {
    public:
        constexpr static int NUM_ELEMENTS = 3;

    public:
        RGBGuiPalettes();

        const QPalette & getPalette( size_t index ) const noexcept;
        const QPalette & getPalette( Qt::GlobalColor color ) const noexcept;
        const QString &  getLabel( size_t index ) const noexcept;
        const QString &  getLabel( Qt::GlobalColor color ) const noexcept;

    private:
        std::array<QPalette, NUM_ELEMENTS + 1>      palettes;
        const std::array<QString, NUM_ELEMENTS + 1> labels;
    };

} // namespace Ouquitoure
