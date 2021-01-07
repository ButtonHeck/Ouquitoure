#pragma once

#include <QOpenGLFunctions_4_5_Core>
#include <parallel_hashmap/phmap.h>

namespace Ouquitoure
{
    /// @brief integer flag representing each buffer object (and transform feedback)
    enum OPENGL_OBJECT : int
    {
        VAO          = 0b000001,
        VBO          = 0b000010,
        INSTANCE_VBO = 0b000100,
        EBO          = 0b001000,
        DIBO         = 0b010000,
        TFBO         = 0b100000
    };

    /**
     * @brief a collection of OpenGL buffer objects, which are to be used as a complete buffer pipeline.
     * Responsible for managing all the "glCreate/Bind/Delete" stuff and creating a collection of OpenGL objects
     * using just a set of flags representing each object's type
     */
    class BufferCollection final
    {
    public:
        BufferCollection( QOpenGLFunctions_4_5_Core * const functions, size_t size );
        BufferCollection( BufferCollection && old ) noexcept;
        BufferCollection( const BufferCollection & copy ) = delete;
        BufferCollection & operator=( const BufferCollection & rhs ) = delete;
        ~BufferCollection();

        /// @brief replaces all bind-to-zero GL calls boilerplate code in one function
        /// @param flag indicator of the GL object type that should be unbound
        void bindZero( int flags ) const noexcept;

        /// @brief sends create command to OpenGL side and stores object's ID in the storage
        /// @param flags integer union of individual flags
        void create( int flags );

        /// @brief sends command to OpenGL to delete each GL object if one exists in a collection
        void deleteBuffers();

        /// @brief sends command to OpenGL to delete a particular GL object
        /// @param flag indicator of the GL object type that should be deleted
        void deleteBuffer( int flag );

        /// @brief sends bind command to OpenGL for a chosen GL objects
        /// @param flags mask of the GL objects to be bound
        void bind( int flags );

        /// @brief similar to create method, but intended to be used after collection has been created, takes one type per call
        /// @param flag indicator of the GL object to be created
        void add( int flag );

    private:
        phmap::flat_hash_map<int, GLuint> objects;
        QOpenGLFunctions_4_5_Core * const functions;
    };

} // namespace Ouquitoure
