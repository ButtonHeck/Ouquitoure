#include "Apps/OpenGL/ColoredTriangleApp"
#include "Utils/RGBGuiPalettes"

#include <QLabel>
#include <QSlider>
#include <QSpinBox>

namespace Ouquitoure
{

    ColoredTriangleApp::ColoredTriangleApp( const QString & appName, QWidget * parent )
        : OpenGLAppBase( appName, parent )
        , viewWidget( appName, parent )
    {
        initializeDescription();
        installOpenGLViewWidget( viewWidget );

        // Palettes and label names
        RGBGuiPalettes palettes;

        // GUI view and layouts setup
        QVBoxLayout * controlsLayout = new QVBoxLayout( controlsGroupBox );
        for( int pointIndex = 0; pointIndex < ColoredTriangleWidget::NUM_POINTS; ++pointIndex )
        {
            QGroupBox *   pointGroupBox  = new QGroupBox( "Point " + QString::number( pointIndex + 1 ) );
            QGridLayout * settingsLayout = new QGridLayout( pointGroupBox );
            settingsLayout->setColumnMinimumWidth( 0, 30 );

            // some utility variables
            const QString     POINT_INDEX_STRING = QString::number( pointIndex );
            const Point2p3c & CURRENT_POINT      = viewWidget.getPoints()[ pointIndex ];
            QFont             colorLabelsFont    = pointGroupBox->font();
            colorLabelsFont.setBold( true );

            // Position controls and indicator labels
            QLabel * xyLabel = new QLabel( "Y \\ X" );
            xyLabel->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
            settingsLayout->addWidget( xyLabel, 0, 0, 1, 1 );
            xPosLabel[ pointIndex ] = new QLabel( "0" );
            settingsLayout->addWidget( xPosLabel[ pointIndex ], 0, 1, 1, 1 );
            yPosLabel[ pointIndex ] = new QLabel( "0" );
            yPosLabel[ pointIndex ]->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
            settingsLayout->addWidget( yPosLabel[ pointIndex ], 1, 0, 1, 1 );

            // Point X position slider
            QSlider * xSlider = new QSlider( Qt::Horizontal );
            xSlider->setObjectName( "xSlider " + POINT_INDEX_STRING );
            xSlider->setRange( -100, 100 );
            xSlider->setTickInterval( 1 );
            xSlider->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Fixed );
            settingsLayout->addWidget( xSlider, 0, 2, 1, 10 );
            // Point Y position slider
            QSlider * ySlider = new QSlider( Qt::Vertical );
            ySlider->setObjectName( "ySlider " + POINT_INDEX_STRING );
            ySlider->setRange( -100, 100 );
            ySlider->setTickInterval( 1 );
            ySlider->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Expanding );
            settingsLayout->addWidget( ySlider, 2, 0, 5, 1 );

            // GUI connections
            connect( xSlider, SIGNAL( valueChanged( int ) ), SLOT( updatePositionLabelText( int ) ) );
            connect( ySlider, SIGNAL( valueChanged( int ) ), SLOT( updatePositionLabelText( int ) ) );
            // update position labels
            xSlider->setValue( CURRENT_POINT.x() * 100 );
            ySlider->setValue( CURRENT_POINT.y() * 100 );
            // OpenGL connections
            connect( xSlider, SIGNAL( valueChanged( int ) ), &viewWidget, SLOT( vertexPositionChanged( int ) ) );
            connect( ySlider, SIGNAL( valueChanged( int ) ), &viewWidget, SLOT( vertexPositionChanged( int ) ) );

            for( int colorIndex = 0; colorIndex < RGBGuiPalettes::NUM_ELEMENTS; ++colorIndex )
            {
                // Label
                const QString &  labelString    = palettes.getLabel( colorIndex );
                const QPalette & currentPalette = palettes.getPalette( colorIndex );
                QLabel *         label          = new QLabel( labelString );
                label->setPalette( currentPalette );
                label->setFont( colorLabelsFont );
                label->setAlignment( Qt::AlignRight | Qt::AlignVCenter );
                settingsLayout->addWidget( label, 2 + colorIndex, 1, 1, 1 );
                // SpinBox
                QSpinBox * spinBox = new QSpinBox();
                spinBox->setRange( 0, 255 );
                spinBox->setSingleStep( 1 );
                spinBox->setMaximumWidth( 50 );
                spinBox->setSizePolicy( QSizePolicy::Maximum, QSizePolicy::Fixed );
                settingsLayout->addWidget( spinBox, 2 + colorIndex, 2, 1, 1 );
                // Slider
                QSlider * slider = new QSlider( Qt::Horizontal );
                slider->setObjectName( labelString + QString::number( pointIndex ) );
                slider->setTickInterval( 1 );
                slider->setRange( 0, 255 );
                slider->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Fixed );
                settingsLayout->addWidget( slider, 2 + colorIndex, 3, 1, 9 );

                // GUI connections
                connect( spinBox, SIGNAL( valueChanged( int ) ), slider, SLOT( setValue( int ) ) );
                connect( slider, SIGNAL( valueChanged( int ) ), spinBox, SLOT( setValue( int ) ) );

                slider->setValue( CURRENT_POINT._data[ Point2p3c::COLOR_OFFSET + colorIndex ] * 255 );

                // OpenGL connections
                connect( slider, SIGNAL( valueChanged( int ) ), &viewWidget, SLOT( vertexColorChanged( int ) ) );
            }
            controlsLayout->addWidget( pointGroupBox );
        }
    }

    void ColoredTriangleApp::initializeDescription()
    {
        info = AppInfo( appName, { "basic", "2D", "triangle" }, OPENGL_APP );
        info.getDescription().setAuthor( "Ilya Malgin (Buttonheck)" );
        info.getDescription().setEmail( "buttonheck@gmail.com" );
        info.getDescription().setBrief( "Hello world application. Just draws colored triangle. Vertices positions and "
                                        "colors could be tweaked using Qt GUI." );
        info.getDescription().setAppImage( ":/appImages/ColoredTriangle.png" );
        info.getDescription().addReference( { QUrl( "https://learnopengl.com/Getting-started/Hello-Triangle" ), "OpenGL hello world" } );
        info.getDescription().addReference(
            { QUrl( "https://www.khronos.org/opengl/wiki/Buffer_Object" ), "OpenGL wiki: buffer objects" } );
        info.getDescription().setNotes( "I've created this test app during Ouquitoure development, just to make sure "
                                        "that everything works as it expected" );
    }

    void ColoredTriangleApp::updatePositionLabelText( int value )
    {
        bool     isX   = sender()->objectName().left( 1 ) == 'x';
        int      index = sender()->objectName().right( 1 ).toInt();
        QLabel * label = isX ? xPosLabel[ index ] : yPosLabel[ index ];
        label->setText( QString::number( value / 100.0 ) );
    }

} // namespace Ouquitoure
