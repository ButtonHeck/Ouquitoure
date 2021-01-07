#include "Utils/BufferCollection"
#include "Log"

#include <QOpenGLFunctions_4_5_Core>

namespace Ouquitoure
{
    BufferCollection::BufferCollection( QOpenGLFunctions_4_5_Core * const functions, size_t size )
        : functions( functions )
    {
        objects.reserve( size );
    }

    BufferCollection::BufferCollection( BufferCollection && old ) noexcept
        : functions( old.functions )
    {
        if( old.objects.contains( VAO ) && old.objects[ VAO ] )
        {
            objects[ VAO ] = old.objects[ VAO ];
        }
        if( old.objects.contains( VBO ) && old.objects[ VBO ] )
        {
            objects[ VBO ] = old.objects[ VBO ];
        }
        if( old.objects.contains( INSTANCE_VBO ) && old.objects[ INSTANCE_VBO ] )
        {
            objects[ INSTANCE_VBO ] = old.objects[ INSTANCE_VBO ];
        }
        if( old.objects.contains( EBO ) && old.objects[ EBO ] )
        {
            objects[ EBO ] = old.objects[ EBO ];
        }
        if( old.objects.contains( DIBO ) && old.objects[ DIBO ] )
        {
            objects[ DIBO ] = old.objects[ DIBO ];
        }
        if( old.objects.contains( TFBO ) && old.objects[ TFBO ] )
        {
            objects[ TFBO ] = old.objects[ TFBO ];
        }
        old.objects.clear();
    }

    BufferCollection::~BufferCollection()
    {
        deleteBuffers();
    }

    void BufferCollection::bindZero( int flag ) const noexcept
    {
        if( flag & VAO )
        {
            functions->glBindVertexArray( 0 );
        }
        if( flag & VBO || flag & INSTANCE_VBO )
        {
            functions->glBindBuffer( GL_ARRAY_BUFFER, 0 );
        }
        if( flag & EBO )
        {
            functions->glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
        }
        if( flag & DIBO )
        {
            functions->glBindBuffer( GL_DRAW_INDIRECT_BUFFER, 0 );
        }
        if( flag & TFBO )
        {
            functions->glBindTransformFeedback( GL_TRANSFORM_FEEDBACK, 0 );
        }
    }

    void BufferCollection::create( int flags )
    {
        if( flags & VAO )
        {
            if( objects.contains( VAO ) && objects[ VAO ] != 0 )
            {
                functions->glDeleteVertexArrays( 1, &objects[ VAO ] );
            }
            GLuint vao;
            functions->glCreateVertexArrays( 1, &vao );
            objects[ VAO ] = vao;
        }
        if( flags & VBO )
        {
            if( objects.contains( VBO ) && objects[ VBO ] != 0 )
            {
                functions->glDeleteBuffers( 1, &objects[ VBO ] );
            }
            GLuint vbo;
            functions->glCreateBuffers( 1, &vbo );
            objects[ VBO ] = vbo;
        }
        if( flags & INSTANCE_VBO )
        {
            if( objects.contains( INSTANCE_VBO ) && objects[ INSTANCE_VBO ] != 0 )
            {
                functions->glDeleteBuffers( 1, &objects[ INSTANCE_VBO ] );
            }
            GLuint vbo;
            functions->glCreateBuffers( 1, &vbo );
            objects[ INSTANCE_VBO ] = vbo;
        }
        if( flags & EBO )
        {
            if( objects.contains( EBO ) && objects[ EBO ] != 0 )
            {
                functions->glDeleteBuffers( 1, &objects[ EBO ] );
            }
            GLuint ebo;
            functions->glCreateBuffers( 1, &ebo );
            objects[ EBO ] = ebo;
        }
        if( flags & DIBO )
        {
            if( objects.contains( DIBO ) && objects[ DIBO ] != 0 )
            {
                functions->glDeleteBuffers( 1, &objects[ DIBO ] );
            }
            GLuint dibo;
            functions->glCreateBuffers( 1, &dibo );
            objects[ DIBO ] = dibo;
        }
        if( flags & TFBO )
        {
            if( objects.contains( DIBO ) && objects[ DIBO ] != 0 )
            {
                functions->glDeleteTransformFeedbacks( 1, &objects[ TFBO ] );
            }
            GLuint tfbo;
            functions->glCreateTransformFeedbacks( 1, &tfbo );
            objects[ TFBO ] = tfbo;
        }
    }

    void BufferCollection::deleteBuffers()
    {
        if( objects.contains( VAO ) && objects[ VAO ] )
        {
            functions->glDeleteVertexArrays( 1, &objects[ VAO ] );
        }
        if( objects.contains( VBO ) && objects[ VBO ] )
        {
            functions->glDeleteBuffers( 1, &objects[ VBO ] );
        }
        if( objects.contains( INSTANCE_VBO ) && objects[ INSTANCE_VBO ] )
        {
            functions->glDeleteBuffers( 1, &objects[ INSTANCE_VBO ] );
        }
        if( objects.contains( EBO ) && objects[ EBO ] )
        {
            functions->glDeleteBuffers( 1, &objects[ EBO ] );
        }
        if( objects.contains( DIBO ) && objects[ DIBO ] )
        {
            functions->glDeleteBuffers( 1, &objects[ DIBO ] );
        }
        if( objects.contains( TFBO ) && objects[ TFBO ] )
        {
            functions->glDeleteTransformFeedbacks( 1, &objects[ TFBO ] );
        }
        objects.clear();
    }

    void BufferCollection::deleteBuffer( int flag )
    {
        if( ( flag & VAO ) && objects.contains( VAO ) )
        {
            functions->glDeleteVertexArrays( 1, &objects[ VAO ] );
            objects.erase( VAO );
        }
        else if( ( flag & VBO ) && objects.contains( VBO ) )
        {
            functions->glDeleteBuffers( 1, &objects[ VBO ] );
            objects.erase( VBO );
        }
        else if( ( flag & INSTANCE_VBO ) && objects.contains( INSTANCE_VBO ) )
        {
            functions->glDeleteBuffers( 1, &objects[ INSTANCE_VBO ] );
            objects.erase( INSTANCE_VBO );
        }
        else if( ( flag & EBO ) && objects.contains( EBO ) )
        {
            functions->glDeleteBuffers( 1, &objects[ EBO ] );
            objects.erase( EBO );
        }
        else if( ( flag & DIBO ) && objects.contains( DIBO ) )
        {
            functions->glDeleteBuffers( 1, &objects[ DIBO ] );
            objects.erase( DIBO );
        }
        else if( ( flag & TFBO ) && objects.contains( TFBO ) )
        {
            functions->glDeleteTransformFeedbacks( 1, &objects[ TFBO ] );
            objects.erase( TFBO );
        }
        else
        {
            throw std::invalid_argument( "Unknown GL object enum flag" );
        }
    }

    void BufferCollection::bind( int flags )
    {
        if( ( flags & VAO ) && objects.contains( VAO ) )
        {
            functions->glBindVertexArray( objects[ VAO ] );
        }
        if( ( flags & VBO ) && objects.contains( VBO ) )
        {
            functions->glBindBuffer( GL_ARRAY_BUFFER, objects[ VBO ] );
        }
        if( ( flags & INSTANCE_VBO ) && objects.contains( INSTANCE_VBO ) )
        {
            functions->glBindBuffer( GL_ARRAY_BUFFER, objects[ INSTANCE_VBO ] );
        }
        if( ( flags & EBO ) && objects.contains( EBO ) )
        {
            functions->glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, objects[ EBO ] );
        }
        if( ( flags & DIBO ) && objects.contains( DIBO ) )
        {
            functions->glBindBuffer( GL_DRAW_INDIRECT_BUFFER, objects[ DIBO ] );
        }
        if( ( flags & TFBO ) && objects.contains( TFBO ) )
        {
            functions->glBindTransformFeedback( GL_TRANSFORM_FEEDBACK, objects[ TFBO ] );
        }
    }

    void BufferCollection::add( int flag )
    {
        if( flag & VAO )
        {
            if( objects.contains( VAO ) && objects[ VAO ] != 0 )
            {
                functions->glDeleteVertexArrays( 1, &objects[ VAO ] );
            }
            GLuint vao;
            functions->glCreateVertexArrays( 1, &vao );
            objects[ VAO ] = vao;
        }
        else if( flag & VBO )
        {
            if( objects.contains( VBO ) && objects[ VBO ] != 0 )
            {
                functions->glDeleteBuffers( 1, &objects[ VBO ] );
            }
            GLuint vbo;
            functions->glCreateBuffers( 1, &vbo );
            objects[ VBO ] = vbo;
        }
        else if( flag & INSTANCE_VBO )
        {
            if( objects.contains( INSTANCE_VBO ) && objects[ INSTANCE_VBO ] != 0 )
            {
                functions->glDeleteBuffers( 1, &objects[ INSTANCE_VBO ] );
            }
            GLuint vbo;
            functions->glCreateBuffers( 1, &vbo );
            objects[ INSTANCE_VBO ] = vbo;
        }
        else if( flag & EBO )
        {
            if( objects.contains( EBO ) && objects[ EBO ] != 0 )
            {
                functions->glDeleteBuffers( 1, &objects[ EBO ] );
            }
            GLuint ebo;
            functions->glCreateBuffers( 1, &ebo );
            objects[ EBO ] = ebo;
        }
        else if( flag & DIBO )
        {
            if( objects.contains( DIBO ) && objects[ DIBO ] != 0 )
            {
                functions->glDeleteBuffers( 1, &objects[ DIBO ] );
            }
            GLuint dibo;
            functions->glCreateBuffers( 1, &dibo );
            objects[ DIBO ] = dibo;
        }
        else if( flag & TFBO )
        {
            if( objects.contains( DIBO ) && objects[ DIBO ] != 0 )
            {
                functions->glDeleteTransformFeedbacks( 1, &objects[ TFBO ] );
            }
            GLuint tfbo;
            functions->glCreateTransformFeedbacks( 1, &tfbo );
            objects[ TFBO ] = tfbo;
        }
        else
        {
            throw std::invalid_argument( "Unknown GL object enum flag" );
        }
    }
} // namespace Ouquitoure
