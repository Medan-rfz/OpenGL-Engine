#include "TextureLoader.hpp"
#include <GLFW/glfw3.h>

#include <memory>
#include <stdio.h>
#include <png.h>

namespace MEngine::Common
{
    typedef struct
    {
        uint8_t r, g, b, a;
    } Texture;

    //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
    GLuint TextureLoader::LoadTGA(const char* path)
    {
        Texture data[2][2];
        memset(data, 0, sizeof(data));
        data[0][0].r = 255;
        data[1][0].g = 255;
        data[1][1].b = 255;
        data[0][1].r = 255;
        data[0][1].g = 255;

        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, 0);

        return textureID;
    }

    //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
    bool TextureLoader::LoadPngImage(const char* file, int& outWidth, int& outHeight, GLubyte** outData)
    {
        png_structp png_ptr;
        png_infop info_ptr;
        unsigned int sig_read = 0;
        int color_type, interlace_type;
        FILE* fp;

        if ((fp = fopen(file, "rb")) == NULL)
            return false;

        png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
            NULL, NULL, NULL);

        if (png_ptr == NULL)
        {
            fclose(fp);
            return false;
        }

        info_ptr = png_create_info_struct(png_ptr);
        if (info_ptr == NULL)
        {
            fclose(fp);
            png_destroy_read_struct(&png_ptr, NULL, NULL);
            return false;
        }

        if (setjmp(png_jmpbuf(png_ptr)))
        {
            png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
            fclose(fp);
            return false;
        }

        png_init_io(png_ptr, fp);
        png_set_sig_bytes(png_ptr, sig_read);
        png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

        png_uint_32 width, height;
        int bit_depth;
        png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
            &interlace_type, NULL, NULL);
        outWidth = width;
        outHeight = height;

        unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
        *outData = (unsigned char*)malloc(row_bytes * outHeight);

        png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

        for (int i = 0; i < outHeight; i++)
            memcpy(*outData + (row_bytes * (outHeight - 1 - i)), row_pointers[i], row_bytes);

        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);

        return true;
    }
}
