// Domaci rad - 3D Kompjuterska grafika
// Vladimir Geroski - 8it/2023

#include <GL/glut.h>
#include <math.h>
#include <vector>

// g++ -o d domaci.cpp -lGL -lglut
// ./d

// vektor
typedef std::vector<GLdouble> VektorD;

// crtanje ivica
void nacrtaj_ivice( const std::vector<VektorD>& koordinate, const VektorD& boja, GLfloat debljina )
{
  glColor3f(boja[0], boja[1], boja[2]);
  glLineWidth(debljina);
  int broj_tacaka = koordinate.size();
  glBegin(GL_LINE_LOOP);
    for (int i = 0; i < broj_tacaka; i++)
    {
      glVertex2f(koordinate[i][0], koordinate[i][1]);
    }
  glEnd();
}

// nacrtaj poligon na osnovu koordinata (spakovane u matricu koordinata)
void nacrtaj_poligon( const std::vector<VektorD>& koordinate, const VektorD& boja )
{
  glColor3f(boja[0], boja[1], boja[2]);

  int broj_tacaka_poligona = koordinate.size();
  glBegin(GL_POLYGON);
    for (int i = 0; i < broj_tacaka_poligona; i++)
    {
      glVertex2f(koordinate[i][0], koordinate[i][1]);
    }
  glEnd();
}

void nacrtaj_krug( GLdouble x, GLdouble y, GLdouble r, GLint broj_tacaka, const VektorD& boja, bool pun_krug = true )
{
  double alfa = 2 * M_PI / broj_tacaka;
  glColor3f(boja[0], boja[1], boja[2]);
  GLenum tip = pun_krug == true ? GL_POLYGON : GL_LINE_LOOP;
  glEnable(GL_LINE_SMOOTH);
  glBegin(tip);
    for (int i = 0; i < broj_tacaka; i++)
    {
      double ugao = i * alfa;
      glVertex2f(x + r*cos(ugao), y + r*sin(ugao));
    }
  glEnd();
}

// osmeh kao polovina kruga (negativan ugao jer hocemo donju polovinu kruga)
void osmeh( GLdouble x, GLdouble y, GLdouble r, GLint broj_tacaka )
{
  double alfa = M_PI / broj_tacaka;
  glColor3f(0.0, 0.0, 0.0);
  glEnable(GL_LINE_SMOOTH);
  glBegin(GL_LINE_STRIP);
    for (int i = broj_tacaka*0.2; i <= broj_tacaka*0.8; i++)
    {
      double ugao = -i * alfa;
      glVertex2f(x + r*cos(ugao), y + r*sin(ugao));
    }
  glEnd();
}

// crtanje pantalona sa crnom ivicom
void pantalone() 
{
  std::vector<VektorD> koordinate_pantalona { VektorD{0.5, 0.0}, VektorD{9.5, 0.0}, VektorD{9.5, 1.0}, VektorD{0.5, 1.0} };
  nacrtaj_poligon( koordinate_pantalona, VektorD{0.6, 0.3, 0.3} );
  nacrtaj_ivice( koordinate_pantalona, VektorD{0.0, 0.0, 0.0}, 10.0 );
}

void crte_pantalona()
{
  glColor3f(0.0, 0.0, 0.0);
  glLineWidth(30.0);
  GLdouble razmak = 0.25;
  GLdouble duzina = 1.9375;
  glBegin(GL_LINES);
    GLdouble x = 0.5;
    for (int i = 0; i < 4; i++)
    {
      x = x + razmak;
      glVertex2f(x, 0.7);
      x += duzina;
      glVertex2f(x, 0.7);
    }
  glEnd();
}

// crtanje kosulje sa crnom ivicom
void kosulja()
{
  std::vector<VektorD> koordinate_kosulje { VektorD{0.5, 1.0}, VektorD{9.5, 1.0}, VektorD{9.5, 2.2}, VektorD{0.5, 2.2} };
  nacrtaj_poligon( koordinate_kosulje, VektorD{1.0, 1.0, 1.0} );
  nacrtaj_ivice( koordinate_kosulje, VektorD{0.0, 0.0, 0.0}, 10.0 );
}

// crtanje kragne sa crnom ivicom
void kragna()
{
  std::vector<VektorD> prva_kragna { VektorD{3.8, 1.3}, VektorD{4.5, 2.2}, VektorD{2.5, 2.2} };
  nacrtaj_ivice( prva_kragna, VektorD{0.0, 0.0, 0.0}, 5.0 );

  std::vector<VektorD> druga_kragna { VektorD{5.5, 2.2}, VektorD{6.2, 1.3}, VektorD{7.5, 2.2} };
  nacrtaj_ivice( druga_kragna, VektorD{0.0, 0.0, 0.0}, 5.0 );
}

// crtanje kravate iz dva dela, cvor i ostatak sa iviciom
void kravata()
{
  std::vector<VektorD> cvor { VektorD{4.4, 2.2}, VektorD{4.8, 1.6}, VektorD{5.2, 1.6}, VektorD{5.6, 2.2} };
  std::vector<VektorD> kravata { VektorD{4.8, 1.6}, VektorD{4.2, 0.7}, VektorD{5.0, 0.1}, VektorD{5.8, 0.7}, VektorD{5.2, 1.6} };
  VektorD crvena_boja{0.8, 0.0, 0.0};
  VektorD crna_boja{0.0, 0.0, 0.0};

  nacrtaj_poligon( cvor, crvena_boja );
  nacrtaj_ivice( cvor, crna_boja, 4.0 );

  nacrtaj_poligon( kravata, crvena_boja );
  nacrtaj_ivice( kravata, crna_boja, 4.0 );
}

// telo
void telo()
{
  std::vector<VektorD> koordinate_tela { VektorD{0.4, 2.0}, VektorD{9.6, 2.0}, VektorD{9.9, 9.9}, VektorD{0.1, 9.9} };
  nacrtaj_poligon( koordinate_tela, VektorD{1.0, 1.0, 0.0} );
  nacrtaj_ivice( koordinate_tela, VektorD{0.7, 0.7, 0.1}, 10.0 );
}

void oci()
{
  // levo oko
  nacrtaj_krug( 2.5, 7.0, 2.0, 100, VektorD{1.0, 1.0, 1.0} );
  nacrtaj_krug( 2.5, 7.0, 2.0, 100, VektorD{0.0, 0.0, 0.0}, false );

  nacrtaj_krug( 3.0, 6.8, 1.0, 100, VektorD{0.0, 0.0, 1.0} );
  nacrtaj_krug( 3.0, 6.8, 1.0, 100, VektorD{0.0, 0.0, 0.0}, false );

  nacrtaj_krug( 3.0, 6.8, 0.5, 100, VektorD{0.0, 0.0, 0.0} );

  // leve obrve
  std::vector<VektorD> leva_obrva{VektorD{2.3, 9.0}, VektorD{2.6, 9.0}, VektorD{2.6, 9.5}, VektorD{2.3, 9.5}};
  nacrtaj_poligon( leva_obrva, VektorD{0.0, 0.0, 0.0} );

  std::vector<VektorD> l_leva_obrva{VektorD{1.8, 8.85}, VektorD{2.1, 8.95}, VektorD{1.9, 9.4}, VektorD{1.6, 9.25}};
  nacrtaj_poligon( l_leva_obrva, VektorD{0.0, 0.0, 0.0} );

  // translacija l_leve obrve u odnosnu na simetriju oka
  std::vector<VektorD> d_leva_obrva{VektorD{2.1 + 0.8, 8.95}, VektorD{1.8 + 1.4, 8.85}, VektorD{1.6 + 1.8, 9.25}, VektorD{1.9 + 1.2, 9.4}};
  nacrtaj_poligon( d_leva_obrva, VektorD{0.0, 0.0, 0.0} );

  // desno oko
  nacrtaj_krug( 7.5, 7.0, 2.0, 100, VektorD{1.0, 1.0, 1.0} );
  nacrtaj_krug( 7.5, 7.0, 2.0, 100, VektorD{0.0, 0.0, 0.0}, false );

  nacrtaj_krug( 7.0, 6.8, 1.0, 100, VektorD{0.0, 0.0, 1.0} );
  nacrtaj_krug( 7.0, 6.8, 1.0, 100, VektorD{0.0, 0.0, 0.0}, false );

  nacrtaj_krug( 7.0, 6.8, 0.5, 100, VektorD{0.0, 0.0, 0.0});

  // desne obrve - transliramo leve obrve za razliku po x u centrima dva kruga (oka)
  std::vector<VektorD> desna_obrva{VektorD{2.3 + 5, 9.0}, VektorD{2.6 + 5, 9.0}, VektorD{2.6 + 5, 9.5}, VektorD{2.3 + 5, 9.5}};
  nacrtaj_poligon( desna_obrva, VektorD{0.0, 0.0, 0.0} );

  std::vector<VektorD> l_desna_obrva{VektorD{1.8 + 5, 8.85}, VektorD{2.1 + 5, 8.95}, VektorD{1.9 + 5, 9.4}, VektorD{1.6 + 5, 9.25}};
  nacrtaj_poligon( l_desna_obrva, VektorD{0.0, 0.0, 0.0} );

  std::vector<VektorD> d_desna_obrva{VektorD{2.1 + 0.8 + 5, 8.95}, VektorD{1.8 + 1.4 + 5, 8.85}, VektorD{1.6 + 1.8 + 5, 9.25}, VektorD{1.9 + 1.2 + 5, 9.4}};
  nacrtaj_poligon( d_desna_obrva, VektorD{0.0, 0.0, 0.0} );
}

void nos()
{
  nacrtaj_krug( 5.0, 5.0, 0.5, 100, VektorD{0.7, 0.7, 0.5} , false);
}

void zubi()
{
  std::vector<VektorD> koordinate_zuba_levi { VektorD{4.3, 3.1}, VektorD{4.3, 2.5}, VektorD{4.9, 2.5}, VektorD{4.9, 3.0} };
  nacrtaj_poligon( koordinate_zuba_levi, VektorD{1.0, 1.0, 1.0} );
  nacrtaj_ivice( koordinate_zuba_levi, VektorD{0.0, 0.0, 0.0}, 10.0 );

  std::vector<VektorD> koordinate_zuba_desni { VektorD{5.1, 3.0}, VektorD{5.1, 2.5}, VektorD{5.7, 2.5}, VektorD{5.7, 3.1} };
  nacrtaj_poligon( koordinate_zuba_desni, VektorD{1.0, 1.0, 1.0} );
  nacrtaj_ivice( koordinate_zuba_desni, VektorD{0.0, 0.0, 0.0}, 10.0 );
}

void display(void)
{
    /* clear all pixels */
    glClear(GL_COLOR_BUFFER_BIT);

    // pantalone
    pantalone();

    // kosulja
    kosulja();

    // crte na pantalonama
    crte_pantalona();

    // kragna
    kragna();

    // kravata
    kravata();

    // telo
    telo();
    
    // oci
    oci();

    // nos
    nos();

    // osmeh
    osmeh( 5.0, 5.5, 2.5, 100 );

    // zubi
    zubi();

    glFlush();
}

void init(void)
{
    /* select clearing (background) color */
    glClearColor(0.5, 0.5, 0.5, 0.0);
    /* initialize viewing values */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(670, 330);
    glutCreateWindow("Domaci rad - Sundjer Bob");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
	
    return 0;
}