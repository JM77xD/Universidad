/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;


public class TestP1 {
    
    public static void main(String [] args) {
        for (int i = 0; i<100; i++) {
            System.out.println(Dado.getInstance().quienEmpieza(4));
        }
        
        Dado.getInstance().setDebug(true);
        
        for (int i = 0; i<10; i++) {
            System.out.println("Tirada "+i+" "+Dado.getInstance().tirar());
        }
        
        Dado.getInstance().setDebug(false);
        
        for (int i = 0; i<10; i++) {
            System.out.println("Tirada "+i+" "+Dado.getInstance().tirar());
        }
        
        System.out.println(Dado.getInstance().getUltimoResultado());
        
        if (Dado.getInstance().salgoDeLaCarcel()) {
            System.out.println("He salido de la carcel");
        } else {
            System.out.println("No he salido de la carcel");
        }
        
        System.out.println(TipoCasilla.CALLE+" "+TipoSorpresa.IRCASILLA+" "+EstadosJuego.DESPUES_AVANZAR+" "+OperacionesJuego.AVANZAR);
        
        MazoSorpresas mazo = new MazoSorpresas(true);
        Sorpresa s1 = new Sorpresa();
        Sorpresa s2 = new Sorpresa();
        mazo.alMazo(s1);
        mazo.alMazo(s2);
        mazo.siguiente();
        mazo.inhabilitarCartaEspecial(s2);
        mazo.habilitarCartaEspecial(s2);
        
        while(Diario.getInstance().eventosPendientes()) {
            System.out.println(Diario.getInstance().leerEvento());
        }
        
        Tablero t = new Tablero(5);
        Casilla c1 = new Casilla("Hola0", TipoCasilla.CALLE);
        Casilla c2 = new Casilla("Hola1", TipoCasilla.CALLE);
        Casilla c3 = new Casilla("Hola2", TipoCasilla.CALLE);
        Casilla c4 = new Casilla("Hola3", TipoCasilla.CALLE);
        Casilla c5 = new Casilla("Hola4", TipoCasilla.CALLE);
        Casilla c6 = new Casilla("Hola5", TipoCasilla.CALLE);
        
        t.añadeCasilla(c1);
        t.añadeCasilla(c2);
        t.añadeCasilla(c3);
        t.añadeCasilla(c4);
        t.añadeCasilla(c5);
        t.añadeCasilla(c6);
        t.añadeJuez();
        int tirada = Dado.getInstance().tirar();
        System.out.println(tirada);
        System.out.println(t.nuevaPosicion(7, tirada));
    }
    
}
