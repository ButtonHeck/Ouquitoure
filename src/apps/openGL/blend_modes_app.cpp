#include "Apps/OpenGL/BlendModesApp"
#include "Utils/RGBGuiPalettes"

#include <QLabel>
#include <QSpinBox>
#include <QSlider>
#include <QButtonGroup>
#include <QRadioButton>

// clang-format off
#define OQ_MAKE_PAIR( name ) { name, #name }
// clang-format on

namespace Ouquitoure
{

    BlendModesApp::BlendModesApp( const QString & appName, QWidget * parent )
        : OpenGLAppBase( appName, parent )
        , viewWidget( appName, parent )
    {
        initializeDescription();
        installOpenGLViewWidget( viewWidget );

        // RGB palettes and labels
        RGBGuiPalettes palettes;

        // main layout
        QVBoxLayout * controlsLayout = new QVBoxLayout( controlsGroupBox );

        // quad colors controls
        for( int quadIndex = 0; quadIndex < 2; ++quadIndex )
        {
            QGroupBox *   quadGroupBox   = new QGroupBox( "Quad" + QString::number( quadIndex + 1 ) );
            QGridLayout * settingsLayout = new QGridLayout( quadGroupBox );

            // utility variables
            const Point2p4c & CURRENT_POINT   = viewWidget.getPoints()[ quadIndex * 4 ];
            QFont             colorLabelsFont = quadGroupBox->font();
            colorLabelsFont.setBold( true );

            for( int colorIndex = 0; colorIndex < RGBGuiPalettes::NUM_ELEMENTS; ++colorIndex )
            {
                const QString &  labelString    = palettes.getLabel( colorIndex );
                const QPalette & currentPalette = palettes.getPalette( colorIndex );
                // Label
                QLabel * colorLabel = new QLabel( labelString );
                colorLabel->setPalette( currentPalette );
                colorLabel->setFont( colorLabelsFont );
                colorLabel->setAlignment( Qt::AlignRight | Qt::AlignVCenter );
                settingsLayout->addWidget( colorLabel, colorIndex, 0, 1, 1 );
                // Spinbox
                QSpinBox * spinBox = new QSpinBox();
                spinBox->setRange( 0, 255 );
                spinBox->setSingleStep( 1 );
                spinBox->setMaximumWidth( 50 );
                spinBox->setSizePolicy( QSizePolicy::Maximum, QSizePolicy::Fixed );
                settingsLayout->addWidget( spinBox, colorIndex, 1, 1, 1 );
                // Slider
                QSlider * slider = new QSlider( Qt::Horizontal );
                slider->setObjectName( labelString + QString::number( quadIndex ) );
                slider->setTickInterval( 1 );
                slider->setRange( 0, 255 );
                slider->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Fixed );
                settingsLayout->addWidget( slider, colorIndex, 2, 1, 9 );

                // GUI connections
                connect( spinBox, SIGNAL( valueChanged( int ) ), slider, SLOT( setValue( int ) ) );
                connect( slider, SIGNAL( valueChanged( int ) ), spinBox, SLOT( setValue( int ) ) );
                slider->setValue( CURRENT_POINT._data[ Point2p4c::COLOR_OFFSET + colorIndex ] * 255 );

                // OpenGL connections
                connect( slider, SIGNAL( valueChanged( int ) ), &viewWidget, SLOT( quadColorChanged( int ) ) );
            }
            controlsLayout->addWidget( quadGroupBox );
        }

        // blend modes controls
        const QString                                 GROUP_NAMES[]{ "Source", "Destination" };
        constexpr int                                 NUM_BLEND_MODES = 19;
        constexpr std::pair<GLenum, std::string_view> BLEND_MODES[ NUM_BLEND_MODES ]{ OQ_MAKE_PAIR( GL_ZERO ),
                                                                                      OQ_MAKE_PAIR( GL_ONE ),
                                                                                      OQ_MAKE_PAIR( GL_SRC_COLOR ),
                                                                                      OQ_MAKE_PAIR( GL_ONE_MINUS_SRC_COLOR ),
                                                                                      OQ_MAKE_PAIR( GL_DST_COLOR ),
                                                                                      OQ_MAKE_PAIR( GL_ONE_MINUS_DST_COLOR ),
                                                                                      OQ_MAKE_PAIR( GL_SRC_ALPHA ),
                                                                                      OQ_MAKE_PAIR( GL_ONE_MINUS_SRC_ALPHA ),
                                                                                      OQ_MAKE_PAIR( GL_DST_ALPHA ),
                                                                                      OQ_MAKE_PAIR( GL_ONE_MINUS_DST_ALPHA ),
                                                                                      OQ_MAKE_PAIR( GL_CONSTANT_COLOR ),
                                                                                      OQ_MAKE_PAIR( GL_ONE_MINUS_CONSTANT_COLOR ),
                                                                                      OQ_MAKE_PAIR( GL_CONSTANT_ALPHA ),
                                                                                      OQ_MAKE_PAIR( GL_ONE_MINUS_CONSTANT_ALPHA ),
                                                                                      OQ_MAKE_PAIR( GL_SRC_ALPHA_SATURATE ),
                                                                                      OQ_MAKE_PAIR( GL_SRC1_COLOR ),
                                                                                      OQ_MAKE_PAIR( GL_ONE_MINUS_SRC1_COLOR ),
                                                                                      OQ_MAKE_PAIR( GL_SRC1_ALPHA ),
                                                                                      OQ_MAKE_PAIR( GL_ONE_MINUS_SRC1_ALPHA ) };

        QHBoxLayout * paramsLayout = new QHBoxLayout;
        for( int parameterIndex = 0; parameterIndex < 2; ++parameterIndex )
        {
            QGroupBox *    paramGroupBox     = new QGroupBox( GROUP_NAMES[ parameterIndex ] );
            QVBoxLayout *  blendModesLayout  = new QVBoxLayout( paramGroupBox );
            QButtonGroup * modesRadioButtons = new QButtonGroup( blendModesLayout );
            for( int blendModeIndex = 0; blendModeIndex < NUM_BLEND_MODES; ++blendModeIndex )
            {
                const auto & [ blendCode, blendName ] = BLEND_MODES[ blendModeIndex ];
                QRadioButton * modeButton             = new QRadioButton( QString( blendName.data() ) );
                modeButton->setObjectName( QString::number( parameterIndex ).append( QString::number( blendCode ) ) );
                modesRadioButtons->addButton( modeButton );
                blendModesLayout->addWidget( modeButton );
                connect( modeButton, SIGNAL( clicked() ), &viewWidget, SLOT( blendFuncModeChanged() ) );
            }
            paramsLayout->addWidget( paramGroupBox );
        }
        controlsLayout->addLayout( paramsLayout );

        // blend constant color controls
        QGroupBox *   blendColorBox    = new QGroupBox( "Blend color" );
        QGridLayout * blendColorLayout = new QGridLayout( blendColorBox );
        QFont         blendColorFont   = blendColorBox->font();
        blendColorFont.setBold( true );
        for( int colorIndex = 0; colorIndex < RGBGuiPalettes::NUM_ELEMENTS; ++colorIndex )
        {
            const QString &  labelString    = palettes.getLabel( colorIndex );
            const QPalette & currentPalette = palettes.getPalette( colorIndex );
            // Label
            QLabel * colorLabel = new QLabel( labelString );
            colorLabel->setPalette( currentPalette );
            colorLabel->setFont( blendColorFont );
            colorLabel->setAlignment( Qt::AlignRight | Qt::AlignVCenter );
            blendColorLayout->addWidget( colorLabel, colorIndex, 0, 1, 1 );
            // Spinbox
            QSpinBox * spinBox = new QSpinBox();
            spinBox->setRange( 0, 255 );
            spinBox->setSingleStep( 1 );
            spinBox->setMaximumWidth( 50 );
            spinBox->setSizePolicy( QSizePolicy::Maximum, QSizePolicy::Fixed );
            blendColorLayout->addWidget( spinBox, colorIndex, 1, 1, 1 );
            // Slider
            QSlider * slider = new QSlider( Qt::Horizontal );
            slider->setObjectName( labelString );
            slider->setTickInterval( 1 );
            slider->setRange( 0, 255 );
            slider->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Fixed );
            blendColorLayout->addWidget( slider, colorIndex, 2, 1, 9 );

            // GUI connections
            connect( spinBox, SIGNAL( valueChanged( int ) ), slider, SLOT( setValue( int ) ) );
            connect( slider, SIGNAL( valueChanged( int ) ), spinBox, SLOT( setValue( int ) ) );

            // OpenGL connections
            connect( slider, SIGNAL( valueChanged( int ) ), &viewWidget, SLOT( blendColorChanged( int ) ) );
        }
        controlsLayout->addWidget( blendColorBox );

        // blend equation controls
        constexpr int                                 NUM_BLEND_EQUATIONS = 5;
        constexpr std::pair<GLenum, std::string_view> BLEND_EQUATIONS[ NUM_BLEND_EQUATIONS ]{
            OQ_MAKE_PAIR( GL_FUNC_ADD ), OQ_MAKE_PAIR( GL_FUNC_SUBTRACT ), OQ_MAKE_PAIR( GL_FUNC_REVERSE_SUBTRACT ), OQ_MAKE_PAIR( GL_MIN ),
            OQ_MAKE_PAIR( GL_MAX )
        };
        QGroupBox *    equationsGroupBox    = new QGroupBox( "Blend equations" );
        QVBoxLayout *  equationsLayout      = new QVBoxLayout( equationsGroupBox );
        QButtonGroup * equationsButtonGroup = new QButtonGroup( equationsLayout );
        for( int blendEquationIndex = 0; blendEquationIndex < NUM_BLEND_EQUATIONS; ++blendEquationIndex )
        {
            const auto & [ equationCode, equationNameView ] = BLEND_EQUATIONS[ blendEquationIndex ];
            QRadioButton * equationButton                   = new QRadioButton( QString( equationNameView.data() ) );
            equationButton->setObjectName( QString::number( equationCode ) );
            equationsButtonGroup->addButton( equationButton );
            equationsLayout->addWidget( equationButton );
            connect( equationButton, SIGNAL( clicked() ), &viewWidget, SLOT( blendFuncEquationChanged() ) );
        }
        controlsLayout->addWidget( equationsGroupBox );
    }

    void BlendModesApp::initializeDescription()
    {
        info = AppInfo( appName, { "basic", "2D", "blending" }, OPENGL_APP );
        info.getDescription().setAuthor( "Ilya Malgin (Buttonheck)" );
        info.getDescription().setEmail( "buttonheck@gmail.com" );
        info.getDescription().setBrief( "Application for playing with different blend factors for source and destination, blend equation "
                                        "and constant blend color values during alpha-blending in OpenGL" );
        info.getDescription().setAppImage( ":/appImages/BlendModes.png" );
        info.getDescription().addReference( { QUrl( "https://www.khronos.org/opengl/wiki/Blending" ), "OpenGL wiki: blending" } );
    }

} // namespace Ouquitoure
