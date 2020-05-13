#ifndef pareja_h
#define pareja_h

class Pareja {
    private:
        int dato;

        int nVeces;
    public:
        Pareja();

        Pareja(int dato, int veces=1);

        inline int devolverNVeces() const {
            return nVeces;
        }

        inline int devolverDato() const {
            return dato;
        }

        inline void incrementar() {
            nVeces++;
        }

        Pareja operator=(const Pareja &igualar);

        void crear(int dato);

        bool operator==(const Pareja &otra);
};

#endif