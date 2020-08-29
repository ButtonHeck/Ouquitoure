#pragma once

#include <QOpenGLFunctions_4_5_Core>
#include <unordered_map>

namespace Ouquitoure
{
    /**
     * @brief integer flag representing each buffer object (and transform feedback)
     */
    enum OPENGL_OBJECT : int
    {
        VAO          = 0x000001,
        VBO          = 0x000010,
        INSTANCE_VBO = 0x000100,
        EBO          = 0x001000,
        DIBO         = 0x010000,
        TFBO         = 0x100000
    };

    /**
     * @brief a collection of OpenGL buffer objects, which are to be used as a complete buffer pipeline.
     * Responsible for managing all the "glCreate/Bind/Delete" stuff and creating a collection of OpenGL objects
     * using just a set of flags representing each object's type
     */
    class BufferCollection final
    {
    public:
        explicit BufferCollection( QOpenGLFunctions_4_5_Core * const functions );
        BufferCollection( QOpenGLFunctions_4_5_Core * functions, int flags );
        BufferCollection( BufferCollection && old ) noexcept;
        BufferCollection( BufferCollection & copy );
        ~BufferCollection();

        /**
         * @brief replaces all bind-to-zero GL calls boilerplate code in one function
         * @param flag indicator of the GL object type that should be unbound
         */
        void bindZero( int flags ) noexcept;

        /**
         * @brief sends create command to OpenGL side and stores object's ID in the storage
         * @param flags integer union of individual flags
         */
        void create( int flags );

        /**
         * @brief sends command to OpenGL to delete each GL object if one exists in a collection
         */
        void deleteBuffers();

        /**
         * @brief sends command to OpenGL to delete a particular GL object
         * @param flag indicator of the GL object type that should be deleted
         */
        void deleteBuffer( int flag );

        /**
         * @brief return a GL object's ID
         * @param flag indicator of the GL object type whose ID should be returned
         */
        GLuint & get( int flag );

        /**
         * @brief sends bind command to OpenGL for a chosen GL objects
         * @param flag indicator of the GL object to be bound
         */
        void bind( int flag );

        /**
         * @brief similar to create method, but intended to be used after collection has been created and supposed to take one type per call
         * @param flag indicator of the GL object to be created
         */
        void add( int flag );

    private:
        QOpenGLFunctions_4_5_Core * const functions;
        std::unordered_map<int, GLuint>   objects;
    };

} // namespace Ouquitoure
