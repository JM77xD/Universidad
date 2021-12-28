#include "aux.h"
#include <string>
#include "jpg_imagen.hpp"
#include "jpg_jinclude.h"
//#include "jpg_memsrc.hpp"
#include "jpg_readwrite.hpp"

class Textura {
    private:
        GLuint textura_id = 0;
        std :: vector < unsigned char > data ;
        int width , height ;

    public:
        Textura ( std::string archivo );
        void activar ();
        GLuint getID();
};