#include "OpenGLApps/ColoredTriangleApp"

#include <QLabel>
#include <QSlider>
#include <QSpinBox>

namespace Ouquitoure
{

    ColoredTriangleApp::ColoredTriangleApp( const QString & appName, QWidget * parent )
        : OpenGLAppBase( appName, parent )
        , viewWidget( appName, parent )
    {
        info = AppInfo( appName, { "basic", "triangle" }, OPENGL_APP );
        installOpenGLViewWidget( viewWidget );

        // GUI view and layouts setup
        QVBoxLayout * controlsLayout = new QVBoxLayout( controlsGroupBox );
        for( int pointIndex = 0; pointIndex < ColoredTriangleWidget::NUM_POINTS; ++pointIndex )
        {
            QGroupBox *   pointGroupBox  = new QGroupBox( "Point " + QString::number( pointIndex + 1 ) );
            QGridLayout * settingsLayout = new QGridLayout( pointGroupBox );
            settingsLayout->setColumnMinimumWidth( 0, 30 );

            // Position controls and indicator labels
            QLabel * xyLabel = new QLabel( "Y \\ X" );
            settingsLayout->addWidget( xyLabel, 0, 0, 1, 1 );
            xPosLabel[ pointIndex ] = new QLabel( "0" );
            settingsLayout->addWidget( xPosLabel[ pointIndex ], 0, 1, 1, 1 );
            yPosLabel[ pointIndex ] = new QLabel( "0" );
            yPosLabel[ pointIndex ]->setAlignment( Qt::AlignLeft );
            settingsLayout->addWidget( yPosLabel[ pointIndex ], 1, 0, 1, 1 );

            // Point X position slider
            QSlider * xSlider = new QSlider( Qt::Horizontal );
            xSlider->setObjectName( "xSlider " + QString::number( pointIndex ) );
            xSlider->setRange( -100, 100 );
            xSlider->setTickInterval( 1 );
            xSlider->setValue( viewWidget.getPoints()[ pointIndex ].point.posColor.x * 100 );
            settingsLayout->addWidget( xSlider, 0, 2, 1, 10 );
            // Point Y position slider
            QSlider * ySlider = new QSlider( Qt::Vertical );
            ySlider->setObjectName( "ySlider " + QString::number( pointIndex ) );
            ySlider->setRange( -100, 100 );
            ySlider->setTickInterval( 1 );
            ySlider->setValue( viewWidget.getPoints()[ pointIndex ].point.posColor.y * 100 );
            settingsLayout->addWidget( ySlider, 2, 0, 5, 1 );

            // GUI connections
            connect( xSlider, SIGNAL( valueChanged( int ) ), SLOT( positionSliderValueChanged( int ) ) );
            connect( ySlider, SIGNAL( valueChanged( int ) ), SLOT( positionSliderValueChanged( int ) ) );
            // OpenGL connections
            connect( xSlider, SIGNAL( valueChanged( int ) ), &viewWidget, SLOT( vertexPositionChanged( int ) ) );
            connect( ySlider, SIGNAL( valueChanged( int ) ), &viewWidget, SLOT( vertexPositionChanged( int ) ) );

            // Palettes and label names
            QPalette redPalette;
            redPalette.setColor( QPalette::WindowText, Qt::red );
            QPalette greenPalette;
            greenPalette.setColor( QPalette::WindowText, Qt::green );
            QPalette bluePalette;
            bluePalette.setColor( QPalette::WindowText, Qt::blue );
            QVector<QPalette> palettes{ redPalette, greenPalette, bluePalette };
            QStringList       labels{ "R", "G", "B" };

            for( int colorIndex = 0; colorIndex < labels.size(); ++colorIndex )
            {
                // Label
                QLabel * label = new QLabel( labels[ colorIndex ] );
                label->setPalette( palettes[ colorIndex ] );
                label->setAlignment( Qt::AlignRight | Qt::AlignVCenter );
                settingsLayout->addWidget( label, 2 + colorIndex, 1, 1, 1 );
                // SpinBox
                QSpinBox * spinBox = new QSpinBox();
                spinBox->setRange( 0, 255 );
                spinBox->setSingleStep( 1 );
                spinBox->setMaximumWidth( 50 );
                spinBox->setSizePolicy( QSizePolicy::Maximum, QSizePolicy::Expanding );
                settingsLayout->addWidget( spinBox, 2 + colorIndex, 2, 1, 1 );
                // Slider
                QSlider * slider = new QSlider( Qt::Horizontal );
                slider->setObjectName( labels[ colorIndex ] + QString::number( pointIndex ) );
                slider->setTickInterval( 1 );
                slider->setRange( 0, 255 );
                slider->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
                settingsLayout->addWidget( slider, 2 + colorIndex, 3, 1, 9 );

                // GUI connections
                connect( spinBox, SIGNAL( valueChanged( int ) ), slider, SLOT( setValue( int ) ) );
                connect( slider, SIGNAL( valueChanged( int ) ), spinBox, SLOT( setValue( int ) ) );

                slider->setValue( viewWidget.getPoints()[ pointIndex ].point._data[ 2 + colorIndex ] * 255 );

                // OpenGL connections
                connect( slider, SIGNAL( valueChanged( int ) ), &viewWidget, SLOT( vertexColorChanged( int ) ) );
            }
            controlsLayout->addWidget( pointGroupBox );
        }
    }

    void ColoredTriangleApp::positionSliderValueChanged( int value )
    {
        bool     isX   = sender()->objectName().left( 1 ) == 'x';
        int      index = sender()->objectName().right( 1 ).toInt();
        QLabel * label = isX ? xPosLabel[ index ] : yPosLabel[ index ];
        label->setText( QString::number( value / 100.0 ) );
    }

} // namespace Ouquitoure
